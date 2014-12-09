#ifndef RAINBOW_H
#define RAINBOW_H

void InitLED();
void SetPixel(byte x, byte y, byte color[]);
void ClearPixel(byte x, byte y);
void Draw();
void BlankLED(char allPages);
void SetMirrorMode(byte mirrorX, byte mirrorY);

#endif
