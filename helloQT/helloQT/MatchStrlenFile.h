/****************************//**
Match String module
@file  MatchStrInFile.h
@author YHF
@data  2018/2/27
@brief
*****************************/
#ifndef __MATCH_STRLEN_FILE__
#define __MATCH_STRLEN_FILE__

#ifndef __READ_SIZE__
#define __READ_SIZE__
#define READ_SIZE 128
#endif

int MatchLessLengthStrInFile(char* pInputStr, const int InputStrLength, char* pInputFile, char* pWriteFile, char* pStandardFile);
int MatchMoreLengthStrInFile(char* pInputStr, const int InputStrLength, char* pInputFile, char* pWriteFile, char* pStandardFile);
int  JudgeOpenFile(FILE* fpFile, char* pFile);
#endif