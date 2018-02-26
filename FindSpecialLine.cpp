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
	char **pMatch;                                         ///<pass a pointer to input character
	unsigned int *InputCharLength;                         ///<pass the length of input character
	int NumberMarks;                                       ///total of N logo head
	MultipleIdentiHead(&pMatch,&InputCharLength,NumberMarks);                        
	OutputSpecialLineToFile(pMatch,InputCharLength,NumberMarks);  
	NumberMarks--;
	while(1+NumberMarks)
	{
		free(pMatch[NumberMarks--]);                              ///<free memory allocated in the function
	}
	
	free(InputCharLength);
	return 0;
}