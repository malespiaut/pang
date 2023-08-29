#pragma once

#include <stdbool.h>

typedef struct shoot Shoot;
struct shoot
{
  int posx; /* Position x dans l'écran (à initialiser) */
  int posy; /* Position y dans l'écran (à initialiser) */
  int xbox;
  int ybox;
  int hbox; /* Hauteur et largeur de la boite de collision */
  int lbox;
  int type;
  bool active;
  int duree;
  int posy_depart;
};

#define MAX_SHOOT 15

extern Shoot shoot[MAX_SHOOT];

void initShoot(void);
void createShoot(int type);
void updateShoot(int i);
void showShoot(int i);
