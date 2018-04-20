#ifndef  __ASSERT_MODULE__
#define  __ASSERT_MODULE__


///unsigned __stdcall StartMatchStrThread(void* param);
void QMessageBoxFailure(QString QSFailureInformation);
int  JudgeOpenFile(FILE* fpFile, char* pFile);
int  JudgeMemory(char* pJudgeMemory);
#endif