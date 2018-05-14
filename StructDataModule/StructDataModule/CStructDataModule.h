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
	void  StorageTheInformation(char* pInputString, int length);

private:
	char  StorageStructData[2][SINGLE_DATA_LENGTH];   ///PINGPONG memory to storage the input datap
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
		char   GGAHeader[16];
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
		unsigned int  GGAAgeofDiffCorr;
		unsigned int  GGADiffRefStationID;
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
	void showGGADataInGUI();
	void storageU8Checksum(char* pU8Checksum,unsigned char* pStrorageU8Checksum);

	void U8XCharConvertLong(char* OxCharNum, unsigned long *LTenNum);
	/********verif variable

	**********************/
	FILE* fpOpenFilePath;
	FILE *fpVerifFile;
	char *pVerifDataCorrectness = (char*)malloc(sizeof(char)*SINGLE_DATA_LENGTH);
	void VerifOpenWriteDataFile();
	void VerifWriteCurrentIndexDataToFile();
signals:
	void ThreadQmessbox(char* pQMessageboxInformation);
public slots:
   void On_PushButton_Clicked();
   void On_StartPushButton2_Clicked();
   void On_PushButton3_Clicked();
   void On_Thread_DataStrct(char *emitData);
   void On_ThreadMessBox_Information(char* pQMessageboxInformation);
   void On_ThreadStop_Slot();
   ///verif slots 
	void VerifCheckDataConvertNoDiscard();
};
