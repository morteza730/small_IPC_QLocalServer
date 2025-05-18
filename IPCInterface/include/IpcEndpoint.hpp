#pragma once

#include <QByteArray>
#include <QObject>
#include "ipcMessage.hpp"
#include "global.hpp"

namespace ipc
{
class IPC_EXPORT IpcEndpoint : public QObject
{
    Q_OBJECT

public:
    QString getUID() const {return m_UID;}

protected:
    explicit IpcEndpoint(const QString &UID)
        : QObject(nullptr),
        m_UID{UID}
    {}

    QString m_UID;

signals:
    void errorOccurred(const QString &error);
};
}
