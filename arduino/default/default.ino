//http://www.seeedstudio.com/wiki/GPRS_Shield_V2.0

//Serial Relay - Arduino will patch a 
//serial link between the computer and the GPRS Shield
//at 9600 bps 8-N-1
//Computer is connected to Hardware UART
//GPRS Shield is connected to the Software UART 
 
#include <SoftwareSerial.h>
 
SoftwareSerial GPRS(7, 8);
unsigned char buffer[256];          // buffer array for data recieve over serial port
int count=0;                       // counter for buffer array 
void setup()
{
  GPRS.begin(19200);               // GPRS baud rate (software)  
  Serial.begin(19200);             // Arduino baud rate (hardware)
}
 
void loop()
{
  
/* Data traveling from GPRS to Arduino ************/
  if (GPRS.available())              
  {
    while(GPRS.available())          // reading data into char array 
    {
      buffer[count++]=GPRS.read();   // writing data into array
      if(count == 64)break;
  }
    Serial.write(buffer,count);      // if no data transmission ends, write buffer to hardware serial port
    clearBufferArray();              // call clearBufferArray function to clear the storaged data from the array
    count = 0;                       // set counter of while loop to zero
  }

/* Data traveling from Arduino to GPRS ***************/
  if (Serial.available())            
    GPRS.write(Serial.read());       // write it to the GPRS shield
}
void clearBufferArray()              // function to clear buffer array
{
  for (int i=0; i<count;i++)
    { buffer[i]=NULL;}               // clear all index of array with command NULL
}
