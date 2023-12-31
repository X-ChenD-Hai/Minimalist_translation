#include "Translation.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QList>
#include <QFile>
#include <QDataStream>
#define CACHE_NUMBER 1000
typedef struct
{
    QString engineLabel;
    QByteArray byteArray;
    unsigned count = 1;
} ResultInfo;

typedef QHash<QByteArray, ResultInfo *> ResultList;
typedef QHash<QString, TransEngine *> EngineList;
ResultList g_cache;
size_t g_size = 0;
EngineList g_engine_list;

auto hash1 = QCryptographicHash(QCryptographicHash::Md5);
auto hash2 = QCryptographicHash(QCryptographicHash::Sha256);
QByteArray hsah(const QString &_str)
{
    QByteArray result;
    result = _str.toUtf8();
    hash1.addData(result);
    hash2.addData(result);
    result = hash1.result() + hash2.result();
    hash1.reset();
    hash2.reset();
    return result;
}
void clear_cache()
{
    for (auto i : g_cache)
        delete i;
    g_cache.clear();
}

ResultInfo *getCache(const QByteArray &_id)
{
    if (auto i = g_cache.find(_id); i != g_cache.end())
    {
        i.value()->count++;
        return i.value();
    }
    return nullptr;
}
void Translation::setEngine(TransEngine *_engine)
{
    if (!find(_engine->label()))
        regist(_engine);
    __p_trans_engine = _engine;
}
void Translation::update(const QString &_text)
{
    QByteArray hash_id = hsah(_text + __p_trans_engine->__to + __p_trans_engine->label());
    ResultInfo *info = getCache(hash_id);
    if (info && __p_trans_engine->__info.enable_cache)
    {
        int errorcode = 0;
        QString result;
        info->count++;
        auto e = find(info->engineLabel);
        if (e)
            if (e->parseResult(info->byteArray, result, errorcode))
            {
                emit finished(errorcode, result);
                if (errorcode == 0)
                    emit successed(result);
                else
                    emit error(errorcode, result);
            }
    }
    else
    {
        QByteArray data;
        QNetworkReply *reply;
        auto request = __p_trans_engine->creatRequests(_text);
        if (!request)
            return;
        if (__p_trans_engine->createPostData(&data))
            reply = __net_manager.post(*request, data);
        else
            reply = __net_manager.get(*request);
        delete request;
        QObject::connect(
            reply, &QNetworkReply::finished, [=]()
            {
            int errorcode=0;
            QByteArray cache;
            QString result = __p_trans_engine->parseResult(reply,errorcode,cache);
            emit finished(errorcode, result);
            if (errorcode == 0)
            {
                emit successed(result);
                if(__p_trans_engine->__info.enable_cache)
               {
                auto i = new ResultInfo();
                i->count = 1;
                i->byteArray = cache;
                i->engineLabel = __p_trans_engine->label();
                g_cache.insert(hash_id, i);
                }
            }
            else
            {
                emit error(errorcode, result);
            reply->deleteLater();
            }; });
    }
    if (g_size > CACHE_NUMBER)
        clear_cache();
}

void Translation::unregist(const QString &_label)
{
    if (auto e = g_engine_list.find(_label); e != g_engine_list.end())
    {
        delete e.value();
        g_engine_list.erase(e);
    }
    else
        throw "translateEngine : " + _label + " Not Regist!";
}

void Translation::regist(TransEngine *_engine)
{
    if (auto e = g_engine_list.find(_engine->label()); e == g_engine_list.end())
    {
        g_engine_list.insert(_engine->label(), _engine);
    }
    else
    {
        delete e.value();
        g_engine_list.insert(e.key(), _engine);
    }
}

TransEngine *Translation::find(const QString &_label)
{
    if (auto e = g_engine_list.find(_label); e != g_engine_list.end())
        return e.value();
    return nullptr;
}

QStringList Translation::allRegistedEngines()
{
    return g_engine_list.keys();
}

void Translation::saveCache(const QString &_path)
{
    QFile f(_path);
    if (f.open(QIODevice::WriteOnly))
    {
        QDataStream s(&f);
        for (auto it = g_cache.begin(); it != g_cache.end(); it++)
            s << it.key() << it.value()->byteArray << it.value()->count << it.value()->engineLabel;
    }
}

void Translation::loadCache(const QString &_path)
{
    QFile f(_path);
    if (f.open(QIODevice::ReadOnly))
    {
        QDataStream s(&f);
        while (!s.atEnd())
        {
            auto cache = new ResultInfo();
            QByteArray key;
            s >> key >> cache->byteArray >> cache->count >> cache->engineLabel;
            g_cache.insert(key, cache);
        }
    }
}

Translation::Translation(TransEngine *_engine, QObject *_parent) : QObject(_parent)
{
    setEngine(_engine);
}

Translation::Translation(QObject *_parent) : QObject(_parent)
{
}

Translation::~Translation()
{
}