#include "shoot.h"
#include "bonus.h"
#include "collisions.h"
#include "gfx.h"
#include "main.h"
#include "platform.h"
#include "sound.h"
#include "structures.h"

Shoot shoot[MAX_SHOOT];

void
initShoot(void)
{
  int i;
  for (i = 0; i < MAX_SHOOT; i++)
  {
    shoot[i].active = 0;
  }
}

void
createShoot(int type)
{
  int i;
  i = 0;
  while ((shoot[i].active) && (i < MAX_SHOOT))
  {
    i++;
  }

  if ((type == WEAPON_NORMAL_SHOOT) || (type == WEAPON_DOUBLE_SHOOT) || (type == WEAPON_GLUE_SHOOT))
  {
    shoot[i].posx = player.posx + 12;
    shoot[i].posy = player.posy; /*-30;*/
    shoot[i].xbox = 0;
    shoot[i].ybox = 0;
    shoot[i].hbox = 0;
    shoot[i].lbox = 9;
    shoot[i].type = type;
    shoot[i].active = 1;
    shoot[i].duree = -1;
    shoot[i].posy_depart = player.posy + 32;
    playSound(3, 0);
  }
}

void
updateShoot(int i)
{
  int p;
  if (shoot[i].active)
  {
    if ((shoot[i].type == WEAPON_NORMAL_SHOOT) || (shoot[i].type == WEAPON_DOUBLE_SHOOT))
    {
      shoot[i].posy = shoot[i].posy - 2;
      shoot[i].hbox = (shoot[i].posy_depart) - shoot[i].posy;
      if (shoot[i].posy < 8)
      {
        shoot[i].active = 0;
        player.nbtir--;
      }
    }
    if (shoot[i].type == WEAPON_GLUE_SHOOT)
    {
      if (shoot[i].duree == -1)
        shoot[i].posy = shoot[i].posy - 2;
      shoot[i].hbox = (shoot[i].posy_depart) - shoot[i].posy;
      if (shoot[i].posy < 8)
      {
        if (shoot[i].duree == -1)
          shoot[i].duree = 120;
        shoot[i].posy = 8;
      }
    }
    if (shoot[i].duree > 0)
      shoot[i].duree--;
    if (shoot[i].duree == 0)
    {
      shoot[i].duree = -1;
      shoot[i].active = 0;
      player.nbtir--;
    }
    for (p = 0; p < MAX_PLATFORMS; p++)
    {
      if (pform[p].active)
      {
        if (isCollide(shoot[i].posx + shoot[i].xbox, shoot[i].posy + shoot[i].ybox, shoot[i].hbox - 5, shoot[i].lbox, pform[p].posx, pform[p].posy, pform[p].hauteur, pform[p].largeur))
        {
          // Si c un shoot normal ou un double shoot quelque soit la plateforme en collide ca dégage
          if ((shoot[i].type == WEAPON_DOUBLE_SHOOT) || (shoot[i].type == WEAPON_NORMAL_SHOOT))
          {
            if (shoot[i].active)
            {
              shoot[i].active = 0;
              player.nbtir--;
              if (player.nbtir < 0)
                player.nbtir = 0;
            }
          }
          // Si c un grappin et un PF_INCASSABLE on laisse le grapin.
          if (shoot[i].type == WEAPON_GLUE_SHOOT)
          {
            if ((pform[p].type == PF_INCASSABLE) || (pform[p].type == PF_INCASSABLEV) || (pform[p].type == PF_MOYEN_INCASSABLE) || (pform[p].type == PF_MICRO_INCASSABLE))
            {
              if (shoot[i].duree == -1)
                shoot[i].duree = 120;
            }
          }
          // Si c une plateforme normale, quelquesoit le shoot, on le dégage.
          if ((pform[p].type == PF_CASSABLE) || (pform[p].type == PF_CASSABLEV) || (pform[p].type == PF_MOYEN_CASSABLE) || (pform[p].type == PF_MICRO_CASSABLE))
          {
            if (shoot[i].active)
            {
              shoot[i].active = 0;
              player.nbtir--;
              if (player.nbtir < 0)
                player.nbtir = 0;
            }
            pform[p].active = 0;
            releaseSprite(pform[p].spriteno);
            if (pform[p].bonus != 0)
            {
              if (pform[p].bonus == BONUS_LIFE)
              {
                if ((player.bonus_life == 0) && (player.bonus_life_level != currentLevel))
                {
                  createBonus(pform[p].bonus, pform[p].posx + 4, pform[p].posy);
                }
              }
              else
              {
                createBonus(pform[p].bonus, pform[p].posx + 4, pform[p].posy);
              }
            }
          }
        }
      }
    }
  }
  if (player.nbtir < 0)
    player.nbtir = 0;
}

void
showShoot(int i)
{
  if (shoot[i].active)
  {
    if ((shoot[i].type == WEAPON_NORMAL_SHOOT) || (shoot[i].type == WEAPON_DOUBLE_SHOOT))
    {
      blitImageToScreen(1, 305, 11, shoot[i].lbox, shoot[i].hbox, shoot[i].posx, shoot[i].posy, shoot[i].lbox, shoot[i].hbox, 320, 240);
    }
    if (shoot[i].type == WEAPON_GLUE_SHOOT)
    {
      if ((shoot[i].duree > 0) && (shoot[i].duree < 30) && (gbl_timer % 2 == 0))
      {
      }
      else
        blitImageToScreen(1, 293, 11, shoot[i].lbox, shoot[i].hbox, shoot[i].posx, shoot[i].posy, shoot[i].lbox, shoot[i].hbox, 320, 240);
    }
  }
}
