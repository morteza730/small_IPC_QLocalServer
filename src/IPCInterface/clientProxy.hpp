#pragma once

#include "clientInterface.hpp"

namespace ipc
{
class ClientInternal;

class ClientProxy: public ClientInterface
{
    Q_OBJECT

public:
    explicit ClientProxy(const QString &UID);
    virtual void sendMessage(const IPCMessage &message) override final;
    virtual IPCMessage readMessage() override final;
    virtual int getMessageCount() const override final;
    virtual void connectToServer(const QString &serverUID) override final;
    virtual bool disconnect() override final;
    virtual bool isConnected() const override final;

private:
    std::unique_ptr<ClientInternal> m_clientInternal;
};

}
