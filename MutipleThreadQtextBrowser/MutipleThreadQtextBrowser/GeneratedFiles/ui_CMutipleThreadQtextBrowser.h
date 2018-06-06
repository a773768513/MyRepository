/********************************************************************************
** Form generated from reading UI file 'CMutipleThreadQtextBrowser.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMUTIPLETHREADQTEXTBROWSER_H
#define UI_CMUTIPLETHREADQTEXTBROWSER_H

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

class Ui_CMutipleThreadQtextBrowserClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CMutipleThreadQtextBrowserClass)
    {
        if (CMutipleThreadQtextBrowserClass->objectName().isEmpty())
            CMutipleThreadQtextBrowserClass->setObjectName(QStringLiteral("CMutipleThreadQtextBrowserClass"));
        CMutipleThreadQtextBrowserClass->resize(600, 400);
        menuBar = new QMenuBar(CMutipleThreadQtextBrowserClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        CMutipleThreadQtextBrowserClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CMutipleThreadQtextBrowserClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CMutipleThreadQtextBrowserClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(CMutipleThreadQtextBrowserClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CMutipleThreadQtextBrowserClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(CMutipleThreadQtextBrowserClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CMutipleThreadQtextBrowserClass->setStatusBar(statusBar);

        retranslateUi(CMutipleThreadQtextBrowserClass);

        QMetaObject::connectSlotsByName(CMutipleThreadQtextBrowserClass);
    } // setupUi

    void retranslateUi(QMainWindow *CMutipleThreadQtextBrowserClass)
    {
        CMutipleThreadQtextBrowserClass->setWindowTitle(QApplication::translate("CMutipleThreadQtextBrowserClass", "CMutipleThreadQtextBrowser", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CMutipleThreadQtextBrowserClass: public Ui_CMutipleThreadQtextBrowserClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMUTIPLETHREADQTEXTBROWSER_H
