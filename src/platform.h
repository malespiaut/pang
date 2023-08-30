#pragma once

#include <stdbool.h>

typedef struct platform Platform;
struct platform
{
  int x;
  int y;
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

#define kPlatform_COUNT 50

extern Platform platforms[kPlatform_COUNT];

void initPlatforms(void);
int createPlatform(int x, int y, int typepf);
void showPlatform(int i);
