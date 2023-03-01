#include "getText.h"
#include <QUrl>
#include <QDebug>
#include <QTime>
#include <QCryptographicHash>
#include <QTextCodec>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

#define YOUDAO_URL "http://fanyi.youdao.com/translate?&doctype=json&"

#define BAIDU_URL "https://fanyi-api.baidu.com/api/trans/vip/translate?"
#define M_BADU_APP_ID "20230224001574792"
#define M_BAIDU_KEY "N4CRgpLT49LXKFZ7UeSt"
#define D qDebug()

getText::~getText()
{
    if (result)
    {
        delete result;
        result = NULL;
    }

    if (jsonData)
    {
        delete jsonData;
        jsonData = NULL;
    }
}

getText::getText() : QObject(),
                     manger(new QNetworkAccessManager(this)) {}

void getText::startTranslate(const QString &text)
{
    this->req.setUrl(this->createUrl(text));
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    if (this->result)
    {
        delete result;
        result = NULL;
    }
    this->rep = manger->get(req);
    connect(this->rep, &QNetworkReply::finished, this, &getText::replyFinshed);
}

void getText::replyFinshed()
{
    // D << "相应";
    if (rep->error())
    {
        // D << "相应失败";
        rep->deleteLater();
        rep = NULL;
        return;
    }
    else
    {
        // D << "相应成功";
        // // int statu_code = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        // // D << statu_code;
        this->jsonData = new QJsonDocument(QJsonDocument::fromJson(rep->readAll()));
        switch (this->tanslate_engine)
        {
        case translation_engine::TR_YOUDAO:
            return this->analysisYoudaoJson();
            break;
        case translation_engine::TR_BAIDU:
            return this->analysisBaiduJson();
            break;
        }
        if (this->jsonData)
        {
            delete this->jsonData;
            this->jsonData = NULL;
        }

        if (this->rep)
        {
            this->rep->deleteLater();
            this->rep = NULL;
        }
        // D << s_result;
    }
}

QString *getText::getTranslateText() const
{
    return this->result;
}

QUrl getText::createUrl(const QString &text)
{
    QUrl url;
    switch (this->tanslate_engine)
    {
    case translation_engine::TR_YOUDAO:
        url = this->createYoudaoUrl(text);
        break;
    case translation_engine::TR_BAIDU:
        url = this->createBaiduUrl(text);
        break;
    }
    return url;
}

QUrl getText::createBaiduUrl(const QString &text)
{
    QMap<QString, QString> &m_p = this->m_url.parameterMap;
    QString &m_u = this->m_url.baseUrl;
    m_u = BAIDU_URL;

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    QString salt = QString("jnbdguvjernbfg") + QString(qrand()) + QString("jnbfugjnbrtgb");
    m_p["q"] = text;
    m_p["from"] = this->from;
    m_p["to"] = this->to;
    m_p["salt"] = salt;
    m_p["appid"] = M_BADU_APP_ID;

    QString osign = (m_p["appid"] + m_p["q"] + m_p["salt"] + M_BAIDU_KEY);
    QByteArray arry = QCryptographicHash::hash(osign.toUtf8(), QCryptographicHash::Md5);
    m_p["sign"] = arry.toHex();
    QString url = m_u;
    m_p["q"] = QString(m_p["q"].toUtf8().toPercentEncoding());

    foreach (const QString a, m_p.keys())
        url += (a + "=" + m_p[a] + "&");
    // D << url;
    return QUrl(url);
}

QUrl getText::createYoudaoUrl(const QString &text)
{
    QString &m_u = this->m_url.baseUrl;
    m_u = YOUDAO_URL;

    QString to = "";
    if (this->to == "zh")
        to = "EN2ZH_CN";
    else if (this->to == "en")
        to = "ZH_CN2EN";

    QString i = QString(text.toUtf8().toPercentEncoding());
    // D << m_u + QString("type=") + from + QString("&i=") + i;
    return QUrl(m_u + QString("type=") + from + QString("&i=") + i);
}

void getText::analysisBaiduJson()
{
    QString s_result = "";
    QJsonObject obj = this->jsonData->object();
    QJsonValue value = obj.value("trans_result");
    QJsonArray arry = value.toArray();
    foreach (QJsonValue a, arry)
        s_result += a.toObject().value("dst").toString() + "\n";
    this->result = new QString(s_result);
}

void getText::analysisYoudaoJson()
{
    QString s_result = "";
    QJsonObject obj = this->jsonData->object();
    QJsonValue value = obj.value("translateResult");
    QJsonArray arry = value.toArray();
    foreach (QJsonValue a, arry)
    {
        foreach(QJsonValue i,a.toArray())
            s_result += i.toObject().value("tgt").toString();
        s_result += "\n";
    }
    this->result = new QString(s_result);
}

void getText::setEngine(translation_engine engine)
{
    this->tanslate_engine = engine;
}
