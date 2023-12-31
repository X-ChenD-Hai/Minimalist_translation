#ifndef MTRANSLATION_H
#define MTRANSLATION_H
#include "core/Translation.h"
#include "resourse/Resource.h"
#include "core/TransEngine.h"
#include "core/engines/Youdao.h"
#include "lib/frameless/framelesswindow.h"
#include "ui_MTranslation.h"
#include <QMainWindow>
#include <QApplication>
#include <QPixmap>
#include <QFile>
#include <QUrl>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QClipboard>
#include <QComboBox>
using namespace TranslateEngines;

class MTranslation : public CFramelessWindow
{
    Q_OBJECT

public slots:
    void on_pushButtonMax_clicked();
    void on_pushButtonMin_clicked();
    void on_pushButtonC_clicked();
    void trackClipboard_triggered(bool ck);
    void showTop_triggered(bool ck);
    void transInTime_triggered(bool ck);
    void translate();
    void loadEngine(TransEngine *_engine);

private:
    void setMenuBar(QMenuBar *menuBar);
    void setCentralWidget(QWidget *widget);
    void setWindowTitle(const QString &tittle);
    void setWindowIcon(const QIcon &icon);


private:
    inline void initWidget();
    inline void initConnection();
    inline void initAction();
    inline void initStyle();
    inline void initFrameWindow();
    inline void initSysIcon();
    inline void preRun();

public:
    MTranslation(QWidget *parent = nullptr);
    ~MTranslation();

private:
private:
    QWidget *w;
    QVBoxLayout *main;
    QPlainTextEdit *textEdit;
    QTextBrowser *textBro;
    QClipboard *sys_clipboard;
    QMenuBar *menubar;
    QComboBox *combox_f;
    QComboBox *combox_t;

    qint64 request_time;
    qint64 resply_time;
    qint64 start_time;

private:
    TransEngine *engine;
    Translation *trs;
    Ui_MTranslation *ui;
};
#endif // MTRANSLATION_H