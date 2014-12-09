#include <avr/pgmspace.h>
#include <GadgetShield.h>

// How much silent time (in milliseconds) to leave between notes
#define MARCATO_MS  1

// How fast to play...the base note time is this many milliseconds. The 'duration'
// field of each Note[] element is multiplied by this number to get total note
// duration. A duration of 0 ends the song.
#define BASE_TEMPO_MS 60

/* Each note is stored in a 16-bit field:
 
   Lower 6 bits: note number from 0 to 62, and 63 means "silence" (i.e., a rest)
   Upper 10 bits: duration, as a multiple of BASE_TEMP_MS (or 0 to indicate end-of-song)
*/
#define MAKE_NOTE(note,dur) ((dur)<<8 | (note))

// Which note is currently playing
unsigned note_index;

// When to play the next note
unsigned long millis_at_next_note;

// Is the next event a between-note silence?
unsigned marcato_time;

uint8_t lastLed;

uint16_t note2freq =1000;
  
void setup() {
  GS.Setup();
  //note_index = 0;
  //marcato_time = 0;
  // Start playing in 0.1s
  //lastLed = 0;
}

// Just a little "light show" to play along with the music. The higher
// the frequency the "higher up" the LED's go, with a little randomness
// thrown in so things don't get too boring.
void loop() {
  uint8_t note;
  uint16_t duration;


  if (millis() >= millis_at_next_note) {
    if (marcato_time) {
      GS.Speaker(0);
      //marcato_time = 0;
      //millis_at_next_note += MARCATO_MS;
    } else {
      duration = pgm_read_word(20);
      //note_index++;

     // note = (uint8_t) (duration & 0x3F);

     

      GS.Speaker(note2freq);


      duration >>= 6;
      millis_at_next_note += BASE_TEMPO_MS * (uint32_t)duration - MARCATO_MS;
      marcato_time = 1;
    }
  }
}
  

