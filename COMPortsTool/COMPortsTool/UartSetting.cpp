#include <QMessageBox>

#include "UartProcess.h"

#define MAX_UART_NUM 50

unsigned int GetAllComPorts(TCHAR * pPortList, unsigned int * ComCount)
{
	//int k=0;
	long lReg;  
	HKEY hKey;  
	DWORD MaxValueLength;  
	DWORD dwValueNumber;  
	 * ComCount = 0;

	lReg=RegOpenKeyExA(HKEY_LOCAL_MACHINE, "HARDWARE\\DEVICEMAP\\SERIALCOMM",0,KEY_QUERY_VALUE, &hKey);

	if(lReg!=ERROR_SUCCESS) //????????ERROR_SUCCESS??
	{  
		QMessageBox::critical(NULL, "critical", "Open Registry Error!\n", QMessageBox::Ok);

		//AfxMessageBox(_T("Open Registry Error!\n"));  
		return 1;	// can not open RegistryError
	}  

	lReg=RegQueryInfoKeyA(hKey, NULL, NULL,  NULL,  NULL,NULL,  NULL,  
		&dwValueNumber, //?????hKey???????
		&MaxValueLength, NULL,  NULL,  NULL);  
	if(lReg!=ERROR_SUCCESS) //??§Ô??
	{  
		QMessageBox::critical(NULL, "critical", "Getting Info Error!\n", QMessageBox::Ok);

		//AfxMessageBox(_T("Getting Info Error!\n"));  
		return 2;	
	}  

	LPSTR pValueName,pCOMNumber;  
	DWORD cchValueName,dwValueSize=6;  

	// max uart number protection
	if(dwValueNumber > MAX_UART_NUM)
		dwValueNumber = MAX_UART_NUM;
	
	 * ComCount = dwValueNumber;

	for(unsigned int i=0;i < dwValueNumber;i++)  
	{  
		cchValueName=MaxValueLength+1;  
		dwValueSize=6;  
		pValueName=(LPSTR)VirtualAlloc(NULL,cchValueName,MEM_COMMIT,PAGE_READWRITE);  
		lReg=RegEnumValueA(hKey,  i,  pValueName,  &cchValueName,  NULL,  NULL,  NULL,  NULL);  

		if((lReg!=ERROR_SUCCESS)&&(lReg!=ERROR_NO_MORE_ITEMS))  
		{  
			QMessageBox::critical(NULL, "critical", "Enum Registry Error or No More Items!\n", QMessageBox::Ok);
			QString slReg = QString("%1").arg(lReg);

			QMessageBox::critical(NULL, "critical", slReg, QMessageBox::Ok);
// 			AfxMessageBox(_T("Enum Registry Error or No More Items!\n"));  
// 			printf("lreg:=%d\n",lReg);  
// 			CString slReg;
// 			slReg.Format(_T("%d"),lReg);
// 			AfxMessageBox(slReg);
			return 3;	// can not open RegistryError
		}  

		pCOMNumber=(LPSTR)VirtualAlloc(NULL,6,MEM_COMMIT,PAGE_READWRITE);  
		lReg=RegQueryValueExA(hKey,  pValueName,  NULL,  NULL,  (LPBYTE)pCOMNumber,  &dwValueSize);  

		if(lReg!=ERROR_SUCCESS)  
		{  
			QMessageBox::critical(NULL, "critical", "Can not get the name of the port", QMessageBox::Ok);
			//AfxMessageBox(_T("Can not get the name of the port"));
			return 4;	// can not open RegistryError
		}  
#ifdef UNICODE
		int nLen = (int)strlen(pCOMNumber) + 1;
		int nwLen = MultiByteToWideChar(CP_ACP,0,pCOMNumber,nLen,NULL, 0);
		MultiByteToWideChar(CP_ACP, 0, pCOMNumber, nLen, pPortList, nwLen);

#else
		_tcscpy(pPortList,pCOMNumber);
#endif
		
		pPortList+=32;
		VirtualFree(pValueName,0,MEM_RELEASE);  
		VirtualFree(pCOMNumber,0,MEM_RELEASE);  
	}  
	return 0;
}