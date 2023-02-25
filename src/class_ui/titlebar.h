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
    explicit titleBar(QWidget *parent = nullptr);
    ~titleBar();
public slots:
    void on_toolButton_2_clicked();

private:
    Ui::titleBar *ui;
    QPoint mPos;
    QWidget *pWidget = this->parentWidget();
    void initTitleBar();
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    bool toNativeEvent(const QByteArray&, void *message, long *result);
    void setTitle(char *title);
    void setIcon(char *iconPath);
};

