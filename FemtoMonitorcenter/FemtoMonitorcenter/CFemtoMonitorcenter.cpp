#include "CFemtoMonitorcenter.h"

CFemtoMonitorcenter::CFemtoMonitorcenter(QWidget *parent)
	: QMainWindow(parent)
{
	StartManageThread();
	CreateMainWindowsGUI();
	AddMainMenuAction();
	FunctionConnectMainWindowsRequirementSlot();

	pQColorSelected = new QColor();
}

CFemtoMonitorcenter::~CFemtoMonitorcenter()
{
	pManagethread->quit();
	delete pCManageThreadObject;
}
void CFemtoMonitorcenter::StartManageThread()
{
	pCManageThreadObject = new CManageThreadObject(this);
	pManagethread = new QThread(this);
	pManagethread->start();
	pCManageThreadObject->moveToThread(pManagethread);
}
/**********************************************************************//**
@brief   Create Main Windows Widgets ;
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::CreateMainWindowsGUI()
{
	pQMainTabWidget = new QTabWidget(this);
	pQMainWidget = new QWidget(this);
	pQMainGridLayout = new QGridLayout(this);
	pQMainTextEdit = new QTextEdit(this);
	pQTableWidgetManageWidgets = new QTableWidget(this);
	///pQMainTextBrowser->setStatusTip("i am just test");
	///pQMainIcon.addFile(".\Resources\mini.png", QSize(), QIcon::Normal, QIcon::Off);
	///this->setWindowIcon(pQMainIcon);
	///
	///OOptimize Main windows information
	pQTableWidgetManageWidgets->setColumnCount(3);
	pQTableWidgetManageWidgets->setRowCount(0);
	QStringList ColumnHeaderLable;
	ColumnHeaderLable << "COM List" << "Operating Status"<< "Acceptance rate"<<"Log Data" ;
	pQTableWidgetManageWidgets->setHorizontalHeaderLabels(ColumnHeaderLable);
	pQTableWidgetManageWidgets->setShowGrid(false);
	pQTableWidgetManageWidgets->setEditTriggers(QAbstractItemView::NoEditTriggers);
	pQTableWidgetManageWidgets->setSelectionBehavior(QAbstractItemView::SelectRows);
	pQTableWidgetManageWidgets->verticalHeader()->hide();
	pQTableWidgetManageWidgets->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	pQTableWidgetManageWidgets->setContextMenuPolicy(Qt::CustomContextMenu);
	///
	pQMainTabWidget->setTabShape(QTabWidget::Triangular);
	pQMainGridLayout->addWidget(pQMainTabWidget, 0, 0,1,1);
	pQMainGridLayout->addWidget(pQTableWidgetManageWidgets, 0, 1, 1, 1);
	pQMainGridLayout->addWidget(pQMainTextEdit, 1, 0, 1, 2);

	///
	///set the row 
	pQMainGridLayout->setRowStretch(0, 3);
	pQMainGridLayout->setRowStretch(1, 1);
	///set layout of the herion
	pQMainGridLayout->setColumnStretch(0, 2);
	pQMainGridLayout->setColumnStretch(1, 1);

	pQMainWidget->setLayout(pQMainGridLayout);

	this->setCentralWidget(pQMainWidget);
	this->resize(QSize(500, 300));                 ///<set the windows w h in the initial size
	///set the close event signal and slot(only connect when this object exist)
	pQMainTabWidget->setTabsClosable(true);
}

/**********************************************************************//**
@brief  AddMainWindows qMenu and action 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::AddMainMenuAction()
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
@brief  Create a child dialog to Open COM
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::CreateOpenFileChildWindows()
{
	/// create dialog and close when delete 
	pDialogOpenFile = new QDialog(this);
	pDialogOpenFile->setAttribute(Qt::WA_DeleteOnClose, true);
	pGridLayoutOpenFileDialog = new QGridLayout(pDialogOpenFile);
	////pGridLayoutOpenFileDialog->setSizeConstraint(QLayout::SetFixedSize);  ///fixed dialog (for hide the pQWidgetDetail but no change the widget relative position
	pGridLayoutOpenFileDialog->setSpacing(20);
	pGridLayoutOpenFileDialog->setMargin(20);
	///
	pQLabelOpenFilePath = new QLabel(pDialogOpenFile);
	pQLabelOpenFilePath->setText("OpenFilePath");
	pGridLayoutOpenFileDialog->addWidget(pQLabelOpenFilePath, 0, 0, 1, 1);

	///line edit to input the opwn file path
	pQTextEditOpenFilePath = new  QLineEdit(pDialogOpenFile);
	pGridLayoutOpenFileDialog->addWidget(pQTextEditOpenFilePath, 0, 1, 1, 2);

	///push button to use filedialog select file path 
	pQPushButtonOpenFilePath = new QPushButton(pDialogOpenFile);
	pQPushButtonOpenFilePath->setText("OpenFile");
	connect(pQPushButtonOpenFilePath, SIGNAL(clicked()), this, SLOT(On_OpenFileChildDialogSelectFile_Clicked()));
	pGridLayoutOpenFileDialog->addWidget(pQPushButtonOpenFilePath, 1, 2, 1, 1);
	///confirm button  and cancel button pQPushButttonOpenFileConfirm
	pQPushButttonOpenFileConfirm = new QPushButton(pDialogOpenFile);
	pQPushButttonOpenFileConfirm->setText("Confirm");
	pGridLayoutOpenFileDialog->addWidget(pQPushButttonOpenFileConfirm, 3, 1);
	pQPushButtonOpenFileCancel = new QPushButton(pDialogOpenFile);
	pQPushButtonOpenFileCancel->setText("Cancel");
	pGridLayoutOpenFileDialog->addWidget(pQPushButtonOpenFileCancel, 3, 2);

	pGridLayoutOpenFileDialog->setColumnStretch(0, 0);
	pGridLayoutOpenFileDialog->setColumnStretch(1, 1);
	pGridLayoutOpenFileDialog->setColumnStretch(2, 1);
	///connect the object and slot (only the object exist can connect this )
	connect(pQPushButttonOpenFileConfirm, SIGNAL(clicked()), this, SLOT(On_pQPushButttonOpenFileConfirm_Clicked()));
	connect(pQPushButtonOpenFileCancel, SIGNAL(clicked()), this, SLOT(On_pQPushButtonOpenFileCancel_Clicked()));
	
	pDialogOpenFile->exec();
}
/**********************************************************************//**
@brief  Create a child dialog to add highlighter rule 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::CreateHighlightingWindows()
{
	///new a dialog and add the grid layout
	pQDialogHighlighter = new QDialog;
	pQDialogHighlighter->setAttribute(Qt::WA_DeleteOnClose, true);
	pQgridLayoutHighlighterDialog = new QGridLayout(pQDialogHighlighter);
	pQDialogHighlighter->resize(QSize(280, 150));
	pQgridLayoutHighlighterDialog->setMargin(20);
	pQgridLayoutHighlighterDialog->setSpacing(15);
	/// combobox to input highlighter string
	pQComboBoxHighlighterDialogStr = new QComboBox(pQDialogHighlighter);
	pQComboBoxHighlighterDialogStr->setEditable(1);
	pQComboBoxHighlighterDialogStr->addItem("");
	pQComboBoxHighlighterDialogStr->addItem("#RANGE");
	pQgridLayoutHighlighterDialog->addWidget(pQComboBoxHighlighterDialogStr, 0, 0, 1, 2);
	///pQLabelSampleStr new 
	pQLabelSampleStr = new QLabel(pQDialogHighlighter);
	pQLabelSampleStr->setText("Sample");
	QFont QQFontinpQLabelSampleStr("Times New Roman", 15, 75);
	pQLabelSampleStr->setFont(QQFontinpQLabelSampleStr);
	pQgridLayoutHighlighterDialog->addWidget(pQLabelSampleStr, 0, 2);

	///new push to open color dialog
	pQOpenColorDialog = new QPushButton(pQDialogHighlighter);
	pQOpenColorDialog->setText("SelectColor");
	pQgridLayoutHighlighterDialog->addWidget(pQOpenColorDialog, 1, 2);
	connect(pQOpenColorDialog, SIGNAL(clicked()), this, SLOT(On_pQOpenColorDialog_Triggered()));
	///
	///Confirm and cancel button pQPushButttonOpenFileConfirm
	pQHighlighterDialogConfirm = new QPushButton(pQDialogHighlighter);
	pQHighlighterDialogConfirm->setText("Confirm");
	pQgridLayoutHighlighterDialog->addWidget(pQHighlighterDialogConfirm, 2, 1);
	pQHighlighterDialogCancel = new QPushButton(pQDialogHighlighter);
	pQHighlighterDialogCancel->setText("Cancel");
	pQgridLayoutHighlighterDialog->addWidget(pQHighlighterDialogCancel, 2, 2);
	connect(pQHighlighterDialogConfirm, SIGNAL(clicked()), this, SLOT(On_pQHighlighterDialogConfirm_Triggered()));
	connect(pQHighlighterDialogCancel, SIGNAL(clicked()), this, SLOT(On_pQHighlighterDialogCancel_Triggered()));
	///hide and wait for show
	pQDialogHighlighter->exec();
}
/**********************************************************************//**
@brief  Create a child dialog to log data to seleted file 
@param  
@return 
@author YHF
@date 2018/06/13   10:51
@note 
History:
**************************************************************************/
void CFemtoMonitorcenter::CreateWriteFileWindow()
{
	///dialog and gridlayout 
	pWriteDialog = new QDialog;
	pWriteDialog->resize(QSize(280, 150));
	pWriteDialog->setAttribute(Qt::WA_DeleteOnClose, true);
	pWriteGridLayout = new QGridLayout(pWriteDialog);
	pWriteGridLayout->setMargin(20);
	pWriteGridLayout->setSpacing(15);
	pQWriteDialogEdit = new QLineEdit(pWriteDialog);
	///add  linedit  and open file button
	pWriteGridLayout->addWidget(pQWriteDialogEdit, 0, 0, 1, 2);
	pQWriteDialogFileButton = new QPushButton(pWriteDialog);
	pQWriteDialogFileButton->setText("OpenFile");
	pWriteGridLayout->addWidget(pQWriteDialogFileButton, 0, 2, 1, 1);
	connect(pQWriteDialogFileButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogFileButton_clicked()));
	/// add  confirm button and cancel button
	pQWriteDialogConfirmButton = new QPushButton(pWriteDialog);
	pQWriteDialogConfirmButton->setText("Confirm");
	pWriteGridLayout->addWidget(pQWriteDialogConfirmButton, 1, 1, 1, 1);
	pQWriteDialogCancelButton = new QPushButton(pWriteDialog);
	pQWriteDialogCancelButton->setText("Cancel");
	pWriteGridLayout->addWidget(pQWriteDialogCancelButton, 1, 2, 1, 1);
	///write data to file dialog 
	connect(pQWriteDialogConfirmButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogConfirmButton_clicked()));
	connect(pQWriteDialogCancelButton, SIGNAL(clicked()), this, SLOT(On_pQWriteDialogCancelButton_clicked()));
	pWriteDialog->exec();
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
void CFemtoMonitorcenter::FunctionConnectMainWindowsRequirementSlot()
{
	///
	///qtabwidget close button 
	connect(pQMainTabWidget, SIGNAL(tabCloseRequested(int)), this, SLOT(On_TabWidget_CloseButton(int)));
	///
	///  Mainwindows triggered  in the qmenu 
	connect(pQActionOpenFileDialog, SIGNAL(triggered()), this, SLOT(On_pQActionOpenFileDialog_triggered()));
	connect(pQActionOpenHighlighterDialog, SIGNAL(triggered()), this, SLOT(On_pQActionOpenHighlighterDialog_triggered()));
	connect(pQActionOpenLogFileDialog, SIGNAL(triggered()), this, SLOT(On_pQActionOpenLogFileDialog_triggered()));
	

	///
	///Qtable widget (show  manage information  right button )
	connect(pQTableWidgetManageWidgets, SIGNAL(customContextMenuRequested(const QPoint*)), this, SLOT(On_pQTableWidgets_RightButton(const QPoint*)));



	///connect(this, SIGNAL(SignalManageThreadCloseTab(int)), &ObjCManageThreadObject, SLOT(On_GUI_SignalManageThreadCloseTab(int)));
	///connect(&ObjCManageThreadObject, SIGNAL(SignalToGUICloseCOM(int)), this, SLOT(On_ManageThread_CloseCOM(int)));
	///
	///connect the Qmessage information of faliure
	connect(this, SIGNAL(EmitQmessageInformation(QString)), this, SLOT(QMessageBoxFailure(QString)));
}