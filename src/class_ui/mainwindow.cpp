#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mTrs.h"
#include "qss.h"
#include <windows.h>
#include <windowsx.h>
#include <QAction>
#include <QDebug>
#include <QVariant>
#include <QMenu>
#define INITIAL_FROMEDIT_FONT_PIXESIZE 30
#define INITIAL_TOEDIT_FONT_PIXESIZE 40
#define INITIAL_WINDOW_SIZE QSize(400, 1030)
#define INITIAL_MINIMUM_SIZE QSize(100, 200)
#define INITIAL_WINDOW_POS 50, 50

typedef enum act_type
{
    WIN_TO_TOP = 1,
    FONT_AMPLIFICATION,
    FONT_REDUCTION,
} act_type;
Q_DECLARE_METATYPE(act_type)

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
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->move(INITIAL_WINDOW_POS);
    this->resize(INITIAL_WINDOW_SIZE);
    this->setMinimumSize(INITIAL_MINIMUM_SIZE);

    QFont from, to;
    from.setPixelSize(INITIAL_FROMEDIT_FONT_PIXESIZE);
    to.setPixelSize(INITIAL_TOEDIT_FONT_PIXESIZE);

    this->font = to;

    this->mtrs = new mTrs(from, to, this);
    this->mtrs->setWindowFlags(Qt::Widget);
    this->mtrs->setfont(this->font);
    this->ui->title_bar->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->ui->verticalLayout->addWidget(this->mtrs);
    this->initAction();

    // QFile style("resource\\QSS\\main.qss");
    // style.open(QFile::ReadOnly);
    // this->setStyleSheet(style.readAll());
    // style.close();
    this->setStyleSheet(M_QSS);
}

void MainWindow::initAction()
{
    QAction *act_font_add = new QAction(this);
    QAction *act_font_minus = new QAction(this);
    QAction *act_window_top = new QAction(this);

    connect(act_font_add, SIGNAL(triggered(bool)), this, SLOT(act_slot(bool)));
    connect(act_font_minus, SIGNAL(triggered(bool)), this, SLOT(act_slot(bool)));
    connect(act_window_top, SIGNAL(triggered(bool)), this, SLOT(act_slot(bool)));

    act_font_add->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Equal));
    act_font_minus->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus));
    QMenu *m_menu = this->ui->title_bar->m_menu;

    act_window_top->setCheckable(true);
    act_window_top->setText("窗口置顶");
    act_window_top->setData(act_type::WIN_TO_TOP);

    act_font_add->setText("放大字体");
    act_font_add->setData(act_type::FONT_AMPLIFICATION);

    act_font_minus->setText("缩小字体");
    act_font_minus->setData(act_type::FONT_REDUCTION);

    m_menu->addAction(act_window_top);
    m_menu->addSeparator();
    m_menu->addAction(act_font_add);
    m_menu->addAction(act_font_minus);

    act_window_top->trigger();
}

void MainWindow::act_slot(bool chicked)
{
    QAction *action = static_cast<QAction *>(sender());
    act_type type = action->data().value<act_type>();
    Qt::WindowFlags flags;
    switch (type)
    {
    case act_type::WIN_TO_TOP:
        flags = this->windowFlags();
        if (chicked)
            flags |= Qt::WindowStaysOnTopHint;
        else
            flags ^= Qt::WindowStaysOnTopHint;
        this->setWindowFlags(flags);
        this->show();
        break;
    case act_type::FONT_REDUCTION:
        this->font.setPixelSize(this->font.pixelSize() - 1);
        this->mtrs->setfont(font);
        break;
    case act_type::FONT_AMPLIFICATION:
        this->font.setPixelSize(this->font.pixelSize() + 1);
        this->mtrs->setfont(font);
        break;
    default:
        break;
    }
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
