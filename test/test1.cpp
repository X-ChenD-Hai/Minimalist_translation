#include <QApplication>
#include <QClipboard>
#include <windows.h>
#include <QMimeData>
#include <QFile>
#include <QString>
#include <QDataStream>
#include <QTextStream>
#include <QSqlQuery>
#include <QSqlDatabase>
#pragma comment(lib, "user32.lib")

const QHash<QString, QString> &g_sl()
{
    // static QHash<QString, QString> res;
    // if (!res.size())
    // {
    //     for (size_t i = 0; i < g_slist.length() - 2; i += 3)
    //         res.insert(g_slist.at(i + 1), g_slist.at(i + 2));
    // }
    // return res;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // db.setDatabaseName("w/youdao.db");
    // if (db.open())
    // {
    //     qDebug() << "open";
    //     QSqlQuery query(db);
    //     qDebug()<<g_slist.size();
    //     query.prepare(R"(INSERT INTO 'language' (zh_name,en_name,code) VALUES (? ,? ,?))");
    //     for (size_t i = 0; i < g_slist.length() - 2; i += 3)
    //     {
    //         query.bindValue(0, g_slist[i + 1]);
    //         query.bindValue(1, g_slist[i]);
    //         query.bindValue(2, g_slist[i + 2]);
    //         if (!query.exec())
    //         {
    //             qDebug() << "ERROR：" << g_slist[i + 2];
    //         }
    //     }
    //     db.close();
    // }
    return a.exec();
}