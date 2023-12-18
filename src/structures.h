#pragma once

#include <stdbool.h>
#include <stdint.h>

#define MAX_LEVEL 25

#define CHEAT 0
#define GRAV 0.5f

#define MAX_OBJECTS 10

#define WEAPON_NORMAL_SHOOT 1
#define WEAPON_DOUBLE_SHOOT 2
#define WEAPON_GLUE_SHOOT 3
#define WEAPON_GUN_SHOOT 4

#define PLAYER_LEFT 1
#define PLAYER_RIGHT 2
#define PLAYER_SHOOT 4
#define PLAYER_STOP 8
#define PLAYER_LADDER 16

#define EVT_TITLE 5
#define EVT_NULL 0
#define EVT_LOOSE_LIFE 1
#define EVT_GAME_OVER 2
#define EVT_NEXT_LEVEL 4

#define LEFT -1
#define RIGHT 1
#define UP -1
#define DOWN 1
#define STOP 0

#define TOUCH_HORIZONTAL 1
#define TOUCH_VERTICAL 2
#define TOUCH_EQUAL 4

#define BONUS_BOOM 5
#define BONUS_FREEZE 6
#define BONUS_LIFE 7
#define BONUS_PROTECTION 8
#define BONUS_RANDOM 99

#define OBJ_MUL 1
#define OBJ_EXPL_BIG 2
#define OBJ_EXPL_NORMAL 3
#define OBJ_EXPL_SMALL 4
#define OBJ_EXPL_MICRO 5
#define OBJ_1UP 6

extern int chrono;
extern char debug[100];
extern int sound_etat;
extern int gbl_timer;
extern int gbl_evt;
extern int onetwo;
extern int currentLevel;

typedef struct sobj
{
  int x;
  int y;
  int type;
  int cpt;
  bool active;
  int value;
} object;

typedef struct sjoueur
{
  int x;
  int y;
  int xbox;
  int ybox;
  int hbox; /* Hauteur et largeur de la boite de collision */
  int lbox;
  uint8_t nblive;
  int weapon;
  int score;
  int nbtir; /* Nombre de tir en cours ... */
  int etat;
  int old_etat;
  int anim_courante;
  int anim_cpt;
  int derniere_balle;
  int multiplicateur; /* multiplicateur du score */
  int shoot_timer;
  int spriteno;

  int bonus_boom;
  int bonus_freeze;
  int bonus_life;
  int bonus_life_level;
  int bonus_protection;
  int bonus_protection_timer;

  int en_descente;
} joueur;

extern joueur player;
extern object obj[MAX_OBJECTS];
