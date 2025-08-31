#pragma once

#include <memory>
#include "IpcEndpoint.hpp"
#include "ipcMessage.hpp"

namespace ipc
{
class IPC_EXPORT ServerInterface: public IpcEndpoint
{
    Q_OBJECT

public:
    static std::unique_ptr<ServerInterface> create(const QString &UID);

    virtual bool sendMessage(const QString &clientUID,const IPCMessage &message)  = 0;
    virtual IPCMessage readMessage(const QString &clientUID)  = 0;

    virtual bool startServer()  = 0;
    virtual void stopServer() = 0;
    virtual bool isListening() const = 0;

protected:
    explicit ServerInterface(const QString &UID)
        : IpcEndpoint{UID}
    {}

signals:
    void clientConnected();
    void clientDisconnected();
    void readyRead();
};
}
