/*****************************/
typedef struct tagMEM_STR MEM_STR;
/*****************************/
/**/
extern struct tagMEM_STR*CreateMem(void ReadMemoryProfileString(char*oname,char*value,int len));
#ifdef _WINDOWS_
extern struct tagMEM_STR*SetupMemorySystem(HWND hwnd,struct tagMEM_STR*,void WriteMemoryProfileString(char*oname,char*value));
#endif
/**/
extern int  InitMem(struct tagMEM_STR*memStr,void ErrorMessage(char*,int),struct tagMEM_STR*oldMemStr);
extern void ZeroMem(struct tagMEM_STR*memStr);
/**/
extern int  ProcessUserArg(struct tagMEM_STR*memStr,char*cp,void ErrorMessage(char*,int));
/**/
extern int  BankSize(struct tagMEM_STR*memStr,int bankNum);
extern int  NumBanks(struct tagMEM_STR*memStr);
/**/
extern char GetCode(struct tagMEM_STR*memStr,int pc);
extern char GetXdata(struct tagMEM_STR*memStr,int index);
extern void PutXdata(struct tagMEM_STR*memStr,int index,char val);
extern char GetDataFromBankAndOffset(struct tagMEM_STR*memStr,int bankNum,int offset);
extern void PutDataFromBankAndOffset(struct tagMEM_STR*memStr,int bankNum,int offset,char val);
extern int  GetTargetBank(struct tagMEM_STR*memStr,int isCode,int address);
extern int  GetTargetIndex(struct tagMEM_STR*memStr,int isCode,int address);
extern void StoreFileValues(struct tagMEM_STR*memStr,int isCode,int fileBank,int recordType,int addHi,int numents,int address,char values[256]);
/*****************************/
