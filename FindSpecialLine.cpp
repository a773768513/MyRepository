/*******************************************************//**


@file  FindSpecialLine.cpp              
@author YHF
@data 2018/2/4
@
***********************************************************/
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "InputCharWriteIn.h"

int main()
{
	char *pMatch;                                 ///<pass a pointer to input character
	int InputCharLength;                         ///<pass the length of input character
	RecordInputCharBuf(&pMatch,InputCharLength);                            
	OutputSpecialLineToFile(pMatch,InputCharLength);          
	delete[] pMatch;                              ///<free memory allocated in the function
	return 0;
}