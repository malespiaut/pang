#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <SDL.h>

#include "gfx.h"
#include "ui.h"

void
showScore(char* string, int x, int y)
{
  int score_x = 148;
  int score_y = 226;

  for (size_t i = 0; i < strlen(string); ++i)
  {
    int number = string[i] - 48;
    blitBMPImageToScreen(1, (number * 14) + score_x + 1, score_y, 13, 13, x + (i * 6), y, 13, 13);
  }
}

void
showFond(int level)
{
  if ((level == 1) && (fond_loaded != 1))
  {
    loadBmp("romdisk/fond1.png", 0);
    fond_loaded = 1;
  }
  else if ((level == 4) && (fond_loaded != 4))
  {
    loadBmp("romdisk/fond2.png", 0);
    fond_loaded = 4;
  }
  else if ((level == 7) && (fond_loaded != 7))
  {
    loadBmp("romdisk/fond3.png", 0);
    fond_loaded = 7;
  }
  else if ((level == 10) && (fond_loaded != 10))
  {
    loadBmp("romdisk/fond4.png", 0);
    fond_loaded = 10;
  }
  else if ((level == 13) && (fond_loaded != 13))
  {
    loadBmp("romdisk/fond5.png", 0);
    fond_loaded = 13;
  }
  else if ((level == 16) && (fond_loaded != 16))
  {
    loadBmp("romdisk/fond6.png", 0);
    fond_loaded = 16;
  }
  else if ((level == 19) && (fond_loaded != 19))
  {
    loadBmp("romdisk/fond7.png", 0);
    fond_loaded = 19;
  }
  else if ((level == 22) && (fond_loaded != 22))
  {
    loadBmp("romdisk/fond8.png", 0);
    fond_loaded = 22;
  }
  else if ((level == 25) && (fond_loaded != 25))
  {
    loadBmp("romdisk/fond9.png", 0);
    fond_loaded = 25;
  }
  else if ((level == 28) && (fond_loaded != 28))
  {
    loadBmp("romdisk/fond10.png", 0);
    fond_loaded = 28;
  }
  else if ((level == 31) && (fond_loaded != 31))
  {
    loadBmp("romdisk/fond11.png", 0);
    fond_loaded = 31;
  }
  else if ((level == 34) && (fond_loaded != 34))
  {
    loadBmp("romdisk/fond12.png", 0);
    fond_loaded = 34;
  }
  else if ((level == 37) && (fond_loaded != 37))
  {
    loadBmp("romdisk/fond13.png", 0);
    fond_loaded = 37;
  }

  blitBMPImageToScreen(0, 0, 0, 320, 240, 0, 0, 320, 240);
}

void
showfps(void)
{
  static float lasttime = 0.0f;
  static uint16_t framespersecond = 0;
  static char strframespersecond[16] = {0};

  float currenttime = SDL_GetTicks64() * 0.001f;
  ++framespersecond;

  if (currenttime - lasttime > 1.0f)
  {
    lasttime = currenttime;
    sprintf(strframespersecond, "FPS %d", framespersecond);
    framespersecond = 0;
  }
  showScore(strframespersecond, 10, 10);
}
