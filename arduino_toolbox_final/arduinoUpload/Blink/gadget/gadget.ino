#include <GadgetShield.h>

unsigned long lastMillis;
#define uint8_T unsigned int
#define real_T int
#define int32_T int 

void setup() {
   GS.Setup();
  lastMillis=millis();
}

void loop() {
  
  real_T time;
  real_T val;
  uint8_T b_val;
  int32_T i0;

  
  time = millis();
  val = millis();
  if (val - lastMillis >= 100) {
    lastMillis = lastMillis+100;
    b_val = GS.Pot();
    b_val = b_val / 13;
    
    GS.IRTransmit(1, b_val);
    //lastMillis += 100;
    // Go up to about 20% duty cycle
  }

  b_val = GS.IRReceive();
  if (b_val != 0) {
    GS.RGB(16, 0, 0);
  } else {
    GS.RGB(0, 0, 0);
  }
}
