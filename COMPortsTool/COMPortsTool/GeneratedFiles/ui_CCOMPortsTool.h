/********************************************************************************
** Form generated from reading UI file 'CCOMPortsTool.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CCOMPORTSTOOL_H
#define UI_CCOMPORTSTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CCOMPortsToolClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CCOMPortsToolClass)
    {
        if (CCOMPortsToolClass->objectName().isEmpty())
            CCOMPortsToolClass->setObjectName(QStringLiteral("CCOMPortsToolClass"));
        CCOMPortsToolClass->resize(600, 400);
        menuBar = new QMenuBar(CCOMPortsToolClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CCOMPortsToolClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CCOMPortsToolClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CCOMPortsToolClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CCOMPortsToolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CCOMPortsToolClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CCOMPortsToolClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CCOMPortsToolClass->setStatusBar(statusBar);

        retranslateUi(CCOMPortsToolClass);

        QMetaObject::connectSlotsByName(CCOMPortsToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *CCOMPortsToolClass)
    {
        CCOMPortsToolClass->setWindowTitle(QApplication::translate("CCOMPortsToolClass", "CCOMPortsTool", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CCOMPortsToolClass: public Ui_CCOMPortsToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CCOMPORTSTOOL_H
