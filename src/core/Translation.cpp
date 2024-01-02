#include "Translation.h"
#include <QDebug>
#include <QCryptographicHash>
#include <QList>
#include <QFile>
#include <QDataStream>
#include <QQueue>
#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#define DB_INIT_ENGINE "\
CREATE TABLE IF NOT EXISTS\
    tbl_engine (\
        id INTEGER PRIMARY KEY AUTOINCREMENT,\
        label char(30) NOT NULL UNIQUE\
    );"

#define DB_INIT_TEXT "CREATE TABLE IF NOT EXISTS\
    tbl_text (\
        id INTEGER PRIMARY KEY AUTOINCREMENT,\
        hash BLOB NOT NULL,\
        text TEXT NOT NULL UNIQUE,\
    );"
#define DB_INIT_REPLY "CREATE TABLE IF NOT EXISTS\
    tbl_reply (\
        id INTEGER PRIMARY KEY AUTOINCREMENT,\
        engine_id INT NOT NULL,\
        from_hash_id BLOB NOT NULL,\
        from_id INT NOT NULL,\
        to_id INT NOT NULL,\
        timestat INT NOT NULL,\
        count INT NOT NULL\
    );"
typedef QHash<QString, TransEngine *> EngineList;

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

void genPath(const QString &_path)
{
    QFileInfo info(_path);
    if (!info.isAbsolute())
        info = QFileInfo(QCoreApplication::applicationDirPath() + info.path());
    if (!info.exists())
    {
        QDir d(info.absoluteDir());
        d.mkpath(d.absolutePath());
    }
}

void Translation::setEngine(TransEngine *_engine)
{
    if (!find(_engine->label()))
        regist(_engine);
    __p_trans_engine = _engine;

    query.prepare("SELECT id FROM tbl_engine WHERE label = ?;");
    query.bindValue(0, _engine->label());
    _engine->__info.id = 0;
    if (query.exec())
        while (query.next())
        {
            _engine->__info.id = query.value("id").toULongLong();
        }
    if (!_engine->__info.id)
    {
        query.prepare("INSERT INTO  tbl_engine (label) VALUES (?);");
        query.bindValue(0, _engine->label());
        if (query.exec())
            _engine->__info.id = query.lastInsertId().toLongLong();
    }
}
void Translation::update(const QString &_text)
{

    QByteArray hash_id = hsah(_text + __p_trans_engine->__to + __p_trans_engine->label());
    query.prepare("SELECT tbl_text.text, tbl_reply.id FROM tbl_text JOIN tbl_reply ON tbl_text.id = tbl_reply.to_id WHERE tbl_reply.from_hash_id = ?;");
    query.bindValue(0, hash_id);
    if (query.exec())
        while (query.next())
        {
            QString result = query.value(0).toString();
            qlonglong id = query.value(1).toLongLong();

            query.prepare("UPDATE tbl_reply SET count = count + 1 ,timestat=? WHERE id = ?;");
            query.bindValue(0, QDateTime::currentSecsSinceEpoch());
            query.bindValue(1, id);

            query.exec();
            emit finished(0, result);
            emit successed(result);
            return;
        }
    else
        qDebug() << query.lastError().text();
    QString label = __p_trans_engine->label();
    QByteArray data;
    QNetworkReply *reply;
    auto request = __p_trans_engine->creatRequests(_text);
    if (!request)
        return;
    if (__p_trans_engine->createPostData(&data))
        reply = __net_manager->post(*request, data);
    else
        reply = __net_manager->get(*request);
    delete request;
    auto hsh = hsah(_text);
    qlonglong i = 0;
    int j = 0;
    query.prepare("SELECT id FROM tbl_text WHERE hash=?;");
    query.bindValue(0, hsh);
    if (query.exec())
        while (query.next())
        {
            if (j > 1)
            {
                i = 0;
                break;
            }
            i = query.value(0).toLongLong();
            j++;
        }
    if (!i)
    {
        query.prepare("INSERT INTO tbl_text (hash,text) VALUES(?,?);");
        query.bindValue(0, hsh);
        query.bindValue(1, _text);
        if (query.exec())
            i = query.lastInsertId().toLongLong();
    }
    if (find(label))
    {
        reply->setProperty("from_hash_id", hash_id);
        reply->setProperty("create_time", QDateTime::currentMSecsSinceEpoch());
        reply->setProperty("engine_id", find(label)->__info.id);
        reply->setProperty("from_id", i);

        QObject::connect(
            reply, &QNetworkReply::finished, this, reply_finished);
    }
}

void Translation::reply_finished()
{
    int errorcode = 0;
    QByteArray cache;
    auto reply = qobject_cast<QNetworkReply *>(sender());
    QString result = __p_trans_engine->parseResult(reply, errorcode, cache);

    emit finished(errorcode, result);
    if (errorcode == 0)
    {
        emit successed(result);
        auto hsh = hsah(result);
        qlonglong id = 0;
        query.prepare("SELECT id FROM tbl_text WHERE hash=?;");
        query.bindValue(0, hsh);
        if (query.exec())
            while (query.next())
            {
                id = query.value(0).toLongLong();
            }
        if (!id)
        {
            query.prepare("INSERT INTO tbl_text (hash,text) VALUES(?,?);");
            query.bindValue(0, hsah(result));
            query.bindValue(1, result);
            if (query.exec())
                id = query.lastInsertId().toLongLong();
        }
        if (id)
        {
            query.prepare("INSERT INTO tbl_reply (engine_id,from_hash_id,from_id,to_id,timestat,count) VALUES (?,?,?,?,?,?);");
            query.bindValue(0, reply->property("engine_id"));
            query.bindValue(1, reply->property("from_hash_id"));
            query.bindValue(2, reply->property("from_id"));
            query.bindValue(3, id);
            query.bindValue(4, QDateTime::currentMSecsSinceEpoch());
            query.bindValue(5, 1);
            if (!query.exec())
                qDebug() << "text instert Faild   ===>    " << query.lastError().text();
        }
    }
    else
    {

        emit error(errorcode, result);
    };
    reply->deleteLater();
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

Translation::Translation(TransEngine *_engine, const QString &_stoargeFolder,
                         QObject *_parent) : QObject(_parent), __stoargeFolder(_stoargeFolder)
{
    setEngine(_engine);
    init();
}

Translation::Translation(const QString &_stoargeFolder, QObject *_parent) : QObject(_parent), __stoargeFolder(_stoargeFolder)
{
    init();
}

Translation::~Translation()
{
    __database.close();
}

void Translation::init()
{
    __net_manager = new QNetworkAccessManager(this);
    if (!QDir(__stoargeFolder).isAbsolute() || __stoargeFolder.isEmpty())
        __stoargeFolder = QCoreApplication::applicationDirPath() + __stoargeFolder + "/";
    __dbpath = __stoargeFolder + "cache/transdata.db";
    genPath(__dbpath);
    __database = QSqlDatabase::addDatabase("QSQLITE");
    __database.setDatabaseName(__dbpath);
    initDB();
}

inline void Translation::initDB()
{
    __database.open();
    query = QSqlQuery(__database);
    databaseInited = (query.exec(DB_INIT_ENGINE) &&
                      query.exec(DB_INIT_TEXT) &&
                      query.exec(DB_INIT_REPLY));
}

void Translation::insertReply()
{
}