/********************************************************************************
** Form generated from reading UI file 'helloqt.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELLOQT_H
#define UI_HELLOQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_helloqtClass
{
public:
    QWidget *centralWidget;
    QPushButton *Match;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *OutputFileLineEdit;
    QLineEdit *InputFileLineEdit;
    QLineEdit *InputStrLineEdit;
    QLabel *label_3;
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *helloqtClass)
    {
        if (helloqtClass->objectName().isEmpty())
            helloqtClass->setObjectName(QStringLiteral("helloqtClass"));
        helloqtClass->resize(600, 400);
        centralWidget = new QWidget(helloqtClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Match = new QPushButton(centralWidget);
        Match->setObjectName(QStringLiteral("Match"));
        Match->setGeometry(QRect(250, 230, 75, 23));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(150, 50, 311, 161));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        OutputFileLineEdit = new QLineEdit(layoutWidget);
        OutputFileLineEdit->setObjectName(QStringLiteral("OutputFileLineEdit"));
        OutputFileLineEdit->setMaxLength(32767);

        gridLayout->addWidget(OutputFileLineEdit, 2, 1, 1, 1);

        InputFileLineEdit = new QLineEdit(layoutWidget);
        InputFileLineEdit->setObjectName(QStringLiteral("InputFileLineEdit"));

        gridLayout->addWidget(InputFileLineEdit, 1, 1, 1, 1);

        InputStrLineEdit = new QLineEdit(layoutWidget);
        InputStrLineEdit->setObjectName(QStringLiteral("InputStrLineEdit"));

        gridLayout->addWidget(InputStrLineEdit, 0, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setTextFormat(Qt::PlainText);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(0, 320, 241, 23));
        progressBar->setValue(0);
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(100, 250, 75, 23));
        helloqtClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(helloqtClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        helloqtClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(helloqtClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        helloqtClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(helloqtClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        helloqtClass->setStatusBar(statusBar);

        retranslateUi(helloqtClass);
        QObject::connect(Match, SIGNAL(clicked()), helloqtClass, SLOT(Btn_MatchClick()));
        QObject::connect(pushButton, SIGNAL(clicked()), progressBar, SLOT(reset()));

        QMetaObject::connectSlotsByName(helloqtClass);
    } // setupUi

    void retranslateUi(QMainWindow *helloqtClass)
    {
        helloqtClass->setWindowTitle(QApplication::translate("helloqtClass", "helloqt", Q_NULLPTR));
        Match->setText(QApplication::translate("helloqtClass", "match", Q_NULLPTR));
        label_2->setText(QApplication::translate("helloqtClass", "input file path", Q_NULLPTR));
        InputStrLineEdit->setText(QString());
        label_3->setText(QApplication::translate("helloqtClass", "output file path", Q_NULLPTR));
        label->setText(QApplication::translate("helloqtClass", "match string", Q_NULLPTR));
        pushButton->setText(QApplication::translate("helloqtClass", "PushButton", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class helloqtClass: public Ui_helloqtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELLOQT_H
