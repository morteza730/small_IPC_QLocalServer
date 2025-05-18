#pragma once

#include <memory>

#include "IpcEndpoint.hpp"
#include "global.hpp"

namespace ipc
{
class IPC_EXPORT ServerInterface: public IpcEndpoint
{
    Q_OBJECT

public:
    static ServerInterface *create(const QString &UID);

    virtual bool sendMessage(const QString &clientUID,const IPCMessage &message)  = 0;
    virtual std::optional<std::tuple<QString, IPCMessage>> readMessage()  = 0;

    virtual bool startServer()  = 0;
    virtual void stopServer() = 0;
    virtual bool isListening() const = 0;


protected:
    explicit ServerInterface(const QString &UID);

signals:
    void clientConnected();
    void clientDisconnected();
    void readyRead();
};
}
