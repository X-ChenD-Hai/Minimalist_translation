#include "getText.h"
#include <QUrl>
#include <QDebug>
#include <QTime>
#include <QCryptographicHash>
#include <QTextCodec>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#define M_URL "https://fanyi-api.baidu.com/api/trans/vip/translate?"
#define M_APP_ID "20230224001574792"
#define M_KEY "N4CRgpLT49LXKFZ7UeSt"
#define D qDebug()

void getText::startTranslate(const QString &text)
{

    this->req.setUrl(this->createUrl(text));
    req.setAttribute(QNetworkRequest::FollowRedirectsAttribute, true);
    this->manger = new QNetworkAccessManager(this);
    this->result = NULL;
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
        return;
    }
    else
    {
        // D << "相应成功";
        // // int statu_code = rep->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        // // D << statu_code;
        this->jsonData = new QJsonDocument(QJsonDocument::fromJson(rep->readAll()));
        QString s_result = "";
        QJsonObject obj = this->jsonData->object();
        QJsonValue value = obj.value("trans_result");
        QJsonArray arry = value.toArray();
        foreach (QJsonValue a, arry)
            s_result += a.toObject().value("dst").toString() + "\n";
        if (this->result)
        {
            delete this->result;
            this->result = NULL;
        }
        this->result = new QString(s_result);
        // D << s_result;
    }
}

QString *getText::getTranslateText() const
{
    return this->result;
}

QUrl getText::createUrl(const QString &text)
{

    QMap<QString, QString> &m_p = this->m_url.parameterMap;
    QString &m_u = this->m_url.baseUrl;
    m_u = M_URL;

    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    QString salt = QString("jnbdguvjernbfg") + QString(qrand()) + QString("jnbfugjnbrtgb");
    m_p["q"] = text;
    m_p["from"] = this->from;
    m_p["to"] = this->to;
    m_p["salt"] = salt;
    m_p["appid"] = M_APP_ID;

    QString osign = (m_p["appid"] + m_p["q"] + m_p["salt"] + M_KEY);
    QByteArray arry = QCryptographicHash::hash(osign.toUtf8(), QCryptographicHash::Md5);
    m_p["sign"] = arry.toHex();
    QString url = m_u;
    m_p["q"] = QString(m_p["q"].toUtf8().toPercentEncoding());

    foreach (const QString a, m_p.keys())
        url += (a + "=" + m_p[a] + "&");
    // D << url;
    return QUrl(url);
}