#include <reg52.h>  
#define PortO_DispData P0  
  
sbit CS_Seg0 = P1 ^ 4;  
sbit CS_Seg1 = P1 ^ 5;  
 
unsigned int Count, Counter = 0;  
code unsigned char CodeSeg[] =  
{ 0x77, 0x11, 0x6D, 0x5D, 0x1B, 0x5E, 0x7E, 0x15,  
  0x7F, 0x5F, 0x3F, 0x7A, 0x66, 0x79, 0x6E, 0x2E  
};  
  
//===============================================  
void Delay(unsigned char msec)  
{ unsigned char i, j;  
  while (msec)  
  { for (i = 1; i <= 250; i++) //not :  
      for (j = 1; j <= 113; j++); //with ;  
    msec--;  
  }  
}  
  
//===============================================  
void int0_isr(void) interrupt 0  
{ 
  EX0 = 0; // Disable Interrupt INT0  
  Counter++; // Increment Counter  
  Delay(4); // Debounce Signal  
  EX0 = 1; // Enable Interrupt INT0  
  IE0 = 0;  
} 

//===============================================  
void int1_isr(void) interrupt 1 
{
    EX1 = 0; 
    if (Counter > 0) {
        Counter--; 
    }
    Delay(4); 
    EX1 = 1;
    IE1 = 0;
}
  
//===============================================  
main()  
{ IT0 = 1; // Edge Trigger Interrupt
  //IT1 = 1; // Edge Trigger Interrupt
  EX0 = 1; // Enable External 0 Interrupt
  EX1 = 1; // Enable External 1 Interrupt 
  EA = 1; // Global Interrupt Enable  
  while (1)  
  { unsigned char i;  
    Count = Counter & 0x0f;  
    CS_Seg0 = 1; CS_Seg1 = 0;  
    PortO_DispData = ~CodeSeg[Count];  
    for (i = 1; i <= 250; i++) {};  
    Count = (Counter >> 4) & 0x0f;  
    CS_Seg0 = 0; CS_Seg1 = 1;  
    PortO_DispData = ~CodeSeg[Count];  
    for (i = 1; i <= 250; i++) {};  
  }  
} 
