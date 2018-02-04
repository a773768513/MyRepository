/*******************************************************//**


@file  FindSpecialLine.cpp              
@author YHF
@data 2018/2/4
@
***********************************************************/
# include "function.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>


int main()
{
	char *pMatch;                                 ///<pass a pointer to input character
	int iInputCharLength;                         ///<pass the length of input character
	ReadBuf(&pMatch,iInputCharLength);                            
	OutputFile(pMatch,iInputCharLength);          
	delete[] pMatch;                              ///<free memory allocated in the function
	return 0;
}