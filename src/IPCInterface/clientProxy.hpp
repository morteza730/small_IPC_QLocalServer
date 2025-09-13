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
    virtual void sendMessage(const IPCMessage &message) final;
    virtual IPCMessage readMessage() final;
    virtual void connectToServer(const QString &serverUID) final;
    virtual bool disconnect() final;
    virtual bool isConnected() const final;

private:
    std::unique_ptr<ClientInternal> m_clientInternal;
};

}
