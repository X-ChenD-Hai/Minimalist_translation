#include "mTrs.h"
#include "getText.h"
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QTimer>
#include <mainwindow.h>
#define MAX_WAIT_BACK_INPUT_TIME 1000
#define MIN_TEST_INTERVAL_TIME 200

#define D qDebug()

class MainWindow;

mTrs::mTrs(QFont from, QFont to, QWidget *parent)
    : QMainWindow(parent), ui(new Ui_mTrs), translater(new getText)
{
    init_mTrs();
    this->ui->fromEdit->setFont(from);
    this->ui->toEdit->setFont(to);
}

mTrs::mTrs(QWidget *parent)
    : QMainWindow(parent), ui(new Ui_mTrs), translater(new getText)
{
    init_mTrs();
}

void mTrs::setCilpboardTracking(bool checked)
{
    // D << "checked" << checked;
    if (checked)
    {
        if (!this->sysclipboard)
        {
            this->sysclipboard = QApplication::clipboard();
            this->sysclipboard->setObjectName("sysclipboard");
        }
        connect(this->sysclipboard, &QClipboard::dataChanged,
                this, &mTrs::updateFromText);
    }
    else
    {
        if (this->sysclipboard)
        {
            disconnect(this->sysclipboard, &QClipboard::dataChanged,
                       this, &mTrs::updateFromText);
        }
    }
}

void mTrs::init_mTrs()
{
    ui->setupUi(this);
    this->ui->fromEdit->setAcceptRichText(false);
    this->previousStr = new QString("");
    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);

    this->timer2->setObjectName("timer2");

    connect(this->ui->fromEdit, &QTextEdit::textChanged,
            this, &mTrs::updateFromText);
    connect(this->timer1, SIGNAL(timeout()),
            this, SLOT(updateToText()));
    connect(this->timer2, &QTimer::timeout, this, [&]()
            {    
                        this->timer2->stop();
                        emit updateFromText(); });
}

void mTrs::updateFromText()
{
    if (sender()->objectName() == "sysclipboard")
    {
        disconnect(this->ui->fromEdit, &QTextEdit::textChanged, this, &mTrs::updateFromText);
        this->ui->fromEdit->setText(this->sysclipboard->text());
        connect(this->ui->fromEdit, &QTextEdit::textChanged, this, &mTrs::updateFromText);
    }
    QString currentStr = this->ui->fromEdit->toPlainText();
    // D << sender()->objectName();
    // D << currentStr.length();
    // D << currentStr[0];
    int i = currentStr.length();
    while (i > 0 && currentStr.at(i - 1) == '\n')
    {
        currentStr.chop(1);
        i = currentStr.length();
    }
    while (i > 0 && currentStr.at(0) == '\n')
    {
        currentStr.remove(0, 1);
    }

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
    if (res)
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

void mTrs::setEngine(bool isChecked)
{
    if (isChecked)
    {
        auto pWidget = static_cast<MainWindow *>(this->parentWidget());
        pWidget->settings->translation_engine = static_cast<QAction *>(sender())->data().value<translation_engine>();
        return this->translater->setEngine(pWidget->settings->translation_engine);
    }
    else
        return;
}

QMap<QString, int> mTrs::getFont()
{
    QMap<QString, int> fontMap;
    fontMap["fromEdit_pixelSize"] = this->ui->fromEdit->font().pixelSize();
    fontMap["toEdit_pixelSize"] = this->ui->toEdit->font().pixelSize();
    return fontMap;
}

mTrs::~mTrs()
{
    delete ui;
    delete translater;
    delete previousStr;
}
