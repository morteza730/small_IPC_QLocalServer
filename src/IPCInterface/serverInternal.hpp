#pragma once

#include <QLocalServer>
#include <QLocalSocket>
#include "circularQueue.hpp"
#include "ipcMessage.hpp"

namespace ipc
{
class ServerInternal: public QObject
{
    Q_OBJECT

public:
    explicit ServerInternal(const QString &UID);
    ~ServerInternal();

    bool startServer();
    void stopServer();
    bool sendMessage(const QString &clientUID,const IPCMessage &message);
    IPCMessage readMessage(const QString &clientUID);
    bool isListening() const {return m_isListening;}

    QString getUID() const {return m_UID;}

private:
    bool m_isListening;
    QLocalServer *m_server;
    QHash<QString,std::shared_ptr<CircularQueue<IPCMessage>>> m_messageHash;
    QString m_serverName;
    QHash<QString,QLocalSocket*> m_clientHash;

    QString m_UID;

    static constexpr uint16_t CONNECTION_WAIT_TIME = 3000;
    static constexpr uint16_t DISCONNECTION_WAIT_TIME = 3000;

private slots:
    void handleNewConnection();
    void readServer();

signals:
    void clientConnected();
    void clientDisconnected();
    void readyRead();
    void errorOccurred(const QString &error);

};
}
