/********************************************************************************
** Form generated from reading UI file 'QbarsetChartModule.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QBARSETCHARTMODULE_H
#define UI_QBARSETCHARTMODULE_H

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

class Ui_QbarsetChartModuleClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QbarsetChartModuleClass)
    {
        if (QbarsetChartModuleClass->objectName().isEmpty())
            QbarsetChartModuleClass->setObjectName(QStringLiteral("QbarsetChartModuleClass"));
        QbarsetChartModuleClass->resize(600, 400);
        menuBar = new QMenuBar(QbarsetChartModuleClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        QbarsetChartModuleClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QbarsetChartModuleClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QbarsetChartModuleClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QbarsetChartModuleClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QbarsetChartModuleClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QbarsetChartModuleClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QbarsetChartModuleClass->setStatusBar(statusBar);

        retranslateUi(QbarsetChartModuleClass);

        QMetaObject::connectSlotsByName(QbarsetChartModuleClass);
    } // setupUi

    void retranslateUi(QMainWindow *QbarsetChartModuleClass)
    {
        QbarsetChartModuleClass->setWindowTitle(QApplication::translate("QbarsetChartModuleClass", "QbarsetChartModule", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QbarsetChartModuleClass: public Ui_QbarsetChartModuleClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QBARSETCHARTMODULE_H
