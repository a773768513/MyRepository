
#include <qfiledialog.h>
#include <qcolordialog.h>
#include <qmessagebox.h>
#include "AssertModule.h"
#include "CCOMPortsTool.h"
#include <tchar.h>
#include "UartSetting.h"
#include <qlineedit.h>
void CCOMPortsTool::On_pConnectDialogAction_Triggered()
{
	CreateConnectChildWindows();
}
void  CCOMPortsTool::On_pQOpenWriteFileDialogAction_Triggered()
{
	CreateWriteFileWindow();
}
void CCOMPortsTool::CreateWriteFileWindow()
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
void CCOMPortsTool::On_pQWriteDialogFileButton_clicked()
{
	QString QSOpenFile = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	this->pQWriteDialogEdit->setText(QSOpenFile);
}
void CCOMPortsTool::On_pQWriteDialogConfirmButton_clicked()
{

}
void CCOMPortsTool::On_pQWriteDialogCancelButton_clicked()
{
	pWriteDialog->close();
}

void CCOMPortsTool::CreateConnectChildWindows()
{
	pDialogOpenFile = new QDialog;
	pDialogOpenFile->setAttribute(Qt::WA_DeleteOnClose, true);
	pGridLayoutOpenFileDialog = new QGridLayout(pDialogOpenFile);
	////pGridLayoutOpenFileDialog->setSizeConstraint(QLayout::SetFixedSize);  ///fixed dialog (for hide the pQWidgetDetail but no change the widget relative position
	pGridLayoutOpenFileDialog->setSpacing(20);
	pGridLayoutOpenFileDialog->setMargin(20);
	///label  to title the user
	pQLabelConnectChildTitle = new QLabel(pDialogOpenFile);
	pQLabelConnectChildTitle->setText("Select COM Ports");
	pGridLayoutOpenFileDialog->addWidget(pQLabelConnectChildTitle, 0, 0, 1, 1);

	/// combobox to show the 
	pQCOMPortsList = new QComboBox(pDialogOpenFile);
	FillPortListComboBox();
	pGridLayoutOpenFileDialog->addWidget(pQCOMPortsList, 0, 1, 1, 2);

	///confirm button  and cancel button pQPushButttonOpenFileConfirm
	pQPushButttonOpenFileConfirm = new QPushButton(pDialogOpenFile);
	pQPushButttonOpenFileConfirm->setText("Confirm");
	pGridLayoutOpenFileDialog->addWidget(pQPushButttonOpenFileConfirm, 1, 1);
	pQPushButtonOpenFileCancel = new QPushButton(pDialogOpenFile);
	pQPushButtonOpenFileCancel->setText("Cancel");
	pGridLayoutOpenFileDialog->addWidget(pQPushButtonOpenFileCancel, 1, 2);
	connect(pQPushButttonOpenFileConfirm, SIGNAL(clicked()), this, SLOT(On_pQConnectOpenFileConfirm_Clicked()));
	connect(pQPushButtonOpenFileCancel, SIGNAL(clicked()), this, SLOT(On_pQConnectOpenFileCancel_Clicked()));

	pGridLayoutOpenFileDialog->setColumnStretch(0, 0);
	pGridLayoutOpenFileDialog->setColumnStretch(1, 1);
	pGridLayoutOpenFileDialog->setColumnStretch(2, 1);
	pDialogOpenFile->exec();
}

void CCOMPortsTool::On_pQConnectOpenFileConfirm_Clicked()
{
	QString  TabTitle = pQCOMPortsList->currentText();
	pDialogOpenFile->close();
	///set max line and warp mode 
	CQThreadTextBrowser* pCQThreadTextBrowser = new CQThreadTextBrowser(this);
	pQMainTabWidget->addTab(pCQThreadTextBrowser, TabTitle);
	///force change the char to tchar;
	TCHAR * pUartName = (TCHAR *)reinterpret_cast<const wchar_t *>(TabTitle.utf16());
	pCQThreadTextBrowser->StartPortsConnect(pUartName);
}
void CCOMPortsTool::On_pQConnectOpenFileCancel_Clicked()
{
	this->pDialogOpenFile->close();
}

void CCOMPortsTool::FillPortListComboBox()
{
	QString      QPortString;
	unsigned int PortNumBin[50];
	unsigned int iPort;
	unsigned int PortNum;
	signed   int iNum;

	TCHAR * pPortList = m_PortList;
	TCHAR * pTemp;

	GetAllComPorts(pPortList, &m_ComCount);

	if (m_ComCount > 0)
	{
		this->pQCOMPortsList->clear();

		/// get port number and sort
		for (iPort = 0; iPort < m_ComCount; iPort++, pPortList += 32)
		{
			pTemp = pPortList + 3;
			PortNum = _ttoi(pTemp);

			if (iPort > 0)
			{
				iNum = iPort - 1;

				while (PortNum < PortNumBin[iNum])
				{
					PortNumBin[iNum + 1] = PortNumBin[iNum];
					iNum--;

					if (iNum < 0)
					{
						break;
					}
				}

				PortNumBin[iNum + 1] = PortNum;
			}
			else
			{
				PortNumBin[iPort] = PortNum;
			}
		}

		for (iPort = 0; iPort < m_ComCount; iPort++)
		{
			QPortString.sprintf("COM%u", PortNumBin[iPort]);
			this->pQCOMPortsList->addItem(QPortString);
		}
	}
}