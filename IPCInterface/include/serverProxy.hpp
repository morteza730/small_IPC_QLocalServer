#pragma once

#include "serverInterface.hpp"

namespace ipc
{
class ServerInternal;

class ServerProxy: public ServerInterface
{
    Q_OBJECT

public:
    explicit ServerProxy(const QString &UID);
    ~ServerProxy();
    bool sendMessage(const QString &clientUID,const IPCMessage &message) final;
    IPCMessage readMessage(const QString &clientUID) final;
    bool startServer() final;
    void stopServer() final;
    bool isListening() const final;

private:
    std::unique_ptr<ServerInternal> m_serverInternal;

};

}
