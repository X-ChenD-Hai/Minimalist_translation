/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <titlebar.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QVBoxLayout *verticalLayout2;
    titleBar *title_bar;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(400, 306);
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout2 = new QVBoxLayout(MainWindow);
        verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
        verticalLayout2->setSizeConstraint(QLayout::SetDefaultConstraint);
        title_bar = new titleBar(MainWindow);
        title_bar->setObjectName(QString::fromUtf8("title_bar"));
        title_bar->setMaximumSize(QSize(16777215, 40));

        verticalLayout2->addWidget(title_bar);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        verticalLayout2->addLayout(verticalLayout);


        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
