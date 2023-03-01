#pragma once
#include <QWidget>
#include "mainwindow.h"
namespace Ui
{
    class titleBar;
}

class titleBar : public QWidget
{
    friend bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result);
    friend void MainWindow::setWindowTitle(char *title);
    friend void MainWindow::setWindowIcon(char *iconPath);
    Q_OBJECT

public:
    QMenu *m_menu = NULL;
    explicit titleBar(QWidget *parent = nullptr);
    ~titleBar();

public slots:
    void on_toolButton_2_clicked();

private:
    Ui::titleBar *ui = NULL;
    QWidget *pWidget = NULL;
    QPoint mPos;
    void initMenu();
    void initTitleBar();
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool toNativeEvent(const QByteArray &, void *message, long *result);
    void setTitle(char *title);
    void setIcon(char *iconPath);
};
