#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSqlDatabase>
#include <QHash>
#include <QSqlQuery>
#include "TransEngine.h"
class TransEngine;
class QSqlDatabase;
class LIB_EXPORT Translation : public QObject
{
    Q_OBJECT
public slots:
    void update(const QString &_text);
    void setEngine(TransEngine *_engine);

private slots:
    void reply_finished();

Q_SIGNALS:
    void successed(QString _result);
    void error(int _error_code, QString _result);
    void finished(int _error_code, QString _result);

public:
    static void unregist(const QString &_label);
    static void regist(TransEngine *_engine);
    static TransEngine *find(const QString &_label);
    static QStringList allRegistedEngines();

public:
    explicit Translation(TransEngine *_engine, const QString &_stoargePath = "", QObject *_parent = nullptr);
    explicit Translation(const QString &_stoargePath = "", QObject *_parent = nullptr);
    ~Translation();

private:
    void init();
    inline void initDB();
    void insertReply();

private:
    TransEngine *__p_trans_engine = nullptr;

private:
    QNetworkAccessManager* __net_manager;
    QSqlDatabase __database;
    QSqlQuery query;
    bool databaseInited = false;
    QString __dbpath;
    QString __stoargeFolder;
};

#endif // TRANSLATION_H
