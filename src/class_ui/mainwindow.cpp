#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mTrs.h"
#include "qss.h"
#include <windows.h>
#include <windowsx.h>
#include <QAction>
#include <QDebug>
#define INITIAL_FROMEDIT_PIXESIZE 20


MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    this->setGeometry(300, 300, 1000, 618);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->font.setPixelSize(INITIAL_FROMEDIT_PIXESIZE);
    this->mtrs = new mTrs(this);
    this->mtrs->setWindowFlags(Qt::Widget);
    this->mtrs->setfont(this->font);
    this->ui->title_bar->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->ui->verticalLayout->addWidget(this->mtrs);
    QAction *act_add = new QAction(this);
    QAction *act_minus = new QAction(this);

    connect(act_add, SIGNAL(triggered()), this, SLOT(setfont()));
    connect(act_minus, SIGNAL(triggered()), this, SLOT(setfont()));

    act_add->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Equal));
    act_minus->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    act_add->setObjectName("add");
    act_minus->setObjectName("minus");

    this->addAction(act_add);
    this->addAction(act_minus);

    // QFile style("resource\\QSS\\main.qss");
    // style.open(QFile::ReadOnly);
    // this->setStyleSheet(style.readAll());
    // style.close();
    this->setStyleSheet(M_QSS);
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    return this->ui->title_bar->toNativeEvent(eventType, message, result);
}

void MainWindow::setWindowTitle(char *title)
{
    this->ui->title_bar->setTitle(title);
}

void MainWindow::setWindowIcon(char *iconPath)
{
    this->ui->title_bar->setIcon(iconPath);
}

void MainWindow::setfont()
{
    int pix = this->font.pixelSize();
    if (sender()->objectName() == "add")
        pix += 2;
    else if(sender()->objectName()=="minus")
        pix -= 2;
    this->font.setPixelSize(pix);
    this->mtrs->setfont(font);
}