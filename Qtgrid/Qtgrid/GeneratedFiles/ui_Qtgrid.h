/********************************************************************************
** Form generated from reading UI file 'Qtgrid.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGRID_H
#define UI_QTGRID_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtgridClass
{
public:
    QAction *action111;
    QAction *actionInitializeCanvas;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QMenuBar *menuBar;
    QMenu *menu11;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtgridClass)
    {
        if (QtgridClass->objectName().isEmpty())
            QtgridClass->setObjectName(QStringLiteral("QtgridClass"));
        QtgridClass->resize(388, 400);
        action111 = new QAction(QtgridClass);
        action111->setObjectName(QStringLiteral("action111"));
        actionInitializeCanvas = new QAction(QtgridClass);
        actionInitializeCanvas->setObjectName(QStringLiteral("actionInitializeCanvas"));
        centralWidget = new QWidget(QtgridClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        QtgridClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtgridClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 388, 21));
        menu11 = new QMenu(menuBar);
        menu11->setObjectName(QStringLiteral("menu11"));
        QtgridClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtgridClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtgridClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtgridClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtgridClass->setStatusBar(statusBar);

        menuBar->addAction(menu11->menuAction());
        menu11->addAction(actionInitializeCanvas);

        retranslateUi(QtgridClass);

        QMetaObject::connectSlotsByName(QtgridClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtgridClass)
    {
        QtgridClass->setWindowTitle(QApplication::translate("QtgridClass", "Qtgrid", Q_NULLPTR));
        action111->setText(QApplication::translate("QtgridClass", "111", Q_NULLPTR));
        actionInitializeCanvas->setText(QApplication::translate("QtgridClass", "InitializeCanvas", Q_NULLPTR));
        label->setText(QString());
        menu11->setTitle(QApplication::translate("QtgridClass", "11", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtgridClass: public Ui_QtgridClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGRID_H
