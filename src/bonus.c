#include "bonus.h"
#include "collisions.h"
#include "gfx.h"
#include "main.h"
#include "platform.h"
#include "stdlib.h"
#include "structures.h"

Bonus bonus[MAX_BONUS] = {0};

void
initBonus(void)
{
  int i;
  for (i = 0; i < MAX_BONUS; i++)
  {
    bonus[i].active = 0;
  }
}

int
getRandomBonus(void)
{
  int i;
  i = 10;

  while (i > 4)
  {
    i = rand();
    i = i - ((int)(i / 10)) * 10;
  }

  if ((i == 0))
    return BONUS_BOOM;
  if ((i == 1))
    return BONUS_FREEZE;
  if ((i == 2))
    return BONUS_PROTECTION;
  if ((i == 3))
    return WEAPON_DOUBLE_SHOOT;
  if ((i == 4))
    return WEAPON_GLUE_SHOOT;

  return 0;
}

int
createBonus(int type, int x, int y)
{
  int i;
  i = 0;
  while ((bonus[i].active) && (i < MAX_BONUS))
  {
    i++;
  }

  bonus[i].posx = x;
  bonus[i].posy = y;
  bonus[i].xbox = 0;
  bonus[i].ybox = 0;
  bonus[i].hbox = 18;
  bonus[i].lbox = 18;
  bonus[i].type = type;
  bonus[i].active = 1;
  bonus[i].etat = DOWN;
  bonus[i].duree_de_vie = 200;

  return i;
}

void
updateBonus(int i)
{
  int p;
  int collide = 0;

  if (bonus[i].active)
  {
    /* On check les collision avec les plateformes */
    for (p = 0; p < MAX_PLATFORMS; p++)
    {
      if (pform[p].active)
      {
        collide += isCollide(bonus[i].xbox + bonus[i].posx, bonus[i].ybox + bonus[i].posy, bonus[i].hbox, bonus[i].lbox, pform[p].posx, pform[p].posy, pform[p].hauteur, pform[p].largeur);
      }
    }
    /* Si il y à collision, l'état passe à stop ! */
    if (collide > 0)
    {
      bonus[i].etat = STOP;
    }
    else
    {
      bonus[i].etat = DOWN;
    }

    /* On check les collision avec le bas */
    if (bonus[i].posy + bonus[i].hbox > 200)
    {
      bonus[i].etat = STOP;
    }

    if (bonus[i].etat == DOWN)
      bonus[i].posy += 2;
    if (bonus[i].etat == STOP)
      bonus[i].duree_de_vie--;
    if (bonus[i].duree_de_vie < 0)
      bonus[i].active = 0;
  }
}

void
showBonus(int i)
{
  if (bonus[i].active)
  {
    if (bonus[i].type == WEAPON_DOUBLE_SHOOT)
      blitBMPImageToScreen(1, 53, 191, 18, 18, bonus[i].posx, bonus[i].posy, 18, 18);
    else if (bonus[i].type == WEAPON_GLUE_SHOOT)
      blitBMPImageToScreen(1, 11, 191, 18, 18, bonus[i].posx, bonus[i].posy, 18, 18);
    else if (bonus[i].type == BONUS_BOOM)
      blitBMPImageToScreen(1, 116, 191, 18, 18, bonus[i].posx, bonus[i].posy, 18, 18);
    else if (bonus[i].type == BONUS_FREEZE)
      blitBMPImageToScreen(1, 32, 191, 18, 18, bonus[i].posx, bonus[i].posy, 18, 18);
    else if (bonus[i].type == BONUS_LIFE)
      blitBMPImageToScreen(1, 74, 191, 18, 18, bonus[i].posx, bonus[i].posy, 18, 18);
    else if (bonus[i].type == BONUS_PROTECTION)
      blitBMPImageToScreen(1, 158, 191, 18, 18, bonus[i].posx, bonus[i].posy, 18, 18);
  }
}
