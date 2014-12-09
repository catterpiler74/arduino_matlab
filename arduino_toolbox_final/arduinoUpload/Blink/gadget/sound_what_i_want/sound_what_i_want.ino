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
  int C3=2867, D3=2554, E3=2276, F3=2148, G3=1914, K3=1705, B3=1519, C4=1434, D4=1277, E4=1138, F4=1074,G4=957, K4=853, B4=760;
 int WW=2000, W=1000, QH=750, H=500, Q=250;

int Notes[] = { E4,D4,C4,D4,E4,E4,E4,D4,D4,D4,E4,G4,G4,E4,D4,C4,D4,E4,E4,E4,E4,D4,D4,E4,D4,C4,0};

// Convert note number to physical frequencies. This mapping uses 110Hz as
// note 0.
int note2freq[] = { Q,Q,Q, Q, Q, Q, H, Q, Q, H, Q,  Q, H, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, Q, W,0};

// Which note is currently playing
unsigned note_index;

// When to play the next note
unsigned long millis_at_next_note;

// Is the next event a between-note silence?
unsigned marcato_time;

uint8_t lastLed;
void setup() {
  GS.Setup();
  note_index = 0;
  marcato_time = 0;
  millis_at_next_note = millis() + 100; // Start playing in 0.1s
  lastLed = 0;
}

// Just a little "light show" to play along with the music. The higher
// the frequency the "higher up" the LED's go, with a little randomness
// thrown in so things don't get too boring.
void rand_led(uint8_t note)
{
  GS.LED(lastLed, 0);
  if (note==63) return;

  if (note <= 12) {
    lastLed = (random(4) >= 2) ? 1 : 0;
  } else if (note <= 24) {
    switch (random(8)) {
      case 7: case 6: lastLed = 2; break;
      case 5: case 4: lastLed = 0; break;
      default: lastLed = 1; break;
    }
  } else if (note <= 36) {
    switch (random(8)) {
      case 7: case 6: lastLed = 1; break;
      case 5: case 4: lastLed = 3; break;
      default: lastLed = 2; break;
    }
  } else {
    lastLed = (random(4) >= 2) ? 2 : 3;
  }
  GS.LED(lastLed, 1);
}

void loop() {
  uint8_t note;
  uint16_t duration;
  int val =millis();
  
  GS.Speaker(pitch);
  
  /*
  if (val>1)
  {
      
    for (int i=0; i<=26; i++){		
    int pitch = Notes[i];		
    GS.Speaker(pitch);
    rand_led(pitch);	
    delay(note2freq[i]);		
    GS.Speaker(0);		
    delay(50);
     
    
  
    }
    */
    
  }
}
