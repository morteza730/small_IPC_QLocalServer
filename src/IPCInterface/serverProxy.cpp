#include "serverProxy.hpp"
#include "serverInternal.hpp"

ipc::ServerProxy::ServerProxy(const QString &UID)
    : ServerInterface{UID},
    m_serverInternal{std::make_unique<ServerInternal>(UID)}
{
    connect(m_serverInternal.get(),&ServerInternal::clientConnected,this,&ServerProxy::clientConnected);
    connect(m_serverInternal.get(),&ServerInternal::clientDisconnected,this,&ServerProxy::clientDisconnected);
    connect(m_serverInternal.get(),&ServerInternal::readyRead,this,&ServerProxy::readyRead);
}

ipc::ServerProxy::~ServerProxy() = default;

bool ipc::ServerProxy::sendMessage(const QString &clientUID, const IPCMessage &message) {
    return m_serverInternal->sendMessage(clientUID,message);
}

ipc::IPCMessage ipc::ServerProxy::readMessage(const QString &clientUID) {
    return m_serverInternal->readMessage(clientUID);
}

int ipc::ServerProxy::getMessageCount(const QString &clientUID) const
{
    return m_serverInternal->getMessageCount(clientUID);
}

bool ipc::ServerProxy::startServer() {
    return m_serverInternal->startServer();
}

void ipc::ServerProxy::stopServer() {m_serverInternal->stopServer();}

bool ipc::ServerProxy::isListening() const {
    return m_serverInternal->isListening();
}

std::unique_ptr<ipc::ServerInterface> ipc::ServerInterface::create(const QString &UID) {
    return std::make_unique<ServerProxy>(UID);
}
