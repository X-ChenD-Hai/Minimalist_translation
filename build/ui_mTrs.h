/********************************************************************************
** Form generated from reading UI file 'mTrs.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MTRS_H
#define UI_MTRS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mTrs
{
public:
    QAction *action123;
    QAction *act_add;
    QAction *act_minus;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QTextEdit *toEdit;
    QTextEdit *fromEdit;

    void setupUi(QMainWindow *mTrs)
    {
        if (mTrs->objectName().isEmpty())
            mTrs->setObjectName(QString::fromUtf8("mTrs"));
        mTrs->resize(800, 600);
        action123 = new QAction(mTrs);
        action123->setObjectName(QString::fromUtf8("action123"));
        act_add = new QAction(mTrs);
        act_add->setObjectName(QString::fromUtf8("act_add"));
        act_minus = new QAction(mTrs);
        act_minus->setObjectName(QString::fromUtf8("act_minus"));
        centralwidget = new QWidget(mTrs);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setLineWidth(0);
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(0);
        toEdit = new QTextEdit(splitter);
        toEdit->setObjectName(QString::fromUtf8("toEdit"));
        toEdit->setMinimumSize(QSize(100, 100));
        splitter->addWidget(toEdit);
        fromEdit = new QTextEdit(splitter);
        fromEdit->setObjectName(QString::fromUtf8("fromEdit"));
        fromEdit->setMinimumSize(QSize(100, 100));
        splitter->addWidget(fromEdit);

        verticalLayout->addWidget(splitter);

        mTrs->setCentralWidget(centralwidget);

        retranslateUi(mTrs);
        QObject::connect(action123, SIGNAL(triggered()), mTrs, SLOT(close()));

        QMetaObject::connectSlotsByName(mTrs);
    } // setupUi

    void retranslateUi(QMainWindow *mTrs)
    {
        mTrs->setWindowTitle(QCoreApplication::translate("mTrs", "mind", nullptr));
        action123->setText(QCoreApplication::translate("mTrs", "123 ", nullptr));
#if QT_CONFIG(shortcut)
        action123->setShortcut(QCoreApplication::translate("mTrs", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        act_add->setText(QCoreApplication::translate("mTrs", "act_add", nullptr));
#if QT_CONFIG(shortcut)
        act_add->setShortcut(QCoreApplication::translate("mTrs", "Ctrl+=", nullptr));
#endif // QT_CONFIG(shortcut)
        act_minus->setText(QCoreApplication::translate("mTrs", "act_minus", nullptr));
#if QT_CONFIG(shortcut)
        act_minus->setShortcut(QCoreApplication::translate("mTrs", "Ctrl+-", nullptr));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class mTrs: public Ui_mTrs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MTRS_H
