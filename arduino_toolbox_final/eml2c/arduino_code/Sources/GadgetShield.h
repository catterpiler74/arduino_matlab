/*
  GadgetShield.h - Library for Rugged Circuits Gadget Shield
  Copyright (c) 2011-2012 Rugged Circuits LLC.  All rights reserved.
  http://ruggedcircuits.com

  This file is part of the Rugged Circuits Gadget Shield library for Arduino.

	This library is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License as published by the Free Software
	Foundation; either version 3 of the License, or (at your option) any later
	version.

	This library is distributed in the hope that it will be useful, but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
	details.

	A copy of the GNU General Public License can be viewed at
	<http://www.gnu.org/licenses>
*/

#ifndef _GADGETSHIELD_H_
#define _GADGETSHIELD_H_
#include <inttypes.h>
#include <avr/interrupt.h>
#include <Arduino.h> 

#include <math.h>
#include "gs_twi.h"
#include <stdlib.h>
#include <string.h>
//#include <Servo.h> // this one is for servo
#include <avr/pgmspace.h>
  
 // servo 
//#include <Servo.h> 


#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

// Pin definitions //////////////////////////////////////////////////
#define IRIN_PIN        2 // Digital
#define IROUT_PIN       3
#define LED2_PIN        4
#define RED_PIN         5
#define GREEN_PIN       6
#define ACC_INTn_PIN    7
#define PB2_PIN         8
#define SPEAKER_PIN     9
#define BLUE_PIN       10
#define LED1_PIN       11
#define PB1_PIN        12
#define LED3_PIN       13
#define MICROPHONE_PIN  0  // Analog
#define LIGHTSENSOR_PIN 1  // Analog
#define POT_PIN         2  // Analog
#if defined(__AVR_ATmega328P__)
#  define LED4_PIN       17  // Digital
#  define SDA_PIN        18  // Digital
#  define SCL_PIN        19  // Digital
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#  define LED4_PIN       57  // Digital
#  define SDA_PIN        20  // Digital
#  define SCL_PIN        21  // Digital
#else
#  error "The GadgetShield library is not supported on this processor"
#endif


	void accel_init(void);
    void errorWrite(uint8_t code);
    uint8_t blue_duty_cycle;
    uint8_t serialDebug;
	uint8_t numValid; 

    uint8_t is_shake; // Store accelerometer status until queried by user code
    uint8_t is_tap;
    uint8_t m_pola;
    uint8_t m_bafro;
	
	

    //void twiWrite(const void *buf, uint8_t length);
    //uint8_t s2u(uint8_t val);
    //uint8_t readAxes(uint8_t *x, uint8_t *y, uint8_t *z, uint8_t *shake, uint8_t *tap, uint8_t *PoLa, uint8_t *BaFro);

    // Variables used to build up a set of 4 readings (X/Y/Z/Tilt) over perhaps multiple
    // TWI accesses, since the Alert flag might be set on one or more readings.
    //uint8_t val[4];     // Values of registers 0-3 read on a single transaction
    //uint8_t valid[4];   // Values of registers 0-3 that have been validated (i.e., Alert is not set)
    
	
	uint8_t m_mic_baseline;
	uint8_t m_alpha;
    uint16_t m_state;
	uint8_t alpha=230;
	void MicrophoneSetBaseline(void);
	uint8_t Pot(void);
	void Speaker(uint16_t freq);
	 
    void IRTransmit(uint8_t ison, uint8_t dc);
	uint8_t IRReceive(void) { return digitalRead(IRIN_PIN)==LOW; }
	
	void Gadget_Init()
	{
		blue_duty_cycle = 0; // Used for Blue channel of RGB LED
		numValid = 0;  // Used for low-level accelerometer accesses
	}
	
	void Setup(void)
	{
		// Configure infrared emitter and detector
		pinMode(IRIN_PIN, INPUT);     // There is already an external pullup in the detector itself but it
		digitalWrite(IRIN_PIN, HIGH); // doesn't hurt to add our own pullup as the detector's is weak.
		pinMode(IROUT_PIN, OUTPUT);
		digitalWrite(IROUT_PIN, LOW);

  // Configure general-purpose LED's
		pinMode(LED1_PIN, OUTPUT); pinMode(LED2_PIN, OUTPUT); pinMode(LED3_PIN, OUTPUT); pinMode(LED4_PIN, OUTPUT);
		digitalWrite(LED1_PIN, LOW); digitalWrite(LED2_PIN, LOW); digitalWrite(LED3_PIN, LOW); digitalWrite(LED4_PIN, LOW);

  // Configure RGB LED
		pinMode(RED_PIN, OUTPUT); pinMode(GREEN_PIN, OUTPUT); pinMode(BLUE_PIN, OUTPUT);
		//RGB(0,0,0);

		// Configure pushbuttons
		pinMode(PB1_PIN, INPUT); // There are already external pullups so no internal pullup is needed
		pinMode(PB2_PIN, INPUT);

		// Configure speaker
		pinMode(SPEAKER_PIN, OUTPUT);
		digitalWrite(SPEAKER_PIN, LOW);
		//Speaker(1000); // Just to initialize timer infrastructure for speaker and Blue RGB LED pin
		//Speaker(0);

		// Configure TWI interface to accelerometer and restore to default settings
		//twi_init();

		// Initialize accelerometer
		//accel_init();

		// Assume microphone baseline is 2.5V. Establish experimentally by calling MicrophoneSetBaseline().
		 m_mic_baseline = 127;
	
	}
	
uint8_t LightSensor()
{
  return analogRead(LIGHTSENSOR_PIN) >> 2;
}

void LED(uint8_t which, uint8_t ison)
{
  uint8_t pin;

  switch (which) {
    case 0: pin=LED1_PIN; break;
    case 1: pin=LED2_PIN; break;
    case 2: pin=LED3_PIN; break;
    case 3: pin=LED4_PIN; break;
    default: return;
  }
  digitalWrite(pin, ison ? HIGH : LOW);
}

	// Filter Input
	
	int8_t Microphone(void)
	{
		return (int8_t)(analogRead(MICROPHONE_PIN) >> 2) - m_mic_baseline;
	}
	
	uint8_t MicrophoneAmplitude(void)
	{
		int8_t val;

		val = Microphone();
		return abs(val);
	}
	
	
	
	 void input(uint8_t sample) {
      m_state = (m_alpha*(uint32_t)m_state
                + (uint8_t)((uint8_t)255-m_alpha)*(uint32_t)(((uint16_t)sample) << 3)
                + 128) >> 8;
    }
	uint8_t result(void) {
      return (uint8_t) (m_state >> 3);
    }
	void set_alpha(uint8_t alpha) 
	 { 
		m_alpha = alpha; 
	 }
	 void reset(void) {
      m_state = 0;
    }
	
	void Filter_Init()
	{
		
		set_alpha(alpha);
		reset();
	
	}
	
	void MicrophoneSetBaseline(void)
	{
		uint8_t sample;
		uint16_t sum;

		for (sample=0, sum=0; sample < 64; sample++) {
			sum += analogRead(MICROPHONE_PIN);
		}
  // Shift right by 6 to divide by 64 and get an average. Shift right again by 2
  // to store as an 8-bit number since that's how we process microphone readings.
  // The additions +32 and +2 are for rounding.
		m_mic_baseline = (uint8_t) ((((sum+32) >> 6)+2) >> 2);
	}
	 
	
	//Until here the Microphone program
	
	// Return the potentiometer setting in the range 0-255
	uint8_t Pot(void)
	{
		return analogRead(POT_PIN) >> 2;
	}
	
	void IRTransmit(uint8_t ison, uint8_t dc)
	{
		// No reason for 100% or 0% duty cycles. Just set 'ison==0' for 0%.
		if (dc > 99) dc=99;
		if (dc < 1) dc=1;

		#ifdef __AVR_ATmega328P__
		/* OC2B is our IR emitter. Turn it on at 38 kHz and given duty cycle.

			Use phase correct PWM mode (WGM22:0=101), set OC2B when downcounting and
			clear when upcounting (mode COM2B1:0=10).

			Use prescale of 1 (16 MHz) so that 38 kHz is given by an OCR2A of:

         OCR2A = F_CPU/(2*1*38kHz) = 210 (actually 38.095 kHz)
  */
  OCR2A = (uint8_t) (F_CPU/(2*1*38000UL)) - 1;
  OCR2B = (uint8_t) ((dc*(uint16_t)(OCR2A+1) + 50)/100);
  TCCR2A = (ison ? _BV(COM2B1) : 0) | _BV(WGM20);
  TCCR2B = _BV(WGM22) | _BV(CS20);
  TCNT2 = 0;
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  /* OC3C is our IR emitter. Turn it on at 38 kHz and given duty cycle.

     Use phase-correct PWM mode (WGM33:0=1010) with ICR3 as top (OCR3A is used
     for PWM on pin 5), set OC3C when downcounting and clear when upcounting
     (mode COM3C1:0=10).

     Use prescale of 1 (16 MHz) so that 38 kHz is given by an ICR3 of:

         ICR3 = F_CPU/(2*1*38kHz) = 210  (actually 38.095 kHz)
   */
  ICR3 = (uint16_t) (F_CPU/(2*1*38000UL)) - 1;
  OCR3C = (uint16_t) ((dc*(ICR3+1)+50)/100) - 1;
  TCCR3A = (ison ? _BV(COM3C1) : 0) | _BV(WGM31);
  TCCR3B = _BV(WGM33) | _BV(CS30);
  TCNT3 = 0;
#endif
}
	
	void RGB(uint8_t r, uint8_t g, uint8_t b)
	{
		analogWrite(RED_PIN, r);
		analogWrite(GREEN_PIN, g);
  
  // Must handle BLUE pin specially since it shares a timer with the Speaker
  blue_duty_cycle = b;
  if (b==0) {
#ifdef __AVR_ATmega328P__
    TCCR1A &= ~(_BV(COM1B1) | _BV(COM1B0)); // Disconnect output compare from Blue pin
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    TCCR2A &= ~(_BV(COM2A1) | _BV(COM2A0)); // Disconnect output compare from Blue pin
    TIFR2 = _BV(OCF2B);     // Clear and disable the OCR2B ISR
    TIMSK2 &= ~_BV(OCIE2B);
#endif
    digitalWrite(BLUE_PIN, 0);
  } else {
#ifdef __AVR_ATmega328P__
    TCCR1A |= _BV(COM1B1); // Clear OC1B on compare match, set it at BOTTOM
    OCR1B = (uint16_t) (((uint32_t)blue_duty_cycle*OCR1A) >> 8);
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    TCCR2A |= _BV(COM2A1) | _BV(COM2A0); // Set OC2A on compare match
    TIFR2 = _BV(OCF2B);
    TIMSK2 |= _BV(OCIE2B); // Interrupt on OCR2B match (manually clear OC2A in the ISR)
    OCR2B = (uint8_t) (((uint16_t)blue_duty_cycle*OCR2A) >> 8);
#endif
  }
}

	// MUSIC PROGRAM // before this everything is okey
	
	
#define make_note(note,dur) ((dur)<<6 | (note))	
				// How much silent time (in milliseconds) to leave between notes
#define MARCATO_MS  1
uint16_t note2freq =1000;
unsigned note_index;

// When to play the next note
unsigned long millis_at_next_note;

// Is the next event a between-note silence?
unsigned marcato_time;
// How fast to play...the base note time is this many milliseconds. The 'duration'
// field of each Note[] element is multiplied by this number to get total note
// duration. A duration of 0 ends the song.
#define BASE_TEMPO_MS 60
		/*
		void Sound_gadget(int val)
		{
			uint8_t note;
			uint16_t duration;


			if (millis() >= millis_at_next_note) {
			if (marcato_time) {
				Speaker(0);
				//marcato_time = 0;
				//millis_at_next_note += MARCATO_MS;
			} 
			else 
			{
				duration = pgm_read_word(val); // val sould be at least 20
				//note_index++;

				// note = (uint8_t) (duration & 0x3F);

     

				Speaker(note2freq);


				duration >>= 6;
				millis_at_next_note += BASE_TEMPO_MS * (uint32_t)duration - MARCATO_MS;
				marcato_time = 1;
			}
		}
	}	
	*/ // Obsolete
	
	
	void Sound_gadget(int freq)
		{
			//int val =millis();
			Speaker(freq);
			/*
			if (val>1)
			{
				Speaker(freq);
			}
			*/
		}
		
	
void Speaker(uint16_t freq)
{
  /* We set a target frequency range of 0-3 kHz as the speaker isn't very responsive beyond that. Pin 9
     is a different timer on different processors:
        * TIMER1A on ATmega328P
        * TIMER2B on ATmega2560/1280

     For TIMER1A we want fast PWM mode (WGM13:0=1111) with OCR1A as the TOP
     value and we configure COM1A1:0=01 so that OC1A toggles on each compare
     match. Thus we want OCR1A to be half the desired target period.

     Here is how we choose prescale (we want the lowest prescale for maximum resolution):
        Prescale=1 (16 MHz): freq = 123 Hz (OCR1A=65040) to 3 kHz (OCR1A=5333)
        Prescale=8 (2 MHz): freq = 16 Hz (OCR1A=62500) to 123 Hz (OCR1A=8130)

     Guiding equation:
              OCR1A = (F_CPU/Prescale)/TargetFreq/2 - 1 = F_CPU/(Prescale*TargetFreq*2) - 1
  */
  uint32_t divisor;
  uint16_t ocrval;

#ifdef __AVR_ATmega328P__
  if (freq == 0) {
    TCCR1A &= ~_BV(COM1A0); // Disconnect output compare from pin
    digitalWrite(SPEAKER_PIN, LOW);
  } else {
    TCCR1A = (TCCR1A & ~(_BV(COM1A1))) | _BV(COM1A0) | _BV(WGM11) | _BV(WGM10); // Set output mode 01, toggle OC1A on compare match, waveform generation mode 1111 (Fast PWM, OCR1A as top)
    TCNT1=0;
    if (freq >= 123) {
      divisor = 1*freq*2;
      TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10); // Divide-by-1 prescale, Fast PWM mode (1111)
    } else {
      divisor = 8*freq*2;
      TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS11); // Divide-by-8 prescale, Fast PWM mode (1111)
    }
    // OCR1A sets the frequency and the Speaker pin toggles on OC1A.
    // 
    // Now, for the Blue LED (OC1B), we set it up such that OC1B is cleared on
    // every compare (COM1B1:0=10) and is set to 1 at BOTTOM.
    ocrval = (uint16_t)((F_CPU + divisor/2) / divisor) - 1;
    OCR1A = ocrval; // Not updated until BOTTOM so save it in a variable for OCR1B computation

    // Preserve duty cycle on OC1B since that's D10, the blue part of the RGB LED
    OCR1B = (uint16_t) (((uint32_t)blue_duty_cycle*ocrval) >> 8);
  }
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  /* For TIMER2B we want CTC mode (WGM22:0=010) with OCR2A as the TOP
     value and we configure COM2B1:0=01 so that OC2B toggles on each compare
     match. Thus we want OCR2A to be half the desired target period.

     For 8-bit Timer 2, here is how we choose prescale:
        Prescale=32 (500 kHz):  freq = 977 Hz (OCR2A = 254) to 3 kHz (OCR2A = 82)
        Prescale=64 (250 kHz):  freq = 489 Hz (OCR2A = 254) to 977 Hz (OCR2A = 126)
        Prescale=128 (125 kHz): freq = 244 Hz (OCR2A = 255) to 489 Hz (OCR2A = 126)
        Prescale=256 (62.5 kHz): freq = 123 Hz (OCR2A = 253) to 244 Hz (OCR2A = 127)
        Prescale=1024 (15.625 kHz): freq = 31 Hz (OCR2A = 251) to 123 Hz (OCR2A = 62)

     Since OC2A is the Blue channel of the RGB LED, we implement a poor-man's PWM mode.
     We set COM2A1:0=11 to set OC2A at the timer TOP value (OCR2A) and we clear OC2A
     in an interrupt service routine for a compare on OCR2B. Thus OCR2B sets the Blue
     channel duty cycle, but it actually controls the OC2A pin.
  */
  if (freq == 0) {
    TCCR2A &= ~_BV(COM2B0);
    digitalWrite(SPEAKER_PIN, LOW);
  } else {
    TCCR2A = (TCCR2A & ~(_BV(COM2B1)|_BV(WGM20))) | _BV(COM2B0) | _BV(WGM21); // Set output mode 01, toggle OC2B on compare match, waveform generation mode 010 (CTC)
    if (freq >= 977) {
      divisor = 32UL*freq*2;
      TCCR2B = _BV(CS21) | _BV(CS20);
    } else if (freq >= 489) {
      divisor = 64UL*freq*2;
      TCCR2B = _BV(CS22);
    } else if (freq >= 244) {
      divisor = 128UL*freq*2;
      TCCR2B = _BV(CS22) | _BV(CS20);
    } else if (freq >= 123) {
      divisor = 256UL*freq*2;
      TCCR2B = _BV(CS22) | _BV(CS21);
    } else {
      divisor = 1024UL*freq*2;
      TCCR2B = _BV(CS22) | _BV(CS21) | _BV(CS20);
    }
    // OCR2A sets the frequency, but the Speaker pin toggles on OC2B. It
    // doesn't matter what OC2B is, however, as long as it's in the range
    // [0,OCR2A]. Once every period OC2B toggles and the speaker has a 50% duty
    // cycle waveform at the frequency set by OCR2A. 
    // 
    // Now, for the Blue LED, we set it up such that OC2A is automatically set
    // to 1 on every compare (COM2A1:0=11) and is cleared in an ISR when we
    // have a compare match on OCR2B.
    OCR2A = (uint8_t) ((F_CPU + divisor/2) / divisor) - 1;
    OCR2B = (uint8_t) (((uint16_t)blue_duty_cycle*(OCR2A+1)) >> 8);
  }
#endif
}




/* Simple first-order IIR filter on 8-bit unsigned inputs. We use a 8-bit
 * state variable with an extra 3 bits of fixed-point precision:

            +-------------------------+-------------+
            |     8-bit state         | 3-bit state |
            +-------------------------.-------------+
            \__saved as the reading__/ 
*/

/*
class IIRFilter
{
  public:
    IIRFilter(uint8_t alpha=230) 
	//{
  //    set_alpha(alpha);
   //   reset();
   // }
*/
/*
    void input(uint8_t sample) {
      m_state = (m_alpha*(uint32_t)m_state
                + (uint8_t)((uint8_t)255-m_alpha)*(uint32_t)(((uint16_t)sample) << 3)
                + 128) >> 8;
    }

    void reset(void) {
      m_state = 0;
    }

    uint8_t result(void) {
      return (uint8_t) (m_state >> 3);
    }

    uint8_t get_alpha(void) { return m_alpha; }
    void set_alpha(uint8_t alpha) { m_alpha = alpha; }

  private:
    uint8_t m_alpha;
    uint16_t m_state;
};
*/

/*
class GadgetShield
{
  private:
    IIRFilter filter_x, filter_y, filter_z; // Filter X/Y/Z accelerometer axes
    void accel_init(void);
    void errorWrite(uint8_t code);
    uint8_t blue_duty_cycle;
    uint8_t serialDebug;

    uint8_t is_shake; // Store accelerometer status until queried by user code
    uint8_t is_tap;
    uint8_t m_pola;
    uint8_t m_bafro;

    uint8_t m_mic_baseline; // Average mic reading (i.e., reading when there is quiet)

    void twiWrite(const void *buf, uint8_t length);
    uint8_t s2u(uint8_t val);
    uint8_t readAxes(uint8_t *x, uint8_t *y, uint8_t *z, uint8_t *shake, uint8_t *tap, uint8_t *PoLa, uint8_t *BaFro);

    // Variables used to build up a set of 4 readings (X/Y/Z/Tilt) over perhaps multiple
    // TWI accesses, since the Alert flag might be set on one or more readings.
    uint8_t val[4];     // Values of registers 0-3 read on a single transaction
    uint8_t valid[4];   // Values of registers 0-3 that have been validated (i.e., Alert is not set)
    uint8_t numValid; // How many validated values we have

  public:
    GadgetShield();

    // Call this function in your setup() code
      void Setup(void);

    // Accelerometer interface
      // Blocking function that reads all 3 axes and performs filtering
      void AccelSample(void);

      // Returns true if accelerometer interrupt is asserted. Currently the
      // accelerometer asserts an interrupt if a "shake" condition is detected.
      uint8_t AccelIsInt(void);

      // Return accelerometer X/Y/Z readings in the range 0-63
      uint8_t AccelResultX(void) { return filter_x.result(); }
      uint8_t AccelResultY(void) { return filter_y.result(); }
      uint8_t AccelResultZ(void) { return filter_z.result(); }

      // Change filtering on accelerometer readings. Filter parameter is in the range
      // 0 to 255 where higher numbers represent more filtering.
      void AccelSetFilterX(uint8_t alpha) { filter_x.set_alpha(alpha); }
      void AccelSetFilterY(uint8_t alpha) { filter_y.set_alpha(alpha); }
      void AccelSetFilterZ(uint8_t alpha) { filter_z.set_alpha(alpha); }

      // Return true if a shake condition was recorded since the last time this function was called
      uint8_t AccelShake(void) { uint8_t retval = is_shake; is_shake=0; return retval; }

      // Return true if a tap condition was recorded since the last time this function was called
      uint8_t AccelTap(void) { uint8_t retval = is_tap; is_tap=0; return retval; }

      // Return current portrait/landscape orientation (see MMA7660FC documentation)
      uint8_t AccelPoLa(void) { return m_pola; }

      // Return current back/front orientation (see MMA7660FC documentation)
      uint8_t AccelBaFro(void) { return m_bafro; }

      // Change the debounce parameter for tap/point detection.
      void AccelSetDebounce(uint8_t val);

    // General-purpose LED interface
      // Turn the given LED (which is 0 to 3) on or off (ison==1 to turn on)
      void LED(uint8_t which, uint8_t ison);

      // Slightly simpler functions for the above
      void LEDSet(uint8_t which) { LED(which, 1); }
      void LEDClear(uint8_t which) { LED(which, 0); }

    // General-purpose switch interface
      // Returns true if the given switch (which is 0 or 1) is pressed
      uint8_t IsSwitch(uint8_t which);

    // RGB LED interface
      // Set the brightness of each RGB LED (parameters are in the range 0 - 255).
      // NOTE: Brightness levels of 16 or lower are recommended. The RGB LED is
      // *VERY BRIGHT* and at high levels should not be looked at directly.
      void RGB(uint8_t r, uint8_t g, uint8_t b);

    // Speaker interface
      // Turn the speaker on with the given frequency in Hertz. Specify 'freq==0'
      // to turn the speaker off.
      void Speaker(uint16_t freq);

    // Potentiometer interface
      // Return potentiometer setting in the range 0 - 255
      uint8_t Pot(void);

    // Microphone interface
      // Return microphone sample in the range [-128,127].
      int8_t Microphone(void); // Signed value!

      // Return absolute value of Microphone()
      uint8_t MicrophoneAmplitude(void);

      // Take 64 samples of the microphone and average them. This average reading
      // is then subtracted out of all future calls to Microphone() and MicrophoneAmplitude().
      // Thus, this function should be called when the microphone is in a "quiet" condition.
      void MicrophoneSetBaseline(void);

    // Light sensor interface
      // Return light sensor reading in the range 0 - 255. NOTE: Lower readings
      // indicate more light.
      uint8_t LightSensor(void);

    // IR receiver interface
      // Return true if the IR logic detector is detecting 38 kHz IR energy
      uint8_t IRReceive(void) { return digitalRead(IRIN_PIN)==LOW; }

      // Turn on IR transmitter at 38 kHz (if ison is non-zero) at the given
      // duty cycle (dc is in the range 1 - 99).
      void IRTransmit(uint8_t ison, uint8_t dc);

      // Blocking function that waits until the given number of 38 kHz pulses
      // have been transmitted. Useful for constructing precise remote control transmissions.
      void IRTransmitCountPulses(uint16_t numPulses);

      // Fast enable/disable of IR transmitter without changing timer parameters.
      void IRTransmitEnable(uint8_t ison);

    // Serial debugging...some functions use Serial.print() for debugging if this is enabled
      void SetSerialDebug(uint8_t ison) { serialDebug = ison; }
};

extern GadgetShield GS;
*/



// Servo Code 

/*
  Servo.h - Interrupt driven Servo library for Arduino using 16 bit timers- Version 2
  Copyright (c) 2009 Michael Margolis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/



/* 
 * Defines for 16 bit timers used with  Servo library 
 *
 * If _useTimerX is defined then TimerX is a 16 bit timer on the curent board
 * timer16_Sequence_t enumerates the sequence that the timers should be allocated
 * _Nbr_16timers indicates how many 16 bit timers are available.
 *
 */

// Say which 16 bit timers can be used and in what order
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
#define _useTimer5
#define _useTimer1 
#define _useTimer3
#define _useTimer4 
typedef enum { _timer5, _timer1, _timer3, _timer4, _Nbr_16timers } timer16_Sequence_t ;

#elif defined(__AVR_ATmega32U4__)  
#define _useTimer1 
typedef enum { _timer1, _Nbr_16timers } timer16_Sequence_t ;

#elif defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB1286__)
#define _useTimer3
#define _useTimer1
typedef enum { _timer3, _timer1, _Nbr_16timers } timer16_Sequence_t ;

#elif defined(__AVR_ATmega128__) ||defined(__AVR_ATmega1281__)||defined(__AVR_ATmega2561__)
#define _useTimer3
#define _useTimer1
typedef enum { _timer3, _timer1, _Nbr_16timers } timer16_Sequence_t ;

#else  // everything else
#define _useTimer1
typedef enum { _timer1, _Nbr_16timers } timer16_Sequence_t ;                  
#endif

#define Servo_VERSION           2      // software version of this library

#define MIN_PULSE_WIDTH       544     // the shortest pulse sent to a servo  
#define MAX_PULSE_WIDTH      2400     // the longest pulse sent to a servo 
#define DEFAULT_PULSE_WIDTH  1500     // default pulse width when servo is attached
#define REFRESH_INTERVAL    20000     // minumim time to refresh servos in microseconds 

#define SERVOS_PER_TIMER       12     // the maximum number of servos controlled by one timer 
#define MAX_SERVOS   (_Nbr_16timers  * SERVOS_PER_TIMER)

#define INVALID_SERVO         255     // flag indicating an invalid servo index

typedef struct  {
  uint8_t nbr        :6 ;             // a pin number from 0 to 63
  uint8_t isActive   :1 ;             // true if this channel is enabled, pin not pulsed if false 
} ServoPin_t   ;  

typedef struct {
  ServoPin_t Pin;
  unsigned int ticks;
} servo_t;


#define usToTicks(_us)    (( clockCyclesPerMicrosecond()* _us) / 8)     // converts microseconds to tick (assumes prescale of 8)  // 12 Aug 2009
#define ticksToUs(_ticks) (( (unsigned)_ticks * 8)/ clockCyclesPerMicrosecond() ) // converts from ticks back to microseconds


#define TRIM_DURATION       2                               // compensation ticks to trim adjust for digitalWrite delays // 12 August 2009

//#define NBR_TIMERS        (MAX_SERVOS / SERVOS_PER_TIMER)




  void Servo();
  uint8_t attach(int pin);           // attach the given pin to the next free channel, sets pinMode, returns channel number or 0 if failure
  uint8_t attach2(int pin, int min, int max); // as above but also sets min and max values for writes. 
  void detach();
  void write(int value);             // if value is < 200 its treated as an angle, otherwise as pulse width in microseconds 
  void writeMicroseconds(int value); // Write pulse width in microseconds 
  int read();                        // returns current pulse width as an angle between 0 and 180 degrees
  int readMicroseconds();            // returns current pulse width in microseconds for this servo (was read_us() in first release)
  bool attached();                   // return true if this servo is attached, otherwise false 
  
                                // maximum is this value times 4 added to MAX_PULSE_WIDTH   

								
								


 uint8_t servoIndex;               // index into the channel data for this servo
 int8_t min;                       // minimum is this value times 4 added to MIN_PULSE_WIDTH    
 int8_t max; 










static servo_t servos[MAX_SERVOS];                          // static array of servo structures
static volatile int8_t Channel[_Nbr_16timers ];             // counter for the servo being pulsed for each timer (or -1 if refresh interval)

uint8_t ServoCount = 0;                                     // the total number of attached servos


// convenience macros
#define SERVO_INDEX_TO_TIMER(_servo_nbr) ((timer16_Sequence_t)(_servo_nbr / SERVOS_PER_TIMER)) // returns the timer controlling this servo
#define SERVO_INDEX_TO_CHANNEL(_servo_nbr) (_servo_nbr % SERVOS_PER_TIMER)       // returns the index of the servo on this timer
#define SERVO_INDEX(_timer,_channel)  ((_timer*SERVOS_PER_TIMER) + _channel)     // macro to access servo index by timer and channel
#define SERVO(_timer,_channel)  (servos[SERVO_INDEX(_timer,_channel)])            // macro to access servo class by timer and channel

#define SERVO_MIN() (MIN_PULSE_WIDTH - min * 4)  // minimum value in uS for this servo
#define SERVO_MAX() (MAX_PULSE_WIDTH - max * 4)  // maximum value in uS for this servo 

/************ static functions common to all instances ***********************/

static inline void handle_interrupts(timer16_Sequence_t timer, volatile uint16_t *TCNTn, volatile uint16_t* OCRnA)
{
  if( Channel[timer] < 0 )
    *TCNTn = 0; // channel set to -1 indicated that refresh interval completed so reset the timer 
  else{
    if( SERVO_INDEX(timer,Channel[timer]) < ServoCount && SERVO(timer,Channel[timer]).Pin.isActive == true )  
      digitalWrite( SERVO(timer,Channel[timer]).Pin.nbr,LOW); // pulse this channel low if activated   
  }

  Channel[timer]++;    // increment to the next channel
  if( SERVO_INDEX(timer,Channel[timer]) < ServoCount && Channel[timer] < SERVOS_PER_TIMER) {
    *OCRnA = *TCNTn + SERVO(timer,Channel[timer]).ticks;
    if(SERVO(timer,Channel[timer]).Pin.isActive == true)     // check if activated
      digitalWrite( SERVO(timer,Channel[timer]).Pin.nbr,HIGH); // its an active channel so pulse it high   
  }  
  else { 
    // finished all channels so wait for the refresh period to expire before starting over 
    if( ((unsigned)*TCNTn) + 4 < usToTicks(REFRESH_INTERVAL) )  // allow a few ticks to ensure the next OCR1A not missed
      *OCRnA = (unsigned int)usToTicks(REFRESH_INTERVAL);  
    else 
      *OCRnA = *TCNTn + 4;  // at least REFRESH_INTERVAL has elapsed
    Channel[timer] = -1; // this will get incremented at the end of the refresh period to start again at the first channel
  }
}

#ifndef WIRING // Wiring pre-defines signal handlers so don't define any if compiling for the Wiring platform
// Interrupt handlers for Arduino 
#if defined(_useTimer1)
SIGNAL (TIMER1_COMPA_vect) 
{ 
  handle_interrupts(_timer1, &TCNT1, &OCR1A); 
}
#endif

#if defined(_useTimer3)
SIGNAL (TIMER3_COMPA_vect) 
{ 
  handle_interrupts(_timer3, &TCNT3, &OCR3A); 
}
#endif

#if defined(_useTimer4)
SIGNAL (TIMER4_COMPA_vect) 
{
  handle_interrupts(_timer4, &TCNT4, &OCR4A); 
}
#endif

#if defined(_useTimer5)
SIGNAL (TIMER5_COMPA_vect) 
{
  handle_interrupts(_timer5, &TCNT5, &OCR5A); 
}
#endif

#elif defined WIRING
// Interrupt handlers for Wiring 
#if defined(_useTimer1)
void Timer1Service() 
{ 
  handle_interrupts(_timer1, &TCNT1, &OCR1A); 
}
#endif
#if defined(_useTimer3)
void Timer3Service() 
{ 
  handle_interrupts(_timer3, &TCNT3, &OCR3A); 
}
#endif
#endif


static void initISR(timer16_Sequence_t timer)
{  
#if defined (_useTimer1)
  if(timer == _timer1) {
    TCCR1A = 0;             // normal counting mode 
    TCCR1B = _BV(CS11);     // set prescaler of 8 
    TCNT1 = 0;              // clear the timer count 
#if defined(__AVR_ATmega8__)|| defined(__AVR_ATmega128__)
    TIFR |= _BV(OCF1A);      // clear any pending interrupts; 
    TIMSK |=  _BV(OCIE1A) ;  // enable the output compare interrupt  
#else
    // here if not ATmega8 or ATmega128
    TIFR1 |= _BV(OCF1A);     // clear any pending interrupts; 
    TIMSK1 |=  _BV(OCIE1A) ; // enable the output compare interrupt 
#endif    
#if defined(WIRING)       
    timerAttach(TIMER1OUTCOMPAREA_INT, Timer1Service); 
#endif	
  } 
#endif  

#if defined (_useTimer3)
  if(timer == _timer3) {
    TCCR3A = 0;             // normal counting mode 
    TCCR3B = _BV(CS31);     // set prescaler of 8  
    TCNT3 = 0;              // clear the timer count 
#if defined(__AVR_ATmega128__)
    TIFR |= _BV(OCF3A);     // clear any pending interrupts;   
	ETIMSK |= _BV(OCIE3A);  // enable the output compare interrupt     
#else  
    TIFR3 = _BV(OCF3A);     // clear any pending interrupts; 
    TIMSK3 =  _BV(OCIE3A) ; // enable the output compare interrupt      
#endif
#if defined(WIRING)    
    timerAttach(TIMER3OUTCOMPAREA_INT, Timer3Service);  // for Wiring platform only	
#endif  
  }
#endif

#if defined (_useTimer4)
  if(timer == _timer4) {
    TCCR4A = 0;             // normal counting mode 
    TCCR4B = _BV(CS41);     // set prescaler of 8  
    TCNT4 = 0;              // clear the timer count 
    TIFR4 = _BV(OCF4A);     // clear any pending interrupts; 
    TIMSK4 =  _BV(OCIE4A) ; // enable the output compare interrupt
  }    
#endif

#if defined (_useTimer5)
  if(timer == _timer5) {
    TCCR5A = 0;             // normal counting mode 
    TCCR5B = _BV(CS51);     // set prescaler of 8  
    TCNT5 = 0;              // clear the timer count 
    TIFR5 = _BV(OCF5A);     // clear any pending interrupts; 
    TIMSK5 =  _BV(OCIE5A) ; // enable the output compare interrupt      
  }
#endif
} 

static void finISR(timer16_Sequence_t timer)
{
    //disable use of the given timer
#if defined WIRING   // Wiring
  if(timer == _timer1) {
    #if defined(__AVR_ATmega1281__)||defined(__AVR_ATmega2561__)
    TIMSK1 &=  ~_BV(OCIE1A) ;  // disable timer 1 output compare interrupt
    #else 
    TIMSK &=  ~_BV(OCIE1A) ;  // disable timer 1 output compare interrupt   
    #endif
    timerDetach(TIMER1OUTCOMPAREA_INT); 
  }
  else if(timer == _timer3) {     
    #if defined(__AVR_ATmega1281__)||defined(__AVR_ATmega2561__)
    TIMSK3 &= ~_BV(OCIE3A);    // disable the timer3 output compare A interrupt
    #else
    ETIMSK &= ~_BV(OCIE3A);    // disable the timer3 output compare A interrupt
    #endif
    timerDetach(TIMER3OUTCOMPAREA_INT);
  }
#else
    //For arduino - in future: call here to a currently undefined function to reset the timer
#endif
}

static boolean isTimerActive(timer16_Sequence_t timer)
{
  // returns true if any servo is active on this timer
  for(uint8_t channel=0; channel < SERVOS_PER_TIMER; channel++) {
    if(SERVO(timer,channel).Pin.isActive == true)
      return true;
  }
  return false;
}


/****************** end of static functions ******************************/

void Servo()
{
  if( ServoCount < MAX_SERVOS) {
    servoIndex = ServoCount++;                    // assign a servo index to this instance
	servos[servoIndex].ticks = usToTicks(DEFAULT_PULSE_WIDTH);   // store default values  - 12 Aug 2009
  }
  else
    servoIndex = INVALID_SERVO ;  // too many servos 
}

uint8_t attach(int pin)
{
  return attach2(pin, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
}

uint8_t attach2(int pin, int mina, int maxa)
{
  if(servoIndex < MAX_SERVOS ) {
    pinMode( pin, OUTPUT) ;                                   // set servo pin to output
    servos[servoIndex].Pin.nbr = pin;  
    // todo min/max check: abs(min - MIN_PULSE_WIDTH) /4 < 128 
    mina  = (MIN_PULSE_WIDTH - mina)/4; //resolution of min/max is 4 uS
    maxa  = (MAX_PULSE_WIDTH - maxa)/4; 
    // initialize the timer if it has not already been initialized 
    timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
    if(isTimerActive(timer) == false)
      initISR(timer);    
    servos[servoIndex].Pin.isActive = true;  // this must be set after the check for isTimerActive
  } 
  //write(0);
  return servoIndex ;
}

void detach()  
{
  servos[servoIndex].Pin.isActive = false;  
  timer16_Sequence_t timer = SERVO_INDEX_TO_TIMER(servoIndex);
  if(isTimerActive(timer) == false) {
    finISR(timer);
  }
}

void write(int value)
{  
  if(value < MIN_PULSE_WIDTH)
  {  // treat values less than 544 as angles in degrees (valid values in microseconds are handled as microseconds)
    if(value < 0) value = 0;
    if(value > 180) value = 180;
    value = map(value, 0, 180, SERVO_MIN(),  SERVO_MAX());      
  }
  writeMicroseconds(value);
}

void writeMicroseconds(int value)
{
  // calculate and store the values for the given channel
  byte channel = servoIndex;
  if( (channel < MAX_SERVOS) )   // ensure channel is valid
  {  
    if( value < SERVO_MIN() )          // ensure pulse width is valid
      value = SERVO_MIN();
    else if( value > SERVO_MAX() )
      value = SERVO_MAX();   
    
  	value = value - TRIM_DURATION;
    value = usToTicks(value);  // convert to ticks after compensating for interrupt overhead - 12 Aug 2009

    uint8_t oldSREG = SREG;
    cli();
    servos[channel].ticks = value;  
    SREG = oldSREG;   
  } 
}

int read() // return the value as degrees
{
  return  map( readMicroseconds()+1, SERVO_MIN(), SERVO_MAX(), 0, 180);     
}

int readMicroseconds()
{
  unsigned int pulsewidth;
  if( servoIndex != INVALID_SERVO )
    pulsewidth = ticksToUs(servos[servoIndex].ticks)  + TRIM_DURATION ;   // 12 aug 2009
  else 
    pulsewidth  = 0;

  return pulsewidth;   
}

bool attached()
{
  return servos[servoIndex].Pin.isActive ;
}
		


   
   
   /*


  int arduino_switch(int val)
  {
	*/


/*

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


*/

int arduino_switch()
{
    char incoming;
 
  #define BELL 0x07
  // char ncoming =0; while(incoming ==0);  
  while(Serial.available() <= 0); // Wait until char available
 
  incoming = Serial.read(); // read char
    while(incoming == -1) // if char == -1 (no button)
    { // keep reading 
  while(Serial.available() <= 0);           // ensure char available before read
 
        incoming = Serial.read();                   // read next char
  }
 
    Serial.write(BELL);                                 // at this point we have read a char
// other than -1 so one of the buttons 
// has been pressed
 
    if (incoming =='1') // 1st button pushed
        return 1;
    else if (incoming =='2') // 2nd button pushed
        return 2;
    else if(incoming =='3') // 3rd button pushed
        return 3;
    else if(incoming =='4') // 4th button pushed
        return 4;
    else if (incoming =='5') // 5th button pushed
        return 5;
    else if(incoming =='6') // 6th button pushed
        return 6;
            
    
    return 0; // how'd we get hear?
}


//write(0);
void rotate_positive()
  {  
  write(180);
  }
void  rotate_negative()
  {
   // write(180);
  //  delay(1000);
    write(0);
  }







#endif // _GADGETSHIELD_H_
// vim: expandtab ts=2 sw=2 ai cindent




