#pragma once
#include "ui_mTrs.h"
#include "getText.h"
#include <QMainWindow>
#include <QModelIndex>
#include <QFileSystemModel>

class mTrs : public QMainWindow
{
    Q_OBJECT;

public:
    mTrs(QFont from, QFont to, QWidget *parent = nullptr);
    mTrs(QWidget *parent = nullptr);
    ~mTrs();
public slots:
    void updateFromText();
    void updateToText();
    void setfont(QFont &font);
    void init_mTrs();
    void setEngine(bool);

private:
    Ui_mTrs *ui=NULL;
    getText *translater=NULL;
    QTimer *timer1=NULL;
    QTimer *timer2=NULL;
    QString *previousStr=NULL;
};