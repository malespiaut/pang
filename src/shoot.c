#include "shoot.h"
#include "bonus.h"
#include "collisions.h"
#include "gfx.h"
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
  size_t i = 0;
  while ((i < MAX_SHOOT) && shoot[i].active)
  {
    ++i;
  }

  if ((type == WEAPON_NORMAL_SHOOT) || (type == WEAPON_DOUBLE_SHOOT) || (type == WEAPON_GLUE_SHOOT))
  {
    shoot[i].x = player.x + 12;
    shoot[i].y = player.y; /*-30;*/
    shoot[i].xbox = 0;
    shoot[i].ybox = 0;
    shoot[i].hbox = 0;
    shoot[i].lbox = 9;
    shoot[i].type = type;
    shoot[i].active = 1;
    shoot[i].duree = -1;
    shoot[i].y_depart = player.y + 32;
    sound_play(kSound_Shoot, 0);
  }
}

void
updateShoot(int i)
{
  if (shoot[i].active)
  {
    if ((shoot[i].type == WEAPON_NORMAL_SHOOT) || (shoot[i].type == WEAPON_DOUBLE_SHOOT))
    {
      shoot[i].y = shoot[i].y - 2;
      shoot[i].hbox = (shoot[i].y_depart) - shoot[i].y;
      if (shoot[i].y < 8)
      {
        shoot[i].active = 0;
        player.nbtir--;
      }
    }
    if (shoot[i].type == WEAPON_GLUE_SHOOT)
    {
      if (shoot[i].duree == -1)
        shoot[i].y = shoot[i].y - 2;
      shoot[i].hbox = (shoot[i].y_depart) - shoot[i].y;
      if (shoot[i].y < 8)
      {
        if (shoot[i].duree == -1)
          shoot[i].duree = 120;
        shoot[i].y = 8;
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
    for (size_t p = 0; p < kPlatform_COUNT; p++)
    {
      if (platforms[p].active)
      {
        if (isCollide(shoot[i].x + shoot[i].xbox, shoot[i].y + shoot[i].ybox, shoot[i].hbox - 5, shoot[i].lbox, platforms[p].x, platforms[p].y, platforms[p].hauteur, platforms[p].largeur))
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
          // Si c un grappin et un kImage_PlatformUnbreakable on laisse le grapin.
          if (shoot[i].type == WEAPON_GLUE_SHOOT)
          {
            if ((platforms[p].type == kImage_PlatformUnbreakable) || (platforms[p].type == kImage_PlatformUnbreakableVertical) || (platforms[p].type == kImage_PlatformMediumUnbreakable) || (platforms[p].type == kImage_PlatformMicroUnbreakable))
            {
              if (shoot[i].duree == -1)
                shoot[i].duree = 120;
            }
          }
          // Si c une plateforme normale, quelquesoit le shoot, on le dégage.
          if ((platforms[p].type == kImage_PlatformBreakable) || (platforms[p].type == kImage_PlatformBreakableVertical) || (platforms[p].type == kImage_PlatformMediumBreakable) || (platforms[p].type == kImage_PlatformMicroBreakable))
          {
            if (shoot[i].active)
            {
              shoot[i].active = 0;
              player.nbtir--;
              if (player.nbtir < 0)
                player.nbtir = 0;
            }
            platforms[p].active = 0;
            sprite_free_set(platforms[p].spriteno);
            if (platforms[p].bonus != 0)
            {
              if (platforms[p].bonus == BONUS_LIFE)
              {
                if ((player.bonus_life == 0) && (player.bonus_life_level != currentLevel))
                {
                  createBonus(platforms[p].bonus, platforms[p].x + 4, platforms[p].y);
                }
              }
              else
              {
                createBonus(platforms[p].bonus, platforms[p].x + 4, platforms[p].y);
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
      bmp_blit(1, 305, 11, shoot[i].lbox, shoot[i].hbox, shoot[i].x, shoot[i].y, shoot[i].lbox, shoot[i].hbox);
    }
    if (shoot[i].type == WEAPON_GLUE_SHOOT)
    {
      if ((shoot[i].duree > 0) && (shoot[i].duree < 30) && (gbl_timer % 2 == 0))
      {
      }
      else
        bmp_blit(1, 293, 11, shoot[i].lbox, shoot[i].hbox, shoot[i].x, shoot[i].y, shoot[i].lbox, shoot[i].hbox);
    }
  }
}
