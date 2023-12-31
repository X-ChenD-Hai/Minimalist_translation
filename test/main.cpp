#include "ui/MTranslation.h"
#include <windows.h>
#include <QApplication>
#include <QSharedMemory>
#include <QDataStream>
#include <QBuffer>
#include <QMessageBox>
#pragma comment(lib, "user32.lib")

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSharedMemory sharedMemory(qApp->applicationName()); // 设置绑定的共享内存段的key值
    if (sharedMemory.attach())
    {
        QMessageBox::warning(nullptr, "Error", "An instance of the application is already running.");
        return 1;
    }
    else
    {
        sharedMemory.create(1); // 创建1byte大小的共享内存段
    }

    MTranslation w;
    w.show();

    return a.exec();
}