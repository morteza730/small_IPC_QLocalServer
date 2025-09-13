#include "ipcMessage.hpp"

ipc::IPCMessage::IPCMessage(CommandMode mode, QString data, QString reserve)
    : m_mode{mode},
    m_data{data},
    m_reserve{reserve}
{}

ipc::IPCMessage::IPCMessage(QJsonObject jsonObject)
    : m_mode{CommandMode::Info},
    m_data{},
    m_reserve{}
{
    if (jsonObject.contains("mode"))
        m_mode = (CommandMode)jsonObject["mode"].toInt();

    if (jsonObject.contains("data"))
        m_data = jsonObject["data"].toString();

    if (jsonObject.contains("reserve"))
        m_reserve = jsonObject["reserve"].toString();

}

QByteArray ipc::IPCMessage::toJson() const
{
    QJsonObject qJsonObject;
    qJsonObject["mode"] = static_cast<int>(m_mode);
    qJsonObject["data"] = m_data;
    qJsonObject["reserve"] = m_reserve;
    return QJsonDocument(qJsonObject).toJson();
}

void ipc::IPCMessage::setMode(CommandMode mode) {
    m_mode = mode;
}

void ipc::IPCMessage::setData(QString data) {
    m_data = data;
}

void ipc::IPCMessage::setReserve(QString reserve) {
    m_reserve = reserve;
}
