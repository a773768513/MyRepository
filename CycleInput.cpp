#include <stdlib.h>
#include <string.h>
#include <stdio.h>
///

void  JudgeMemory(char* pJudgeMemory)
{
   if (pJudgeMemory ==NULL)
	   {
		   printf("No enough stroage,Memory allocate failed,press any key to exit");
	       getchar();
		   getchar();
	   	   exit(EXIT_FAILURE);
	   }
}

int main ()
{
	int size = 10;                  ///the length of the array to first read the character each time
	int iActiveLength,iTotalLength;  ///
	char *pReadBuf = (char*)malloc(sizeof(char)*size);
	void (*pReadBuf);
	///read fixed length character form input stream
	pReadBuf = fgets(pReadBuf,size,stdin);
	iActiveLength = strlen(pReadBuf);     
	char *pAllChar = (char*)malloc(sizeof(char)*(iActiveLength+1));
	void (*pAllChar);
	strcpy(pAllChar,pReadBuf);
	///judge whether newline in the last one
	///allocate new length to pAllChar rach time
	while(pAllChar[iActiveLength-1] != '\n')
	{
		fgets(pReadBuf,size,stdin);
		iActiveLength = strlen (pReadBuf);
		iTotalLength += iActiveLength;
		pAllChar = (char*)realloc(pAllChar,sizeof(char)*iTotalLength);
	    void (*pAllLength);
		strcpy(pAllChar+iTotalLength-iActiveLength,pReadBuf);
	}
	free(pReadBuf);
	pReadBuf = NULL;
	return 0;
}