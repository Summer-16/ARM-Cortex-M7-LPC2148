#include <lpc214x.h>

#define switch1 15
#define switch2 13
#define switch3 12
#define switch4 30

#define led1 16 
#define led2 17
#define led3 18
#define led4 19

int main()
{
unsigned int switchstatus1,switchstatus2,switchstatus3,switchstatus4,ir;

PINSEL0 = 0x000000;
PINSEL1 = 0x000000;
PINSEL2 = 0x000000;

IO1DIR = (1<<led1)|(1<<led2)|(1<<led3)|(1<<led4);
IO0DIR = (0<<switch1)|(0<<switch2)|(0<<switch3)|(0<<switch4)|(1<<11)|(0<<10);

while(1)
{
switchstatus1 = (IOPIN0>>switch1) & 0x01 ;
switchstatus2 = (IOPIN0>>switch2) & 0x01 ;
switchstatus3 = (IOPIN0>>switch3) & 0x01 ;
switchstatus4 = (IOPIN0>>switch4) & 0x01 ;
ir = (IOPIN0>>10) & 0x01 ;
if (10 == 1)
{  
         IOSET1 = (1<<led1);
		 IOCLR0 = (1<<11);
       }
       else
       {
         IOCLR1 = (1<<led1);
		 IOSET0=(1<<11);
       }      
if(switchstatus1 == 0)                
       {  
         IOSET1 = (1<<led1);
		 IOCLR0 = (1<<11);
       }
       else
       {
         IOCLR1 = (1<<led1);
		 IOSET0=(1<<11);
       }      
if(switchstatus2 == 0)                
       {  
         IOSET1 = (1<<led2);
       }
       else
       {
         IOCLR1 = (1<<led2);
       }      
if(switchstatus3 == 0)                
       {  
         IOSET1 = (1<<led3);
       }
       else
       {
         IOCLR1 = (1<<led3);
       }      
if(switchstatus4 == 0)                
       {  
         IOSET1 = (1<<led4);
       }
       else
       {
         IOCLR1 = (1<<led4);
       }      
}
}