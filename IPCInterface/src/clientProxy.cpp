#include "clientProxy.hpp"


ipc::ClientProxy::ClientProxy(const QString &UID)
    : ClientInterface(UID),
    m_clientInternal{new ClientInternal{UID}}
{
    connect(m_clientInternal.get(),&ClientInternal::connected,this,&ClientProxy::connected);
    connect(m_clientInternal.get(),&ClientInternal::disconnected,this,&ClientProxy::disconnected);
    connect(m_clientInternal.get(),&ClientInternal::readyRead,this,&ClientProxy::readyRead);
    connect(this,&ClientProxy::errorOccurred,[](){
        qDebug() << "error wittnessed from proxy";
    });
}

void ipc::ClientProxy::sendMessage(const IPCMessage &message) {
    m_clientInternal->sendMessage(message);
}

std::optional<ipc::IPCMessage> ipc::ClientProxy::readMessage() {
    return m_clientInternal->readMessage();
}

void ipc::ClientProxy::connectToServer(const QString &serverUID) {m_clientInternal->connectToServer(serverUID);}

bool ipc::ClientProxy::disconnect() {
    return m_clientInternal->disconnect();
}

bool ipc::ClientProxy::isConnected() const {
    return m_clientInternal->isConnected();
}


ipc::ClientInterface *ipc::ClientInterface::create(const QString &UID) {
    return new ClientProxy(UID);
}

