#pragma once

#include <memory>

#include "IpcEndpoint.hpp"
#include "global.hpp"

namespace ipc
{
class IPC_EXPORT ClientInterface: public IpcEndpoint
{
    Q_OBJECT

public:
    static ClientInterface *create(const QString &UID);

    virtual void sendMessage(const IPCMessage &message) = 0;
    virtual std::optional<IPCMessage> readMessage() = 0;

    virtual void connectToServer(const QString &serverUID) = 0;
    virtual bool disconnect() = 0;
    virtual bool isConnected() const = 0;

protected:
    explicit ClientInterface(const QString &UID);
    ~ClientInterface();

signals:
    void connected();
    void disconnected();
    void readyRead();
};
}
