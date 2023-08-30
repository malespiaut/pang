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
  int origin_x = 148;
  int origin_y = 226;

  for (size_t i = 0; i < strlen(string); ++i)
  {
    int number = string[i] - 48;
    bmp_blit(1, (number * 14) + origin_x + 1, origin_y, 13, 13, x + (i * 6), y, 13, 13);
  }
}

void
showFond(int level)
{
  if ((level == 1) && (fond_loaded != 1))
  {
    bmp_load("romdisk/fond1.png", 0);
    fond_loaded = 1;
  }
  else if ((level == 4) && (fond_loaded != 4))
  {
    bmp_load("romdisk/fond2.png", 0);
    fond_loaded = 4;
  }
  else if ((level == 7) && (fond_loaded != 7))
  {
    bmp_load("romdisk/fond3.png", 0);
    fond_loaded = 7;
  }
  else if ((level == 10) && (fond_loaded != 10))
  {
    bmp_load("romdisk/fond4.png", 0);
    fond_loaded = 10;
  }
  else if ((level == 13) && (fond_loaded != 13))
  {
    bmp_load("romdisk/fond5.png", 0);
    fond_loaded = 13;
  }
  else if ((level == 16) && (fond_loaded != 16))
  {
    bmp_load("romdisk/fond6.png", 0);
    fond_loaded = 16;
  }
  else if ((level == 19) && (fond_loaded != 19))
  {
    bmp_load("romdisk/fond7.png", 0);
    fond_loaded = 19;
  }
  else if ((level == 22) && (fond_loaded != 22))
  {
    bmp_load("romdisk/fond8.png", 0);
    fond_loaded = 22;
  }
  else if ((level == 25) && (fond_loaded != 25))
  {
    bmp_load("romdisk/fond9.png", 0);
    fond_loaded = 25;
  }
  else if ((level == 28) && (fond_loaded != 28))
  {
    bmp_load("romdisk/fond10.png", 0);
    fond_loaded = 28;
  }
  else if ((level == 31) && (fond_loaded != 31))
  {
    bmp_load("romdisk/fond11.png", 0);
    fond_loaded = 31;
  }
  else if ((level == 34) && (fond_loaded != 34))
  {
    bmp_load("romdisk/fond12.png", 0);
    fond_loaded = 34;
  }
  else if ((level == 37) && (fond_loaded != 37))
  {
    bmp_load("romdisk/fond13.png", 0);
    fond_loaded = 37;
  }

  bmp_blit(0, 0, 0, 320, 240, 0, 0, 320, 240);
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
