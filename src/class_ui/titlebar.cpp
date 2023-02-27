#include "titlebar.h"
#include "ui_titlebar.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QToolButton>
#include <windows.h>
#include <windowsx.h>
#define D qDebug()

titleBar::titleBar(QWidget *parent) : QWidget(parent),
                                      ui(new Ui::titleBar)
{
    ui->setupUi(this);
    this->initTitleBar();
}

titleBar::~titleBar()
{
    delete ui;
}

void titleBar::initTitleBar()
{
    this->pWidget = this->parentWidget();
    QFont font;
    font.setPixelSize(25);
    font.setBold(true);
    this->ui->label_2->setFont(font);
    connect(this->ui->toolButton_3, QToolButton::clicked, qApp, QApplication::quit);
    connect(this->ui->toolButton, QToolButton::clicked, this->pWidget, QWidget::showMinimized);
    this->initMenu();
}

void titleBar::on_toolButton_2_clicked()
{
    this->mouseDoubleClickEvent(nullptr);
}

void titleBar::mouseDoubleClickEvent(QMouseEvent *event = nullptr)
{
    if (!pWidget->isMaximized())
        this->pWidget->showMaximized();
    else
        this->pWidget->showNormal();
    if (event)
        return QWidget::mouseDoubleClickEvent(event);
}

void titleBar::mousePressEvent(QMouseEvent *event)
{

    if (event->buttons() == Qt::MouseButton::LeftButton)
        this->mPos = event->pos();
}

void titleBar::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pPoint = event->globalPos() - this->mPos;
    if (pPoint != this->pWidget->pos() && pWidget->pos() != QPoint(0, 0) && pPoint != QPoint(16, 16))
        this->pWidget->move(pPoint);
}

bool titleBar::toNativeEvent(const QByteArray &, void *message, long *result)
{
    MSG *msg = (MSG *)message;
    switch (msg->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(msg->lParam) - this->pWidget->frameGeometry().x();
        int yPos = GET_Y_LPARAM(msg->lParam) - this->pWidget->frameGeometry().y();
        if (this->pWidget->childAt(xPos, yPos) == 0)
        {
            *result = HTCAPTION;
        }
        else
        {
            return false;
        }
        if (xPos > 0 && xPos < 8)
            *result = HTLEFT;
        if (xPos > (this->pWidget->width() - 8) && xPos < (this->pWidget->width() - 0))
            *result = HTRIGHT;
        if (yPos > 0 && yPos < 8)
            *result = HTTOP;
        if (yPos > (this->pWidget->height() - 8) && yPos < (this->pWidget->height() - 0))
            *result = HTBOTTOM;
        if (xPos > 18 && xPos < 22 && yPos > 18 && yPos < 22)
            *result = HTTOPLEFT;
        if (xPos > (this->pWidget->width() - 22) && xPos < (this->pWidget->width() - 18) && yPos > 18 && yPos < 22)
            *result = HTTOPRIGHT;
        if (xPos > 18 && xPos < 22 && yPos > (this->pWidget->height() - 22) && yPos < (this->pWidget->height() - 18))
            *result = HTBOTTOMLEFT;
        if (xPos > (this->pWidget->width() - 22) && xPos < (this->pWidget->width() - 18) && yPos > (this->pWidget->height() - 22) && yPos < (this->pWidget->height() - 18))
            *result = HTBOTTOMRIGHT;
        return true;
    }
    return false;
}

void titleBar::setTitle(char *title)
{
    this->ui->label_2->setText(title);
    this->pWidget->setWindowTitle(title);
}

void titleBar::setIcon(char *iconPath)
{
    this->ui->label->setPixmap(QPixmap(iconPath));
    this->pWidget->setWindowIcon(QIcon(iconPath));
}

void titleBar::initMenu()
{
    QToolButton *&btMenu = this->ui->toolButton_4;
    btMenu->setIcon(QIcon("resource\\icon\\符号-菜单.png"));
    btMenu->setIconSize(QSize(40, 40));
    btMenu->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btMenu->setPopupMode(QToolButton::InstantPopup);
    btMenu->setArrowType(Qt::ArrowType::NoArrow);

    this->m_menu = new QMenu(btMenu);
    btMenu->setMenu(this->m_menu);
}
