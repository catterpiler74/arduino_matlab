#include <arduino.h>
#include <avr/pgmspace.h>
#include "rainbow.h"

//=============================================
//MBI5168
#define SH_DIR_OE    DDRC
#define SH_DIR_SDI   DDRC
#define SH_DIR_CLK   DDRC
#define SH_DIR_LE    DDRC

#define SH_BIT_OE    0x08
#define SH_BIT_SDI   0x01
#define SH_BIT_CLK   0x02
#define SH_BIT_LE    0x04

#define SH_PORT_OE   PORTC
#define SH_PORT_SDI  PORTC
#define SH_PORT_CLK  PORTC
#define SH_PORT_LE   PORTC
//============================================
#define clk_rising  {SH_PORT_CLK&=~SH_BIT_CLK;SH_PORT_CLK|=SH_BIT_CLK;}
#define le_high     {SH_PORT_LE|=SH_BIT_LE;}
#define le_low      {SH_PORT_LE&=~SH_BIT_LE;}
#define enable_oe   {SH_PORT_OE&=~SH_BIT_OE;}
#define disable_oe  {SH_PORT_OE|=SH_BIT_OE;}

#define shift_data_1     {SH_PORT_SDI|=SH_BIT_SDI;}
#define shift_data_0     {SH_PORT_SDI&=~SH_BIT_SDI;}
//============================================
#define open_line0	{PORTB=0x04;}
#define open_line1	{PORTB=0x02;}
#define open_line2	{PORTB=0x01;}
#define open_line3	{PORTD=0x80;}
#define open_line4	{PORTD=0x40;}
#define open_line5	{PORTD=0x20;}
#define open_line6	{PORTD=0x10;}
#define open_line7	{PORTD=0x08;}
#define close_all_line	{PORTD&=~0xf8;PORTB&=~0x07;}
//============================================

#define CheckRequest (g8Flag1&0x01)
#define SetRequest (g8Flag1|=0x01)
#define ClrRequest (g8Flag1&=~0x01)

//==============================================
#define waitingcmd 0x00
#define processing  0x01
#define checking  0x02

#define showPrefabnicatel 0x01
#define showChar 0x02
#define showColor 0x03

/*
const unsigned char GammaTab[16]=
{0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7};
*/
#define GAMMA 0xE7

//========================================================
unsigned char dots[2][3][8][4];
byte pageIndex = 0; // the index of buffer

//=============================================================
unsigned char line,level;
unsigned char State=0;

void SetPixel(byte x, byte y, byte color[])
{
    y = 7 - y;
    byte page = 1 - pageIndex;
    if ((x & 1)) {
        x >>= 1;
        dots[page][0][y][x] = (color[1] >> 4) | (dots[page][0][y][x] & 0xF0);
        dots[page][1][y][x] = (color[0] >> 4) | (dots[page][1][y][x] & 0xF0);
        dots[page][2][y][x] = (color[2] >> 4) | (dots[page][2][y][x] & 0xF0);
    } else {
        x >>= 1;
        dots[page][0][y][x] = (color[1] & 0xF0) | (dots[page][0][y][x] & 0x0F);
        dots[page][1][y][x] = (color[0] & 0xF0) | (dots[page][1][y][x] & 0x0F);
        dots[page][2][y][x] = (color[2] & 0xF0) | (dots[page][2][y][x] & 0x0F);
    }
}

void ClearPixel(byte x, byte y)
{
    y = 7 - y;
    byte page = 1 - pageIndex;
    if ((x & 1)) {
        x >>= 1;
        dots[page][0][y][x] &= 0xF0;
        dots[page][1][y][x] &= 0xF0;
        dots[page][2][y][x] &= 0xF0;
    } else {
        x >>= 1;
        dots[page][0][y][x] &= 0x0F;
        dots[page][1][y][x] &= 0x0F;
        dots[page][2][y][x] &= 0x0F;
    }
}

void init_timer2(void)
{
  TCCR2A |= (1 << WGM21) | (1 << WGM20);
  TCCR2B |= (1<<CS22);   // by clk/64
  TCCR2B &= ~((1<<CS21) | (1<<CS20));   // by clk/64
  TCCR2B &= ~((1<<WGM21) | (1<<WGM20));   // Use normal mode
  ASSR |= (0<<AS2);       // Use internal clock - external clock not used in Arduino
  TIMSK2 |= (1<<TOIE2) | (0<<OCIE2B);   //Timer2 Overflow Interrupt Enable
#ifdef GAMMA
  TCNT2 = GAMMA;
#else
  TCNT2 = GammaTab[0];
#endif
  sei();
}

//==============================================================
void shift_1_bit(unsigned char LS)  //shift 1 bit of  1 Byte color data into Shift register by clock
{
  if(LS)
  {
    shift_data_1;
  }
  else
  {
    shift_data_0;
  }
  clk_rising;
}

//==============================================================
void shift_24_bit(unsigned char line,unsigned char level)   // display one line by the color level in buff
{
  unsigned char color=0,row=0;
  unsigned char data0=0,data1=0;
  le_high;

  for(color=0;color<3;color++)//GBR
  {
    for(row=0;row<4;row++)
    {
      data1=dots[pageIndex][color][line][row]&0x0f;
      data0=dots[pageIndex][color][line][row]>>4;

      //gray scale,0x0f aways light
      shift_1_bit(data0 > level ? 1 : 0);
      shift_1_bit(data1 > level ? 1 : 0);
    }
  }
  le_low;
}


//==============================================================
void open_line(unsigned char line)     // open the scaning line
{
  switch(line)
  {
  case 0: open_line0; break;
  case 1: open_line1; break;
  case 2: open_line2; break;
  case 3: open_line3; break;
  case 4: open_line4; break;
  case 5: open_line5; break;
  case 6: open_line6; break;
  case 7: open_line7; break;
  }
}

//==============================================================
void flash_next_line(unsigned char line,unsigned char level) // scan one line
{
  disable_oe;
  close_all_line;
  open_line(line);
  shift_24_bit(line,level);
  enable_oe;
}

ISR(TIMER2_OVF_vect)          //Timer2  Service
{
#ifdef GAMMA
    TCNT2 = GAMMA;
#else
    TCNT2 = GammaTab[level];    // Reset a  scanning time by gamma value table
#endif

    flash_next_line(line,level);  // scan the next line in LED matrix level by level.
    // when have scaned all LEC the back to line 0 and add the level
    if(++line>7) {
        line=0;
        /*
        level++;
        if(level>15) level=0;
        */
        level = (level + 1) & 0xf;
    }
}

void InitLED()
{
    DDRD=0xff;
    DDRC=0xff;
    DDRB=0xff;
    PORTD=0;
    PORTB=0;
    BlankLED(1);
    init_timer2();  // initial the timer for scanning the LED matrix
}

void Draw()
{
    pageIndex = 1 - pageIndex;
}

void BlankLED(char allPages)
{
    if (allPages) {
        memset(dots, 0, sizeof(dots));
    } else {
        memset(&dots[1 - pageIndex], 0, sizeof(dots[0]));
    }
}
