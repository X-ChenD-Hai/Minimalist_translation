#pragma once
#include <QObject>
#include <QUrl>
#include <QMap>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>

typedef struct mUrl
{
    QString baseUrl;
    QMap<QString, QString> parameterMap;
} mUrl;

class getText : public QObject
{
    Q_OBJECT
public:
    QString &getTranslateText() const;
    void setPattem();
    void startTranslate(const QString &text);

private:
    QNetworkAccessManager *manger;
    QNetworkReply *rep;
    QNetworkRequest req;
    QJsonDocument *jsonData;
    QString *result = new QString("");
    void replyFinshed();

private:
    mUrl m_url;
    QString to = "zh";
    QString from = "auto";
    QUrl createUrl(const QString &text);
};
