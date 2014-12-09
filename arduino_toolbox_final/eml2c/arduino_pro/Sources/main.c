 



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
  
  Setup();

  
  MicrophoneSetBaseline();
}

void output_ar(void)
{
  uint8_T mic_val;

  
  input_ar();
  Filter_Init();
  while (1) {
    mic_val = MicrophoneAmplitude();
    input(mic_val);
    mic_val = result();

    
    if (mic_val > 100) {
      LED(3.0, 1.0);
    } else {
      LED(3.0, 0.0);
    }

    if (mic_val > 75) {
      LED(2.0, 1.0);
    } else {
      LED(2.0, 0.0);
    }

    if (mic_val > 50) {
      LED(1.0, 1.0);
    } else {
      LED(1.0, 0.0);
    }

    if (mic_val > 25) {
      LED(0.0, 1.0);
    } else {
      LED(0.0, 0.0);
    }
  }
}

void output_ar_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

void output_ar_terminate(void)
{
  
}

