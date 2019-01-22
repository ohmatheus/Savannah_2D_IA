/********************************************************************************
** Form generated from reading UI file 'SavannahUI.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVANNAHUI_H
#define UI_SAVANNAHUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QSavannahMainWindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QSavannahMainWindowClass)
    {
        if (QSavannahMainWindowClass->objectName().isEmpty())
            QSavannahMainWindowClass->setObjectName(QString::fromUtf8("QSavannahMainWindowClass"));
        QSavannahMainWindowClass->resize(600, 400);
        menuBar = new QMenuBar(QSavannahMainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        QSavannahMainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QSavannahMainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSavannahMainWindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QSavannahMainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSavannahMainWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QSavannahMainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QSavannahMainWindowClass->setStatusBar(statusBar);

        retranslateUi(QSavannahMainWindowClass);

        QMetaObject::connectSlotsByName(QSavannahMainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *QSavannahMainWindowClass)
    {
        QSavannahMainWindowClass->setWindowTitle(QApplication::translate("QSavannahMainWindowClass", "QSavannahMainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QSavannahMainWindowClass: public Ui_QSavannahMainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVANNAHUI_H
