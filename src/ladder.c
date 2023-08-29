#include <stddef.h>

#include "gfx.h"
#include "main.h"
#include "ladder.h"
#include "structures.h"

Ladder ladder[MAX_LADDER];

void
initLadders(void)
{
  for (size_t i = 0; i < MAX_LADDER; ++i)
  {
    ladder[i].active = 0;
  }
}

/* Mini : 3 Barreau !! */
void
createLadder(int x, int y, int nbBarreau)
{
  size_t i = 0;
  while ((ladder[i].active) && (i < MAX_LADDER))
  {
    ++i;
  }

  ladder[i].active = 1;
  ladder[i].posx = x;
  ladder[i].posy = y;
  ladder[i].hauteur = 4 * nbBarreau;
  ladder[i].largeur = 22;
  ladder[i].nbBarreau = nbBarreau;

  ladder[i].pad_haut_x = x;
  ladder[i].pad_haut_y = y - 4;
  ladder[i].pad_haut_largeur = ladder[i].largeur;
  ladder[i].pad_haut_hauteur = 4;

  ladder[i].pad_milieu_x = x;
  ladder[i].pad_milieu_y = y;
  ladder[i].pad_milieu_largeur = ladder[i].largeur;
  ladder[i].pad_milieu_hauteur = ladder[i].hauteur - 4;

  ladder[i].pad_bas_x = x;
  ladder[i].pad_bas_y = y + ladder[i].hauteur - 4;
  ladder[i].pad_bas_largeur = ladder[i].largeur;
  ladder[i].pad_bas_hauteur = 4;
}

void
showLadder(size_t i)
{
  if (ladder[i].active)
  {
    for (size_t e = 0; e < ladder[i].nbBarreau; e++)
    {
      blitImageToScreen(1, 71, 53, 22, 4, ladder[i].posx, ladder[i].posy + (e * 4), 22, 4, 320, 240);
    }
  }
}
