#include "clientProxy.hpp"
#include "clientInternal.hpp"

ipc::ClientProxy::ClientProxy(const QString &UID)
    : ClientInterface(UID),
    m_clientInternal{std::make_unique<ClientInternal>(UID)}
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

ipc::IPCMessage ipc::ClientProxy::readMessage() {
    return m_clientInternal->readMessage();
}

int ipc::ClientProxy::getMessageCount() const
{
    return m_clientInternal->getMessageCount();
}

void ipc::ClientProxy::connectToServer(const QString &serverUID) {m_clientInternal->connectToServer(serverUID);}

bool ipc::ClientProxy::disconnect() {
    return m_clientInternal->disconnect();
}

bool ipc::ClientProxy::isConnected() const {
    return m_clientInternal->isConnected();
}


std::unique_ptr<ipc::ClientInterface> ipc::ClientInterface::create(const QString &UID) {
    return std::make_unique<ClientProxy>(UID);
}

