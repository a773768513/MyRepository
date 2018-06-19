/********************************************************************************
** Form generated from reading UI file 'CFemtoMonitorcenter.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFEMTOMONITORCENTER_H
#define UI_CFEMTOMONITORCENTER_H

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

class Ui_CFemtoMonitorcenterClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CFemtoMonitorcenterClass)
    {
        if (CFemtoMonitorcenterClass->objectName().isEmpty())
            CFemtoMonitorcenterClass->setObjectName(QStringLiteral("CFemtoMonitorcenterClass"));
        CFemtoMonitorcenterClass->resize(600, 400);
        menuBar = new QMenuBar(CFemtoMonitorcenterClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CFemtoMonitorcenterClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CFemtoMonitorcenterClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CFemtoMonitorcenterClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CFemtoMonitorcenterClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CFemtoMonitorcenterClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CFemtoMonitorcenterClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CFemtoMonitorcenterClass->setStatusBar(statusBar);

        retranslateUi(CFemtoMonitorcenterClass);

        QMetaObject::connectSlotsByName(CFemtoMonitorcenterClass);
    } // setupUi

    void retranslateUi(QMainWindow *CFemtoMonitorcenterClass)
    {
        CFemtoMonitorcenterClass->setWindowTitle(QApplication::translate("CFemtoMonitorcenterClass", "CFemtoMonitorcenter", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CFemtoMonitorcenterClass: public Ui_CFemtoMonitorcenterClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFEMTOMONITORCENTER_H
