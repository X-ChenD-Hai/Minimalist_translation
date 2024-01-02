#ifndef YOUDAO_H
#define YOUDAO_H
#ifdef LIBRARY
#include "TransEngine.h"
#endif // LIBRARY
#include <QString>
namespace TranslateEngines
{

    class LIB_EXPORT Youdao : public TransEngine
    {

    public:
        virtual QString label() override { return __label; };
        virtual bool parseResult(const QByteArray &_data, QString &_result, int &_errorcode) override;
        virtual bool createPostData(QByteArray *_data) override;
        virtual QNetworkRequest *creatRequests(const QString &_text) override;
        virtual QString parseResult(QNetworkReply *_reply, int &errorcode, QByteArray &_cache) override;
        virtual const QHash<QString, QString> &supportto() override;
        virtual const QHash<QString, QString> &supportfrom() override;
        virtual const QString &defaultFrom() override;
        virtual const QString &defaultTo() override;

        void setID(const QString &_appid);
        void setKey(const QString &_appkey);

    public:
        void setLabel(const QString &_label) { __label = _label; };
        explicit Youdao(const QString &_appid,
                        const QString &_appkey,
                        const QString &_to="zh-CHS",
                        const QString &_fron = "auto");
        ~Youdao();

    private:
        QString __app_id;
        QString __app_key;
        QString __label;

    private:
        static QString __url;
    };

} // namespace TranslateEngines

#endif // YOUDAO_H