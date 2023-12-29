#include "Youdao.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QUrlQuery>
#include <QCryptographicHash>
#include <QDateTime>
QString TranslateEngines::Youdao::__url = "https://openapi.youdao.com/api";

QNetworkRequest *TranslateEngines::Youdao::creatRequests(const QString &_text)
{
    auto request = new QNetworkRequest();
    QCryptographicHash sha256(QCryptographicHash::Sha256);
    QString url = __url + '?';
    QUrlQuery query;
    QString input;
    qsizetype len = _text.length();
    if (len > 20)
        input = _text.mid(0, 10) + QString::number(len) + _text.mid(len - 10, 10);
    else
        input = _text;
    QString salt = QUuid::createUuid().toString();
    QString curtime = QString::number(QDateTime::currentSecsSinceEpoch());
    QString sign = __app_id + input + salt + curtime + __app_key;
    sha256.addData(sign.toUtf8());

    url += "q=" + _text.toUtf8().toPercentEncoding();
    url += "&from=" + __from + "&to=" + __to + "&appKey=" + __app_id + "&salt=" + salt + "&signType=v3";
    url += "&sign=" + sha256.result().toHex() + "&curtime=" + curtime;
    request->setUrl(url);
    return request;
}


bool TranslateEngines::Youdao::parseResult(const QByteArray &_data, QString &_result, int &_errorcode)
{
    QJsonObject json;
    _result = "";
    json = QJsonDocument::fromJson(_data).object();
    if (json["errorCode"].toString() == "0")
    {
        for (auto i : json["translation"].toArray())
            _result += i.toString();
        return true;
    }
    else
    {
        _result = "API ERROR: code = " + json["errorCode"].toString();
        _errorcode = json["errorCode"].toString().toInt();
    }
    return false;
}

QString TranslateEngines::Youdao::parseResult(QNetworkReply *_reply, int &errorcode, QByteArray &_cache)
{
    QString result;
    QNetworkReply::NetworkError error;
    if (error = _reply->error())
        return QString("Network ERROR: code = ") + QString::number(error);
    else
        parseResult(_cache = _reply->readAll(), result, errorcode);
    
    return result;
}

bool TranslateEngines::Youdao::createPostData(QByteArray *_data)
{
    return false;
}

void TranslateEngines::Youdao::setID(const QString &_appid)
{
    __app_id = _appid;
}

void TranslateEngines::Youdao::setKey(const QString &_appkey)
{
    __app_key = _appkey;
}

TranslateEngines::Youdao::Youdao(const QString &_appid,
                                 const QString &_appkey,
                                 const QString &_to,
                                 const QString &_from) : __app_id(_appid),
                                                         __app_key(_appkey), TransEngine(_to, _from)
{
    __info.name = "有道翻译";
    __info.enable_cache = true;
    __label=__info.name;
}

TranslateEngines::Youdao::~Youdao()
{
}
