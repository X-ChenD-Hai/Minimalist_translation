#include "MTranslation.h"
#include "Translation.h"
#include <QApplication>
#include <QPixmap>
#include <QFile>
#include <QUrl>
MTranslation::MTranslation(QWidget *parent)
    : QMainWindow(parent)
{
    QString str = ":qss/main.qss";
    QUrl url = QUrl(str);
    QFile f(str, this);
    f.open(QIODevice::Text | QIODevice::ReadOnly);
    if (f.isOpen())
        qApp->setStyleSheet(f.readAll());
    Translation trans;
    qDebug() << trans.translate();
}

MTranslation::~MTranslation()
{
}