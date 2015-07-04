# Setting up a SeeedStudios GPRS board (v2)
Here are the [original instructions](http://www.seeedstudio.com/wiki/GPRS_Shield_V2.0). 
I've added to them and cleaned things up for readability. I'm working in OSX.

### Activate GSM card

I got mine through [Adafruit](https://www.adafruit.com/products/2505), but it looks like you can order straight through Ting too.
ting.com/go  
Enter IMEI number from Seeed board  
Enter number on back of sim

### Board preparation

Insert activated SIM card into Seeed board  
Upload default.ino to Arduino  
Attach Seeed board to Arduino  

### Coolterm

I couldn't do everything the Seeed tutorial asked me to do with the
Arduino IDE serial monitor, so I downloaded this one:
http://freeware.the-meiers.org/  

Options  
* Serial Port  
  * Baud = 19200  
  * Port = usbmodemXXXX  
* Terminal  
  * Line mode
  * Enter Key Emulation = cf+lf  
  
Power on the Seeed board by holding down the power button for a second
or two. Select `Connect` in Coolterm. You should get some confirmation
text from the board. If you get some garbage, you might need to set the Seeed board to the
correct baud rate. Enter `AT+IPR=19200` into the terminal and press
enter. You'll get an `OK` if this works.

### Sending your first text

Enter `AT+CMGS="XXXXXXXXXXX"` where the XX's are the phone number you
want to dial. In the US I included a 1 before the area code. Hit enter.
Type in the text you want to send and hit enter. Now select Connection >
Send String. Change the mode to `Hex`, type `1A`, and hit enter.

  
