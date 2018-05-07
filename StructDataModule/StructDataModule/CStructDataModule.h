#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CStructDataModule.h"
#include <stdio.h>
#include <tchar.h>
#include <QReadDataThread.h>

#ifndef  SINGLE_DATA_LENGTH
#define  SINGLE_DATA_LENGTH   1024*8
#endif

class CStructDataModule : public QMainWindow
{
	Q_OBJECT

public:
	CStructDataModule(QWidget *parent = Q_NULLPTR);

	~CStructDataModule();
private:
	Ui::CStructDataModuleClass ui;
public:
	int StorageTheInformation(char* pInputString, int length);

private:
	char  StorageStructData[2][SINGLE_DATA_LENGTH];   ///PINGPONG memory to storage the input data
	unsigned long  StorageStructDataSize[2];               ///the data size in receive the data buffer
	unsigned int   CurrentStorageStructDataIndex;

	QString QSChecksumBuf; /// using to chang  the checksum form char* to unsigned char;
	enum N_SIndicator
	{
		N, S
	};
	enum E_WIndicator
	{
		E, W
	};
	struct StrGGAData
	{
		char   *GGAHeader;
		double  GGAUTCTime;
		double  GGALatitude;
		N_SIndicator    GGANSIndicator;
		double  GGALongitude;
		E_WIndicator    GGAEWIndicator;
		unsigned int    GGAPositionFixIndicator;
		unsigned int    GGASatellitesUsed;
		double  GGAHDOP;
		double  GGAMSLAltitude;
		double  GGAGeoidSeparation;
		double  GGAAgeofDiffCorr;
		double  GGADiffRefStationID;
		unsigned long  GGACheckSum;
	};
	StrGGAData  GGAData;
	QString  QSOpenFilePath;
	CQReadDataThread *pCQReadDataThread;
private:
	bool Initial();
	void DataImportStruct();
	void GGADataStorageStruct(char* GGAHeaderData);
	void MovePointerRemoveSectionData(char **ppPonitingMidData, char* pSectionData, int* pSectionDataLength);
	bool CheckNMEADataCorrectness(unsigned long ulCount, unsigned char *ucBuffer, unsigned char AcceptedChecksum);
	bool CheckFeiNaDataCorrectness(unsigned long ulCount, unsigned char *ucBuffer, unsigned long AcceptedChecksum);

public slots:
   void On_PushButton_Clicked();
   void On_StartPushButton2_Clicked();
  
};
