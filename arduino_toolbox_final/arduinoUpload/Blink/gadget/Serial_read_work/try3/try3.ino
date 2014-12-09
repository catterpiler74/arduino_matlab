//Serial Test
// This is a sample/test program to show the basic functions and software configuration of
// the Unified Microsystems ATS-1 Arduino compatible Terminal Shield (www.unifiedmicro.com)
// The ATS-1 acts like a miniature ASCII terminal.  Characters sent to the transmit line will be
// printed out on the 16X2 LCD screen. There are 6 buttons. Pressing a button will send an ASCII 1-6 
// corresponding to the button pressed.
//  This program prints out a message saying what button is pressed.  Buttons 4-6 also control the buzzer and LED.
//  
// Gary C. Sutcliffe
// January 2011
// 
///ATS-1 Demo Program by Gary C. Sutcliffe is licensed under a Creative Commons Attribution-ShareAlike 3.0 Unported License.
//Updates:
// Changed to use Serial.write function when using Arduino IDE 1.0 or later which no longer supports the BYTE modifier with Serial.print()  1/28/2012


//These are some of the commands that control the ATS-1. These are binary so Serial.write  must be used
#define BELL 0x07  //Character to send to the ATS-1 to generate a beep
#define CLS  0x01  //Character to send to the ATS-1 to clear the LCD and home the cursor
#define LED_ON 0x11  //Character to send to the ATS-1 to turn LED on
#define LED_OFF 0x12 //Character to send to the ATS-1 to turn LED off


void setup() 
{
Serial.begin(4800);   // opens serial port, sets data rate to 4800 baud   
}

int arduino_switch()
{
  
char ch;       //variable for holding key press value

Serial.write(CLS);    //clears the LCD display and puts cursor in upper left corner
Serial.write(LED_OFF);  //start with the ATS-1 LED turned off
Serial.println("Hello, Arduino!");
Serial.print("Press buttons->");
//Serial.write(BELL); //generates a 1/3 second beep
 ch = Serial.read();


while(ch==-1)
  {
   //wait for a button press
   ch = Serial.read();
 
  switch(ch)  //print out the switch number of the switch pressed, also some special things for SW 4,5 &6
    {
    case '1':
    Serial.print("\rSW1 ^          ");
    ch='1';
    break;
    
    case '2':
    Serial.print("\rSW2 >          ");
    ch ='2';
    break;
    
    case '3':
    Serial.print("\rSW3 V          ");
    ch='3';
    break;
    
    case '4':
    ch='4';
    Serial.print("\rSW4 <  Beep    ");
    Serial.write(BELL);  //Also send a beep
    break;
     
    case '5':
    Serial.print("\rSW5 F1  LED On ");
    Serial.write(LED_ON);
    break;
    
    case '6':
    Serial.print("\rSW6 F2  LED Off");
    Serial.write(LED_OFF );
    break;
    
    default: 
    break;
    } //end of switch-case statements   
    
    if(ch=='1' | ch=='2'| ch=='3'| ch=='4'){
      Serial.print("\rSuccess");
      Serial.print("\rComes");
      return 4;
    } 
    
    delay(10000);
      
    
  } // end of main while loop
 
 
  
}  
void loop() 
{
   //char h;
   int h;
   h=arduino_switch();
   Serial.print(h);
} // End of loop() 


