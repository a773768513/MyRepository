/********************************************************************************
** Form generated from reading UI file 'cpackageinput.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPACKAGEINPUT_H
#define UI_CPACKAGEINPUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CPackageInputClass
{
public:
    QAction *actionQuickMatch;
    QAction *actionMatchStr;
    QAction *actionWriteInFile;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QTextEdit *textEdit;
    QMenuBar *menuBar;
    QMenu *menumenu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *CPackageInputClass)
    {
        if (CPackageInputClass->objectName().isEmpty())
            CPackageInputClass->setObjectName(QStringLiteral("CPackageInputClass"));
        CPackageInputClass->resize(516, 421);
        actionQuickMatch = new QAction(CPackageInputClass);
        actionQuickMatch->setObjectName(QStringLiteral("actionQuickMatch"));
        actionMatchStr = new QAction(CPackageInputClass);
        actionMatchStr->setObjectName(QStringLiteral("actionMatchStr"));
        actionWriteInFile = new QAction(CPackageInputClass);
        actionWriteInFile->setObjectName(QStringLiteral("actionWriteInFile"));
        centralWidget = new QWidget(CPackageInputClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);
        CPackageInputClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(CPackageInputClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 516, 21));
        menumenu = new QMenu(menuBar);
        menumenu->setObjectName(QStringLiteral("menumenu"));
        CPackageInputClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(CPackageInputClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        CPackageInputClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(CPackageInputClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        CPackageInputClass->setStatusBar(statusBar);

        menuBar->addAction(menumenu->menuAction());
        menumenu->addAction(actionMatchStr);
        menumenu->addAction(actionWriteInFile);

        retranslateUi(CPackageInputClass);

        QMetaObject::connectSlotsByName(CPackageInputClass);
    } // setupUi

    void retranslateUi(QMainWindow *CPackageInputClass)
    {
        CPackageInputClass->setWindowTitle(QApplication::translate("CPackageInputClass", "CPackageInput", Q_NULLPTR));
        actionQuickMatch->setText(QApplication::translate("CPackageInputClass", "QuickMatch", Q_NULLPTR));
        actionMatchStr->setText(QApplication::translate("CPackageInputClass", "MtachStr", Q_NULLPTR));
        actionWriteInFile->setText(QApplication::translate("CPackageInputClass", "WriteInFile", Q_NULLPTR));
        menumenu->setTitle(QApplication::translate("CPackageInputClass", "menu", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CPackageInputClass: public Ui_CPackageInputClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPACKAGEINPUT_H
