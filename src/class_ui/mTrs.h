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
    mTrs(QWidget *parent = nullptr);
    ~mTrs();
public slots:
    void updateFromText();
    void updateToText();
    void setfont(QFont &font);

private:
    Ui_mTrs *ui;
    getText *translater;
    QTimer *timer;
};