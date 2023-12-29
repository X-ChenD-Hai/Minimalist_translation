#include "MTranslation.h"
#include <QTextDocument>
using namespace TranslateEngines;
char a[] = R"(We've combined the power of the Following feed with the For you feed so there’s one place to discover content on GitHub. There’s improved filtering so you can customize your feed exactly how you like it, and a shiny new visual design.)";

void MTranslation::initWidget()
{
    youdao = new Youdao("74b31a9fb7b2c903", "0xlLu49lEWbe13Oel18peX69wZ7OYTj8", "zh-CHS");
    trs = new Translation(youdao, this);
    w = new QWidget(this);
    main = new QVBoxLayout(w);
    textEdit = new QPlainTextEdit(this);
    textBro = new QTextBrowser(this);

    setCentralWidget(w);
    resize(600, 500);
}
void MTranslation::initConnection()
{
    QPushButton *btn1 = new QPushButton("翻译", w);
    auto hbox_text = new QHBoxLayout();

    hbox_text->addWidget(textEdit);
    hbox_text->addWidget(textBro);
    main->addLayout(hbox_text, 10);
    main->addWidget(btn1);
    connect(btn1, &QPushButton::clicked, [&]()
            { trs->update(textEdit->toPlainText()); });
    connect(trs, &Translation::successed, textBro, &QTextBrowser::setPlainText);
}
void MTranslation::initAction()
{
}

MTranslation::MTranslation(QWidget *parent)
    : QMainWindow(parent)
{
    Resource re;
    initWidget();
    initAction();
    initConnection();
    initStyle();
    update();
}

MTranslation::~MTranslation()
{
}
void MTranslation::initStyle()
{
    QString str = ":qss/main.qss";
    QFile f(str, this);
    f.open(QIODevice::Text | QIODevice::ReadOnly);
    if (f.isOpen())
        qApp->setStyleSheet(f.readAll());
}