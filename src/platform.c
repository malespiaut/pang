#include "platform.h"
#include "gfx.h"
#include "structures.h"

Platform pform[MAX_PLATFORMS];

void
initPlatforms(void)
{
  int i;
  for (i = 0; i < MAX_PLATFORMS; i++)
  {
    pform[i].active = 0;
  }
}

int
createPlatform(int x, int y, int typepf)
{
  int i;
  i = 0;
  while ((pform[i].active) && (i < MAX_PLATFORMS))
  {
    i++;
  }

  if (typepf == PF_INCASSABLE)
  {
    pform[i].type = PF_INCASSABLE;
    pform[i].x = x;
    pform[i].y = y;
    pform[i].hauteur = 8;
    pform[i].largeur = 32;
    pform[i].active = 1;
    pform[i].bonus = 0;
  }
  else if (typepf == PF_CASSABLE)
  {
    pform[i].type = PF_CASSABLE;
    pform[i].x = x;
    pform[i].y = y;
    pform[i].hauteur = 8;
    pform[i].largeur = 32;
    pform[i].active = 1;
    pform[i].bonus = 0;
  }
  else if (typepf == PF_CASSABLEV)
  {
    pform[i].type = PF_CASSABLEV;
    pform[i].x = x;
    pform[i].y = y;
    pform[i].hauteur = 32;
    pform[i].largeur = 8;
    pform[i].active = 1;
    pform[i].bonus = 0;
  }
  else if (typepf == PF_INCASSABLEV)
  {
    pform[i].type = PF_INCASSABLEV;
    pform[i].x = x;
    pform[i].y = y;
    pform[i].hauteur = 32;
    pform[i].largeur = 8;
    pform[i].active = 1;
    pform[i].bonus = 0;
  }
  else if (typepf == PF_MOYEN_INCASSABLE)
  {
    pform[i].type = PF_MOYEN_INCASSABLE;
    pform[i].x = x;
    pform[i].y = y;
    pform[i].hauteur = 8;
    pform[i].largeur = 16;
    pform[i].active = 1;
    pform[i].bonus = 0;
  }
  else if (typepf == PF_MOYEN_CASSABLE)
  {
    pform[i].type = PF_MOYEN_CASSABLE;
    pform[i].x = x;
    pform[i].y = y;
    pform[i].hauteur = 8;
    pform[i].largeur = 16;
    pform[i].active = 1;
    pform[i].bonus = 0;
  }
  else if (typepf == PF_MICRO_INCASSABLE)
  {
    pform[i].type = PF_MICRO_INCASSABLE;
    pform[i].x = x;
    pform[i].y = y;
    pform[i].hauteur = 8;
    pform[i].largeur = 8;
    pform[i].active = 1;
    pform[i].bonus = 0;
  }
  else if (typepf == PF_MICRO_CASSABLE)
  {
    pform[i].type = PF_MICRO_CASSABLE;
    pform[i].x = x;
    pform[i].y = y;
    pform[i].hauteur = 8;
    pform[i].largeur = 8;
    pform[i].active = 1;
    pform[i].bonus = 0;
  }

  pform[i].spriteno = sprite_init_free(pform[i].x, pform[i].y, pform[i].type);

  return i;
}

void
showPlatform(int i)
{
  if (pform[i].active)
  {
    sprite_blit(pform[i].spriteno);
  }
}
