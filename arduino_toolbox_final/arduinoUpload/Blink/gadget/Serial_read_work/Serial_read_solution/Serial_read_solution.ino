
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

int ch=0;
int arduino_read()
{
  
  
  Serial.print("\r   ");
  //ch=Serial.read();
  
  while(1)
  {
     
    ch=Serial.read();
    //while(ch==0); 
      switch(ch)
      {
        case 1:
         Serial.print("\rOne"); 
         ch=1;
         return 1;
         break;
        case 2:
                Serial.print("\rTwo");
               ch=2; 
               return 2;
               break;
        case 3:
               Serial.print("\rThree");
               ch=3;
               return 3;
               break;
        case 4:
               Serial.print("\rFor");
               ch=4;
               return 4;
               break;
        case 5:
                Serial.print("\rZero");
                ch=5;
                return 5;
                break;
      }
  }
}


int arduino_switch()
{
    #define BELL 0x07
    
    while(Serial.available() > 0)
    {
        char incoming =Serial.read();
        Serial.write(BELL);
        
        if (incoming =='1')
            return 1;
        else if (incoming =='2')
            return 2;
        else if(incoming =='3')
            return 3;
        else if(incoming =='4')
            return 4;
        else if (incoming =='5')
            return 5;
        else if(incoming =='6')
            return 6;
            
    }
    return 0;
}
        


void loop(){
  // read the state of the pushbutton value:
 int h,a,b,c; 
 int v;
 //char 
  
 a=arduino_switch();
 b=arduino_switch();
 //c=arduino_switch()
 //d=arduino_switch();
 
 //delay(4000)  ;
 if(a)
   Serial.print(a);
 if(b)
   Serial.print(b);
   
 if(a==b)
   Serial.print("\r  matched");
//else if (b)
  //Serial.print(b);
  
 //  b=arduino_read();
  // if(b)
   //   Serial.print(b);
  delay(1000);    

}
