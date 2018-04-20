/**********************************************************************//**
		 Flexible TEST Server  

		 Client UART operate
*-
@file UartProcess.h
@author Dracula
@date 2017/07/03 13:42:30
@brief UartProcess.h is used for XXX

**************************************************************************/
#ifndef _UART_PROCESS_H_
#define _UART_PROCESS_H_

#include <tchar.h>
#include <Windows.h>
#include <stdio.h>

/// the write buffer size of the uart
#define UART_WRITE_BUFF_SIZE		4096
/// the read buffer size of the uart
#define UART_READ_BUFF_SIZE		(32 * 1024)

#define UART_DEFAULT_RX_INTERVAL		100

/**********************************************************************//**
@brief class for the basic operate of UART
@author Dracula
**************************************************************************/
class CUartProcess
{
friend unsigned __stdcall UartCommThread(LPVOID lpParameter);

public:
	CUartProcess(void);
	~CUartProcess(void);
	

public:
	HANDLE m_hRXBufferReady;		///< the signal event of the receiver buffer ready
	HANDLE m_ThreadEndFlag;			///< the signal event for the communication thread to end
	BOOL m_bForceStop;				///< force stop the uart communication thread
	int m_ErrorFlag;				///< the error flag
	
public:	
	/**********************************************************************//**
	@brief	get the read data
	
	the data buffer is safe as long as the process is not that time consuming
	it will get the pointer of the buffer that is not used by uart
	
	one could use the m_hRXBufferReady to signal

	@param pData 	[In] 	the data pointer that ready buffer
	@param pDataSize 	[Out] 	the size of the data in the buffer


	@return Success flag
	@author Dracula
	@date 2017/07/03 13:42:30
	@note 
	History:
	**************************************************************************/
	void GetReadyBuffer(char ** ppBuf, unsigned int * pDataSize)
	{
		unsigned int ReadyBufferIndex = m_CurRXIndex ^ 1;
		* ppBuf  = m_RXBuffer[ReadyBufferIndex];
		* pDataSize = m_RXDataSize[ReadyBufferIndex];

		char tcMsg[1024];
		sprintf(tcMsg, "Data Size %s,%u,%u,%u,%u\n", *pDataSize, strlen(*ppBuf), ReadyBufferIndex,m_RXDataSize[0], m_RXDataSize[1]);
		OutputDebugStringA(tcMsg);
	}
	BOOL SendData(char * pData, unsigned int DataSize);	
	TCHAR * GetErrorMsg()
	{
		return m_tcErrorMsg;
	}
	void SetRXInterval(unsigned int RXInterval)
	{
		m_RXInterval = RXInterval;
	}

	unsigned int GetReceiveNoDataCount()
	{
		return m_NoDataCount;
	}

public:
	BOOL Initial();
	BOOL Connection(const TCHAR * ptcUartName,unsigned int BaudRate);
	BOOL CloseConnection();
	BOOL StartUartService();
	BOOL SetBaudRate(unsigned int BaudRate);
	
protected:	
	virtual int UartCommRoutine(void);	
	void ForceBufferReady(void);
	virtual int QuickRead(char * pDataBuffer, unsigned int * pDataSizeInBuffer);
	void ClearReadBuffer();

protected:
	TCHAR m_tcErrorMsg[256];		///< the error message 
	
private:	
	HANDLE m_hUart; 	///< the uart handle
	TCHAR m_tcCOMName[32];		///< the name of the uart
	
	char m_RXBuffer[2][UART_READ_BUFF_SIZE];		///< the receiver ping pang buffer
	unsigned int m_RXDataSize[2];		///< the data size of the receive data buffer
	unsigned int m_CurRXIndex;		///< the current Index of the buffer for UART to receive
	unsigned int m_TXDataSize;		///< the data size of the Data for send

	char m_TXBuffer[UART_READ_BUFF_SIZE];		///< the receiver  buffer
	unsigned int m_RXInterval;			///< the interval for receive OS timeout (will invoke RX op event ) in unit of ms

	OVERLAPPED	m_OpRead;			///< the read overlap file structure
	OVERLAPPED	m_OpWrite;			///< the write overlap file structure
	unsigned int m_NoDataCount;		///< receive no data count
protected:
	BOOL ReadData(char * pData, unsigned int ExpectDataSize,unsigned int &ActualReadSize);
	BOOL WriteData(char * pData, unsigned int DataSize);
};
#endif
