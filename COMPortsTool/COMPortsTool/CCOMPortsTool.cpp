#include "CCOMPortsTool.h"

CCOMPortsTool::CCOMPortsTool(QWidget *parent)
	: QMainWindow(parent)
{
	SetMainWindows();
	AddMainMenuAction();
}

CCOMPortsTool::~CCOMPortsTool()
{
	delete pQMainWidget;
}

void CCOMPortsTool::SetMainWindows()
{
	pQMainTabWidget = new QTabWidget(this);
	pQMainTabWidget->setTabsClosable(true);      ///<set whether close able 
	///connect the signal and the widgets close event
	connect(pQMainTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(On_tabCloseRequested_Triggered(int)));

	pQMainWidget = new QWidget;
	pQMainGridLayout = new QGridLayout(this);
	pQMainTextEdit = new QTextEdit(this);
	///pQMainTextBrowser->setStatusTip("i am just test");
	///pQMainIcon.addFile(".\Resources\mini.png", QSize(), QIcon::Normal, QIcon::Off);
	///this->setWindowIcon(pQMainIcon);
	pQMainTabWidget->setTabShape(QTabWidget::Triangular);
	pQMainGridLayout->addWidget(pQMainTabWidget, 0, 0);
	pQMainGridLayout->addWidget(pQMainTextEdit, 1, 0, 1, 1);

	pQMainGridLayout->setRowStretch(0, 3);
	pQMainGridLayout->setRowStretch(1, 1);
	pQMainWidget->setLayout(pQMainGridLayout);

	this->setCentralWidget(pQMainWidget);
	this->resize(QSize(500, 300));                 ///<set the windows w h in the initial size
}

void CCOMPortsTool::AddMainMenuAction()
{

	///main windows action 
	/// new the action and set text and status tip
	pQConnectDialogAction = new QAction;
	pQConnectDialogAction->setText("Connect");
	pQConnectDialogAction->setStatusTip("Open a File and display data in main windows");
	connect(pQConnectDialogAction, SIGNAL(triggered()), this, SLOT(On_pConnectDialogAction_Triggered()));

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
	pQMainMenu->addAction(pQConnectDialogAction);
	pQMainMenu->addAction(pQOpenHighlighterDialogAction);
	pQMainMenu->addSeparator();
	pQMainMenu->addAction(pQOpenWriteFileDialogAction);

	///add status bar 
	pQMainStatusBar = new QStatusBar;
	this->setStatusBar(pQMainStatusBar);
}


///close slot and delete this widgets
void CCOMPortsTool::On_tabCloseRequested_Triggered(int CurrentIndex)
{
	CQThreadTextBrowser *pStopTextBrowser = dynamic_cast<CQThreadTextBrowser*>(pQMainTabWidget->currentWidget());
	pStopTextBrowser->close();
}