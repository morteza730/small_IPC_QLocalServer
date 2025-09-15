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
    virtual bool sendMessage(const QString &clientUID,const IPCMessage &message) override final;
    IPCMessage readMessage(const QString &clientUID) override final;
    virtual int getMessageCount(const QString &clientUID) const override final;
    virtual bool startServer() override final;
    virtual void stopServer() override final;
    virtual bool isListening() const override final;

private:
    std::unique_ptr<ServerInternal> m_serverInternal;

};

}
