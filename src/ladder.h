#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef struct ladder Ladder;
struct ladder
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
  int nbBarreau;

  int pad_haut_x;
  int pad_haut_y;
  int pad_haut_largeur;
  int pad_haut_hauteur;

  int pad_milieu_x;
  int pad_milieu_y;
  int pad_milieu_largeur;
  int pad_milieu_hauteur;

  int pad_bas_x;
  int pad_bas_y;
  int pad_bas_largeur;
  int pad_bas_hauteur;
};

#define MAX_LADDER 10

extern Ladder ladder[MAX_LADDER];

void initLadders(void);
/* Mini : 3 Barreau !! */
void createLadder(int x, int y, int nbBarreau);
void showLadder(size_t i);
