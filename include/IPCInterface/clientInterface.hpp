#pragma once

#include <memory>

#include "IpcEndpoint.hpp"
#include "ipcMessage.hpp"

namespace ipc
{
class IPC_EXPORT ClientInterface: public IpcEndpoint
{
    Q_OBJECT

public:
    static std::unique_ptr<ipc::ClientInterface> create(const QString &UID); // flyweight design pattern

    virtual void sendMessage(const IPCMessage &message) = 0;
    virtual IPCMessage readMessage() = 0;
    virtual int getMessageCount() const = 0;

    virtual void connectToServer(const QString &serverUID) = 0;
    virtual bool disconnect() = 0;
    virtual bool isConnected() const = 0;

protected:
    explicit ClientInterface(const QString &UID)
        : IpcEndpoint{UID}
    {}

signals:
    void connected();
    void disconnected();
    void readyRead();
};
}
