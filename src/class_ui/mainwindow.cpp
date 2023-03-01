#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mTrs.h"
#include "qss.h"
#include <QObject>
#include <windows.h>
#include <windowsx.h>
#include <QAction>
#include <QDebug>
#include <QVariant>
#include <QMenu>
#include <QKeyEvent>
#include <QEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#define D qDebug()
#define INITIAL_WINDOW_TOP true
#define INITIAL_TOEDIT_HEIGHT 100
#define INITIAL_FROMEDIT_HEIGHT 100
#define INITIAL_CLIPBOARD_TRACKING false
#define INITIAL_TRANSLATION_ENGINE translation_engine::TR_YOUDAO
#define INITIAL_FROMEDIT_FONT_PIXESIZE 30
#define INITIAL_TOEDIT_FONT_PIXESIZE 40
#define INITIAL_WINDOW_SIZE 450, 1030
#define INITIAL_MINIMUM_SIZE 100, 200
#define INITIAL_WINDOW_POS 50, 50

typedef enum act_type
{
    WIN_TO_TOP = 1,
    FONT_AMPLIFICATION,
    FONT_REDUCTION,
} act_type;
Q_DECLARE_METATYPE(act_type);

MainWindow::MainWindow(QWidget *parent) : QWidget(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->loadSettings();
    this->initUI();
    this->initAction();
}

MainWindow::~MainWindow()
{
    delete ui;
    this->writeInSettings();
    delete settings;
}

void MainWindow::loadSettings()
{
    this->settings = new Settings;
    QFile jsonFile("settings.json", this);
    if (jsonFile.open(QIODevice::ReadOnly))
    {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonFile.readAll());
        QJsonObject rootObj = jsonDoc.object();
        this->settings->fromedit_font_pixesize = rootObj.value("fromedit_font_pixesize").toInt();
        this->settings->toedit_font_pixesize = rootObj.value("toedit_font_pixesize").toInt();
        this->settings->window_top = rootObj.value("window_top").toBool();
        this->settings->cilpboard_tracking = rootObj.value("cilpboard_tracking").toBool();
        int engine = rootObj.value("translation_engine").toInt();
        switch (engine)
        {
        case translation_engine::TR_YOUDAO:
            this->settings->translation_engine = TR_YOUDAO;
            break;
        case translation_engine::TR_BAIDU:
            this->settings->translation_engine = TR_BAIDU;
            break;
        default:
            this->settings->translation_engine = INITIAL_TRANSLATION_ENGINE;
            break;
        }
        QJsonArray GeometryArry = rootObj.value("Geometry").toArray();
        for (int i = 0; i < 4; i++)
        {
            this->settings->Geometry[i] = GeometryArry[i].toInt();
        }
        this->settings->fromedit_height = rootObj.value("fromedit_height").toInt();
        this->settings->toedit_height = rootObj.value("toedit_height").toInt();
    }
    else
    {
        this->settings->fromedit_font_pixesize = INITIAL_FROMEDIT_FONT_PIXESIZE;
        this->settings->toedit_font_pixesize = INITIAL_TOEDIT_FONT_PIXESIZE;
        this->settings->window_top = INITIAL_WINDOW_TOP;
        this->settings->translation_engine = INITIAL_TRANSLATION_ENGINE;
        this->settings->cilpboard_tracking = INITIAL_CLIPBOARD_TRACKING;
        int geom[] = {INITIAL_WINDOW_POS, INITIAL_WINDOW_SIZE};
        this->settings->fromedit_height = INITIAL_FROMEDIT_HEIGHT;
        this->settings->toedit_height = INITIAL_TOEDIT_HEIGHT;

        for (int i = 0; i < 4; i++)
        {
            this->settings->Geometry[i] = geom[i];
        }
    }
    jsonFile.close();
}

void MainWindow::writeInSettings()
{
    QFile jsonFile("settings.json", this);
    if (jsonFile.open(QIODevice::WriteOnly))
    {
        mTrsSettings mTrs_settings = this->mtrs->getSettings();
        QJsonObject rootObj;
        rootObj.insert("fromedit_font_pixesize", mTrs_settings.fromEditPixeSize);
        rootObj.insert("toedit_font_pixesize", mTrs_settings.toEditPixeSize);
        rootObj.insert("toedit_font_pixesize", mTrs_settings.toEditPixeSize);
        rootObj.insert("toedit_height", mTrs_settings.toEditHeight);
        rootObj.insert("fromedit_height", mTrs_settings.fromEditHeight);
        rootObj.insert("window_top", this->settings->window_top);
        rootObj.insert("cilpboard_tracking", this->settings->cilpboard_tracking);
        rootObj.insert("translation_engine", int(this->settings->translation_engine));
        QJsonArray GeometryArry;
        GeometryArry.append(this->pos().x());
        GeometryArry.append(this->pos().y());
        GeometryArry.append(this->size().width());
        GeometryArry.append(this->size().height());
        rootObj.insert("Geometry", GeometryArry);
        QJsonDocument jsonDoc(rootObj);
        jsonFile.write(jsonDoc.toJson());
    }
    jsonFile.close();
}

void MainWindow::initUI()
{
    Settings &settings = *this->settings;
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->move(settings.Geometry[0], settings.Geometry[1]);
    this->resize(settings.Geometry[2], settings.Geometry[3]);
    this->setMinimumSize(INITIAL_MINIMUM_SIZE);

    QFont to;
    to.setPixelSize(settings.toedit_font_pixesize);
    this->font = to;

    mTrsSettings mTrs_settings = {
        this->settings->fromedit_font_pixesize,
        this->settings->toedit_font_pixesize,
        this->settings->fromedit_height,
        this->settings->toedit_height};
    this->mtrs = new mTrs(this);
    this->mtrs->setWindowFlags(Qt::Widget);

    this->ui->title_bar->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    this->ui->verticalLayout->addWidget(this->mtrs);

    this->mtrs->initSettings(mTrs_settings);

    // QFile style("resource\\QSS\\main.qss");
    // style.open(QFile::ReadOnly);
    // this->setStyleSheet(style.readAll());
    // style.close();
    this->setStyleSheet(M_QSS);
    // this->installEventFilter(this);
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

    auto m_trs_eg = new QMenu("设置翻译引擎", m_menu);
    auto acgr_trs_rg = new QActionGroup(m_trs_eg);
    auto act_bd_en = new QAction("百度翻译", acgr_trs_rg);
    auto act_yd_en = new QAction("有道翻译", acgr_trs_rg);

    act_bd_en->setData(translation_engine::TR_BAIDU);
    act_yd_en->setData(translation_engine::TR_YOUDAO);

    act_bd_en->setCheckable(true);
    act_yd_en->setCheckable(true);

    connect(act_bd_en, SIGNAL(triggered(bool)), this->mtrs, SLOT(setEngine(bool)));
    connect(act_yd_en, SIGNAL(triggered(bool)), this->mtrs, SLOT(setEngine(bool)));

    acgr_trs_rg->addAction(act_bd_en);
    acgr_trs_rg->addAction(act_yd_en);

    m_trs_eg->addAction(act_bd_en);
    m_trs_eg->addAction(act_yd_en);

    m_menu->addSeparator();
    m_menu->addMenu(m_trs_eg);

    auto act_clipborad_tracking = new QAction("跟踪剪贴板", m_menu);

    act_clipborad_tracking->setCheckable(true);

    connect(act_clipborad_tracking, SIGNAL(triggered(bool)), this->mtrs, SLOT(setCilpboardTracking(bool)));
    connect(act_clipborad_tracking, &QAction::triggered, this, [this, act_clipborad_tracking]()
            { this->settings->cilpboard_tracking = act_clipborad_tracking->isChecked(); });

    m_menu->addSeparator();
    m_menu->addAction(act_clipborad_tracking);

    if (this->settings->window_top)
        act_window_top->trigger();
    if (this->settings->cilpboard_tracking)
        act_clipborad_tracking->trigger();
    switch (this->settings->translation_engine)
    {
    case translation_engine::TR_YOUDAO:
        act_yd_en->trigger();
        break;
    case translation_engine::TR_BAIDU:
        act_bd_en->trigger();
        break;
    default:
        break;
    }
}

void MainWindow::act_slot(bool opt)
{
    QAction *action = static_cast<QAction *>(sender());
    act_type type = action->data().value<act_type>();
    Qt::WindowFlags flags;
    switch (type)
    {
    case act_type::WIN_TO_TOP:
        flags = this->windowFlags();
        if (opt)
            flags |= Qt::WindowStaysOnTopHint;
        else
            flags ^= Qt::WindowStaysOnTopHint;
        this->settings->window_top = opt;
        this->setWindowFlags(flags);
        this->show();
        break;
    case act_type::FONT_REDUCTION:
        this->font.setPixelSize(this->font.pixelSize() - 1);
        this->mtrs->setfont(this->font);
        break;
    case act_type::FONT_AMPLIFICATION:
        this->font.setPixelSize(this->font.pixelSize() + 1);
        this->mtrs->setfont(this->font);
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
