#ifndef TRANSLATION_H
#define TRANSLATION_H
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QHash>
#include "TransEngine.h"
class TransEngine;
class LIB_EXPORT Translation : public QObject
{
    Q_OBJECT
public slots:
    void update(const QString &_text);
    void setEngine(TransEngine *_engine);

Q_SIGNALS:
    void successed(QString _result);
    void error(int _error_code, QString _result);
    void finished(int _error_code, QString _result);

public:
    static void unregist(const QString &_label);
    static void regist(TransEngine *_engine);
    static TransEngine *find(const QString &_label);
    explicit Translation(TransEngine *_engine = nullptr, QObject *_parent = nullptr);
    explicit Translation(QObject *_parent = nullptr);
    ~Translation();

private:
    TransEngine *__p_trans_engine = nullptr;

public:
    QNetworkAccessManager __net_manager;
};

#endif // TRANSLATION_H
