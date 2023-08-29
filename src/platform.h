#pragma once

#include <stdbool.h>

typedef struct platform Platform;
struct platform
{
  int posx;
  int posy;
  int hauteur;
  int largeur;
  bool active;
  int xbox;
  int ybox;
  int hbox; /* Hauteur et largeur de la boite de collision */
  int lbox;
  int type;
  int spriteno;
  int bonus;
};

#define MAX_PLATFORMS 50

extern Platform pform[MAX_PLATFORMS];

void initPlatforms(void);
int createPlatform(int posx, int posy, int typepf);
void showPlatform(int i);
