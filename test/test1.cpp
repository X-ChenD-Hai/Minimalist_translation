#include <QApplication>
#include <QHotkey>
#include <QClipboard>
#include <windows.h>
#include <QMimeData>
#include <QFile>
#include <QString>
#include <QDataStream>
#include <QTextStream>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile f("resource/data.csv");
    QFile f1("resource/youdao.sl");
    QStringList sl;
    if (f.open(QIODeviceBase::ReadOnly | QIODeviceBase::Text))
    {
        QString str;
        QTextStream s(&f);
        while (!s.atEnd())
        {
            s >> str;
            sl.push_back(str);
        }
    }
    if (f1.open(QIODeviceBase::WriteOnly))
    {
        QString str;
        QDataStream s(&f1);
        while (!sl.isEmpty())
        {
            s << sl.front();
            sl.pop_front();
        }
        f1.close();
    }
    qDebug() << "ok";
    qApp->quit();

    return a.exec();
}