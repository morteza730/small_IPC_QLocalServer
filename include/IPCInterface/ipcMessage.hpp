#pragma once

#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#include "ipcExport.hpp"

enum class CommandMode
{
    Info,
    VasType,
    Trx, //Transaction
    Verify,
    Print,
    TimeOut,
    Inquiry,
    Online,
    CInquiry, // R.A. in mored baraye estelam va estefade az "TransactionInquiry" ast.
    C2C_Trx,
    VasLanguage,
    TMSError,
    TMSMessage,
    AFC,
    TMSVersion,
    BCR,
    Reg,
    Dereg,
};

namespace ipc
{
class IPC_EXPORT IPCMessage
{
public:
    IPCMessage(CommandMode mode = CommandMode::Info, QString data = "", QString reserve = "");
    IPCMessage(QJsonObject jsonObject);

    QByteArray toJson() const;

    void setMode(CommandMode mode);
    void setData(QString data);
    void setReserve(QString reserve);

    CommandMode mode() const {return m_mode;}
    QString data() const {return m_data;}
    QString reserve() const {return m_reserve;}

private:
    CommandMode m_mode;
    QString m_data;
    QString m_reserve; // jahate etminan, in gozine baraye har 2 taraf ghabele estefade ast

};
}
