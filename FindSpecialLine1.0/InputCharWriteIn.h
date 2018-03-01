/**************************************************//**
			Training  Module
*-
@file InputCharWriteIn.h
@author YHF
@data 2018/1/31
@package try to package

**********************************************/
#ifndef __INPUTCHARWRITEIN_H_
#define __INPUTCHARWRITEIN_H_
///
///marco defines a fixed length
#ifndef   __READ_SIZE__
#define     READ_SIZE 128  
#endif

///
///function declaration
void JudgeMemory(char* pJudgeMemory);
int RecordInputCharBuf (char** pAllChar,unsigned int &ActualTotalLength,const int NumberNHead,const int NumberMarks);
int ReadFileFirstLine(FILE* &fpReadFile,char* &pGetLine,int &LineTotalLength);
int FileNormallyMode(char* &pReadFile,int &FileNum);
int FileListMode(char* &pReadFile,int &RecordFileLine);
int FileManualMode(char* &pReadFile,int &FileNth);
int FileModeStorage(char* &pFileStorage,int FileNum);
int SaveMultipleFileInput(char* &pReadFile,const int NumberMarks,int &FileNumInput);
int SaveMultipleFileOutput(char* &pWriteFile,int FileNumOutput,const int NumberMarks,const int FileNumInput);
int MultipleIdentiHead(char ***pMatch,unsigned int** pInputCharLength,int &NumberMarks);
int OutputSpecialLineToFile(char **pMatch,const unsigned int*const InputCharLength,const int &NumberMarks);
#endif

