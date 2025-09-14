#include "clientInternal.hpp"
#include "utility.hpp"
#include "config.h"

namespace ipc
{

ClientInternal::ClientInternal(const QString &UID)
    : m_socket{new QLocalSocket(this)},
    m_connectionTimer{new QTimer(this)},
    m_isConnected{false},
    m_messages{std::make_unique<CircularQueue<IPCMessage>>()},
    m_UID{UID}
{
    connect(m_socket, &QLocalSocket::connected, this, &ClientInternal::clientConnected);
    connect(m_socket, &QLocalSocket::disconnected, this, &ClientInternal::clientDisconnected);
    connect(m_socket, &QLocalSocket::readyRead, this, &ClientInternal::readSocket);
    connect(m_socket, &QLocalSocket::errorOccurred, this, &ClientInternal::error);

    if (!isVerificationRequired())
        m_isConnected = true;
    
}

ClientInternal::~ClientInternal()
{
    m_socket->disconnect(this);
    m_socket->close();
}

void ClientInternal::error(const QLocalSocket::LocalSocketError &socketError)
{
    emit errorOccurred(m_socket->errorString());
}

void ClientInternal::readSocket()
{
    qint64 size = m_socket->bytesAvailable();
    char *newMessage;
    newMessage = new char[size];
    memset(newMessage, 0, size);
    m_socket->read(newMessage, size);

    QList<QString> ResponseList = splitJSONResponse(newMessage);
    foreach(const QString &response, ResponseList)
    {
        std::unique_ptr<QJsonObject> jsonObject = std::move(makeResponseJson(response));
        IPCMessage message{*jsonObject};

        if (message.mode() == CommandMode::Reg && message.data() == getUID())
            m_isConnected = true;
        else if (m_isConnected)
            m_messages->enqueue(message);
    }
    emit readyRead();
}

void ClientInternal::connectToServer(const QString &serverUID)
{
    if (!m_socket)
        return;

    m_socket->abort();
    m_socket->connectToServer(serverUID);
}

bool ClientInternal::disconnect()
{
    if (!m_socket)
        return false;
    
    m_connectionTimer->stop();
    
    if (!m_isConnected)
        return true;
        
    IPCMessage regMSG(CommandMode::Dereg,getUID());
    sendMessage(regMSG);

    m_socket->disconnectFromServer();
    m_isConnected = !(m_socket->waitForDisconnected(DISCONNECTION_WAIT_TIME));
    return m_isConnected;
}

void ClientInternal::clientConnected()
{
    IPCMessage regMSG(CommandMode::Reg,getUID());
    sendMessage(regMSG);
    emit connected();
}

void ClientInternal::clientDisconnected()
{
    emit disconnected();
}

void ClientInternal::sendMessage(const IPCMessage &message)
{
    QByteArray block = message.toJson();

    if (!m_socket)
        return;

    if (!m_isConnected)
        return;

    m_socket->write(block);
    m_socket->flush();
}

IPCMessage ClientInternal::readMessage()
{
    IPCMessage message = m_messages->dequeue();
    return message;
}

}

