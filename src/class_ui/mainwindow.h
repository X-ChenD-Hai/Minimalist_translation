#pragma once
#include "mTrs.h"
#include <QWidget>
class titleBar;
class mTrs;
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    friend class titleBar;
    friend class mTrs;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setWindowTitle(char *title);
    void setWindowIcon(char *iconPath);

private:
    Ui::MainWindow *ui = NULL;
    mTrs *mtrs = NULL;
    QTimer *timer = NULL;
    QFont font;
    void initUI();
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void initAction();

private slots:
    void act_slot(bool chicked);
};
