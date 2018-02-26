/*******************************************************//**


@file  MatchCharacterModule.h           
@author YHF
@data 2018/2/25
@
***********************************************************/
#ifndef __MATCH_CHAR_MODULE__
#define __MATCH_CHAR_MODULE__
///
///define three mode of processing
#ifndef __PROCESSING_MODE__
#define __PROCESSING_MODE__
#define UNIFIED_OUTPUT_MODE 1
#define SEPARATE_CHAR_OUTPUT   2
#define SEPARATE_INPUT_FILE_OUTPUT  3
#endif

int ProcessMode(const int InputCharNum,const int ReadFileNum,const int WriteFileNum);
int ReadFileFirstLine(FILE* fpReadFile,char** pGetLine,int* LineTotalLength);
int ExecuteFindSpecial(int MatchMode,char* pInputChar,int* pInputCharLength,const int InputCharNum,char* pReadFile,const int ReadFileNum,char* pWriteFile,const int WriteFileNum);
int  JudgeOpenFile(FILE* fpFile,char* pFile);
int PositionNChar(int* pInputCharLength,int NumNChar);
int UnifiedOutputMode(char* pInputChar,int* pInputCharLength,const int InputCharNum,char* pReadFile,const int ReadFileNum,char* pWriteFile,const int WriteFileNum);
int SeparateCharOutput(char* pInputChar,int* pInputCharLength,const int InputCharNum,char* pReadFile,const int ReadFileNum,char* pWriteFile,const int WriteFileNum);
int SeparateInputFileOutput(char* pInputChar,int* pInputCharLength,const int InputCharNum,char* pReadFile,const int ReadFileNum,char* pWriteFile,const int WriteFileNum);

#endif