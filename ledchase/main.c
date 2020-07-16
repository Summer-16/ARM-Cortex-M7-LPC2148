#include<lpc214x.h>

#define led1 16
#define led2 17
#define led3 18
#define led4 19

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
PINSEL0=0x000000;
PINSEL1=0x000000;
PINSEL2=0x000000;

IO1DIR=(1<<led1)|(1<<led2)|(1<<led3)|(1<<led4);

while(1)
{
IOSET1=(1<<led1);
delay(25);
IOSET1=(1<<led2);
delay(25);
IOSET1=(1<<led3);
delay(25);
IOSET1=(1<<led4);
delay(25);
}
}