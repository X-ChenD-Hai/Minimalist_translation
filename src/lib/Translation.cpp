#include "Translation.h"
#include <QDebug>
QString Translation::translate()
{
    qDebug() << "in asdfgfdgsfdghgfdh lib";
    qDebug() << translate1();
    return "Hello";
}
QString Translation::translate1()
{
    qDebug() << "in lib";
    return "Hello 12132134";
}

Translation::Translation()
{
}

Translation::~Translation()
{
}