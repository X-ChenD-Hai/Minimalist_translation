#include "MTranslation.h"
#include "QHotkey"
#include <windows.h>
#include <QTextDocument>
#include <QToolButton>
#include <QVariant>
#include <QDateTime>
#include <QSplitterHandle>
#include <QMouseEvent>
#include <QMenu>
#include <QTimer>
#include <QSystemTrayIcon>
using namespace TranslateEngines;
// GLOBAL_TYPPE
struct
{
    QAction *showTop,
        *trackClipboard,
        *translate,
        *quit,
        *showhide,
        *transInTime;
} g_act;
struct
{
    QMenu *options;
} g_menu;

struct
{
    QHotkey *showhide;
} g_hotKeys;

QTimer g_timer;
// GLOBAL_FUNCTION

// 将窗口置顶
void G_setWindowTopmost(HWND hWnd)
{
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

// 取消窗口置顶
void G_setWindowNotTopmost(HWND hWnd)
{
    SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}
// GLOBAL_VARIATE
QStringList::iterator G_find(QStringList::iterator f, QStringList::iterator t, const QString &_s)
{
    for (; f != t; f++)
        if (*f == _s)
            return f;
    return t;
}
// INIT_MEMBER_FUNC
inline void MTranslation::initAction()
{
    g_act.showTop = new QAction(tr("置顶窗口"), this);
    g_act.showTop->setObjectName("showTop");
    g_act.showTop->setCheckable(true);
    g_act.trackClipboard = new QAction(tr("跟踪剪贴板"), this);
    g_act.trackClipboard->setObjectName("trackClipboard");
    g_act.trackClipboard->setCheckable(true);
    g_act.transInTime = new QAction(tr("即时翻译"), this);
    g_act.transInTime->setObjectName("transInTime");
    g_act.transInTime->setCheckable(true);
    g_act.translate = new QAction(tr("翻译"), this);
    g_act.translate->setObjectName("translate");
    g_act.quit = new QAction(tr("退出"), this);
    g_act.quit->setObjectName("quit");
    g_act.showhide = new QAction(tr("隐藏窗口"), this);
    g_act.showhide->setObjectName("showhide");

    g_act.translate->setShortcut(QKeySequence("ctrl+T"));
    g_act.quit->setShortcut(QKeySequence("ctrl+Q"));
    g_act.showhide->setShortcut(QKeySequence("alt+t"));

    g_hotKeys.showhide = new QHotkey(QKeySequence("alt+t"), true, this);
}

inline void MTranslation::initWidget()
{
    w = new QWidget(this);
    trs = new Translation(this);
    sys_clipboard = QApplication::clipboard();
    textEdit = new QPlainTextEdit(this);
    textBro = new QTextBrowser(this);
    auto spliter_text = new QSplitter(this);
    QToolButton *btn = new QToolButton(this);
    menubar = new QMenuBar(this);

    combox_f = new QComboBox(this);
    combox_t = new QComboBox(this);

    g_timer.start(500);
    connect(&g_timer, &QTimer::timeout, [&]()
            {
                auto p = mapFromGlobal(QCursor::pos());
                if (ui->widgetTittleBar->rect().contains(p))
                {if(menubar->isHidden())
                menubar->show();}
                else
                if(!menubar->isHidden())
                menubar->hide(); });

    g_menu.options = menubar->addMenu("选项");
    g_menu.options->addAction(g_act.showTop);
    g_menu.options->addAction(g_act.trackClipboard);
    g_menu.options->addAction(g_act.transInTime);
    g_menu.options->addSeparator();
    g_menu.options->addAction(g_act.translate);
    g_menu.options->addSeparator();
    g_menu.options->addAction(g_act.showhide);
    g_menu.options->addAction(g_act.quit);

    g_menu.options->setToolTipsVisible(true);

    setMenuBar(menubar);

    main = new QVBoxLayout(w);
    auto boottom = new QHBoxLayout;
    textEdit->setObjectName("textEdit");
    textBro->setObjectName("textBro");
    spliter_text->setOrientation(Qt::Horizontal);
    btn->setDefaultAction(g_act.translate);
    spliter_text->addWidget(textEdit);
    spliter_text->addWidget(textBro);
    main->addWidget(spliter_text, 10);
    boottom->addWidget(combox_f, 1);
    boottom->addWidget(btn, 0);
    boottom->addWidget(combox_t, 1);
    main->addLayout(boottom, 0);
    setCentralWidget(w);
    resize(600, 500);
}

inline void MTranslation::initStyle()
{
    QString str = ":qss/main.qss";
    QFile f(str, this);
    f.open(QIODevice::Text | QIODevice::ReadOnly);
    if (f.isOpen())
    {
        auto s = f.readAll();
        qApp->setStyleSheet(s);
    }
}

inline void MTranslation::initFrameWindow()
{
    addIgnoreWidget(ui->tittleWidget);
    addIgnoreWidget(ui->labelWindowIcon);
    setTitleBar(ui->widgetTittleBar);
    setBtnMax(ui->pushButtonMax);
    setBtnMin(ui->pushButtonMin);
    setBtnClose(ui->pushButtonC);
    setWindowIcon(QIcon(R"(:icons/main.ico)"));
}

inline void MTranslation::initSysIcon()
{

    //    定义托盘图标，并设置父控件为mainwindow
    QSystemTrayIcon *icon = new QSystemTrayIcon(this);
    //    挑一个顺眼的icon，路径从qrc中复制即可
    icon->setIcon(QIcon(":/icons/main.ico"));

    icon->setContextMenu(g_menu.options);

    //    设置单击显示主界面
    connect(icon, &QSystemTrayIcon::activated, [=](QSystemTrayIcon::ActivationReason r)
            {
        if (r == QSystemTrayIcon::ActivationReason::Trigger)
            emit g_act.showhide->triggered(); });
    //    显示托盘图标
    icon->show();
}

inline void MTranslation::initConnection()
{
    connect(g_act.showTop, &QAction::triggered, this, showTop_triggered);
    connect(g_act.trackClipboard, &QAction::triggered, this, trackClipboard_triggered);
    connect(g_act.transInTime, &QAction::triggered, this, transInTime_triggered);
    connect(g_act.translate, &QAction::triggered, this, translate);
    connect(g_act.quit, &QAction::triggered, [&]()
            { QCoreApplication::quit(); });
    connect(g_act.showhide, &QAction::triggered, [&]()
            {
        if (isHidden())
        {
            show();
            g_act.showhide->setText("隐藏窗口");
        }
        else
        {
            
                hide();
                g_act.showhide->setText("显示主窗口");
            
        } });
    connect(g_hotKeys.showhide, &QHotkey::activated, g_act.showhide, &QAction::trigger);

    connect(trs, &Translation::successed, textBro, &QTextBrowser::setPlainText);
    connect(combox_f, &QComboBox::currentTextChanged, [&](const QString &str)
            { engine->__from = engine->supportfrom()[str]; });
    connect(combox_t, &QComboBox::currentTextChanged, [&](const QString &str)
            { engine->__to = engine->supportto()[str]; });
}

inline void MTranslation::preRun()
{
    start_time = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    Translation::loadCache("a.cache");
    auto engine = new Youdao("74b31a9fb7b2c903", "0xlLu49lEWbe13Oel18peX69wZ7OYTj8");
    loadEngine(engine);
}

// MEMBER_FUNCTION
MTranslation::MTranslation(QWidget *parent)
    : CFramelessWindow(parent), ui(new Ui_MTranslation)
{
    Resource re;
    ui->setupUi(this);
    initStyle();
    initAction();
    initWidget();
    initFrameWindow();
    initConnection();
    initSysIcon();
    preRun();
    update();
}

MTranslation::~MTranslation()
{
    Translation::saveCache("a.cache");
}

void MTranslation::setWindowTitle(const QString &tittle)
{
    QMainWindow::setWindowTitle(tittle);
}

void MTranslation::setMenuBar(QMenuBar *_menubar)
{
    QWidget *mw = new QWidget(this);
    auto hb = new QHBoxLayout(mw);
    _menubar->setObjectName("menubar");
    hb->setContentsMargins(3, 6, 0, 0);
    mw->setMaximumSize(_menubar->sizeHint());
    hb->setMenuBar(_menubar);
    qobject_cast<QHBoxLayout *>(ui->widgetTittleBar->layout())->insertWidget(1, mw, 2);
}

void MTranslation::setWindowIcon(const QIcon &icon)
{
    QMainWindow::setWindowIcon(icon);

    ui->labelWindowIcon->setPixmap(QMainWindow::windowIcon().pixmap(30, 30));
}

// SLOTS
void MTranslation::translate()
{
    trs->update(textEdit->toPlainText());
    request_time = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
}

void MTranslation::loadEngine(TransEngine *_engine)
{
    engine = _engine;
    auto lf = engine->supportfrom().keys();
    lf.erase(G_find(lf.begin(), lf.end(), engine->defaultFrom()));
    auto lt = engine->supportto().keys();
    lt.erase(G_find(lt.begin(), lt.end(), engine->defaultTo()));
    combox_f->addItem(engine->defaultFrom());
    combox_t->addItem(engine->defaultTo());
    combox_f->addItems(lf);
    combox_t->addItems(lt);
    combox_t->setCurrentIndex(0);
    combox_f->setCurrentIndex(0);
    trs->setEngine(engine);
}

void MTranslation::transInTime_triggered(bool ck)
{
    if (ck)
        connect(textEdit, &QPlainTextEdit::textChanged, this, translate);
    else
        disconnect(textEdit, &QPlainTextEdit::textChanged, this, translate);
}

void MTranslation::showTop_triggered(bool ck)
{
#ifdef Q_OS_WIN
    if (ck)
        G_setWindowTopmost(reinterpret_cast<HWND>(winId()));
    else
        G_setWindowNotTopmost(reinterpret_cast<HWND>(winId()));
#endif
}

void MTranslation::trackClipboard_triggered(bool ck)
{
    if (ck)
        connect(sys_clipboard, &QClipboard::dataChanged, [&]()
                {
        QString text=sys_clipboard->text();
        if(!text.isEmpty())
        textEdit->setPlainText(text); });
    else
        disconnect(sys_clipboard, &QClipboard::dataChanged, nullptr, nullptr);
}

void MTranslation::on_pushButtonC_clicked()
{
    hide();
}

void MTranslation::setCentralWidget(QWidget *widget)
{
    widget->setWindowFlags(Qt::WindowFlags::enum_type::FramelessWindowHint);
    auto layout = ui->mainWidget->layout();
    if (!layout)
    {
        ui->mainWidget->setLayout(new QHBoxLayout);
        layout = ui->mainWidget->layout();
        layout->setContentsMargins(0, 0, 0, 0);
    }
    layout->addWidget(widget);
}

void MTranslation::on_pushButtonMin_clicked()
{
    showMinimized();
}

void MTranslation::on_pushButtonMax_clicked()
{
    if (isMaximized())
        showNormal();
    else
        showMaximized();
}
