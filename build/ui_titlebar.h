/********************************************************************************
** Form generated from reading UI file 'titlebar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TITLEBAR_H
#define UI_TITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_titleBar
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;

    void setupUi(QWidget *titleBar)
    {
        if (titleBar->objectName().isEmpty())
            titleBar->setObjectName(QString::fromUtf8("titleBar"));
        titleBar->resize(400, 40);
        titleBar->setMaximumSize(QSize(16777215, 40));
        horizontalLayout = new QHBoxLayout(titleBar);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(titleBar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(40, 40));
        label->setFrameShadow(QFrame::Plain);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_2 = new QLabel(titleBar);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(16777215, 40));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton = new QToolButton(titleBar);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setMinimumSize(QSize(40, 40));

        horizontalLayout->addWidget(toolButton);

        toolButton_2 = new QToolButton(titleBar);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setMinimumSize(QSize(40, 40));

        horizontalLayout->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(titleBar);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setMinimumSize(QSize(40, 40));

        horizontalLayout->addWidget(toolButton_3);


        retranslateUi(titleBar);

        QMetaObject::connectSlotsByName(titleBar);
    } // setupUi

    void retranslateUi(QWidget *titleBar)
    {
        titleBar->setWindowTitle(QCoreApplication::translate("titleBar", "Form", nullptr));
        label->setText(QString());
        label_2->setText(QCoreApplication::translate("titleBar", "TextLabel", nullptr));
        toolButton->setText(QCoreApplication::translate("titleBar", "-", nullptr));
        toolButton_2->setText(QCoreApplication::translate("titleBar", "\342\226\242", nullptr));
        toolButton_3->setText(QCoreApplication::translate("titleBar", "x", nullptr));
    } // retranslateUi

};

namespace Ui {
    class titleBar: public Ui_titleBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TITLEBAR_H
