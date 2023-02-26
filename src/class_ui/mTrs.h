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

private:
    Ui_mTrs *ui;
    getText *translater;
    QTimer *timer1;
    QTimer *timer2;
    QString *previousStr = new QString("");
};