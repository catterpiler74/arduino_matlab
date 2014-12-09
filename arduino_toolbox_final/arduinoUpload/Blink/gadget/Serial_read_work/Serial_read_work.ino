/*
  Button
 
 Turns on and off a light emitting diode(LED) connected to digital  
 pin 13, when pressing a pushbutton attached to pin 2. 
 
 
 The circuit:
 * LED attached from pin 13 to ground 
 * pushbutton attached to pin 2 from +5V
 * 10K resistor attached to pin 2 from ground
 
 * Note: on most Arduinos there is already an LED on the board
 attached to pin 13.
 
 
 created 2005
 by DojoDave <http://www.0j0.org>
 modified 30 Aug 2011
 by Tom Igoe
 
 This example code is in the public domain.
 
 http://www.arduino.cc/en/Tutorial/Button
 */
  
void setup() {
  // initialize the LED pin as an output:
  Serial.begin(4800);
 
}

int arduino_read()
{
  
  char val,ch;
  ch=Serial.read();
  while(ch ==-1);
  while(ch !=-1){
    if(ch=='1') {
       Serial.print("Value");
       return 1; 
       //ch=-1;
     }
    else if (ch=='2'){
      Serial.print("Alu");
       return 2;
       //ch =-1;
     }
     /*
    else
     {
        Serial.print(0x65);
        return 3;
        //ch=-1; 
      }*/
  }
}


void loop(){
  // read the state of the pushbutton value:
 char h,a,b,c; 
 int v;
 //char 
 h=arduino_read();
 
 a=arduino_read();
 b=arduino_read();
 //delay(4000)  ;
 if(a==b)
   Serial.print("Sucess");
 
 //Serial.print(h);
 //Serial.print("hello");
 
}
