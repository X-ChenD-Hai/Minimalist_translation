#pragma once
#include"mTrs.h"                
#include <QWidget>
class titleBar;
class mTrs;
namespace Ui
{
    class MainWindow;
}

class MainWindow : public QWidget
{
    friend class titleBar;
    friend class mTrs;

    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setWindowTitle(char*title);
    void setWindowIcon(char*iconPath);

private:
    Ui::MainWindow *ui;
    mTrs *mtrs;
    QFont font;
    void initUI();
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
private slots:
    void setfont();
};

