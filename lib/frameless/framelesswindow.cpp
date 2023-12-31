#include "framelesswindow.h"
#include <QApplication>
#include <QPoint>
#include <QSize>
#include <QMouseEvent>

#ifdef Q_OS_WIN

#include <windows.h>
#include <WinUser.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <objidl.h> // Fixes error C2504: 'IUnknown' : base class undefined
#include <gdiplus.h>
// #include <GdiPlusColor.h>
#include <QDebug>
#pragma comment(lib, "Dwmapi.lib") // Adds missing library, fixes error LNK2019: unresolved external symbol __imp__DwmExtendFrameIntoClientArea
#pragma comment(lib, "user32.lib")

BtnHelper::BtnHelper(QObject *parent) : QObject(parent),
                                        mBtn(nullptr),
                                        isInBtnRect(false), isInBtnRectOld(false),
                                        isLeave(false),
                                        isPress(false), isRealease(false),
                                        isMoveInClientFirst(false), mIsValid(false) {}

BtnHelper::~BtnHelper()
{
    mBtn = nullptr;
}

void BtnHelper::setAbstractButton(QAbstractButton *btn)
{
    mBtn = btn;
    mIsValid = true;
}

void BtnHelper::setInRectBtnFlag(bool _isInRectBtn)
{
    isInBtnRect = _isInRectBtn;
}
QAbstractButton *BtnHelper::AbstractButton()
{
    return mBtn;
}

bool BtnHelper::mousePressDeal(qintptr *result)
{
    *result = 0;
    if (this->mIsValid)
    {
        this->isMoveInClientFirst = true;
        this->isPress = true;
        this->sendMousePress();
        return true; // 截获信息，交由自己处理
    }
    return false; // 信息交由win32处理
}

// isNClient  判断是否不在客户区释放
bool BtnHelper::mouseRealseDeal(qintptr *result, bool isNClient)
{
    *result = 0;
    if (this->mIsValid)
    {
        if (isPress)
        {
            isPress = false;
            if (isNClient)
            {
                sendMouseRelease(isInBtnRect);
                // 为了防止按钮仅释放不移动，导致leave异常的情况，这里发送释放事件的同时，发送鼠标离开事件
                isLeave = true; // 重新设置标志位
                isInBtnRect = false;
                isInBtnRectOld = false;
                sendMouseLeave();
                return true; // 截获信息，交由自己处理
            }
            else
            {
                if (isInBtnRect) // 非客户区释放
                {
                    // 模拟鼠标双击
                    sendMousePress();
                    sendMouseRelease(true);
                }
            }
        }
    }
    return false; // 信息交由win32处理
}
void BtnHelper::mouseEnterLeaveDeal()
{
    if (this->mIsValid)
    {
        if (isLeave)
        { // 如果鼠标在自己的区域释放 isLeave mouse离开,
            isLeave = false;
            return;
        }
        if (isInBtnRect != isInBtnRectOld)
        { // 当前状态与上次状态不一致，代表鼠标进出该区域
            isInBtnRectOld = isInBtnRect;
            if (isInBtnRect)
            { // 鼠标进入该区域
                sendMouseEnter();
            }
            else
            { // 鼠标离开该区域
                sendMouseLeave();
            }
        }
    }

    isInBtnRect = false;
}
void BtnHelper::sendMouseEnter()
{
    QEvent event(QEvent::Enter);
    QApplication::sendEvent(mBtn, &event);
    mBtn->update(); // 按钮进入，样式发生改变，需要更新一下按钮样式
}
void BtnHelper::sendMouseLeave()
{
    QEvent event(QEvent::Leave);
    QApplication::sendEvent(mBtn, &event);
    mBtn->update(); // 按钮进入，样式发生改变，需要更新一下按钮样式
}
void BtnHelper::sendMousePress()
{
    QMouseEvent event(QEvent::MouseButtonPress, QPointF(0, 0), QPointF(0, 0), QPointF(0, 0), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier, Qt::MouseEventNotSynthesized);
    QApplication::sendEvent(mBtn, &event);
}
void BtnHelper::sendMouseRelease(bool isInBtnRect)
{
    if (isInBtnRect)
    { // 发送鼠标在按钮内释放的信号
        // QMouseEvent event(QEvent::MouseButtonRelease, QPointF(0, 0), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QMouseEvent event(QEvent::MouseButtonRelease, QPointF(0, 0), QPointF(0, 0), QPointF(0, 0), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);

        QApplication::sendEvent(mBtn, &event);
    }
    else
    { // 发送鼠标不在按钮内释放的信号
        QMouseEvent event(QEvent::MouseButtonRelease, QPointF(-1, -1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(mBtn, &event);
    }
}

CFramelessWindow::CFramelessWindow(QWidget *parent)
    : QMainWindow(parent),
      m_titlebar(Q_NULLPTR),
      m_borderWidth(5),
      m_bJustMaximized(false),
      m_bResizeable(true),
      mMinBtnHelper(new BtnHelper),
      mMaxBtnHelper(new BtnHelper),
      mCloseBtnHelper(new BtnHelper)
{

    setWindowFlags(windowFlags() | Qt::Window | Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);

    setResizeable(m_bResizeable);
}

void CFramelessWindow::setResizeable(bool resizeable)
{
    bool visible = isVisible();
    m_bResizeable = resizeable;
    if (m_bResizeable)
    {
        setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
        //        setWindowFlag(Qt::WindowMaximizeButtonHint);

        // 此行代码可以带回Aero效果，同时也带回了标题栏和边框,在nativeEvent()会再次去掉标题栏
        //
        // this line will get titlebar/thick frame/Aero back, which is exactly what we want
        // we will get rid of titlebar and thick frame again in nativeEvent() later
        HWND hwnd = (HWND)this->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
        ::SetWindowLong(hwnd, GWL_STYLE, style | WS_MAXIMIZEBOX | WS_THICKFRAME | WS_CAPTION);
    }
    else
    {
        setWindowFlags(windowFlags() & ~Qt::WindowMaximizeButtonHint);
        //        setWindowFlag(Qt::WindowMaximizeButtonHint,false);

        HWND hwnd = (HWND)this->winId();
        DWORD style = ::GetWindowLong(hwnd, GWL_STYLE);
        ::SetWindowLong(hwnd, GWL_STYLE, style & ~WS_MAXIMIZEBOX & ~WS_CAPTION);
    }

    // 保留一个像素的边框宽度，否则系统不会绘制边框阴影
    // win32接口内部判断top上有1像素非客户区的扩展，所以优先级更高。
    // we better left 1 piexl width of border untouch, so OS can draw nice shadow around it
    const MARGINS shadow = {1, 1, 0, 1};
    DwmExtendFrameIntoClientArea(HWND(winId()), &shadow);

    setVisible(visible);
}

void CFramelessWindow::setResizeableAreaWidth(int width)
{
    if (1 > width)
        width = 1;
    m_borderWidth = width;
}

void CFramelessWindow::setTitleBar(QWidget *titlebar)
{
    m_titlebar = titlebar;
    if (!titlebar)
        return;
    connect(titlebar, SIGNAL(destroyed(QObject *)), this, SLOT(onTitleBarDestroyed()));
}

void CFramelessWindow::setBtnMin(QAbstractButton *btnMin)
{
    mMinBtnHelper->setAbstractButton(btnMin);
}

void CFramelessWindow::setBtnMax(QAbstractButton *btnMax)
{
    mMaxBtnHelper->setAbstractButton(btnMax);
}

void CFramelessWindow::setBtnClose(QAbstractButton *btnClose)
{
    mCloseBtnHelper->setAbstractButton(btnClose);
}

void CFramelessWindow::onTitleBarDestroyed()
{
    if (m_titlebar == QObject::sender())
    {
        m_titlebar = Q_NULLPTR;
    }
}

void CFramelessWindow::addIgnoreWidget(QWidget *widget)
{
    if (!widget)
        return;
    if (m_whiteList.contains(widget))
        return;
    m_whiteList.append(widget);
}

bool CFramelessWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
// Workaround for known bug -> check Qt forum : https://forum.qt.io/topic/93141/qtablewidget-itemselectionchanged/13
#if (QT_VERSION == QT_VERSION_CHECK(5, 11, 1))
    MSG *msg = *reinterpret_cast<MSG **>(message);
#else
    MSG *msg = reinterpret_cast<MSG *>(message);
#endif

    switch (msg->message)
    {
    case WM_NCCALCSIZE:
    {
        NCCALCSIZE_PARAMS &params = *reinterpret_cast<NCCALCSIZE_PARAMS *>(msg->lParam);
        if (params.rgrc[0].top != 0)
            params.rgrc[0].top -= 1;

        // this kills the window frame and title bar we added with WS_THICKFRAME and WS_CAPTION
        *result = WVR_REDRAW;
        return true;
    }
    case WM_LBUTTONUP:
        //        qDebug() << " ==========   WM_LBUTTONUP   ========== "   <<  countAll++;
        mMinBtnHelper->mouseRealseDeal(result, false);
        mMaxBtnHelper->mouseRealseDeal(result, false);
        mCloseBtnHelper->mouseRealseDeal(result, false);
        return false;
        // 鼠标在客户区移动
    case WM_MOUSEMOVE:
    {
        // qDebug() << " ==========   WM_MOUSEMOVE   ========== "   <<  countAll++;
        *result = 0;
        // 鼠标按下的情况下，第一次从按钮移入客户区，发送鼠标释放的事件
        if (mMinBtnHelper->isFirstMove())
        {
            mMinBtnHelper->setMoveInClientFirst(false);
            mMinBtnHelper->sendMouseRelease(false);
            // qDebug() << " ==========   MOVE  mMinBtnHelper  MOVE   ========== "   <<  countAll++;
        }
        if (mMaxBtnHelper->isFirstMove())
        {
            mMaxBtnHelper->setMoveInClientFirst(false);
            mMaxBtnHelper->sendMouseRelease(false);
            // qDebug() << " ==========   MOVE    mMaxBtnHelper   MOVE   ========== "   <<  countAll++;
        }
        if (mCloseBtnHelper->isFirstMove())
        {
            mCloseBtnHelper->setMoveInClientFirst(false);
            mCloseBtnHelper->sendMouseRelease(false);
            // qDebug() << " ==========   MOVE  mCloseBtnHelper  MOVE   ========== "   <<  countAll++;
        }

        mMinBtnHelper->mouseEnterLeaveDeal();
        mMaxBtnHelper->mouseEnterLeaveDeal();
        mCloseBtnHelper->mouseEnterLeaveDeal();

        // x,y 为鼠标在窗口客户区的坐标
        long x = GET_X_LPARAM(msg->lParam);
        long y = GET_Y_LPARAM(msg->lParam);
        // support highdpi
        double dpr = this->devicePixelRatioF();
        QPoint pos = QPoint(x / dpr, y / dpr);
        if (!m_titlebar->rect().contains(pos))
            return false;

        QWidget *child = m_titlebar->childAt(pos);
        if (child)
        {
            if (m_whiteList.contains(child))
            {
                *result = HTCAPTION;
                return true;
            }
            if (mMinBtnHelper->isValid())
            { // 鼠标位于标题栏中最小化按钮
                if (mMinBtnHelper->AbstractButton() == child)
                {
                    mMinBtnHelper->setInRectBtnFlag(true);
                }
            }
            if (mMaxBtnHelper->isValid())
            { // 鼠标位于标题栏中最大化
                if (mMaxBtnHelper->AbstractButton() == child)
                {
                    mMaxBtnHelper->setInRectBtnFlag(true);
                }
            }
            if (mCloseBtnHelper->isValid())
            { // 鼠标位于标题栏中关闭按钮
                if (mCloseBtnHelper->AbstractButton() == child)
                {
                    mCloseBtnHelper->setInRectBtnFlag(true);
                }
            }
        }
        return false;
    }

    // 非客户端区域鼠标左键按下
    case WM_NCLBUTTONDOWN:
    {
        //        qDebug() << "**********   WM_NCLBUTTONDOWN   ****************"   <<  countAll++;
        // 处理鼠标事件
        mMinBtnHelper->mouseEnterLeaveDeal();
        mMaxBtnHelper->mouseEnterLeaveDeal();
        mCloseBtnHelper->mouseEnterLeaveDeal();
        if (msg->wParam == HTMINBUTTON)
        { // 最小化按钮
            if (mMinBtnHelper->mousePressDeal(result))
                return true;
        }
        else if (msg->wParam == HTMAXBUTTON)
        { // 最大化按钮
            if (mMaxBtnHelper->mousePressDeal(result))
                return true;
        }
        else if (msg->wParam == HTCLOSE)
        { // 关闭按钮
            if (mCloseBtnHelper->mousePressDeal(result))
                return true;
        }
        return false; //
    }
    // 非客户端区域鼠标左键释放
    case WM_NCLBUTTONUP:
    {
        //        qDebug() << "=========   WM_NCLBUTTONUP   ****************"   <<  countAll++;
        if (msg->wParam == HTMINBUTTON)
        { // 最小化按钮
            if (mMinBtnHelper->mouseRealseDeal(result))
                return true;
        }
        else if (msg->wParam == HTMAXBUTTON)
        { // 最大化按钮
            if (mMaxBtnHelper->mouseRealseDeal(result))
                return true;
        }
        else if (msg->wParam == HTCLOSE)
        { // 关闭按钮
            if (mCloseBtnHelper->mouseRealseDeal(result))
                return true;
        }

        mMinBtnHelper->releaseFlag();
        mMaxBtnHelper->releaseFlag();
        mCloseBtnHelper->releaseFlag();
        return false;
    }
    case WM_NCHITTEST:
    {
        // qDebug() << "**********   WM_NCHITTEST   ****************"   <<  countAll++;
        mMinBtnHelper->mouseEnterLeaveDeal();
        mMaxBtnHelper->mouseEnterLeaveDeal();
        mCloseBtnHelper->mouseEnterLeaveDeal();

        *result = 0;
        const LONG border_width = m_borderWidth;
        RECT winrect;
        GetWindowRect(HWND(winId()), &winrect);

        // x,y 为鼠标在屏幕的坐标
        long x = GET_X_LPARAM(msg->lParam);
        long y = GET_Y_LPARAM(msg->lParam);

        if (m_bResizeable)
        {

            bool resizeWidth = minimumWidth() != maximumWidth();
            bool resizeHeight = minimumHeight() != maximumHeight();

            if (resizeWidth)
            {
                // left border
                if (x >= winrect.left && x < winrect.left + border_width)
                {
                    *result = HTLEFT;
                }
                // right border
                if (x < winrect.right && x >= winrect.right - border_width)
                {
                    *result = HTRIGHT;
                }
            }
            if (resizeHeight)
            {
                // bottom border
                if (y < winrect.bottom && y >= winrect.bottom - border_width)
                {
                    *result = HTBOTTOM;
                }
                // top border
                if (y >= winrect.top && y < winrect.top + border_width)
                {
                    *result = HTTOP;
                }
            }
            if (resizeWidth && resizeHeight)
            {
                // bottom left corner
                if (x >= winrect.left && x < winrect.left + border_width &&
                    y < winrect.bottom && y >= winrect.bottom - border_width)
                {
                    *result = HTBOTTOMLEFT;
                }
                // bottom right corner
                if (x < winrect.right && x >= winrect.right - border_width &&
                    y < winrect.bottom && y >= winrect.bottom - border_width)
                {
                    *result = HTBOTTOMRIGHT;
                }
                // top left corner
                if (x >= winrect.left && x < winrect.left + border_width &&
                    y >= winrect.top && y < winrect.top + border_width)
                {
                    *result = HTTOPLEFT;
                }
                // top right corner
                if (x < winrect.right && x >= winrect.right - border_width &&
                    y >= winrect.top && y < winrect.top + border_width)
                {
                    *result = HTTOPRIGHT;
                }
            }
        }
        if (0 != *result)
            return true;

        //*result still equals 0, that means the cursor locate OUTSIDE the frame area
        // but it may locate in titlebar area
        if (!m_titlebar)
            return false;

        // support highdpi
        double dpr = this->devicePixelRatioF();
        QPoint pos = m_titlebar->mapFromGlobal(QPoint(x / dpr, y / dpr));

        if (!m_titlebar->rect().contains(pos))
            return false;
        QWidget *child = m_titlebar->childAt(pos);
        if (!child)
        {
            *result = HTCAPTION;
            return true;
        }
        else
        {
            if (m_whiteList.contains(child))
            {
                *result = HTCAPTION;
                return true;
            }
            if (mMinBtnHelper->isValid())
            { // 鼠标位于标题栏中最小化按钮
                if (mMinBtnHelper->AbstractButton() == child)
                {
                    mMinBtnHelper->setInRectBtnFlag(true);
                    *result = HTMINBUTTON; // 最小化
                    return true;
                }
            }
            if (mMaxBtnHelper->isValid())
            { // 鼠标位于标题栏中最大化
                if (mMaxBtnHelper->AbstractButton() == child)
                {
                    mMaxBtnHelper->setInRectBtnFlag(true);
                    *result = HTMAXBUTTON; // 最大化
                    return true;
                }
            }
            if (mCloseBtnHelper->isValid())
            { // 鼠标位于标题栏中关闭按钮
                if (mCloseBtnHelper->AbstractButton() == child)
                {
                    mCloseBtnHelper->setInRectBtnFlag(true);
                    *result = HTCLOSE; // 关闭
                    return true;
                }
            }
        }
        return false;
    } // end case WM_NCHITTEST
    case WM_GETMINMAXINFO:
    {
        if (::IsZoomed(msg->hwnd))
        {
            RECT frame = {0, 0, 0, 0};
            AdjustWindowRectEx(&frame, WS_OVERLAPPEDWINDOW, FALSE, 0);

            // record frame area data
            double dpr = this->devicePixelRatioF();

            m_frames.setLeft(abs(frame.left) / dpr + 0.5);
            m_frames.setTop(abs(frame.bottom) / dpr + 0.5);
            m_frames.setRight(abs(frame.right) / dpr + 0.5);
            m_frames.setBottom(abs(frame.bottom) / dpr + 0.5);

            QMainWindow::setContentsMargins(m_frames.left() + m_margins.left(),
                                            m_frames.top() + m_margins.top(),
                                            m_frames.right() + m_margins.right(),
                                            m_frames.bottom() + m_margins.bottom());
            m_bJustMaximized = true;
        }
        else
        {
            if (m_bJustMaximized)
            {
                QMainWindow::setContentsMargins(m_margins);
                m_frames = QMargins();
                m_bJustMaximized = false;
            }
        }
        return false;
    }
    default:
        return QMainWindow::nativeEvent(eventType, message, result);
    }
}

void CFramelessWindow::setContentsMargins(const QMargins &margins)
{
    QMainWindow::setContentsMargins(margins + m_frames);
    m_margins = margins;
}
void CFramelessWindow::setContentsMargins(int left, int top, int right, int bottom)
{
    QMainWindow::setContentsMargins(left + m_frames.left(),
                                    top + m_frames.top(),
                                    right + m_frames.right(),
                                    bottom + m_frames.bottom());
    m_margins.setLeft(left);
    m_margins.setTop(top);
    m_margins.setRight(right);
    m_margins.setBottom(bottom);
}
QMargins CFramelessWindow::contentsMargins() const
{
    QMargins margins = QMainWindow::contentsMargins();
    margins -= m_frames;
    return margins;
}
void CFramelessWindow::getContentsMargins(int *left, int *top, int *right, int *bottom) const
{
    auto marg = QMainWindow::contentsMargins();
    *left = marg.left();
    *right = marg.right();
    *top = marg.top();
    *bottom = marg.bottom();
    if (!(left && top && right && bottom))
        return;
    if (isMaximized())
    {
        *left -= m_frames.left();
        *top -= m_frames.top();
        *right -= m_frames.right();
        *bottom -= m_frames.bottom();
    }
}
QRect CFramelessWindow::contentsRect() const
{
    QRect rect = QMainWindow::contentsRect();
    int width = rect.width();
    int height = rect.height();
    rect.setLeft(rect.left() - m_frames.left());
    rect.setTop(rect.top() - m_frames.top());
    rect.setWidth(width);
    rect.setHeight(height);
    return rect;
}
void CFramelessWindow::showFullScreen()
{
    if (isMaximized())
    {
        QMainWindow::setContentsMargins(m_margins);
        m_frames = QMargins();
    }
    QMainWindow::showFullScreen();
}

#endif // Q_OS_WIN
