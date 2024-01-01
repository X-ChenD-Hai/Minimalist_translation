#ifndef TRANSENGINE_H
#define TRANSENGINE_H
#ifdef LIBRARY
#define LIB_EXPORT Q_DECL_EXPORT
#else
#define LIB_EXPORT Q_DECL_IMPORT
#endif
#include <QString>
class QNetworkRequest;
class QNetworkReply;
class LIB_EXPORT TransEngine
{
    friend class Translation;

public:
    typedef struct
    {
        QString name;
        QString details[1024];
        qlonglong id;
        bool enable_cache = false;
    } EngineInfo;

public:
    virtual bool parseResult(const QByteArray &_data, QString &_result, int &_errorcode) { return false; };
    virtual QNetworkRequest *creatRequests(const QString &_text) = 0;
    virtual QString parseResult(QNetworkReply *_reply, int &errorcode, QByteArray &_cache) = 0;
    virtual const QHash<QString, QString> &supportto() = 0;
    virtual const QHash<QString, QString> &supportfrom() = 0;
    virtual const QString &defaultFrom() = 0;
    virtual const QString &defaultTo() = 0;

public:
    virtual bool createPostData(QByteArray *_data) { return false; };
    virtual QString label() { return __info.name; };

public:
    explicit TransEngine(const QString &_to,
                         const QString &_from) : __to(_to), __from(_from) {}

protected:
    EngineInfo __info;

public:
    QString __from;
    QString __to;

public:
    TransEngine(){};
    virtual ~TransEngine(){};
};
#endif // TRANSENGINE_H