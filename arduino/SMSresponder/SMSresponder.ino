// Example usage of http://www.seeedstudio.com/wiki/GPRS_Shield_V2.0
// Code hacked together from many sources by Taylor Hokanson | www.taylorhokanson.com

// Plug Arduino/GPRS stack into computer via USB (must include activated SIM card)
// Connect via Coolterm
// Send an SMS to GPRS from any phone, will print SMS contents via serial monitor
 
#include <SoftwareSerial.h>
 
SoftwareSerial mySerial(7, 8);

String content = "";
String SMScontent = "";
char character;

void setup()
{
  mySerial.begin(19200);               // Software   
  Serial.begin(19200);                 // Hardware   
}
 
void loop()
{
  while (mySerial.available())                                          // Read data from GPRS, write to Arduino
  {
    content = content + char(mySerial.read());
    
    if(content.substring(2,7) == "+CMTI" && content.endsWith("\n"))     //  Respond to incoming SMS notificaiton       
    {
      content = ""; 
      mySerial.flush();  
      Serial.print("Incoming SMS\n\n");
      mySerial.println("AT+CMGR=1");                                    // Tell GPRS to fetch first SMS in memory
    }
    
    if((content.substring(2,7) == "+CMGR") && (content.endsWith("OK"))) // Respond to SMS content          
    { 
      int lastNL = content.lastIndexOf("\n");                           // strip GPRS response of extra data, print SMS only
      int secondToLastNL = content.lastIndexOf("\n", lastNL - 1);
      int thirdToLastNL = content.lastIndexOf("\n", secondToLastNL - 1);
      SMScontent = content.substring((thirdToLastNL + 1), (secondToLastNL - 1));   
      
      content = ""; 
      Serial.print("SMS reads: " + SMScontent);
      
      mySerial.println("AT+CMGD=1,4");                                  // Delete all SMS from GPRS memory
      delay(1000);                                                      // Probably not the best way to do this, but works for now. Should probably wait for "OK"
      mySerial.flush();                                                 // Clear out software serial buffer  
    }
  }
  
  if (Serial.available())
  {
    mySerial.write(Serial.read()); 
  }

}


