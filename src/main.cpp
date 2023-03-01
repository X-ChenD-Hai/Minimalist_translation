#include "mTrs.h"
#include "mainwindow.h"
#include "getText.h"
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QTextCodec>
#include <QHBoxLayout>
#include <QCryptographicHash>
#include <QDebug>
#include <QThread>
#define D qDebug()



int main(int argc, char *argv[])
{
    // return app.exec();

    // QString a = "你好";
    // QByteArray b = a.toUtf8();

    // // QByteArray b = QCryptographicHash::hash(a.toUtf8(), QCryptographicHash::Md5);
    // qDebug()<<QString(b.toPercentEncoding());

    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.setWindowTitle((char*)"------极简翻译------");
    mainWindow.setWindowIcon((char*)"resource\\icon\\右_40x40.png");
    mainWindow.show();


    app.exec();
    return 0;
}
