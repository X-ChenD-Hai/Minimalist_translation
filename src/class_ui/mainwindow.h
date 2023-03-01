#pragma once
#include "mTrs.h"
#include <QWidget>
typedef struct Settings
{
    int Geometry[4];
    int fromedit_font_pixesize;
    int toedit_font_pixesize;
    int fromedit_height;
    int toedit_height;
    translation_engine translation_engine;
    bool window_top;
    bool cilpboard_tracking;

} Settings;

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
    Settings *settings;
    void writeInSettings();
    void loadSettings();
    void initUI();
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    void initAction();

private slots:
    void act_slot(bool chicked);
};
