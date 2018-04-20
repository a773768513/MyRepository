/**********************************************************************//**
		 Flexible TEST Server  

		 Client UART operate
*-
@file UartProcess.cpp
@author Dracula
@date 2017/07/03 13:42:30
@brief UartProcess.cpp is used for basic operate of UART

**************************************************************************/
#include "UartProcess.h"
#include <process.h>

#include <stdio.h>
#include "string.h"
#include <tchar.h>



CUartProcess::CUartProcess(void)
{
	m_hUart = NULL;
	m_hRXBufferReady = NULL;
	m_ThreadEndFlag = NULL;

	memset(m_RXBuffer, 0, UART_READ_BUFF_SIZE * 2);
	memset(m_TXBuffer, 0, UART_READ_BUFF_SIZE);

	m_RXInterval = 100;

	memset(&m_OpRead,0,sizeof(OVERLAPPED));
	memset(&m_OpWrite,0,sizeof(OVERLAPPED));
	
	m_NoDataCount = 0;
	Initial();
}

CUartProcess::~CUartProcess(void)
{
	CloseConnection();

}
/**********************************************************************//**
@brief	Initial the uart process related parameters

@return Success flag

@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
BOOL CUartProcess::Initial()
{
	CloseConnection();

	m_hRXBufferReady = CreateEvent(NULL,TRUE,FALSE,NULL);	// initial as true so that read will perform first
	
	m_ThreadEndFlag = CreateEvent(NULL,TRUE,FALSE,NULL);

	m_bForceStop = FALSE;
	m_hUart = NULL;
	
	m_tcCOMName[0] = _T('\0');
	m_tcErrorMsg[0] = _T('\0');

	m_RXDataSize[0] = 0;
	m_RXDataSize[1] = 0;	

	m_CurRXIndex = 0;
	m_TXDataSize = 0;

	m_OpRead.hEvent = CreateEvent(NULL,TRUE,TRUE,NULL);//manual reset; initial state: signaled;
	m_OpRead.Offset = 0;
	m_OpRead.OffsetHigh = 0;
	m_OpWrite.hEvent = CreateEvent(NULL,TRUE,TRUE,NULL);
	m_OpWrite.Offset = 0;
	m_OpWrite.OffsetHigh = 0;

	return TRUE;

}
/**********************************************************************//**
@brief	close the uart connection

wait for uart service process  to terminate and
close all the handles

@return Success flag

@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
BOOL CUartProcess::CloseConnection()
{
	
	if(m_hRXBufferReady)
	{
		CloseHandle(m_hRXBufferReady);
		m_hRXBufferReady = NULL;
	}
	if(m_ThreadEndFlag)
	{
		CloseHandle(m_ThreadEndFlag);
		m_ThreadEndFlag = NULL;
	}
	if(m_hUart)
	{
		// TODO: check if the thread is already invoked
		WaitForSingleObject(m_ThreadEndFlag,INFINITE);

		if(m_OpRead.hEvent)
			CloseHandle(m_OpRead.hEvent );
		if(m_OpWrite.hEvent)
			CloseHandle(m_OpWrite.hEvent );		
			
		CloseHandle(m_hUart);
		m_hUart = NULL;
	}
	return TRUE;
}
/**********************************************************************//**
@brief	connect the uart
@param ptcUartName 	[In] 	uart name
@param BaudRate 	[In] 	baud rate

@return Success flag
@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
BOOL CUartProcess::Connection(const TCHAR * ptcUartName,unsigned int BaudRate)
{
	DCB dcb ;
	TCHAR UartName4Connect[32];

	// notice the for windows AIP if the com number is bigger than 9, shall use ////.//COM%d
	unsigned int UartNumber = _tstoi(ptcUartName+3);
	if (UartNumber > 9)
	{
		_stprintf_s(UartName4Connect, _T("\\\\.\\%s"), ptcUartName);
	} 
	else
	{
		_tcscpy(UartName4Connect,ptcUartName);
	}

	_tcscpy(m_tcCOMName,ptcUartName);
	
	m_hUart = CreateFile(UartName4Connect,
		GENERIC_READ | GENERIC_WRITE,
		0,	//exclusive
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_OVERLAPPED,//read/write return immediately
		0);
	
	if(m_hUart == INVALID_HANDLE_VALUE) 
	{
		_tcscpy(m_tcErrorMsg,m_tcCOMName);
		_tcscat(m_tcErrorMsg,_T(" has been opened, please detect the device!"));
		m_hUart = NULL;
		return FALSE;
	}

//Section 3: config Uart
	//event mask
	if (!SetCommMask( m_hUart, EV_RXCHAR))
	{
		return FALSE;
	}
	//set write/read buffer size
	if (!SetupComm( m_hUart, UART_WRITE_BUFF_SIZE, UART_READ_BUFF_SIZE ))
	{
		return FALSE;
	}
	//clean buffer
	if (!PurgeComm( m_hUart, PURGE_TXABORT | PURGE_RXABORT |PURGE_TXCLEAR | PURGE_RXCLEAR ))
	{
		return FALSE;
	}

	dcb.DCBlength = sizeof( DCB );
	GetCommState( m_hUart, &dcb );
	dcb.BaudRate = BaudRate;
	dcb.ByteSize = 8;
	dcb.Parity =  NOPARITY;
	dcb.StopBits = ONESTOPBIT ;
	dcb.EvtChar = 0x0d;
	dcb.fBinary = TRUE;
	//dcb.fParity = TRUE;

	if (!SetCommState( m_hUart, &dcb))
	{
		return FALSE;
	}

	//config timeouts
	COMMTIMEOUTS uart_timeout_sets;
	GetCommTimeouts(m_hUart,&uart_timeout_sets);
	uart_timeout_sets.ReadIntervalTimeout = 0;	// in unit of ms
	uart_timeout_sets.ReadTotalTimeoutConstant = 1024;
	if(!SetCommTimeouts(m_hUart,&uart_timeout_sets))
		return false;

	//Sends the DTR (data-terminal-ready) signal	
	if (!EscapeCommFunction( m_hUart, SETDTR ))
	{
		return FALSE;
	}

	return TRUE;
}
/**********************************************************************//**
@brief	read data from UART

for the internal use
@param pData 	[In] 	the buffer pointer that read data store
@param ExpectDataSize 	[In] 	expect read data size, if exceed, the m_OpRead signal
	will be invoked
@param &ActualReadSize 	[Out] 	the actual data size of read

@return Success flag

@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
-2017.07.08 clear code
**************************************************************************/
BOOL CUartProcess:: ReadData(char * pData, unsigned int ExpectDataSize,unsigned int &ActualReadSize)
{
	if (!m_hUart)
	{
		return FALSE;
	}

	DWORD	dwErrorFlags;
	COMSTAT ComStat;
	DWORD dwLength;
	DWORD dwActualReadThisTime = 0;
	BOOL bReadState;

	// the signal is set when 1) uart_timeout_sets.ReadIntervalTimeout 2) the size of the read file required is reached
	int WaitFlag = WaitForSingleObject(m_OpRead.hEvent, m_RXInterval);
	if ((WAIT_OBJECT_0 == WaitFlag) || (WAIT_TIMEOUT == WaitFlag))
	//if (WaitCommEvent(m_hUart, &dwCommEvent, &m_OpRead))
	{
		ClearCommError( m_hUart, &dwErrorFlags, &ComStat);

		if(ExpectDataSize > (UART_READ_BUFF_SIZE >> 1))
			ExpectDataSize = (UART_READ_BUFF_SIZE >> 1);
			
		if ((DWORD) ExpectDataSize > ComStat.cbInQue)
			dwLength =  ComStat.cbInQue;
		else
			dwLength = ExpectDataSize;

		ResetEvent(m_OpRead.hEvent);// reset first for preparing next read event
		bReadState = ReadFile( m_hUart, pData,dwLength, &dwActualReadThisTime, &m_OpRead);

		#if 0
		char cTest[128];
		static int TestCount = 0;
		sprintf(cTest, "Get Data %d %d\n", TestCount++, dwActualReadThisTime);
		OutputDebugStringA(cTest);
		#endif

		ActualReadSize = (unsigned int)dwActualReadThisTime;
		while (!bReadState)  
		{
			DWORD dwError = GetLastError();
			switch (dwError)
			{
			case ERROR_IO_PENDING:
				{
					dwActualReadThisTime = 0;

					bReadState = GetOverlappedResult(m_hUart,	// Handle to COMM port 
						&m_OpRead,		// Overlapped structure
						&dwActualReadThisTime,		// Stores number of bytes sent
						TRUE); 			// Wait flag

					ActualReadSize += (unsigned int)dwActualReadThisTime;

					break;
				}
			default:
				{
					// all other error codes
					return FALSE;
				}
			}
		}

		if (ActualReadSize)
		{
			return TRUE;
		}
		else
			return FALSE;
		
	}
	else
	{
		// TODO: Fast read mode do not wait for the m_RXInterval
		//OutputDebugStringA("Wait RX ready Timeout\n");
	}
	return FALSE;
}
/**********************************************************************//**
@brief	write data to the uart

for the internal use
block process, not use the handle

@param pData 	[In] 	the data pointer that expected to send
@param DataSize 	[In] 	the size of the data expected to send
@return Success flag

@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
BOOL CUartProcess:: WriteData(char * pData, unsigned int DataSize)
{
	if (!m_hUart)
	{
		return FALSE;
	}

	DWORD	dwErrorFlags;
	COMSTAT	ComStat;
	DWORD BytesSent = 0;
	BOOL bResult;

	ClearCommError(m_hUart, &dwErrorFlags, &ComStat ) ;
	PurgeComm(m_hUart, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	bResult = WriteFile(m_hUart, pData,(DWORD)DataSize, &BytesSent, &m_OpWrite);

	//OutputDebugStringA(pData);

	while (!bResult)  
	{
		DWORD dwError = GetLastError();
		switch (dwError)
		{
			case ERROR_IO_PENDING:
			{
				BytesSent = 0;

				bResult = GetOverlappedResult(m_hUart,	// Handle to COMM port 
					&m_OpWrite,		// Overlapped structure
					&BytesSent,		// Stores number of bytes sent
					TRUE); 			// Wait flag

				break;
			}
			default:
			{
				// all other error codes
				return FALSE;
			}
		}
	}

	return TRUE;
}
void CUartProcess::ForceBufferReady(void)
{
	//switch ping pang buffer
	m_CurRXIndex ^= 1;
	m_RXDataSize[m_CurRXIndex] = 0;
	
	// seems force m_hRXBufferReady ready does not work
	//SetEvent(m_hRXBufferReady);
}
/**********************************************************************//**
@brief	the uart communication routine

it will invoked in the service thread
the data read and send will be execute in here
@return Error flag

@retval 0: success
@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
- 2017.07.18 reduce the max size of UART ready to avoid overflow
- 2017.07.08 Fix a bug that CPU load is too high
**************************************************************************/
int CUartProcess::UartCommRoutine(void)
{
	BOOL bRead;
	while(!m_bForceStop)
	{
		unsigned int ActualReadData = 0;
		// the max size of the data size of last buffer is (UART_READ_BUFF_SIZE >> 1), if the reas size of this time 
		// is larger the the (UART_READ_BUFF_SIZE >> 1) if might overflow
		bRead = ReadData(m_RXBuffer[m_CurRXIndex]+m_RXDataSize[m_CurRXIndex], 
		(UART_READ_BUFF_SIZE >> 2), ActualReadData);

		if(bRead)
		{

			///printf("ReadData %6u Index %6d DataBuffer %6u\n",ActualReadData,m_CurRXIndex,m_RXDataSize[m_CurRXIndex]);

			QuickRead(m_RXBuffer[m_CurRXIndex] + m_RXDataSize[m_CurRXIndex], &ActualReadData);
			m_RXDataSize[m_CurRXIndex] += ActualReadData;
			///m_RXDataSize[m_CurRXIndex] += ActualReadData;
			////QuickRead(m_RXBuffer[m_CurRXIndex], &(m_RXDataSize[m_CurRXIndex]));


			// the current ping buffer is full
			if(m_RXDataSize[m_CurRXIndex] > (UART_READ_BUFF_SIZE >> 1))
			{
				//switch ping pang buffer
				m_CurRXIndex ^= 1;
				m_RXDataSize[m_CurRXIndex] = 0;
				SetEvent(m_hRXBufferReady);

			}
			m_NoDataCount = 0;
		}
		else
		{
			m_NoDataCount++;
		}
		

		if(m_TXDataSize)
		{
			BOOL bSend;
			bSend = WriteData(m_TXBuffer, m_TXDataSize);
			if(bSend)
			{
				m_TXDataSize = 0;
			}
		}

		Sleep(m_RXInterval >> 1);
	}

	return 0;
}
/**********************************************************************//**
@brief	Send data
send data interface

if there is a data required to send are not finished sending yet
it returns false

@param pData 	[In] 	the data pointer that expected to send
@param DataSize 	[In] 	the size of the data expected to send


@return Success flag
@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
BOOL CUartProcess::SendData(char * pData, unsigned int DataSize)
{
	if(m_TXDataSize)
		return FALSE;

	if(DataSize > UART_WRITE_BUFF_SIZE)
		return FALSE;

	memcpy(m_TXBuffer, pData,DataSize);

	m_TXDataSize = DataSize;

	return TRUE;
}

/**********************************************************************//**
@brief	Start uart service thread

for user to invoke

@return Success flag
@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
BOOL CUartProcess::StartUartService()
{
	ResetEvent(m_ThreadEndFlag);
	unsigned int ThreadAddr;
	// Create a thread for this client. 
	HANDLE  hThread = (HANDLE)_beginthreadex(NULL, 0,
			&UartCommThread,
		 	this,
		 	0,
		 	&ThreadAddr);
	if (hThread == NULL) 
	{
		return FALSE;
	}
	else 
	{
		CloseHandle(hThread);
		return TRUE;
	}

}
/**********************************************************************//**
@brief	set the baud rate of the UART

do not need the disconnect the uart

@return Success flag
@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
BOOL CUartProcess::SetBaudRate(unsigned int BaudRate)
{
	DCB dcb ;
	dcb.DCBlength = sizeof( DCB );
	GetCommState( m_hUart, &dcb );
	dcb.BaudRate = BaudRate;
	dcb.ByteSize = 8;
	dcb.Parity =  NOPARITY;
	dcb.StopBits = ONESTOPBIT ;
	dcb.EvtChar = 0x0d;
	dcb.fBinary = TRUE;
	//dcb.fParity = TRUE;

	//this->ClearReadBuffer();

	if (!SetCommState( m_hUart, &dcb))
	{
		return FALSE;
	}
	return TRUE;
}
/**********************************************************************//**
@brief Clear read buffer

@author Dracula
@date 2017/07/28 13:42:30
@note 
History:
**************************************************************************/
void CUartProcess::ClearReadBuffer(void)
{
	memset(m_RXBuffer, 0, sizeof(char) * 2 * UART_READ_BUFF_SIZE);
	m_RXDataSize[0] = 0;
	m_RXDataSize[1] = 0;
	m_CurRXIndex = 0;
}
/**********************************************************************//**
@brief	get the received data ASAP rather than wait for the ping pang buffer ready

for further usage extension e.g. XModem
the ping pang buffer mechanism does not work automatically here
one shall deal with the data in the buffer by himself 
e.g. for XModem, one shall clear the received key word manually

@param	pDataBuffer [In] 	the read buffer(do not know which ping pang buffer)
@param	DataSizeInBuffer [InOut]  the total data size in the buffer

@return Success flag
@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
int CUartProcess::QuickRead(char * pDataBuffer, unsigned int * pDataSizeInBuffer)
{	
	//char tcMsg[1024];
	//sprintf(tcMsg, "Data Size %s,%u,%u,%u,%u\n", *pDataSize, strlen(*ppBuf), ReadyBufferIndex, m_RXDataSize[0], m_RXDataSize[1]);
	OutputDebugStringA(pDataBuffer);

	return TRUE;
}
/**********************************************************************//**
@brief	uart service thread

@param	lpParameter [In] 	thread process parameters

@author Dracula
@date 2017/07/03 13:42:30
@note 
History:
**************************************************************************/
unsigned __stdcall UartCommThread(LPVOID lpParameter)
{
	CUartProcess * pUart = (CUartProcess * )lpParameter;
	
	pUart->UartCommRoutine();
	
	SetEvent(pUart->m_ThreadEndFlag);

	return 0;
}
