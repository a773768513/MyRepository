#include "CStructDataModule.h"
#include <qdebug.h>
#include "CRCChecksum.h"
#include <qfiledialog.h>
#include <qmessagebox.h>
CStructDataModule::CStructDataModule(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Initial();
	///signal and slots 
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(On_PushButton_Clicked()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(On_StartPushButton2_Clicked()));
	connect(this, SIGNAL(ThreadQmessbox(char*)), this, SLOT(On_ThreadMessBox_Information(char*)));
	///verif data 
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(On_PushButton3_Clicked()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(VerifCheckDataConvertNoDiscard()));
}

bool CStructDataModule::Initial()
{
	StorageStructDataSize[0] = 0;
	StorageStructDataSize[1] = 0;
	CurrentStorageStructDataIndex = 0;
	return 1;
}
CStructDataModule::~CStructDataModule()
{

}

void CStructDataModule::On_PushButton_Clicked()
{
	QSOpenFilePath = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	ui.lineEdit->setText(QSOpenFilePath);
}
void CStructDataModule::On_StartPushButton2_Clicked()
{
	pCQReadDataThread = new CQReadDataThread;
	QSOpenFilePath = ui.lineEdit->text();
	VerifOpenWriteDataFile();
	pCQReadDataThread->WriteOpenFilePath(QSOpenFilePath);
	connect(pCQReadDataThread, SIGNAL(Emitemitdata(char*)), this, SLOT(On_Thread_DataStrct(char*)), Qt::BlockingQueuedConnection);
	connect(pCQReadDataThread, SIGNAL(EimtThreadStop()), this, SLOT(On_ThreadStop_Slot()),Qt::BlockingQueuedConnection);
	pCQReadDataThread->start();
}

void CStructDataModule::On_Thread_DataStrct(char *emitData)
{
	int length = strlen(emitData);
	StorageTheInformation(emitData, length);
}

void  CStructDataModule::StorageTheInformation(char* pInputString, int length)
{
	char *pSeekHeader = pInputString;      /// storage the header to compare
	unsigned int MarkerPosition = 0;       ///the length before # or $;
	unsigned long LChecksumDataLength;    ///checksum data length  NOT have # and *checksum;
	unsigned  char* pChecksumData;        ///point  checksum data   NOT have # and *checksum;
	char ChecksumBuf[4];                  ///buffer for checksum 
	memset(ChecksumBuf, 0, 4);
	while (('#' != *(pSeekHeader + MarkerPosition)) && ('$' != *(pSeekHeader + MarkerPosition)))
	{
		MarkerPosition++;
		if (MarkerPosition == length)
		{
			memcpy(StorageStructData[CurrentStorageStructDataIndex] + StorageStructDataSize[CurrentStorageStructDataIndex], pInputString, length);
			StorageStructDataSize[CurrentStorageStructDataIndex] += length;
			return;
		}
	}
	memcpy(StorageStructData[CurrentStorageStructDataIndex] + StorageStructDataSize[CurrentStorageStructDataIndex], pInputString, MarkerPosition);
	StorageStructDataSize[CurrentStorageStructDataIndex] += MarkerPosition;

	if (*StorageStructData[CurrentStorageStructDataIndex] == '$')
	{
		/*****
		return ;
		memcpy(ChecksumBuf, StorageStructData[CurrentStorageStructDataIndex] + StorageStructDataSize[CurrentStorageStructDataIndex] - 1, 1);
		///change the type from char* to QString
		unsigned char NMEAChecksum = (unsigned char)ChecksumBuf[0];
		LChecksumDataLength = StorageStructDataSize[CurrentStorageStructDataIndex] - 2;
		pChecksumData = (unsigned char*)(StorageStructData[CurrentStorageStructDataIndex]);
		if (CheckNMEADataCorrectness(LChecksumDataLength,
		pChecksumData,
		NMEAChecksum))
		{
		qDebug("the data is correct");
		DataImportStruct();
		/*
		do something    emit OutputMessage and length

		///reset the length and memory
		}
		else
		{
		qDebug("the data is in-correct");
		}
		*******************/
	}
	if (*StorageStructData[CurrentStorageStructDataIndex] == '#')
	{
		/**
		memcpy(ChecksumBuf, StorageStructData[CurrentStorageStructDataIndex] + StorageStructDataSize[CurrentStorageStructDataIndex] - 4, 4);
		///change the type from char* to unsigned long
		QString QSChangeCharLongBuf = ChecksumBuf;
		unsigned long LFeiNaCheckSum = QSChangeCharLongBuf.toLong();
		LChecksumDataLength = StorageStructDataSize[CurrentStorageStructDataIndex] -5;
		pChecksumData = (unsigned char*)(StorageStructData[CurrentStorageStructDataIndex]);
		if (CheckFeiNaDataCorrectness(
		LChecksumDataLength,
		pChecksumData,
		LFeiNaCheckSum))
		{
		qDebug("the data is correct");
		DataImportStruct();
		/*
		do something    emit OutputMessage and length

		///reset the length and memory
		}
		else
		{
		qDebug("the data is in-correct");
		}
		**************/
	}

	DataImportStruct();
	StorageStructDataSize[CurrentStorageStructDataIndex] = 0;
	CurrentStorageStructDataIndex ^= 1;
	memcpy(StorageStructData[CurrentStorageStructDataIndex], pInputString + MarkerPosition, length - MarkerPosition);
	StorageStructDataSize[CurrentStorageStructDataIndex] = length - MarkerPosition;
	return;

}
/***************************************************
@brief  check data correctness
@param  ulCount [IN], Number of bytes in the data block
        ucBuffer [IN] Data block
		AcceptedChecksum [IN] 
@author  YHF
@data   2018/5/4
@
********************************************************/
bool CStructDataModule::CheckNMEADataCorrectness(
	unsigned long ulCount,
	unsigned char *ucBuffer,
	unsigned char AcceptedChecksum)
{
	unsigned char CalculationAccptionData = NMEA_Check(ulCount, ucBuffer);
	if (AcceptedChecksum == CalculationAccptionData)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/***************************************************
@brief  check data correctness
@param  ulCount [IN], Number of bytes in the data block
        ucBuffer [IN] Data block
		AcceptedChecksum [IN] 
@author  YHF
@data   2018/5/4
@
********************************************************/
bool CStructDataModule::CheckFeiNaDataCorrectness(
	unsigned long ulCount,
	unsigned char *ucBuffer,
	unsigned long AcceptedChecksum)
{
	unsigned long CalculationAccptionData = CalculateBlockCRC32(ulCount, ucBuffer);
	if (AcceptedChecksum == CalculationAccptionData)
	{
		return true;
	}
	else
	{
		return false;
	}
}
/***************************************************
@brief  Data Cor the header and Storage in Struct
@param  
@author  YHF
@data   2018/5/4
@
********************************************************/
void  CStructDataModule::DataImportStruct()
{
	if ((*StorageStructData[CurrentStorageStructDataIndex] != '#')&&(*StorageStructData[CurrentStorageStructDataIndex] != '$'))
	{
		return;
	}
	if (StorageStructDataSize[CurrentStorageStructDataIndex] == 0)
	{
		return;
	}
	char Header[16];
	memset(Header, 0, 16);
	int headerLength = 0;
	char *pData = StorageStructData[CurrentStorageStructDataIndex];
	while (*pData != ',')
	{
		headerLength++;
		pData++;
	}
	memcpy(Header, StorageStructData[CurrentStorageStructDataIndex], headerLength);
	pData = Header; 
	pData += 3;
	if (!strcmp(pData,"GGA"))
	{

		pData = StorageStructData[CurrentStorageStructDataIndex];
		GGADataStorageStruct(pData);
	}
}

void CStructDataModule::showGGADataInGUI()
{
	QString QStringShowBuf;
	///header   0
	QStringShowBuf = GGAData.GGAHeader;
	ui.lineEdit_2->setText(QStringShowBuf);
	/// get the the UTC Time  1
	QStringShowBuf.setNum(GGAData.GGAUTCTime,'f',3);
	ui.lineEdit_3->setText(QStringShowBuf);
	///  get the the Latitude 2
	QStringShowBuf.setNum(GGAData.GGALatitude,'f',7);
	ui.lineEdit_4->setText(QStringShowBuf);
	///  get the the N/S Indicator 3GGALatitude
	///QStringShowBuf = GGAData.GGANSIndicator;
	///ui.lineEdit_5->setText(QStringShowBuf);
	
	switch (GGAData.GGANSIndicator)
	{
	case N_SIndicator::N :
		QStringShowBuf = 'N';
		break;
	case N_SIndicator::S:
		QStringShowBuf = 'N';
		break;
	}
	ui.lineEdit_5->setText(QStringShowBuf);
	///  get the the Longitude   4
	QStringShowBuf.setNum(GGAData.GGALongitude,'f',7);
	ui.lineEdit_6->setText(QStringShowBuf);
	///  get the the E/W Indicator    5
	///QStringShowBuf = GGAData.GGAEWIndicator;
	///ui.lineEdit_7->setText(QStringShowBuf);
	switch (GGAData.GGAEWIndicator)
	{
	case E_WIndicator::E:
		QStringShowBuf = 'E';
		break;
	case E_WIndicator::W:
		QStringShowBuf = 'W';
		break;
	}
	ui.lineEdit_7->setText(QStringShowBuf);
	///  get the the Position Fix Indicator  6
	QStringShowBuf.setNum(GGAData.GGAPositionFixIndicator);
	ui.lineEdit_8->setText(QStringShowBuf);
	///  get the the Satellites Used  7
	QStringShowBuf.setNum(GGAData.GGASatellitesUsed);
	ui.lineEdit_9->setText(QStringShowBuf);
	///  get the the HDOP  8
	QStringShowBuf.setNum(GGAData.GGAHDOP);
	ui.lineEdit_10->setText(QStringShowBuf);
	///  get the the MSL Altitude  9GGAHDOP
	QStringShowBuf.setNum(GGAData.GGAMSLAltitude,'f',4);
	ui.lineEdit_11->setText(QStringShowBuf);
	///  get the the MSL Geoid Separation 10
	/// throw away "M"
	QStringShowBuf.setNum(GGAData.GGAGeoidSeparation,'f',3);
	ui.lineEdit_12->setText(QStringShowBuf);
	///  get the the  Age of Diff. Corr. 11
	/// throw away "M"
	QStringShowBuf.setNum(GGAData.GGAAgeofDiffCorr);
	ui.lineEdit_13->setText(QStringShowBuf);
	///  get the the  Diff. Ref. Station ID 12
	QStringShowBuf.setNum(GGAData.GGADiffRefStationID);
	ui.lineEdit_14->setText(QStringShowBuf);

	///  get the the  Dchecksm 13
	QStringShowBuf.setNum(GGAData.GGACheckSum,16);
	ui.lineEdit_15->setText(QStringShowBuf);
}
/***************************************************
@brief  synthsis the data in Data and storade the GGA data 
@param  GGAHeaderData [IN]  point the data  to  storage GGA
@author  YHF
@data   2018/5/4
@
********************************************************/
void  CStructDataModule::GGADataStorageStruct(char* GGAHeaderData)
{
	int SectionDataLength;
	char  SectionData[128];
	QString QSConvertTypeBuf;
	/// get the header
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	memcpy(GGAData.GGAHeader, SectionData, SectionDataLength);
	/// get the the UTC Time  1
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGAUTCTime = QSConvertTypeBuf.toDouble();
	///  get the the Latitude 2
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGALatitude = QSConvertTypeBuf.toDouble();
	///  get the the N/S Indicator 3
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	if (*SectionData == 'N')
	{
		GGAData.GGANSIndicator = N;
	}
	else
	{
		GGAData.GGANSIndicator = S;
	}	
	///  get the the Longitude   4
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGALongitude = QSConvertTypeBuf.toDouble();
	///  get the the E/W Indicator    5
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	if (*SectionData == 'E')
	{
		GGAData.GGAEWIndicator = E;
	}
	else
	{
		GGAData.GGAEWIndicator = W;
	}
	///  get the the Position Fix Indicator  6
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGAPositionFixIndicator = (unsigned int) QSConvertTypeBuf.toInt();
	///  get the the Satellites Used  7
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGASatellitesUsed = (unsigned int)QSConvertTypeBuf.toInt();
	///  get the the HDOP  8
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGAHDOP = QSConvertTypeBuf.toDouble();
	///  get the the MSL Altitude  9
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGAMSLAltitude = QSConvertTypeBuf.toDouble();
	///  get the the MSL Geoid Separation 10
	/// throw away "M"
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGAGeoidSeparation = QSConvertTypeBuf.toDouble();
	///  get the the  Age of Diff. Corr. 11
	/// throw away "M"
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGAAgeofDiffCorr = QSConvertTypeBuf.toInt();
	///  get the the  Diff. Ref. Station ID 12  after this data  not hanve ,  judge *
	GGAHeaderData;
	memset(SectionData, 0, 128);
	SectionDataLength = 0;
	while ((*GGAHeaderData) != '*')
	{
		(SectionDataLength)++;
		(GGAHeaderData)++;
	}
	memcpy(SectionData, GGAHeaderData - SectionDataLength, SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGADiffRefStationID = QSConvertTypeBuf.toInt();
	///  get the the  checksum
	///checksum   discard the '*'
	GGAHeaderData++;
	memset(SectionData, 0, 128);
	memcpy(SectionData, GGAHeaderData, 2);
	unsigned char StrorageU8Checksum;
	storageU8Checksum(SectionData, &StrorageU8Checksum);
	GGAData.GGACheckSum = (GGAData.GGACheckSum) & 0x00000000;
	GGAData.GGACheckSum = ((GGAData.GGACheckSum) | StrorageU8Checksum) & 0x000000ff;
	////
	showGGADataInGUI();
	VerifWriteCurrentIndexDataToFile();
}
void CStructDataModule::U8XCharConvertLong(char* U8xCharNum, unsigned long *LTenNum)
{
	
}
/***************************************************
@brief  Move Pointor To next separator
@param  pPonitingMidData [IN] [OUT]  point the data
pSectionDataLength  [OUT] section data length
SectionData     [OUT]  sCTION data
@author  YHF
@data   2018/5/4
@
********************************************************/
void  CStructDataModule::MovePointerRemoveSectionData(char **ppPonitingMidData, char* pSectionData, int* pSectionDataLength)
{
	*pSectionDataLength = 0;
	memset(pSectionData, 0, 128);
	while (',' != (*ppPonitingMidData)[0])
	{
		(*ppPonitingMidData)++;
		(*pSectionDataLength)++;
	}
	memcpy(pSectionData, (*ppPonitingMidData) - (*pSectionDataLength), *pSectionDataLength);
	(*ppPonitingMidData)++;
	return;
}
void CStructDataModule::storageU8Checksum(char* pU8Checksum, unsigned char* pStrorageU8Checksum)
{
	unsigned char DataBuf;
	///first
	if ((pU8Checksum[0] - 48) < 10)
	{
		(*pStrorageU8Checksum) = (pU8Checksum[0] - 48);
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) << 4;
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) & 0xF0;
	}
	else if ((pU8Checksum[0] - 64) < 10)
	{
		(*pStrorageU8Checksum) = (pU8Checksum[0] - 64) + 9;
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) << 4;
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) & 0xF0;
	}
	else if ((pU8Checksum[0] - 96) < 10)
	{
		(*pStrorageU8Checksum) = (pU8Checksum[0] - 96) + 9;
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) << 4;
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) & 0xF0;
	}
	///last
	if ((pU8Checksum[1] - 48) < 10)
	{
		DataBuf = (pU8Checksum[1] - 48);
		DataBuf = DataBuf & 0x0F;
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) | (DataBuf);
	}
	else if ((pU8Checksum[1] - 64) < 10)
	{

		DataBuf = (pU8Checksum[1] - 64) + 9;
		DataBuf = DataBuf & 0x0F;
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) | (DataBuf);
	}
	else if ((pU8Checksum[1] - 96) < 10)
	{
		DataBuf = (pU8Checksum[1] - 96) + 9;
		DataBuf = DataBuf & 0x0F;
		(*pStrorageU8Checksum) = (*pStrorageU8Checksum) | (DataBuf);
	}
}


void CStructDataModule::VerifOpenWriteDataFile()
{
	///char VerifFileName[128] = "C:/Users/77376/Desktop/Computer/header/11111111.txt";
	QString QSOpenFilePath2;
	QSOpenFilePath2 = ui.lineEdit_16->text();
	QByteArray QBSOpenFilePath = QSOpenFilePath2.toLatin1();
	char *VerifFileName = QBSOpenFilePath.data();
	if (VerifFileName == NULL)
	{
		return;
	}
	fpVerifFile = fopen(VerifFileName, "w+");
	if (NULL == fpVerifFile)
	{
		emit ThreadQmessbox("Open Verification File Failure");
	}
}
void CStructDataModule::VerifWriteCurrentIndexDataToFile()
{
	char StorageSectionData[16];
	memset(pVerifDataCorrectness, 0, SINGLE_DATA_LENGTH);
	int  DataOffset = 0;
	int SectionLength = 0;
	/// frist 6 char  to header and one ,   6+1
	memcpy(pVerifDataCorrectness + DataOffset, GGAData.GGAHeader, 6);
	DataOffset += 6;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset ++;
	///UTC Time     7+10+1
	SectionLength = sprintf(StorageSectionData, "%.3f", GGAData.GGAUTCTime);
	///DataOffset = strlen(pVerifDataCorrectness);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 10; 
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///  Latitude        18+12+1
	SectionLength = sprintf(StorageSectionData, "%.7f", GGAData.GGALatitude);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 12;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///N/S Indicator  DataOffset +=1+1
	switch (GGAData.GGANSIndicator)
	{
	case N_SIndicator::N:
		StorageSectionData[0] = 'N';
		break;
	case N_SIndicator::S:
		StorageSectionData[0] = 'S';
		break;
	}
	SectionLength = 1;
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 1;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///Longitude  offset+=13+1;
	SectionLength = sprintf(StorageSectionData, "%.7f", GGAData.GGALongitude);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 13;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///E/W Indicator  offsett+=1+1;
	switch (GGAData.GGAEWIndicator)
	{
	case E_WIndicator::E:
		StorageSectionData[0] = 'E';
		break;
	case E_WIndicator::W:
		StorageSectionData[0] = 'W';
		break;
	}
	SectionLength = 1;
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 1;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///Position Fix Indicator  offset 1+1

	SectionLength = sprintf(StorageSectionData, "%d", GGAData.GGAPositionFixIndicator);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 1;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///Satellites Used  offsett 2+1
	SectionLength = sprintf(StorageSectionData, "%02d", GGAData.GGASatellitesUsed);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 2;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///HDOP      OFFSET  +=3+1
	SectionLength = sprintf(StorageSectionData, "%.1f", GGAData.GGAHDOP);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 3;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	/// MSL Altitude     7+1
	SectionLength = sprintf(StorageSectionData, "%.4f", GGAData.GGAMSLAltitude);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 7;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///add  M to Data
	pVerifDataCorrectness[DataOffset] = 'M';
	DataOffset++;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///Geoid Separation  6+1 
	SectionLength = sprintf(StorageSectionData, "%.3f", GGAData.GGAGeoidSeparation);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 6;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///add  M to Data
	pVerifDataCorrectness[DataOffset] = 'M';
	DataOffset++;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///Age of Diff. Corr.  2+1
	SectionLength = sprintf(StorageSectionData, "%02d", GGAData.GGAAgeofDiffCorr);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 2;
	pVerifDataCorrectness[DataOffset] = ',';
	DataOffset++;
	///Diff. Ref. Station ID  4+1
	SectionLength = sprintf(StorageSectionData, "%04d", GGAData.GGADiffRefStationID);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, SectionLength);
	DataOffset += 4;
	///checksum    
	pVerifDataCorrectness[DataOffset] = '*';
	DataOffset++;
	QString QSpVerifDataChecksumBuf;
	QSpVerifDataChecksumBuf.setNum(GGAData.GGACheckSum, 16);
	QSpVerifDataChecksumBuf = QSpVerifDataChecksumBuf.toUpper();
	QByteArray QBpVerifDataChecksumBuf = QSpVerifDataChecksumBuf.toLatin1();
	char *pQBpVerifDataChecksumBuf = QBpVerifDataChecksumBuf.data();

	memcpy(StorageSectionData, pQBpVerifDataChecksumBuf, 2);
	memcpy(pVerifDataCorrectness + DataOffset, StorageSectionData, 2);
	DataOffset += 2;
	///add /r/n
	///pVerifDataCorrectness[DataOffset] = '\r';
	///DataOffset++;
	pVerifDataCorrectness[DataOffset] = '\n';
	DataOffset++;
	pVerifDataCorrectness[DataOffset] = '\0';
	if (NULL != fpVerifFile)
	{
		int error = fprintf(fpVerifFile, "%s", pVerifDataCorrectness);
	}
	return;
}
void CStructDataModule::On_ThreadMessBox_Information(char* ThreadQmessgeboxInformation)
{
	QMessageBox::information(this, "prompt", ThreadQmessgeboxInformation);
}
void CStructDataModule::On_PushButton3_Clicked()
{
	QString  QSOpenFilePath2;
	QSOpenFilePath2 = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	ui.lineEdit_16->setText(QSOpenFilePath2);
}
void CStructDataModule::On_ThreadStop_Slot()
{
	///showGGADataInGUI();
	///VerifWriteCurrentIndexDataToFile();
	fclose(fpVerifFile);
}
void CStructDataModule::VerifCheckDataConvertNoDiscard()
{
	char fpOpenFilePathBuf[512];
	char fpVerifFileBuf[512];
	long fpOpenFilePathLength;
	long fpVerifFileLength;

	QSOpenFilePath = ui.lineEdit->text();
	QByteArray  QBOpenFilePathBuf = QSOpenFilePath.toLatin1();
	char *pOpenFile = QBOpenFilePathBuf.data();
	fpOpenFilePath = fopen(pOpenFile, "r+");
	if (fpOpenFilePath == NULL)
	{
		return;
	}
	QSOpenFilePath = ui.lineEdit_16->text();
	QBOpenFilePathBuf = QSOpenFilePath.toLatin1();
	pOpenFile = QBOpenFilePathBuf.data();
	fpVerifFile = fopen(pOpenFile, "r+");
	if (fpVerifFile == NULL)
	{
		return;
	}
	fseek(fpOpenFilePath, 0L, SEEK_END);
	fseek(fpVerifFile, 0L, SEEK_END);

	fpOpenFilePathLength = ftell(fpOpenFilePath);
	fpVerifFileLength = ftell(fpVerifFile);
	if (fpOpenFilePathLength != fpVerifFileLength)
	{
		On_ThreadMessBox_Information("data lost ");

	}
		fseek(fpOpenFilePath, 0L, SEEK_SET);
		fseek(fpVerifFile, 0L, SEEK_SET);
		if (!feof(fpOpenFilePath))
		{
			fgets(fpOpenFilePathBuf, 512, fpOpenFilePath);
			fgets(fpVerifFileBuf, 512, fpVerifFile);
			if (strcmp(fpOpenFilePathBuf, fpVerifFileBuf))
			{

				 On_ThreadMessBox_Information("data lost ");
			}
		}
	On_ThreadMessBox_Information("data correctness ");
}