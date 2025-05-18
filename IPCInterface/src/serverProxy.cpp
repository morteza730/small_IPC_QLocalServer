#include "serverProxy.hpp"

ipc::ServerProxy::ServerProxy(const QString &UID)
    : ServerInterface{UID},
    m_serverInternal{new ServerInternal{UID}}
{
    connect(m_serverInternal.get(),&ServerInternal::clientConnected,this,&ServerProxy::clientConnected);
    connect(m_serverInternal.get(),&ServerInternal::clientDisconnected,this,&ServerProxy::clientDisconnected);
    connect(m_serverInternal.get(),&ServerInternal::readyRead,this,&ServerProxy::readyRead);
}

bool ipc::ServerProxy::sendMessage(const QString &clientUID, const IPCMessage &message) {
    return m_serverInternal->sendMessage(clientUID,message);
}

std::optional<std::tuple<QString, ipc::IPCMessage>> ipc::ServerProxy::readMessage() {
    return m_serverInternal->readMessage();
}

bool ipc::ServerProxy::startServer() {
    return m_serverInternal->startServer();
}

void ipc::ServerProxy::stopServer() {m_serverInternal->stopServer();}

bool ipc::ServerProxy::isListening() const {
    return m_serverInternal->isListening();
}

ipc::ServerInterface *ipc::ServerInterface::create(const QString &UID) {
    return new ServerProxy(UID);
}
