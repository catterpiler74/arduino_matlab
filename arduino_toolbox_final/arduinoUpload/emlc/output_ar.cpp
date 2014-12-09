/*
 * output_ar.c
 *
 * Code generation for function 'output_ar'
 *
 * C source code generated on: Mon Nov 19 13:20:26 2012
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "output_ar.h"

/* Custom Source Code */
#include "Arduino.h"
#define char_T                         char

void input_ar(void);
void setup()
{
  input_ar();
}

void loop()
{
  output_ar();
}

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */


/* Function Definitions */
 void input_ar(void)
{
  /* global pin OUTPUT */
  /* HIGH=1000; */
  /* LOW=0000; */
  /* INPUT =0000; */
  /* LED =int16(13); */
  pinMode(13, 1.0);
}

void output_ar(void)
{
  /* global HIGH LOW OUTPUT INPUT pin */
  input_ar();
  digitalWrite(13.0, 1.0);
  delay(1000.0);
  digitalWrite(13.0, 0.0);
  delay(1000.0);
}

void output_ar_initialize(void)
{
  rt_InitInfAndNaN(8U);
}

void output_ar_terminate(void)
{
  /* (no terminate code required) */
}

/* End of code generation (output_ar.c) */
