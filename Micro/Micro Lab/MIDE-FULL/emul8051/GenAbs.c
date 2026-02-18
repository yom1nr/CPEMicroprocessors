//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//
typedef unsigned int   BOOL;
#define FALSE 0
#define TRUE  1
//
#define IS_STR(cp,str)   (memicmp(cp,str,sizeof(str)-1)==0)
//
BOOL ParseForOffset(FILE*fpX,char*name,int*offPtr){
   fseek(fpX,0,0);
   for(;;){
      char ibuf[256];
      if(fgets(ibuf,256,fpX) == 0)break;
      if(strchr(ibuf,'\n')!=0)*strchr(ibuf,'\n')=0;
      if(strchr(ibuf,'\r')!=0)*strchr(ibuf,'\r')=0;
      if(strlen(ibuf) > 53){
         if(memcmp(ibuf,"            CODE    ",20)==0){     // only code segments of interest!
            if(stricmp(ibuf+53,name)==0){
               *offPtr = strtol(ibuf+20,0,16);
               return TRUE;}}}}
   return FALSE;}
//
void process(FILE*fpX){
   //
   char aa[1024],*ap;
   BOOL segmentFound=FALSE;
   int  offset = 0;
   int  val;

   //
   while(gets(aa) != 0){    // to end-of-file
      // check for segment start
      if(IS_STR(aa,"----")){     // new Segment
         char*ap=aa+29;          // skip line #
         offset = 0;
         //
         while(*ap==' ')ap++;    // skip spaces
         //
         if(IS_STR(ap,"rseg")){
            char name[128],*aq;
            int len;
            ap += 4;             // skip "rseg"
            //
            while(*ap==' ')ap++; // skip spaces
            //
            aq = ap;
            while(*aq>' ')aq++;  // find space or eol
            //
            len = aq-ap;
            memcpy(name,ap,len); name[len]=0;
            segmentFound = ParseForOffset(fpX,name,&offset);}
         else if(IS_STR(ap,"cseg")){
            segmentFound = TRUE;
            offset = 0;}}
      //
      // replace address by address + segment_base?
      //
      if(offset != 0
        && aa[0] > ' '
        && ((val = strtol(aa,&ap,16)),ap == aa+4)
        && aa[4] == ' '){
         sprintf(aa,"%04x",offset + val);
         aa[4] = ' ';}  // remove the null
      if(segmentFound)puts(aa);}}
//
int main(int nargs,char**argpp){  int rv=0;
   if(nargs!=2){
      fprintf(stderr,"usage:  genabs xx.m51 <yy.lst >zz.l\n"); rv=3;}
   else {  
      FILE*fpX=fopen(argpp[1],"rb");
      if(fpX==0){
         fprintf(stderr,"Can't open  %s\n",argpp[1]); return -1;}
      process(fpX);
      fclose(fpX);}
   return(rv);}
//------------------------------------//
