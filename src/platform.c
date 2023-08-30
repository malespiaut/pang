#include "platform.h"
#include "gfx.h"
#include "structures.h"

Platform platforms[kPlatform_COUNT];

void
initPlatforms(void)
{
  int i;
  for (i = 0; i < kPlatform_COUNT; i++)
  {
    platforms[i].active = 0;
  }
}

int
createPlatform(int x, int y, int typepf)
{
  int i;
  i = 0;
  while ((platforms[i].active) && (i < kPlatform_COUNT))
  {
    i++;
  }

  if (typepf == PF_INCASSABLE)
  {
    platforms[i].type = PF_INCASSABLE;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 32;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == PF_CASSABLE)
  {
    platforms[i].type = PF_CASSABLE;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 32;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == PF_CASSABLEV)
  {
    platforms[i].type = PF_CASSABLEV;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 32;
    platforms[i].largeur = 8;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == PF_INCASSABLEV)
  {
    platforms[i].type = PF_INCASSABLEV;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 32;
    platforms[i].largeur = 8;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == PF_MOYEN_INCASSABLE)
  {
    platforms[i].type = PF_MOYEN_INCASSABLE;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 16;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == PF_MOYEN_CASSABLE)
  {
    platforms[i].type = PF_MOYEN_CASSABLE;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 16;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == PF_MICRO_INCASSABLE)
  {
    platforms[i].type = PF_MICRO_INCASSABLE;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 8;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == PF_MICRO_CASSABLE)
  {
    platforms[i].type = PF_MICRO_CASSABLE;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 8;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }

  platforms[i].spriteno = sprite_init_free(platforms[i].x, platforms[i].y, platforms[i].type);

  return i;
}

void
showPlatform(int i)
{
  if (platforms[i].active)
  {
    sprite_blit(platforms[i].spriteno);
  }
}
