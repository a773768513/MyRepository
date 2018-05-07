#include "CStructDataModule.h"
#include <qdebug.h>
#include "CRCChecksum.h"
#include <qfiledialog.h>
CStructDataModule::CStructDataModule(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	Initial();
	///signal and slots 
	
}

bool CStructDataModule::Initial()
{
	StorageStructDataSize[0] = 0;
	StorageStructDataSize[1] = 0;
	CurrentStorageStructDataIndex = 0;
	return 1;
}

void CStructDataModule::On_PushButton_Clicked()
{
	QString  QSOpenFilePath = QFileDialog::getOpenFileName(NULL, "OpenFile", ".", NULL);
	ui.lineEdit->setText(QSOpenFilePath);
}
void CStructDataModule::On_StartPushButton2_Clicked()
{
	pCQReadDataThread = new CQReadDataThread;
	pCQReadDataThread->WriteOpenFilePath();
}

CStructDataModule::~CStructDataModule()
{

}

int CStructDataModule::StorageTheInformation(char* pInputString, int length)
{
	char *pSeekHeader = pInputString;      /// storage the header to compare
	unsigned int MarkerPosition = 0;       ///the length before # or $;
	unsigned long LChecksumDataLength;    ///checksum data length  NOT have # and *checksum;
	unsigned  char* pChecksumData;        ///point  checksum data   NOT have # and *checksum;
	char ChecksumBuf[4];                  ///buffer for checksum 
	memset(ChecksumBuf, 0, 4);
	while (('#' != *(pSeekHeader + MarkerPosition)) || ('$' != *(pSeekHeader + MarkerPosition)))
	{
		MarkerPosition++;
		if (MarkerPosition == length)
		{
			memcpy(StorageStructData[CurrentStorageStructDataIndex] + StorageStructDataSize[CurrentStorageStructDataIndex], pInputString, length);
			StorageStructDataSize[CurrentStorageStructDataIndex] += length;
			return 0;
		}
	}
	memcpy(StorageStructData[CurrentStorageStructDataIndex] + StorageStructDataSize[CurrentStorageStructDataIndex], pInputString, MarkerPosition);
	StorageStructDataSize[CurrentStorageStructDataIndex] += MarkerPosition;
	if (*StorageStructData[CurrentStorageStructDataIndex] == '$')
	{
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
			*/
			///reset the length and memory
		}
		else
		{
			qDebug("the data is in-correct");
		}
	}
	if (*StorageStructData[CurrentStorageStructDataIndex] == '#')
	{
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
			*/
			///reset the length and memory
		}
		else
		{
			qDebug("the data is in-correct");
		}
	}

	StorageStructDataSize[CurrentStorageStructDataIndex] = 0;
	CurrentStorageStructDataIndex ^= 1;
	memcpy(StorageStructData[CurrentStorageStructDataIndex], pInputString + MarkerPosition, length - MarkerPosition);
	return 0;
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
	if ((*StorageStructData[CurrentStorageStructDataIndex] != '#')&(*StorageStructData[CurrentStorageStructDataIndex] != '$'))
	{
		return;
	}

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
	if ('GGA' != *(SectionData + 3))
	{
		qDebug("DataStoragetoGGA failure");
		return;
	}
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
	GGAData.GGAAgeofDiffCorr = QSConvertTypeBuf.toDouble();
	///  get the the  Diff. Ref. Station ID 12
	MovePointerRemoveSectionData(&GGAHeaderData, SectionData, &SectionDataLength);
	QSConvertTypeBuf = SectionData;
	GGAData.GGADiffRefStationID = QSConvertTypeBuf.toDouble();
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
	while (',' != **ppPonitingMidData)
	{
		*ppPonitingMidData++;
		*pSectionDataLength++;
	}
	memcpy(pSectionData, (*ppPonitingMidData) - (*pSectionDataLength), *pSectionDataLength);
	*ppPonitingMidData++;
	return;
}
