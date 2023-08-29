#include <stdbool.h>

#include "structures.h"

int chrono = 0;
char debug[100];
int sound_etat = 0;
int gbl_timer = 1;
int gbl_evt = EVT_NULL;
int onetwo = 0;
int currentLevel = 1;

ladder ech[MAX_ECHELLE];
b bonus[MAX_BONUS];
joueur player;
object obj[MAX_OBJECTS];
