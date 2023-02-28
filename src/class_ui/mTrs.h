#pragma once
#include "ui_mTrs.h"
#include "getText.h"
#include <QMainWindow>
#include <QModelIndex>
#include <QFileSystemModel>
#include <QClipboard>
#include<QMap>

class mTrs : public QMainWindow
{
    Q_OBJECT;

public:
    mTrs(QFont from, QFont to, QWidget *parent = nullptr);
    mTrs(QWidget *parent = nullptr);
    ~mTrs();
    QMap<QString, int> getFont();
public slots:
    void updateFromText();
    void updateToText();
    void setfont(QFont &font);
    void init_mTrs();
    void setEngine(bool);
    void setCilpboardTracking(bool);

private:
    Ui_mTrs *ui = NULL;
    getText *translater = NULL;
    QTimer *timer1 = NULL; /* 尝试读取翻译结果的间隔 */
    QTimer *timer2 = NULL; /* 删除部分内容时发起请求的间隔 */
    QString *previousStr = NULL;
    QClipboard *sysclipboard = NULL;
};