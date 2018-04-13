#include "CMutipleThreadQtextBrowser.h"

CMutipleThreadQtextBrowser::CMutipleThreadQtextBrowser(QWidget *parent)
	: QMainWindow(parent)
{
	SetMainWindows();
	AddMainMenuAction();

}


CMutipleThreadQtextBrowser::~CMutipleThreadQtextBrowser()
{
	/***
	///delete write file dialog widgets
	delete pQWriteDialogEdit;
	delete pQWriteDialogFileButton;
	delete pQWriteDialogConfirmButton;
	delete pQWriteDialogCancelButton;
	delete pWriteGridLayout;
	///delete pWriteDialog;
	///delete the highlighting dialog widgets
	delete pQComboBoxHighlighterDialogStr;
	delete pQLabelSampleStr;
	delete pQOpenColorDialog;
	delete pQHighlighterDialogConfirm;
	delete pQHighlighterDialogCancel;	
	delete pQgridLayoutHighlighterDialog;
	///delete pQDialogHighlighter;


	///delte OpenFileChilde Dialog
	delete pQPushButtonOpenFileCancel;
	delete pQPushButttonOpenFileConfirm;
	delete pQPushButtonOpenFilePath;
	delete pQTextEditOpenFilePath;
	delete pQLabelOpenFilePath;
	delete pGridLayoutOpenFileDialog;
	///delete pDialogOpenFile;
	**********************/

	/// delete  main window widget (last delete)
	delete pQMainTextEdit;
	delete pQMainGridLayout;
	delete pQMainTabWidget;
	delete pQMainWidget;
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

	pQMainGridLayout->setRowStretch(0, 3);
	pQMainGridLayout->setRowStretch(1, 1);
	pQMainWidget->setLayout(pQMainGridLayout);

	this->setCentralWidget(pQMainWidget);
	this->resize(QSize(500, 300));                 ///<set the windows w h in the initial size
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
