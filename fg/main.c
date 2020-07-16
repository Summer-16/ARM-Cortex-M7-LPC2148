
#include  <lpc214x.h>	  //Includes LPC2148 register definitions

#define DATA_PORT() IO0SET=(1<<16)		 //Function to select data port on LCD
#define READ_DATA() IO0SET=(1<<17)		 //Function to select read operation on LCD
#define EN_HI() IO0SET=(1<<18)			 //Function to Enable LCD


#define COMMAND_PORT() IO0CLR=(1<<16)	  //Function to select command port on LCD
#define WRITE_DATA() IO0CLR=(1<<17)		  //Function to select write operation on LCD
#define EN_LOW() IO0CLR=(1<<18)			  //Function to disable LCD

#define switch1 15
#define switch2 13
#define switch3 12
#define switch4 30
#define led1 16 
#define led2 17
#define led3 18
#define led4 19
#define buz 11
#define ir 20

unsigned char String1[16]={"F.G Engineering "};
unsigned char String2[16]={"ARM7 Programming"};

void delay(unsigned char j)
{
unsigned int i;
for(;j>0;j--)
{		
for(i=0; i<60000; i++);
}
}

void Delay(unsigned char j)
{  
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<60000; i++);
 } 
}

void Delay_Small(unsigned char j)
{
 unsigned int  i;
 for(;j>0;j--)
 {
  for(i=0; i<1000; i++);
 } 
}
                               

unsigned char Busy_Wait()			   //This function checks the busy status of LCD
{
 unsigned int temp=0;
 EN_LOW();
 COMMAND_PORT();
 READ_DATA();
 
 IO0PIN&=0xFF87FFFF;	  
 IO0DIR&=0xFF87FFFF;
 IO0PIN|=0x00400000;
 
 do{
 EN_HI();
 EN_LOW();
 EN_HI();
 EN_LOW();
 temp=IO0PIN;
 }
 while((temp & 0x00400000)==0x00400000);
 EN_LOW();
 WRITE_DATA();
 IO0DIR&=0xFF80FFFF;
 IO0DIR|=0x007F0000;
 return (0);
}    


void LCD_Command(unsigned int data)			  //This function is used to send LCD commands
{
 unsigned int temp=0;
 EN_LOW();
 COMMAND_PORT();
 WRITE_DATA();
 
 temp=data;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp & 0xF0) << 15;

 EN_HI();
 EN_LOW();
 
 temp=data & 0x0F;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp) << 19;

 EN_HI();
 EN_LOW();
 while(Busy_Wait());
 Delay(10);
} 


void LCD_Data(unsigned int data)		   //This function is used to send data to LCD
{
 unsigned int temp=0;
 EN_LOW();
 DATA_PORT();
 WRITE_DATA();
 
 temp=data;
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp & 0xF0) << 15;

 EN_HI();
 EN_LOW();
 
 temp=data & 0x0F;
 
 IO0PIN&=0xFF87FFFF;
 IO0PIN|=(temp) << 19;

 EN_HI();
 EN_LOW();
 Delay_Small(1);
}

void LCD_Init()
{
 LCD_Command(0x20);
 LCD_Command(0x28);
 LCD_Command(0x0C);
 LCD_Command(0x06);
}


void LCD_String(unsigned char *data)
{
 while(*data)
 {
  LCD_Data(*data);
  data++;
 } 
}  


int main(void)
{ 
unsigned int switchstatus1,switchstatus2,switchstatus3,switchstatus4,Ir;  

 PINSEL0 = 0x00000000;		// Enable GPIO on all pins
 PINSEL1 = 0x00000000;
 PINSEL2 = 0x00000000;

 Delay(20);
 IO0DIR = (1<<22) | (1<<21) | (1<<20) | (1<<19) | (1<<18) | (1<<17) | (1<<16) | (0<<switch1)|(0<<switch2)|(0<<switch3)|(0<<switch4)|(1<<buz);		// Set P0.16, P0.17, P0.18, P0.19, P0.20, P0.21, P0.22 as Output
 IO1DIR = (1<<16) | (1<<led1)|(1<<led2)|(1<<led3)|(1<<led4)|(0<<ir);
 
 LCD_Init();
 LCD_Command(0x01);
 Delay(20);

 LCD_Command(0x80);
 LCD_String(&String1[0]);
 LCD_Command(0xC0);
 LCD_String(&String2[0]);
 while(1)	
 { 
 switchstatus1 = (IOPIN0>>switch1) & 0x01 ;
switchstatus2 = (IOPIN0>>switch2) & 0x01 ;
switchstatus3 = (IOPIN0>>switch3) & 0x01 ;
switchstatus4 = (IOPIN0>>switch4) & 0x01 ;
Ir = (IOPIN1>>ir) & 0x01 ;
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


