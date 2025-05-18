#pragma once

#include "clientInterface.hpp"
#include "clientInternal.hpp"
#include <optional>

namespace ipc
{
class ClientProxy: public ClientInterface
{
    Q_OBJECT

public:
    explicit ClientProxy(const QString &UID);
    void sendMessage(const IPCMessage &message) override final;
    std::optional<IPCMessage> readMessage() override final;
    void connectToServer(const QString &serverUID) override final;
    bool disconnect() override final;
    bool isConnected() const override final;

private:
    std::unique_ptr<ClientInternal> m_clientInternal;
};

}
