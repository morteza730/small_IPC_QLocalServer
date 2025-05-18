#pragma once

#include <QObject>
#include "circularQueue.hpp"
#include "IpcMessage.hpp"
#include <QLocalSocket>
#include <optional>

namespace ipc
{
class ClientInternal: public QObject
{
    Q_OBJECT

public:
    explicit ClientInternal(const QString &UID);
    ~ClientInternal();

    virtual void connectToServer(const QString &serverUID);
    virtual bool disconnect();
    virtual bool isConnected() const {return m_isConnected;}
    virtual void sendMessage(const IPCMessage &message);
    virtual std::optional<IPCMessage> readMessage();

    QString getUID() const {return m_UID;}

private:
    bool m_isConnected;
    QLocalSocket *m_socket;
    std::unique_ptr<CircularQueue<IPCMessage>> m_messages;

    QString m_UID;

    static constexpr uint16_t CONNECTION_WAIT_TIME = 3000;
    static constexpr uint16_t DISCONNECTION_WAIT_TIME = 3000;

private slots:
    void error(const QLocalSocket::LocalSocketError &socketError);
    void readSocket();

signals:
    void connected();
    void disconnected();
    void readyRead();
    void errorOccurred(const QString &error);
};
}
