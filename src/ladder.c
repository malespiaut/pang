#include <stddef.h>

#include "gfx.h"
#include "main.h"
#include "structures.h"

void
initLadders(void)
{
  for (size_t i = 0; i < MAX_ECHELLE; ++i)
  {
    ech[i].active = 0;
  }
}

/* Mini : 3 Barreau !! */
void
createLadder(int x, int y, int nbBarreau)
{
  size_t i = 0;
  while ((ech[i].active) && (i < MAX_ECHELLE))
  {
    ++i;
  }

  ech[i].active = 1;
  ech[i].posx = x;
  ech[i].posy = y;
  ech[i].hauteur = 4 * nbBarreau;
  ech[i].largeur = 22;
  ech[i].nbBarreau = nbBarreau;

  ech[i].pad_haut_x = x;
  ech[i].pad_haut_y = y - 4;
  ech[i].pad_haut_largeur = ech[i].largeur;
  ech[i].pad_haut_hauteur = 4;

  ech[i].pad_milieu_x = x;
  ech[i].pad_milieu_y = y;
  ech[i].pad_milieu_largeur = ech[i].largeur;
  ech[i].pad_milieu_hauteur = ech[i].hauteur - 4;

  ech[i].pad_bas_x = x;
  ech[i].pad_bas_y = y + ech[i].hauteur - 4;
  ech[i].pad_bas_largeur = ech[i].largeur;
  ech[i].pad_bas_hauteur = 4;
}

void
showLadder(size_t i)
{
  if (ech[i].active)
  {
    for (size_t e = 0; e < ech[i].nbBarreau; e++)
    {
      blitImageToScreen(1, 71, 53, 22, 4, ech[i].posx, ech[i].posy + (e * 4), 22, 4, 320, 240);
    }
  }
}
