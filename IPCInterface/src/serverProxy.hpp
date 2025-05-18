#pragma once

#include "serverInterface.hpp"
#include "serverInternal.hpp"
#include <optional>

namespace ipc
{
class ServerProxy: public ServerInterface
{
    Q_OBJECT

public:
    explicit ServerProxy(const QString &UID);
    bool sendMessage(const QString &clientUID,const IPCMessage &message) override final;
    std::optional<std::tuple<QString, IPCMessage>> readMessage() override final;
    bool startServer() override final;
    void stopServer() override final;
    bool isListening() const override final;

private:
    std::unique_ptr<ServerInternal> m_serverInternal;

};

}
