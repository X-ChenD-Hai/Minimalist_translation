#ifndef MTRANSLATION_H
#define MTRANSLATION_H
#include "lib/core/Translation.h"
#include "lib/resourse/Resource.h"
#include "lib/core/engines/Youdao.h"
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
using namespace TranslateEngines;
class MTranslation : public QMainWindow
{
    Q_OBJECT

private:
    void initWidget();
    void initConnection();
    void initAction();
    void initStyle();

public:
    MTranslation(QWidget *parent = nullptr);
    ~MTranslation();

private:
    QWidget *w;
    QVBoxLayout *main;
    QPlainTextEdit* textEdit;
QTextBrowser* textBro;
private:
    Youdao *youdao;
    Translation *trs;
};
#endif // MTRANSLATION_H