#pragma once

#include <QObject>
#include "circularQueue.hpp"
#include "IpcMessage.hpp"
#include <QLocalSocket>
#include <QTimer>

namespace ipc
{
class ClientInternal: public QObject
{
    Q_OBJECT

public:
    explicit ClientInternal(const QString &UID);
    ~ClientInternal();

    void connectToServer(const QString &serverUID);
    bool disconnect();
    bool isConnected() const {return m_isConnected;}
    void sendMessage(const IPCMessage &message);
    IPCMessage readMessage();

    QString getUID() const {return m_UID;}

private:
    bool m_isConnected;
    QLocalSocket *m_socket;
    QTimer *m_connectionTimer;
    std::unique_ptr<CircularQueue<IPCMessage>> m_messages;

    QString m_UID;

    static constexpr uint16_t CONNECTION_WAIT_TIME = 3000;
    static constexpr uint16_t DISCONNECTION_WAIT_TIME = 3000;
    static constexpr uint16_t ACK_WAIT_TIME = 1000;

private slots:
    void error(const QLocalSocket::LocalSocketError &socketError);
    void readSocket();
    void clientConnected();
    void clientDisconnected();

signals:
    void connected();
    void disconnected();
    void readyRead();
    void errorOccurred(const QString &error);
};
}
