 



#include "rt_nonfinite.h"
#include "output_ar.h"


#include "Arduino.h"
#include "GadgetShield.h"
#define char_T                         char
#define uint8_T                        unsigned int
#define int32_T                        int
#define real_T                         int

void input_ar();
void setup()
{
  input_ar();
}

void loop()
{
  output_ar();
}










  void input_ar(void);


  void input_ar(void)
{
  Serial.begin(4800);
  Setup();

  
  Servo();

  
}

void output_ar(void)
{
  char* tempStr;
  char_T ah;
  char_T bh;
  char_T ch;
  char_T dh;
  char_T eh;
  char_T fh;
  char_T gh;
  char_T hh;
  input_ar();
  attach(9.0);

  
  Gadget_Init();

  
  Serial.write(1.0);

  
  Serial.write(17.0);

  
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter 1st digit");
  Serial.println(tempStr);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rPassword");
  Serial.println(tempStr);
  ah = arduino_switch();

  
  delay(1000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter 2nd digit");
  Serial.println(tempStr);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rPassword");
  Serial.println(tempStr);
  bh = arduino_switch();
  delay(1000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter 3rd digit");
  Serial.println(tempStr);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rPassword");
  Serial.println(tempStr);
  ch = arduino_switch();
  delay(1000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter 4th digit");
  Serial.println(tempStr);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rPassword");
  Serial.println(tempStr);
  dh = arduino_switch();
  delay(1000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rActivating..");
  Serial.println(tempStr);
  delay(3000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rActivated");
  Serial.println(tempStr);
  rotate_positive();
  delay(1000.0);
  Serial.write(17.0);

  
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter Password");
  Serial.println(tempStr);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rto Unlock");
  Serial.println(tempStr);
  delay(3000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter 1st digit");
  Serial.println(tempStr);
  eh = arduino_switch();
  delay(1000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter 2nd digit");
  Serial.println(tempStr);
  fh = arduino_switch();
  delay(1000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter 3rd digit");
  Serial.println(tempStr);
  gh = arduino_switch();
  delay(1000.0);
  tempStr = (char*)calloc(sizeof(char*),17);
  sprintf(tempStr, "%-16s", "\rEnter 4th digit");
  Serial.println(tempStr);
  hh = arduino_switch();
  delay(1000.0);
  if ((ah == eh) && (bh == fh) && (ch == gh) && (dh == hh)) {
    Serial.write(18.0);

    
    rotate_negative();
    delay(2000.0);

    
    tempStr = (char*)calloc(sizeof(char*),17);
    sprintf(tempStr, "%-16s", "\rDONE");
    Serial.println(tempStr);
    tempStr = (char*)calloc(sizeof(char*),17);
    sprintf(tempStr, "%-16s", "\rGood Bye");
    Serial.println(tempStr);
  } else {
    Serial.write(17.0);
    tempStr = (char*)calloc(sizeof(char*),17);
    sprintf(tempStr, "%-16s", "\rWrong Password");
    Serial.println(tempStr);
    tempStr = (char*)calloc(sizeof(char*),17);
    sprintf(tempStr, "%-16s", "\r              ");
    Serial.println(tempStr);

    
    
  }

  while (1) {
    delay(100.0);
  }
}

void output_ar_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

void output_ar_terminate(void)
{
  
}

