#ifndef TRANSLATION_H
#define TRANSLATION_H
#include "TransEngine.h"
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QSqlDatabase>
#include <QHash>
#include <QSqlQuery>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
class TransEngine;
class QSqlDatabase;
class LIB_EXPORT Translation : public QThread
{
    Q_OBJECT
public slots:
    void update(const QString &_text);
    void setEngine(TransEngine *_engine);

private slots:
    virtual void run() override;
    void translate(QNetworkAccessManager *_manager);
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
    QSqlDatabase __database;
    QSqlQuery query;
    bool databaseInited = false;
    QString __dbpath;
    QString __stoargeFolder;
    QString __text;
    bool __run;
    QMutex __mutex;
    QWaitCondition __wait;
    QThread * __subthread;
};

#endif // TRANSLATION_H
