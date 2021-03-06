# Setting up a SeeedStudios GPRS board (v2)

These little boards give your Arduino the ability to send and receive
phone calls and texts! Here are the [original
instructions](http://www.seeedstudio.com/wiki/GPRS_Shield_V2.0). 
I've added to them and cleaned things up for readability. I'm working in OSX.

### Activate GSM card

I got mine through [Adafruit](https://www.adafruit.com/products/2505), but it looks like you can order straight through Ting too.  
ting.com/go  
Enter IMEI number from GPRS (on SIM900 chip)  
Enter number on back of sim

### Board preparation

Insert activated SIM card into GPRS  
Upload default.ino to Arduino  
Attach GPRS to Arduino  

### Serial monitor

I couldn't do everything the Seeed tutorial asked me to do with the
Arduino IDE serial monitor, so I downloaded
[Coolterm](http://freeware.the-meiers.org/) (free). I'll include my
Coolterm profile, though you may have to go in and reset the port
anyway. 

Options  
* Serial Port  
  * Baud = 19200 
  * Port = usbmodemXXXX  
* Terminal  
  * Line mode
  * Enter Key Emulation = cf+lf  
  
Power on the Seeed board by holding down the power button for a second
or two. Select `Connect` in Coolterm. You should get some confirmation
text from the board. If you get a clipped response, you may have to
increase the serial buffer size. This can't be done from the IDE,
rather, you have to edit the following files:  
/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/cores/arduino/HardwareSerial.h  
/Applications/Arduino.app/Contents/Java/hardware/arduino/avr/libraries/SoftwareSerial.h  
Look for all instances of buffers set to 64 and replace with 256. Note that this takes
up a lot of memory, so make sure to change back when you move on to a
new project.

### Sending your first text

Enter `AT+CMGS="XXXXXXXXXXX"` where the XX's are the phone number you
want to dial. In the US I included a 1 before the area code. Hit enter.
Type in the text you want to send and hit enter. Now select Connection >
Send String. Change the mode to `Hex`, type `1A`, and hit enter.

### AT commands

I don't know if you call this a language or syntax or what, but the
attached AT Commands PDF lists all the different things you can talk to
the board about. Here are some useful ones:

Command  
* AT+CMGR=1 | print first SMS in memory 
* AT+CMGD=1,4 | delete all SMS messages

Response  
* +CMTI: "SM",1 = text received, memory location  

### Gotchas  

Quotes indicate string start/stop to the Arduino, so including AT
commands with internal quotes can be tricky. You're supposed to be able
to do `\"` to make a quotation mark work within a string, but I couldn't make the GPRS
understand it.

### Now have fun

Please send me a note or some photos if you use this in a project. Enjoy!
  
