#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct ladder Ladder;
struct ladder
{
  int32_t posx;
  int32_t posy;
  int32_t hauteur;
  int32_t largeur;
  bool active;
  int32_t xbox;
  int32_t ybox;
  int32_t hbox; /* Hauteur et largeur de la boite de collision */
  int32_t lbox;
  uint32_t nb_rungs;

  int32_t pad_haut_x;
  int32_t pad_haut_y;
  int32_t pad_haut_largeur;
  int32_t pad_haut_hauteur;

  int32_t pad_milieu_x;
  int32_t pad_milieu_y;
  int32_t pad_milieu_largeur;
  int32_t pad_milieu_hauteur;

  int32_t pad_bas_x;
  int32_t pad_bas_y;
  int32_t pad_bas_largeur;
  int32_t pad_bas_hauteur;
};

#define MAX_LADDER 10

extern Ladder ladder[MAX_LADDER];

void initLadders(void);
/* Mini : 3 Barreau !! */
void createLadder(int32_t x, int32_t y, int32_t nb_rungs);
void showLadder(size_t i);
