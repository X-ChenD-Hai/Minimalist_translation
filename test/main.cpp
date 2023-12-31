#include "ui/MTranslation.h"
#include <windows.h>
#include <QApplication>
#pragma comment(lib, "user32.lib")



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MTranslation w;
    w.show();

    return a.exec();
}