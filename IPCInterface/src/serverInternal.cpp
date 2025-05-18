#include "serverInternal.hpp"
#include "utility.hpp"

namespace ipc
{

ServerInternal::ServerInternal(const QString &UID)
    : m_isListening{false},
    m_server{new QLocalServer(this)},
    m_messages{new CircularQueue<std::tuple<QString,IPCMessage>>{}},
    m_UID{UID}
{
    connect(m_server, &QLocalServer::newConnection, this, &ServerInternal::handleNewConnection);
}

ServerInternal::~ServerInternal()
{
    m_server->disconnect(this);
    m_server->close();
}

void ServerInternal::handleNewConnection()
{
    if (!m_server->hasPendingConnections())
    {
        WARNING("No pending connection");
        return;
    }

    QLocalSocket *socket = m_server->nextPendingConnection();

    if (!socket) {
        WARNING("Invalid client connection");
        return;
    }

    connect(socket, &QLocalSocket::readyRead, this, &ServerInternal::readServer);
    connect(socket, &QLocalSocket::disconnected, socket, &QLocalSocket::deleteLater);
    connect(socket, &QLocalSocket::errorOccurred, this, [this,socket](){
        emit errorOccurred(socket->errorString());
    });

    emit clientConnected();
}

void ServerInternal::readServer()
{
    QLocalSocket *client = qobject_cast<QLocalSocket*>(sender());

    if (!client)
        return;

    qint64 size = client->bytesAvailable();
    char *newMessage;
    newMessage = new char[size];
    memset(newMessage, 0, size);
    client->read(newMessage, size);

    QList<QString> ResponseList = splitJSONResponse(newMessage);
    foreach(const QString &response, ResponseList)
    {
        std::unique_ptr<QJsonObject> jsonObject = std::move(makeResponseJson(response));
        IPCMessage message{*jsonObject};
        switch (message.mode()) {
        case CommandMode::Reg:
        {
            if (m_clientHash.contains(message.data()))
                continue;

            m_clientHash.insert(message.data(),client);
        } break;
        default:
        {
            QString clientUID = m_clientHash.key(client);
            std::tuple<QString,IPCMessage> clientMessage(clientUID,message);
            m_messages->enqueue(clientMessage);
            emit readyRead();
        }break;
        }
    }
}

bool ServerInternal::startServer()
{
    if (m_server->isListening()) {
        return true;
    }

    QLocalServer::removeServer(m_UID);
    if (!m_server->listen(m_UID))
    {
        emit errorOccurred(m_server->errorString());
        return false;
    }
    return true;
}

void ServerInternal::stopServer()
{
    if (!m_server)
        return;

    m_server->close();
}

bool ServerInternal::sendMessage(const QString &clientUID, const IPCMessage &message)
{
    QByteArray block = message.toJson();
    QLocalSocket* client = m_clientHash[clientUID];

    if (!client || !client->isOpen())
        return -1;

    client->write(block);
    return client->waitForBytesWritten();
}

std::optional<std::tuple<QString, IPCMessage>> ServerInternal::readMessage()
{
    if (m_messages->isEmpty())
        return std::nullopt;

    return m_messages->dequeue();
}

}
