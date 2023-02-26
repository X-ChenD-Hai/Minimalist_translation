#include "mTrs.h"
#include "getText.h"
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#define MAX_WAIT_BACK_INPUT_TIME 1000
#define MIN_TEST_INTERVAL_TIME 200

#define D qDebug()

mTrs::mTrs(QFont from, QFont to, QWidget *parent)
    : QMainWindow(parent), ui(new Ui_mTrs), translater(new getText)
{
    init_mTrs();
    this->ui->fromEdit->setFont(from);
    this->ui->fromEdit->setFont(to);
}

mTrs::mTrs(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_mTrs), translater(new getText)
{
    init_mTrs();
}

void mTrs::init_mTrs()
{
    ui->setupUi(this);
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);
    this->timer2->setObjectName("timer2");

    connect(this->ui->fromEdit, SIGNAL(textChanged()),
            this, SLOT(updateFromText()));
    connect(this->timer1, SIGNAL(timeout()),
            this, SLOT(updateToText()));
    connect(this->timer2, &QTimer::timeout, this, [&]()
            {    
                        this->timer2->stop();
                        emit updateFromText(); });
}

void mTrs::updateFromText()
{
    const QString &currentStr = this->ui->fromEdit->toPlainText();
    // D << sender()->objectName();
    this->timer1->stop();
    if ((this->previousStr->indexOf(currentStr) == -1 || sender()->objectName() == "timer2") && currentStr != "")
    {
        this->timer1->start(MIN_TEST_INTERVAL_TIME);
        *this->previousStr = currentStr;
        this->translater->startTranslate(currentStr);
    }
    else if (currentStr == "")
        this->ui->toEdit->setText("");
    else
    {
        this->timer2->start(MAX_WAIT_BACK_INPUT_TIME);
    }
}

void mTrs::updateToText()
{
    QString *res = this->translater->getTranslateText();
    // D << "test";
    if (res != NULL)
    {
        this->ui->toEdit->setText(*res);
        this->timer1->stop();
        // D << "ok";
    }
}

void mTrs::setfont(QFont &font)
{
    this->ui->toEdit->setFont(font);
    this->ui->toEdit->update();
}

mTrs::~mTrs()
{
    delete ui;
    delete translater;
    delete previousStr;
}
