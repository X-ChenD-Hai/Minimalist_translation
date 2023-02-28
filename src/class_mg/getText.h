#pragma once
#include <QObject>
#include <QUrl>
#include <QMap>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QJsonDocument>

typedef enum translation_engine
{
    TR_YOUDAO = 1,
    TR_BAIDU,
} translation_engine;

Q_DECLARE_METATYPE(translation_engine);

typedef struct mUrl
{
    QString baseUrl;
    QMap<QString, QString> parameterMap;
} mUrl;

class getText : public QObject
{
    Q_OBJECT
public:
    QString *getTranslateText() const;
    void setPattem();
    void startTranslate(const QString &text);
    void setEngine(translation_engine);
    getText();
    ~getText();

private:
    QNetworkAccessManager *manger = NULL;
    QNetworkReply *rep = NULL;
    QNetworkRequest req;
    QJsonDocument *jsonData = NULL;
    QString *result = NULL;
    void replyFinshed();

private:
    translation_engine tanslate_engine;
    mUrl m_url;
    QString to = "zh";
    QString from = "auto";
    QUrl createUrl(const QString &text);
    QUrl createBaiduUrl(const QString &text);
    QUrl createYoudaoUrl(const QString &text);
    void analysisBaiduJson();
    void analysisYoudaoJson();
};
