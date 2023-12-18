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

  if (typepf == kImage_PlatformUnbreakable)
  {
    platforms[i].type = kImage_PlatformUnbreakable;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 32;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == kImage_PlatformBreakable)
  {
    platforms[i].type = kImage_PlatformBreakable;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 32;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == kImage_PlatformBreakableVertical)
  {
    platforms[i].type = kImage_PlatformBreakableVertical;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 32;
    platforms[i].largeur = 8;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == kImage_PlatformUnbreakableVertical)
  {
    platforms[i].type = kImage_PlatformUnbreakableVertical;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 32;
    platforms[i].largeur = 8;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == kImage_PlatformMediumUnbreakable)
  {
    platforms[i].type = kImage_PlatformMediumUnbreakable;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 16;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == kImage_PlatformMediumBreakable)
  {
    platforms[i].type = kImage_PlatformMediumBreakable;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 16;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == kImage_PlatformMicroUnbreakable)
  {
    platforms[i].type = kImage_PlatformMicroUnbreakable;
    platforms[i].x = x;
    platforms[i].y = y;
    platforms[i].hauteur = 8;
    platforms[i].largeur = 8;
    platforms[i].active = 1;
    platforms[i].bonus = 0;
  }
  else if (typepf == kImage_PlatformMicroBreakable)
  {
    platforms[i].type = kImage_PlatformMicroBreakable;
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
