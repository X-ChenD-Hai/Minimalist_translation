#include "mTrs.h"
#include "getText.h"
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#define D qDebug()
mTrs::mTrs(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_mTrs), translater(new getText)
{

    ui->setupUi(this);
    this->timer = new QTimer(this);

    connect(this->ui->fromEdit, SIGNAL(textChanged()), this, SLOT(updateFromText()));
    connect(this->timer, SIGNAL(timeout()), this, SLOT(updateToText()));
}

void mTrs::updateFromText()
{
    this->translater->startTranslate(this->ui->fromEdit->toPlainText());
    this->timer->start(1500);
}
void mTrs::updateToText()
{
    this->ui->toEdit->setText(this->translater->getTranslateText());
}

mTrs::~mTrs()
{
    delete ui;
    delete translater;
}

void mTrs::setfont(QFont &font)
{
    this->ui->toEdit->setFont(font);
    this->ui->toEdit->update();
}
