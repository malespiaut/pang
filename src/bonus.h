#pragma once

#include <stdbool.h>

typedef struct bonus Bonus;
struct bonus
{
  int posx;
  int posy;
  int duree_de_vie;
  int xbox;
  int ybox;
  int hbox;
  int lbox;
  int etat;
  int type;
  bool active;
};

#define MAX_BONUS 5

extern Bonus bonus[MAX_BONUS];

void initBonus(void);
int getRandomBonus(void);
int createBonus(int type, int x, int y);
void updateBonus(int i);
void showBonus(int i);
