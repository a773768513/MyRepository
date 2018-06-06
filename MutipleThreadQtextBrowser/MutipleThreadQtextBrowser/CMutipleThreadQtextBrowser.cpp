#include "CMutipleThreadQtextBrowser.h"

CMutipleThreadQtextBrowser::CMutipleThreadQtextBrowser(QWidget *parent)
	: QMainWindow(parent)
{
	initProject();
	SetMainWindows();
	AddMainMenuAction();
	pQColorSelected = new QColor(Qt::black);

}


CMutipleThreadQtextBrowser::~CMutipleThreadQtextBrowser()
{
	ManageThread.quit();
	ManageThread.wait();
	/// delete  main window widget (last delete)
	delete pQMainTextEdit;
	delete pQMainGridLayout;
	delete pQMainTabWidget;
	delete pQMainWidget;
	delete pQColorSelected;
}

void CMutipleThreadQtextBrowser::initProject()
{
	ObjCManageThreadObject.moveToThread(&ManageThread);
	ManageThread.start();
	connect(this, SIGNAL(SignalcreateTextbrowser(QString)), &ObjCManageThreadObject, SLOT(CreatetextbrowserRecord(QString)));
	connect(&ObjCManageThreadObject, SIGNAL(SignalCreateTextbrowser(QString)), this, SLOT(SlotCreateTextbrowser(QString)));
	///connect to change the spped void EmitSignal(QVector<int>* RecordDataSpeedPara);
	connect(&ObjCManageThreadObject, SIGNAL(EmitSignal(QVector<int>*)), this, SLOT(On_ManageThread_speed(QVector<int>*)), Qt::BlockingQueuedConnection);
	/// connect the right button 
	connect(&ObjCManageThreadObject, SIGNAL(SignalToGUICreateRightMenu()), this, SLOT(On_SiganlManage_CreateRightMenu()));
	
}
void CMutipleThreadQtextBrowser::SetMainWindows()
{
	pQMainTabWidget = new QTabWidget;
	pQMainWidget = new QWidget;
	pQMainGridLayout = new QGridLayout(this);
	pQMainTextEdit = new QTextEdit;
	///pQMainTextBrowser->setStatusTip("i am just test");
	///pQMainIcon.addFile(".\Resources\mini.png", QSize(), QIcon::Normal, QIcon::Off);
	///this->setWindowIcon(pQMainIcon);
	pQMainTabWidget->setTabShape(QTabWidget::Triangular);
	pQMainGridLayout->addWidget(pQMainTabWidget, 0, 0);
	pQMainGridLayout->addWidget(pQMainTextEdit, 1, 0, 1, 1);
	///
	///
	pQMainGridLayout->setRowStretch(0, 3);
	pQMainGridLayout->setRowStretch(1, 1);
	pQMainWidget->setLayout(pQMainGridLayout);

	this->setCentralWidget(pQMainWidget);
	this->resize(QSize(500, 300));                 ///<set the windows w h in the initial size
	///set the close event signal and slot(only connect when this object exist)
	pQMainTabWidget->setTabsClosable(true);
	connect(pQMainTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(On_TabWidget_CloseButton(int)));

	connect(this, SIGNAL(SignalManageThreadCloseTab(int)), &ObjCManageThreadObject, SLOT(On_GUI_SignalManageThreadCloseTab(int)));
	connect(&ObjCManageThreadObject, SIGNAL(SignalToGUICloseCOM(int)), this, SLOT(On_ManageThread_CloseCOM(int)));
}

void CMutipleThreadQtextBrowser::AddMainMenuAction()
{

	///main windows action 
	/// new the action and set text and status tip
	pQOpenFileDialogAction = new QAction;
	pQOpenFileDialogAction->setText("OpenFile");
	pQOpenFileDialogAction->setStatusTip("Open a File and display data in main windows");
	connect(pQOpenFileDialogAction, SIGNAL(triggered()), this, SLOT(On_pQOpenFileDialogAction_Triggered()));

	///action to add  highlighter rule  
	pQOpenHighlighterDialogAction = new QAction;
	pQOpenHighlighterDialogAction->setText("HighlightStr");
	pQOpenHighlighterDialogAction->setStatusTip("HighLight the selected character");
	connect(pQOpenHighlighterDialogAction, SIGNAL(triggered()), this, SLOT(On_pQOpenHighlighterDialogAction_Triggered()));

	/// action write data to file,
	pQOpenWriteFileDialogAction = new QAction;
	pQOpenWriteFileDialogAction->setText("WriteInFile");
	pQOpenWriteFileDialogAction->setStatusTip("write data to the file");
	connect(pQOpenWriteFileDialogAction, SIGNAL(triggered()), this, SLOT(On_pQOpenWriteFileDialogAction_Triggered()));

	///
	///set the main menu 
	pQMainMenu = new QMenu;
	pQMainMenu = menuBar()->addMenu("File");

	/// add the action to the menu
	pQMainMenu->addAction(pQOpenFileDialogAction);
	pQMainMenu->addAction(pQOpenHighlighterDialogAction);
	pQMainMenu->addSeparator();
	pQMainMenu->addAction(pQOpenWriteFileDialogAction);

	///add status bar 
	pQMainStatusBar = new QStatusBar;
	this->setStatusBar(pQMainStatusBar);
}
void CMutipleThreadQtextBrowser::On_DeleteRowAction_Triggered()
{
	int DeleteRowIndex = ObjCManageThreadObject.pQTableWidget->currentRow();
	if (DeleteRowIndex >= 0)
	{
		On_TabWidget_CloseButton(DeleteRowIndex);
	}
}