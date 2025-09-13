#pragma once

#include <QList>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatchIterator>
#include <QJsonDocument>
#include <QJsonObject>
#include <memory>

#define LOG(...) qInfo(__VA_ARGS__)
#define WARNING(...) qWarning(__VA_ARGS__)

inline QList<QString> splitJSONResponse(QString str)
{
    QList<QString> substrings;

    // Regular expression to match a JSON object
    static QRegularExpression re(R"(\{(?:[^{}]|(?R))*\})");
    QRegularExpressionMatchIterator i = re.globalMatch(str);

    // Find and store JSON objects
    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        substrings.append(match.captured());
    }
    return substrings;
}

inline std::unique_ptr<QJsonObject> makeResponseJson(const QString &response)
{
    if(response.isEmpty() || response.isNull())
        return std::unique_ptr<QJsonObject>{};

    QJsonDocument jsonDocument = QJsonDocument::fromJson(response.toUtf8());
    if(!jsonDocument.isObject())
        return std::unique_ptr<QJsonObject>{};

    return std::unique_ptr<QJsonObject>{new QJsonObject{jsonDocument.object()}};
}
