//********************************************//
//            memory system emulation         //
//********************************************//
//
#define STRICT
#define WIN32_LEAN_AND_MEAN
#ifndef WIN32
#define WIN32        // ??? //
#endif
#pragma warning( disable : 4201 4214 4514 4115 4018)
#include <windows.h>
#include "resourc2.h"
//
#include <stdlib.h>
#include <stdio.h>
//#include <string.h>
//
#include "dllintf.h"
//
//*****************************//
//
typedef struct tagBANK{
   int size;
   char*data;
   }BANK;
//
typedef struct tagMECH{
   int baseBank;
   int magicLocation;
   int mask;
   int shift;
   }MECH,(*MECHARRAY)[];
//
typedef struct tagMEM_STR{
   int model;
   int numBanks;
   int bankSize;
   int magicBank;
   int addMask;
   int addShift;
   int numDataMechs;
   int numCodeMechs;
   MECHARRAY dataMechs;
   MECHARRAY codeMechs;
   BANK(*banks)[];
   }MEM_STR;
//
//********************************************//
//
#define NEW(TYPE,ptr)   TYPE*ptr=(TYPE*)calloc(1,sizeof(TYPE))
//
#define UNDEFINED_MODEL 0 
#define TINY_MODEL      1   // 65k of memory is all you get
#define SMALL_MODEL     2   // 65k of code / 65k of data
#define LARGE_MODEL     3   // something else
//
#define BANK_TINY_CODE_DATA   0     // bank 0 is data/code in tiny model
#define BANK_SMALL_DATA       0     // bank 0 is data in small model
#define BANK_SMALL_CODE       1     // bank 1 is code in small model
//
//********************************************//
//
static BOOL CALLBACK CfgMemProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);   
static int  GetMechs(char*cp,MECHARRAY*mp,void ErrorMessage(char*,int));
static void FreeMechs(MEM_STR*memStr);
static void FreeBanks(MEM_STR*memStr);
static void FreeMemStruct(MEM_STR*memStr);
static void BuildMechsString(MECHARRAY mechArray,int numMechs,char buff[]);
static BOOL SameMemStructs(MEM_STR*newMemStr,MEM_STR*memStr);
//
//********************************************//
// get source/dest memory bank# & offset-within-bank //
static void GetPhysicalAddress(MEM_STR*memStr,int isCode,int address,int*bankNumPtr,int*offsetPtr){
   int bankNum;
   //
   if(memStr->model == TINY_MODEL ){
      bankNum = BANK_TINY_CODE_DATA;}
   else if(memStr->model == SMALL_MODEL){
      bankNum = isCode ? BANK_SMALL_CODE : BANK_SMALL_DATA;}
   else {
      int mechIndex = (unsigned short)address >> memStr->addShift;
      MECH*mech = &(isCode ? (*memStr->codeMechs) : (*memStr->dataMechs))[mechIndex];
      int rawMagicValue = (*memStr->banks)[memStr->magicBank].data[mech->magicLocation];
      bankNum = ((rawMagicValue >> mech->shift) & mech->mask) + mech->baseBank;
      if(bankNum >= memStr->numBanks)bankNum %= memStr->numBanks;}
   *bankNumPtr = bankNum;
   *offsetPtr = address & memStr->addMask;}
//
// get code memory at given index //
char GetCode(MEM_STR*memStr,int index){
   int bankNum,offset;
   GetPhysicalAddress(memStr,1,index,&bankNum,&offset);
   return (*memStr->banks)[bankNum].data[offset];}
//
// get memory for "MOVX" //
char GetXdata(MEM_STR*memStr,int index){
   int bankNum,offset;
   GetPhysicalAddress(memStr,0,index,&bankNum,&offset);
   return (*memStr->banks)[bankNum].data[offset];}
//
// put memory for "MOVX" //
void PutXdata(MEM_STR*memStr,int index,char val){
   int bankNum,offset;
   GetPhysicalAddress(memStr,0,index,&bankNum,&offset);
   (*memStr->banks)[bankNum].data[offset] = val;}
//
// for data-display/edit windows
char GetDataFromBankAndOffset(MEM_STR*memStr,int bankNum,int offset){
   // protection against explosion //
   if(bankNum >= memStr->numBanks)bankNum = 0;
   if(offset  >= (*memStr->banks)[bankNum].size)offset = 0;
   //
   return (*memStr->banks)[bankNum].data[offset];}
//
void PutDataFromBankAndOffset(MEM_STR*memStr,int bankNum,int offset,char val){
   // protection against explosion //
   if(bankNum >= memStr->numBanks)bankNum = 0;
   if(offset  >= (*memStr->banks)[bankNum].size)offset = 0;
   //
   (*memStr->banks)[bankNum].data[offset] = val;}
//
int BankSize(MEM_STR*memStr,int bankNum){
   // protection against explosion //
   if(bankNum >= memStr->numBanks)bankNum = 0;
   //
   return (*memStr->banks)[bankNum].size;}
//
int NumBanks(struct tagMEM_STR*memStr){
   return memStr->numBanks;}
//
// for data-display/edit windows (for underlining)
int GetTargetBank(MEM_STR*memStr,int isCode,int address){
   int bankNum,offset;
   GetPhysicalAddress(memStr,isCode,address,&bankNum,&offset);
   return bankNum;}
//
int GetTargetIndex(MEM_STR*memStr,int isCode,int address){
   int bankNum,offset;
   GetPhysicalAddress(memStr,isCode,address,&bankNum,&offset);
   return offset;}
//
// for loading hex files: store values in bank (bank found from isCode / fileBank / recordType / addHi)
void StoreFileValues(MEM_STR*memStr,int isCode,int fileBank,int recordType,int addHi,int numents,int address,char values[256]){
   int bankNum=0;
   //
   // what bank?
   if(memStr->model == TINY_MODEL){
      bankNum = BANK_TINY_CODE_DATA;}
   else if(memStr->model == SMALL_MODEL){
      bankNum = isCode ? BANK_SMALL_CODE : BANK_SMALL_DATA;}
   else {
      if(recordType < 2){
         bankNum = fileBank;}
      else {
         bankNum = addHi + fileBank;}}
   //
   if(bankNum >= memStr->numBanks)bankNum %= memStr->numBanks;
   //
   // store values
   {  int n;
      for(n=0;n<numents;n++,address++){
         if(address >= memStr->bankSize){
            bankNum = (bankNum + (address / memStr->bankSize)) % memStr->numBanks;
            address = address % memStr->bankSize;}
         (*memStr->banks)[bankNum].data[address] = values[n];}}}
//
// ******************************** //
// initialization
// ******************************** //
MEM_STR*CreateMem(void ReadMemoryProfileString(char*oname,char*value,int len)){
   char buff[256];
   //
   NEW(MEM_STR,memStr);
   //
   // default value //
   memStr->model    = UNDEFINED_MODEL;
   memStr->bankSize = 0x10000;
   memStr->addMask  = 0xffff;
   //
   buff[0]=0;ReadMemoryProfileString("MODE",buff,sizeof buff);
   if(buff[0]!=0){
      memStr->model = strtol(buff,0,0);
      if(memStr->model == TINY_MODEL){
         memStr->numBanks = 1;}
      else if(memStr->model == SMALL_MODEL){
         memStr->numBanks = 2;}
      else {
         buff[0]=0;ReadMemoryProfileString("NUMBANKS",buff,sizeof buff);
         memStr->numBanks = strtol(buff,0,0);
         if(memStr->numBanks == 0)memStr->numBanks = 1;     // safe anyway //
         //
         buff[0]=0;ReadMemoryProfileString("BANKSIZE",buff,sizeof buff);
         memStr->bankSize = strtol(buff,0,0);
         if(memStr->bankSize == 0)memStr->bankSize = 65536;     // safe anyway //
         //
         buff[0]=0;ReadMemoryProfileString("MAGICBANK",buff,sizeof buff);
         memStr->magicBank = strtol(buff,0,0);
         //
         buff[0]=0;ReadMemoryProfileString("CODEMECHS",buff,sizeof buff);
         memStr->numCodeMechs = GetMechs(buff,&memStr->codeMechs,0);
         //
         buff[0]=0;ReadMemoryProfileString("DATAMECHS",buff,sizeof buff);
         memStr->numDataMechs = GetMechs(buff,&memStr->dataMechs,0);
         //
         if(  memStr->model        != LARGE_MODEL
           || memStr->codeMechs    == 0
           || memStr->dataMechs    == 0
           || memStr->numCodeMechs == 0 
           || memStr->numCodeMechs != memStr->numDataMechs){
            // something's rotten .... //
            // go to small model - it's at least safe //
            FreeMechs(memStr);
            memStr->model    = SMALL_MODEL;
            memStr->bankSize = 0x10000;
            memStr->addMask  = 0xffff;}}}
   //
   return memStr;}
//
int InitMem(MEM_STR*memStr,void ErrorMessage(char*,int),MEM_STR*oldMemStr){
   int n;
   if(memStr->model == UNDEFINED_MODEL){
      //
      // default tiny model?
      //memStr->model = TINY_MODEL;
      //memStr->numBanks = 1;
      //
      // default small model
      memStr->model = SMALL_MODEL;
      memStr->numBanks = 2;
      //
      memStr->bankSize = 0x10000;
      memStr->addMask  = 0xffff;}
   //
   if(memStr->model == LARGE_MODEL){
      if(memStr->codeMechs == 0 || memStr->dataMechs == 0){
         if(ErrorMessage!=0)ErrorMessage("Both '-mCODE' and '-mDATA' must be specified for large model\n",1);
         return 0;}
      if(memStr->numCodeMechs != memStr->numDataMechs){
         if(ErrorMessage!=0)ErrorMessage("Number of code-mapping-mechanisms must be same as number of data-mapping-mechanisms\n",1);
         return 0;}
      //
      {  int numMechs = memStr->numCodeMechs;
         int log=numMechs-1;
         //
         if(numMechs == 1 /* log=0 */ || numMechs == 2 /* log=1 */ || numMechs == 4 && (log=2,1) || numMechs == 8 && (log=3,1)){
            memStr->addShift = 16-log;
            memStr->addMask  = 0xffff >> log;}
         else {
            if(ErrorMessage!=0)ErrorMessage("Number of mapping-mechanisms must be 1,2,4 or 8\n",1);
            return 0;}}}
   //
   memStr->banks = calloc(memStr->numBanks,sizeof(BANK));
   for(n=0;n<memStr->numBanks;n++){
      (*memStr->banks)[n].size = memStr->bankSize;
      (*memStr->banks)[n].data = calloc((*memStr->banks)[n].size,1);
      // copy data from old memory system? //
      if(oldMemStr != 0 && oldMemStr->numBanks > n && (*oldMemStr->banks)[n].data != 0){
         int size = min(memStr->bankSize,oldMemStr->bankSize);
         memcpy((*memStr->banks)[n].data,(*oldMemStr->banks)[n].data,size);}}
   return 1;}
//
void ZeroMem(MEM_STR*memStr){
   int n;
   for(n=0;n<memStr->numBanks;n++){
      memset((*memStr->banks)[n].data,0,(*memStr->banks)[n].size);}}
//
MEM_STR*SetupMemorySystem(HWND hwnd,MEM_STR*memStr,void WriteMemoryProfileString(char*oname,char*value)){
   char buff[256];
   //
   HINSTANCE hInst   = LoadLibrary("Emem8051.dll");
   MEM_STR*newMemStr = (MEM_STR*)DialogBoxParam(hInst,"MEMORY_CFG",hwnd,CfgMemProc,(LONG)memStr);
   //
   if(newMemStr != 0){
      if(SameMemStructs(newMemStr,memStr)){
         FreeMemStruct(newMemStr);}       // don't destroy old data unless necessary
      else {
         InitMem(newMemStr,0,memStr);     // initialize memory blocks, using old blocks
         FreeMemStruct(memStr);           // remove old mem struct
         memStr = newMemStr;              // promote the new one
         //
         // write memory config to INI file //
         //
         sprintf(buff,"%d",memStr->model);
         WriteMemoryProfileString("MODE",buff);
         //
         sprintf(buff,"%d",memStr->numBanks);
         WriteMemoryProfileString("NUMBANKS",buff);
         //
         sprintf(buff,"%d",memStr->bankSize);
         WriteMemoryProfileString("BANKSIZE",buff);
         //
         sprintf(buff,"%d",memStr->magicBank);
         WriteMemoryProfileString("MAGICBANK",buff);
         //
         BuildMechsString(memStr->codeMechs,memStr->numCodeMechs,buff);
         WriteMemoryProfileString("CODEMECHS",buff);
         //
         BuildMechsString(memStr->dataMechs,memStr->numDataMechs,buff);
         WriteMemoryProfileString("DATAMECHS",buff);
         //
         }}
   return memStr;}
//
// ******************************** //
// argument processing
// ******************************** //
int ProcessUserArg(MEM_STR*memStr,char*cp,void ErrorMessage(char*,int)){
   //
   if(*cp=='-' || *cp=='/'){    
      char cmd = *++cp;
      if(cmd >= 'A' && cmd <= 'Z')cmd |= 0x20;
      cp++;
      switch(cmd){
         case 'm':{
            if(memicmp(cp,"TINY",4)==0){
               //if(memStr->model != UNDEFINED_MODEL){ ErrorMessage("Multiple model definition\n",0); return 0;}
               memStr->model = TINY_MODEL;
               FreeMechs(memStr);         // get rid of any mechs generated by CreateMem
               memStr->numBanks = 1;
               memStr->bankSize = 0x10000;
               memStr->addMask  = 0xffff;}
            else if(memicmp(cp,"SMALL",5)==0){
               //if(memStr->model != UNDEFINED_MODEL){ ErrorMessage("Multiple model definition\n",0); return 0;}
               memStr->model = SMALL_MODEL;
               FreeMechs(memStr);         // get rid of any mechs generated by CreateMem
               memStr->numBanks = 2;
               memStr->bankSize = 0x10000;
               memStr->addMask  = 0xffff;}
            else if(memicmp(cp,"LARGE",5)==0){
               //if(memStr->model != UNDEFINED_MODEL){ ErrorMessage("Multiple model definition\n",0); return 0;}
               memStr->model = LARGE_MODEL;
               FreeMechs(memStr);         // get rid of any mechs generated by CreateMem
               //
               cp+=5;
               while(*cp==' ')cp++;
               if(*cp==':')cp++;
               memStr->numBanks = strtol(cp,&cp,0);
               if(memStr->numBanks == 0){
                  ErrorMessage("# of memory banks must be non-zero (-mLARGE:nnn/sss)\n",0);
                  return 0;}
               while(*cp==' ')cp++;
               if(*cp=='/')cp++;
               memStr->bankSize = strtol(cp,&cp,0);
               if(memStr->bankSize == 0){
                  ErrorMessage("bank size must be non-zero (-mLARGE:nnn/sss)\n",0);
                  return 0;}
               if(*cp=='/')cp++;
               memStr->magicBank = strtol(cp,&cp,0);
               }
            else if(memcmp(cp,"code:",5)==0 || memcmp(cp,"data:",5)==0){
               //
               MECHARRAY*mechPP = (*cp=='c' || *cp=='C') ? &memStr->codeMechs    : &memStr->dataMechs;
               int*numMechPtr   = (*cp=='c' || *cp=='C') ? &memStr->numCodeMechs : &memStr->numDataMechs;
               //
               cp+=5;
               //
               if(memStr->model != LARGE_MODEL){
                  ErrorMessage("'-mLARGE:nnn' must precede '-mCODE' or '-mDATA'\n",0);
                  return 0;}
               if(*mechPP != 0){
                  ErrorMessage("Duplicate specifications of '-mCODE' or '-mDATA'\n",0);
                  return 0;}
               //
               *numMechPtr = GetMechs(cp,mechPP,ErrorMessage);
               if(*numMechPtr == 0){
                  ErrorMessage("one or more illegal mapping mechanism definition(s)\n",0);
                  return 0;}}
            return 1;}
         default:break;}}
   return 0;}     // not handled //
//
static char*GetSingleMech(char buff[],char*cp){
   char*cq;
   for(cq=cp;*cq!=0 && *cq!=',';cq++){}
   strcpy(buff,cp);
   buff[cq-cp]=0;
   if(*cq==',')cq++;
   return cq;}
//
static int GetNumMechs(char*cp){
   int n;
   for(n=0;;n++){
      char buff[256];
      cp = GetSingleMech(buff,cp);
      if(buff[0]==0){         // empty buffer? must be end-of-line (or 2 consecutive commas)
         if(*cp!=0)return 0;  // not end-of-line (error!)
         break;}}
   return n;}
//
static int GetNumber(char**cpp,int*returnValue){
   char*cp=*cpp;
   while(*cp==' ')cp++;
   if(*cp>='0' && *cp<='9'){
      *returnValue = strtol(cp,&cp,0);
      while(*cp==' ')cp++;
      *cpp=cp;
      return 1;}
   return 0;}
//
// base[magic/mask/shift] or base[]
static int ParseMech(char*cp,MECH*mechP){
   if(!GetNumber(&cp,&mechP->baseBank))return 0;
   if(*cp == '(')cp++;
   if(GetNumber(&cp,&mechP->magicLocation)){
      if(*cp == '/')cp++;
      if(!GetNumber(&cp,&mechP->mask))return 0;
      if(*cp == '/')cp++;
      if(!GetNumber(&cp,&mechP->shift))return 0;}
   else {                  // [] (all zero)
      mechP->magicLocation = 0;
      mechP->mask = 0;
      mechP->shift = 0;}
   if(*cp == ')')cp++;
   if(*cp++ != 0)return 0;
   return 1;}
//
// base[magic/mask/shift],base[magic/mask/shift], ...
static int GetMechs(char*cp,MECHARRAY*mp,void ErrorMessage(char*,int)){
   int numMechs = GetNumMechs(cp);
   if(numMechs != 0){
      int n;
      MECHARRAY mechArray = calloc(numMechs,sizeof(MECH));
      for(n=0;n<numMechs;n++){
         char buff[256];
         cp = GetSingleMech(buff,cp);
         if(!ParseMech(buff,&(*mechArray)[n])){
            if(ErrorMessage != 0){
               char erbuf[256];
               sprintf(erbuf,"Illegal mapping mechanism <%s>\n",buff);
               ErrorMessage(erbuf,0);}
            return 0;}}
      *mp = mechArray;}
   return numMechs;}
//
static void FreeMechs(MEM_STR*memStr){
   if(memStr->codeMechs!=0){ free(memStr->codeMechs); memStr->codeMechs=0;}
   if(memStr->dataMechs!=0){ free(memStr->dataMechs); memStr->dataMechs=0;}
   memStr->numCodeMechs=0;
   memStr->numDataMechs=0;}
//
static void FreeBanks(MEM_STR*memStr){
   int n;
   if(memStr->banks != 0){
      for(n=0;n<memStr->numBanks;n++){
         free((*memStr->banks)[n].data);}
      free(memStr->banks);}
   memStr->numBanks = 0;}
//
static void FreeMemStruct(MEM_STR*memStr){
   // free any alloc'd memory
   FreeMechs(memStr);
   FreeBanks(memStr);
   free(memStr);}
//
static void BuildMechsString(MECHARRAY mechArray,int numMechs,char buff[]){
   int n;
   //
   char*cp=buff;
   //
   if(mechArray!=0 && numMechs>0){
      for(n=0;n<numMechs;n++){
         MECH*mechP = &(*mechArray)[n];
         cp += sprintf(cp,"%d(",mechP->baseBank);
         if(mechP->magicLocation != 0 || mechP->mask != 0){
            cp += sprintf(cp,"%d/%d/%d",mechP->magicLocation,mechP->mask,mechP->shift);}
         *cp++=')';
         *cp++=',';}
      cp--;}      // remove final comma //
   *cp=0;}
//
static BOOL SameMechs(int numMechs,MECHARRAY mech1,MECHARRAY mech2){
   int n;
   if(mech1==0 || mech2==0){
      return mech1==mech2;}
   for(n=0;n<numMechs;n++){
      MECH*mp1 = &(*mech1)[n];
      MECH*mp2 = &(*mech2)[n];
      if(mp1->baseBank      != mp2->baseBank      )return FALSE;
      if(mp1->magicLocation != mp2->magicLocation )return FALSE;
      if(mp1->mask          != mp2->mask          )return FALSE;
      if(mp1->shift         != mp2->shift         )return FALSE;}
   return TRUE;}        // all the same
//
static BOOL SameMemStructs(MEM_STR*newMemStr,MEM_STR*memStr){
   if(  newMemStr->model    == memStr->model
     && newMemStr->numBanks == memStr->numBanks 
     && newMemStr->bankSize == memStr->bankSize
     && newMemStr->addMask  == memStr->addMask){
      if(  memStr->model   == TINY_MODEL
        || memStr->model   == SMALL_MODEL
        || ( memStr->model == LARGE_MODEL 
          && newMemStr->addShift     == memStr->addShift
          && newMemStr->magicBank    == memStr->magicBank
          && newMemStr->numCodeMechs == memStr->numCodeMechs
          && newMemStr->numDataMechs == memStr->numDataMechs
          && SameMechs(newMemStr->numCodeMechs,newMemStr->codeMechs,memStr->codeMechs)
          && SameMechs(newMemStr->numDataMechs,newMemStr->dataMechs,memStr->dataMechs))){
         return TRUE;}}
   return FALSE;}
//
// ******************************** //
//
#define HIDE_ALTERNATES
//
static void ShowModelButtons(HWND hwnd,int mode){
   BOOL ewT = (mode == TINY_MODEL);
   BOOL ewS = (mode == SMALL_MODEL);
   BOOL ewL = (mode == LARGE_MODEL);
   //
   CheckRadioButton(hwnd,IDR_TINY,IDR_LARGE,
                    ewT ? IDR_TINY : ewS ? IDR_SMALL : IDR_LARGE);
   //
#ifdef HIDE_ALTERNATES
   {
      int swT = (ewT  ? SW_SHOW : SW_HIDE);
      int swS = (ewS  ? SW_SHOW : SW_HIDE);
      int swL = (ewL  ? SW_SHOW : SW_HIDE);
      //
      ShowWindow(GetDlgItem(hwnd,IDG_LARGE),swL);
      ShowWindow(GetDlgItem(hwnd,IDS_BANK) ,swL);
      ShowWindow(GetDlgItem(hwnd,IDE_BANK) ,swL);
      ShowWindow(GetDlgItem(hwnd,IDS_BANKSIZE),swL);
      ShowWindow(GetDlgItem(hwnd,IDE_BANKSIZE),swL);
      ShowWindow(GetDlgItem(hwnd,IDS_CODE) ,swL);
      ShowWindow(GetDlgItem(hwnd,IDE_CODE) ,swL);
      ShowWindow(GetDlgItem(hwnd,IDS_DATA) ,swL);
      ShowWindow(GetDlgItem(hwnd,IDE_DATA) ,swL);
      ShowWindow(GetDlgItem(hwnd,IDS_MAGICBANK),swL);
      ShowWindow(GetDlgItem(hwnd,IDE_MAGICBANK),swL);
      //
      ShowWindow(GetDlgItem(hwnd,IDS_BANK_TINY),swT);
      ShowWindow(GetDlgItem(hwnd,IDS_BANK_SMALL),swS);
      ShowWindow(GetDlgItem(hwnd,IDS_BANK_SMALL2),swS);}
   //
#else
   EnableWindow(GetDlgItem(hwnd,IDG_LARGE),ewL);
   EnableWindow(GetDlgItem(hwnd,IDS_BANK) ,ewL);
   EnableWindow(GetDlgItem(hwnd,IDE_BANK) ,ewL);
   EnableWindow(GetDlgItem(hwnd,IDS_BANKSIZE),ewL);
   EnableWindow(GetDlgItem(hwnd,IDE_BANKSIZE),ewL);
   EnableWindow(GetDlgItem(hwnd,IDS_CODE) ,ewL);
   EnableWindow(GetDlgItem(hwnd,IDE_CODE) ,ewL);
   EnableWindow(GetDlgItem(hwnd,IDS_DATA) ,ewL);
   EnableWindow(GetDlgItem(hwnd,IDE_DATA) ,ewL);
   EnableWindow(GetDlgItem(hwnd,IDS_MAGICBANK),ewL);
   EnableWindow(GetDlgItem(hwnd,IDE_MAGICBANK),ewL);
   //
   EnableWindow(GetDlgItem(hwnd,IDS_BANK_TINY),ewT);
   EnableWindow(GetDlgItem(hwnd,IDS_BANK_SMALL),ewS);
   EnableWindow(GetDlgItem(hwnd,IDS_BANK_SMALL2),ewS);
#endif
   }
//
static BOOL CALLBACK CfgMemProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
   char buff[256];
   MEM_STR*memStr;
   //
   switch(uMsg){
      case WM_INITDIALOG:{
         memStr = (MEM_STR*)lParam;
         CheckRadioButton(hwnd,IDR_TINY,IDR_LARGE,
           (   memStr->model == TINY_MODEL  ? IDR_TINY
             : memStr->model == LARGE_MODEL ? IDR_LARGE
             : IDR_SMALL));
         if(memStr->model == LARGE_MODEL){
            SetDlgItemInt(hwnd,IDE_BANK,memStr->numBanks,FALSE);
            SetDlgItemInt(hwnd,IDE_BANKSIZE,memStr->bankSize,FALSE);
            SetDlgItemInt(hwnd,IDE_MAGICBANK,memStr->magicBank,FALSE);
            BuildMechsString(memStr->codeMechs,memStr->numCodeMechs,buff);
            SetDlgItemText(hwnd,IDE_CODE,buff);
            BuildMechsString(memStr->dataMechs,memStr->numDataMechs,buff);
            SetDlgItemText(hwnd,IDE_DATA,buff);
            }
         ShowModelButtons(hwnd,memStr->model);
         return FALSE;}    // don't want default focus
      case WM_COMMAND:{
         switch(wParam){
            case IDR_TINY: { ShowModelButtons(hwnd,TINY_MODEL);  return FALSE;}
            case IDR_SMALL:{ ShowModelButtons(hwnd,SMALL_MODEL); return FALSE;}
            case IDR_LARGE:{ ShowModelButtons(hwnd,LARGE_MODEL); return FALSE;}
            case IDCANCEL:{
               EndDialog(hwnd,0);
               return TRUE;}
            case IDOK:{
               NEW(MEM_STR,memStr);
               //
               // default value //
               memStr->model    = UNDEFINED_MODEL;
               memStr->bankSize = 0x10000;
               memStr->addMask  = 0xffff;
               //
               if(IsDlgButtonChecked(hwnd,IDR_TINY)){
                  memStr->model    = TINY_MODEL;
                  memStr->numBanks = 1;}
               else if(IsDlgButtonChecked(hwnd,IDR_SMALL)){
                  memStr->model    = SMALL_MODEL;
                  memStr->numBanks = 2;}
               else {
                  memStr->model    = LARGE_MODEL;
                  //
                  memStr->numBanks = GetDlgItemInt(hwnd,IDE_BANK,0,FALSE);
                  if(memStr->numBanks == 0){
                     MessageBox(hwnd,"# of banks must be non-zero",0,0);
error_quit:          FreeMechs(memStr);
                     free(memStr);
                     return TRUE;}
                  //
                  memStr->bankSize = GetDlgItemInt(hwnd,IDE_BANKSIZE,0,FALSE);
                  if(memStr->bankSize == 0){
                     MessageBox(hwnd,"bank size must be non-zero",0,0);
                     goto error_quit;}
                  //
                  memStr->magicBank = GetDlgItemInt(hwnd,IDE_MAGICBANK,0,FALSE);
                  //
                  GetDlgItemText(hwnd,IDE_CODE,buff,sizeof buff);
                  memStr->numCodeMechs = GetMechs(buff,&memStr->codeMechs,0);
                  if(memStr->codeMechs == 0 || memStr->numCodeMechs == 0){
                     MessageBox(hwnd,"Error in code mapping parameters",0,0);
                     goto error_quit;}
                  //
                  GetDlgItemText(hwnd,IDE_DATA,buff,sizeof buff);
                  memStr->numDataMechs = GetMechs(buff,&memStr->dataMechs,0);
                  if(memStr->dataMechs == 0 || memStr->numDataMechs == 0){
                     MessageBox(hwnd,"Error in data mapping parameters",0,0);
                     goto error_quit;}
                  //
                  if(memStr->numCodeMechs != memStr->numDataMechs){
                     MessageBox(hwnd,"# of code mapping parameters must be same as # of data mapping parameters",0,0);
                     goto error_quit;}
                  //
                  }
               //
               EndDialog(hwnd,(long)memStr);
               return TRUE;}
            default:break;}}
      default:break;}
   return FALSE;}
//
// ******************************** //
//
