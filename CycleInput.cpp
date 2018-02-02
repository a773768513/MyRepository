#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char buf[10];
	char *pMatch = new char[10];
	int iCharLength = 0;
	while(printf("%s",&pMatch))
	{
		{
		  iCharLength = strlen(pMatch) + strlen (buf) + 1;
		  char *pStiting = new char[iCharLength];
		  pStiting = strcat(pMatch,buf);
		  delete[] pMatch;
		  pMatch = new char[iCharLength];
		  pMatch = pStiting;
		}
	}
}