#include "QtGuider.h"
#include "QtFlexWidget.h"
#include "QtFlexHelper.h"
#include "QtDockGuider.h"
#include "QtDockWidget.h"
#include "QtFlexManager.h"
#include <QtCore/QSettings>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDesktopWidget>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QPushButton>
#include "ui_qtguider.h"

#include "ThreadQtextbrowser.h"
#include "ManageThreadObject.h"
#include <qgridlayout.h>
QtCentral::QtCentral(QWidget* parent) : QWidget(parent)
{
    setObjectName("Central");

    QHBoxLayout* box = new QHBoxLayout(this);
    box->setContentsMargins(0, 0, 0, 0);

    
    _widget = new QPushButton("Click");

	createOne();
	
}
void QtCentral::on_flexWidgetCreated(FlexWidget* flexWidget)
{
	if (flexWidget->objectName() == "M")
	{
		layout()->addWidget(flexWidget);
	}
	else
	{
		flexWidget->show();
	}

}

void QtCentral::on_dockWidgetCreated(DockWidget* dockWidget)
{

}
void QtCentral::createOne()
{
    auto content = FlexManager::instance()->createFlexWidget(Flex::HybridView, this, Flex::widgetFlags(), "M");
    layout()->addWidget(content);

}

void QtCentral::createTwo()
{
    auto splitter = new QSplitter(this);
    auto l = FlexManager::instance()->createFlexWidget(Flex::HybridView, this, Flex::widgetFlags(), "L");
    auto r = FlexManager::instance()->createFlexWidget(Flex::HybridView, this, Flex::widgetFlags(), "R");

	
    splitter->addWidget(l);
    splitter->addWidget(r);
    layout()->addWidget(splitter);
	
}



class QtGuiderImpl
{
public:
    Ui::QtGuiderClass ui;
};

QtGuider::QtGuider(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags), impl(new QtGuiderImpl)
{
	
	StartManageThread();
    qApp->setProperty("window", QVariant::fromValue<QObject*>(this));

    ///impl->ui.setupUi(this);
	///impl->ui.menuFile->addAction(QString("File-%1").arg(i), this, SLOT(actionFile_X_triggered()));
    ///impl->ui.menuView->addAction(QString("View-%1").arg(i), this, SLOT(actionView_X_triggered()));
    
	pQtCentral = new QtCentral(this);
	setCentralWidget(pQtCentral);
    auto docker1 = new QDockWidget("Command window", this);
	pQGridLayoutCommandWindows = new QGridLayout(docker1);
	pQWidgetCommandWindows = new QWidget(this);
	docker1->setWidget(pQWidgetCommandWindows);
	pQWidgetCommandWindows->setLayout(pQGridLayoutCommandWindows);
	///dynamic_cast<QGridLayout*>(docker1->layout())->addWidget(new QPushButton(), 0, 0);
	pQTextEditCommandWindows = new QTextEdit();
	///b->show();
	pQGridLayoutCommandWindows->addWidget(pQTextEditCommandWindows, 0, 0);
	
	///dynamic_cast<QGridLayout*>(docker1->layout())->addWidget(new QTextEdit(docker1), 1, 0, 1, -1);
    auto docker2 = new QDockWidget("Docker2", this);
    docker2->setWidget(new QWidget(this));

    addDockWidget(Qt::BottomDockWidgetArea, docker1);
    ///addDockWidget(Qt::LeftDockWidgetArea, docker2);
	docker1->setMinimumHeight(100);

    setGeometry(QApplication::desktop()->availableGeometry().adjusted(100, 100, -100, -100));
	AddMainMenuAction();

	///CONNECT The GUI function and the 
	FunctionConnectMainWindowsRequirementSlot();
	///qtable widget 
	pQTableWidgetManageWidgets = new QTableWidget(this);
	///pQMainTextBrowser->setStatusTip("i am just test");
	///pQMainIcon.addFile(".\Resources\mini.png", QSize(), QIcon::Normal, QIcon::Off);
	///this->setWindowIcon(pQMainIcon);
	///
	///OOptimize Main windows information
	pQTableWidgetManageWidgets->setColumnCount(4);
	pQTableWidgetManageWidgets->setRowCount(0);
	QStringList ColumnHeaderLable;
	ColumnHeaderLable << "COM List" << "Operating Status" << "Acceptance rate" << "Log Data";
	pQTableWidgetManageWidgets->setHorizontalHeaderLabels(ColumnHeaderLable);
	pQTableWidgetManageWidgets->setShowGrid(false);
	pQTableWidgetManageWidgets->setEditTriggers(QAbstractItemView::NoEditTriggers);
	pQTableWidgetManageWidgets->setSelectionBehavior(QAbstractItemView::SelectRows);
	pQTableWidgetManageWidgets->verticalHeader()->hide();
	pQTableWidgetManageWidgets->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	pQTableWidgetManageWidgets->setContextMenuPolicy(Qt::CustomContextMenu);

	auto docker22 = new QDockWidget("Docker2", this);
	docker22->setWidget(pQTableWidgetManageWidgets);
	addDockWidget(Qt::RightDockWidgetArea, docker22);
	///addDockWidget(Qt::LeftDockWidgetArea, docker2);
	docker22->setMinimumWidth(200);
}

QtGuider::~QtGuider()
{
	
	delete pCManageThreadObject;
	pManagethread->quit();
}
void QtGuider::StartManageThread()
{
	pCManageThreadObject = new CManageThreadObject(this);
	pManagethread = new QThread(this);
	pManagethread->start();
	pCManageThreadObject->moveToThread(pManagethread);

}
void QtGuider::AddMainMenuAction()
{
	pQMenuMainwindows = new QMenu(this);
	pQActionOpenFileDialog = new QAction(pQMenuMainwindows);
	pQActionOpenHighlighterDialog = new QAction(pQMenuMainwindows);
	pQActionOpenLogFileDialog = new QAction(pQMenuMainwindows);
	pQStatusBarMainWindows = new QStatusBar(this);
	/// Open File Dialog Action 
	pQActionOpenFileDialog->setText("Open COM List");
	pQActionOpenFileDialog->setStatusTip("Show and open a COM in Main Windows");

	///Open Highlighter Dialog in main windows 
	pQActionOpenHighlighterDialog->setText("Highlight String");
	pQActionOpenHighlighterDialog->setStatusTip("Highlight the selected String");

	///Open Log Fil dialog 
	pQActionOpenLogFileDialog->setText("Log");
	pQActionOpenLogFileDialog->setStatusTip("Log Data to File");
	pQMenuMainwindows = menuBar()->addMenu("File");
	this->setStatusBar(pQStatusBarMainWindows);
	///add action to qmenu 
	pQMenuMainwindows->addAction(pQActionOpenFileDialog);
	pQMenuMainwindows->addAction(pQActionOpenHighlighterDialog);
	pQMenuMainwindows->addSeparator();
	pQMenuMainwindows->addAction(pQActionOpenLogFileDialog);

}
/**********************************************************************//**
@brief  connect all slots and user requirestment
@param  
@return  
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void QtGuider::FunctionConnectMainWindowsRequirementSlot()
{
	///
	///  Mainwindows triggered  in the qmenu 
	connect(pQActionOpenFileDialog, SIGNAL(triggered()), this, SLOT(On_pQActionOpenFileDialog_triggered()));
	connect(pQActionOpenHighlighterDialog, SIGNAL(triggered()), this, SLOT(On_pQActionOpenHighlighterDialog_triggered()));
	connect(pQActionOpenLogFileDialog, SIGNAL(triggered()), this, SLOT(On_pQActionOpenLogFileDialog_triggered()));
	

	///
	///Qtable widget (show  manage information  right button )
	///connect(pQTableWidgetManageWidgets, SIGNAL(customContextMenuRequested(const QPoint*)), this, SLOT(On_pQTableWidgets_RightButton(const QPoint*)));



	///connect(this, SIGNAL(SignalManageThreadCloseTab(int)), &ObjCManageThreadObject, SLOT(On_GUI_SignalManageThreadCloseTab(int)));
	///connect(&ObjCManageThreadObject, SIGNAL(SignalToGUICloseCOM(int)), this, SLOT(On_ManageThread_CloseCOM(int)));
	///
	///connect the Qmessage information of faliure
	connect(this, SIGNAL(EmitQmessageInformation(QString)), this, SLOT(QMessageBoxFailure(QString)));
	///delete triggererd()
	connect(FlexManager::instance(), SIGNAL(flexWidgetCreated(FlexWidget*)), SLOT(on_flexWidgetCreated(FlexWidget*)));
	connect(FlexManager::instance(), SIGNAL(dockWidgetCreated(DockWidget*)), SLOT(on_dockWidgetCreated(DockWidget*)));
	connect(FlexManager::instance(), SIGNAL(flexWidgetDestroying(FlexWidget*)), SLOT(on_flexWidgetDestroying(FlexWidget*)));
	connect(FlexManager::instance(), SIGNAL(dockWidgetDestroying(DockWidget*)), SLOT(on_dockWidgetDestroying(DockWidget*)));

}



void QtGuider::openFile_N(int n)
{
    QString dockWidgetName = QString("File-%1").arg(n);

    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::FileView, Flex::parent(Flex::FileView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::FileView, flexWidget, Flex::widgetFlags(), dockWidgetName);
            dockWidget->setViewMode(Flex::FileView);

			auto *pThreadTextbrower = new CThreadQtextbrowser(this);
			dockWidget->attachWidget(pThreadTextbrower);
            dockWidget->setWindowTitle(dockWidgetName);
            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void QtGuider::openView_N(int n)
{
    QString dockWidgetName = QString("View-%1").arg(n);

    DockWidget* widget = nullptr;

    if ((widget = FlexManager::instance()->dockWidget(dockWidgetName)) != nullptr)
    {
        widget->activate();
    }
    else
    {
        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            FlexWidget* flexWidget = FlexManager::instance()->createFlexWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, flexWidget, Flex::widgetFlags(), dockWidgetName);
            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);
            flexWidget->addDockWidget(dockWidget);
            flexWidget->show();
            flexWidget->move(geometry().center() - flexWidget->rect().center());
        }
    }
}

void QtGuider::on_actionFile_N_triggered()
{
    static int i = 0;
    for (;; i++)
    {
        QString dockWidgetName = QString("File-%1").arg(i);

        if (FlexManager::instance()->hasDockWidget(dockWidgetName))
        {
            continue;
        }

        openFile_N(i);

        break;
    }
}



void QtGuider::on_actionTool_N_triggered()
{
    FlexManager::instance()->flexWidget("M")->clearDockSites();
}

void QtGuider::actionFile_X_triggered()
{
    openFile_N(static_cast<QAction*>(sender())->text().split("-")[1].toInt());
}

void QtGuider::actionView_X_triggered()
{
    openView_N(static_cast<QAction*>(sender())->text().split("-")[1].toInt());
}

void QtGuider::on_actionEdit_Undo_triggered()
{
    static int i = 0;
    for (;; i++)
    {
        QString dockWidgetName = QString("FileTool-%1").arg(i);

        if (FlexManager::instance()->hasDockWidget(dockWidgetName))
        {
            continue;
        }

        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::FileView, Flex::parent(Flex::FileView), Flex::windowFlags());
            dockWidget->setViewMode(Flex::FileView);
            dockWidget->setWindowTitle(dockWidgetName);
            dockWidget->show();
            dockWidget->move(geometry().center() - dockWidget->rect().center());
        }

        break;
    }
}

void QtGuider::on_actionEdit_Redo_triggered()
{
    static int i = 0;
    for (;; i++)
    {
        QString dockWidgetName = QString("ViewTool-%1").arg(i);

        if (FlexManager::instance()->hasDockWidget(dockWidgetName))
        {
            continue;
        }

        if (!FlexManager::instance()->restore(dockWidgetName))
        {
            DockWidget* dockWidget = FlexManager::instance()->createDockWidget(Flex::ToolView, Flex::parent(Flex::ToolView), Flex::windowFlags());
            dockWidget->setViewMode(Flex::ToolView);
            dockWidget->setWindowTitle(dockWidgetName);
            dockWidget->show();
            dockWidget->move(geometry().center() - dockWidget->rect().center());
        }

        break;
    }
}

void QtGuider::closeEvent(QCloseEvent* evt)
{
    QByteArray content = FlexManager::instance()->save();

    QSettings settings("QtFlex5", "QtGuider");

    settings.setValue("Flex", content);

    FlexManager::instance()->close();
}
