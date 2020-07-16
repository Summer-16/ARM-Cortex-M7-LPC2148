#include <lpc214x.h>

#define switch1 15
#define switch2 13
#define switch3 12
#define switch4 30
#define led1 16 
#define led2 17
#define led3 18
#define led4 19
#define buz 11
#define ir 16
//#define t1 20
//#define t2 21
//#define t3 22
//#define t4 23

void delay(unsigned char j)
{
unsigned int i;
for(;j>0;j--)
{		
for(i=0; i<60000; i++);
}
}

int main()
{

unsigned int switchstatus1,switchstatus2,switchstatus3,switchstatus4,Ir;  

PINSEL0 = 0x000000;
PINSEL1 = 0x000000;
PINSEL2 = 0x000000;

IO1DIR = (1<<led1)|(1<<led2)|(1<<led3)|(1<<led4);
IO0DIR = (0<<switch1)|(0<<switch2)|(0<<switch3)|(0<<switch4)|(0<<ir)|(1<<buz);			

while(1)
{

switchstatus1 = (IOPIN0>>switch1) & 0x01 ;
switchstatus2 = (IOPIN0>>switch2) & 0x01 ;
switchstatus3 = (IOPIN0>>switch3) & 0x01 ;
switchstatus4 = (IOPIN0>>switch4) & 0x01 ;
Ir = (IOPIN0>>ir) & 0x01 ;
IOSET0 = (1<<buz);

if(switchstatus1 == 0)
{
IOSET1=(1<<led1);
delay(25);
IOCLR1=(1<<led1);
delay(25);
}  
	     
if(switchstatus2 == 0)
{	
IOSET1=(1<<led1);
delay(25);
IOCLR1=(1<<led1);
IOSET1=(1<<led2);
delay(25);
IOCLR1=(1<<led2);
IOSET1=(1<<led3);
delay(25);
IOCLR1=(1<<led3);
IOSET1=(1<<led4);
delay(25);
IOCLR1=(1<<led4);
}	 

if(switchstatus3 == 0)
{		IOCLR0=(1<<buz);
}

if(switchstatus4 == 0)
{
if (Ir == 1)
{
IOCLR0 = (1<<11);  
IOSET1=(1<<led1);
delay(25);
IOCLR1=(1<<led1);
IOCLR0 = (1<<11);
IOSET1=(1<<led2);
delay(25);
IOCLR1=(1<<led2);
IOCLR0 = (1<<11);
IOSET1=(1<<led3);
delay(25);
IOCLR1=(1<<led3);
IOCLR0 = (1<<11);
IOSET1=(1<<led4);
delay(25);
IOCLR1=(1<<led4);
		 
       }
       else
       {
         IOCLR1 = (1<<led1);
		 IOCLR1 = (1<<led2);
		 IOCLR1 = (1<<led3);
		 IOCLR1 = (1<<led4);
		 IOSET0=(1<<11);
       }
}		   
}
}