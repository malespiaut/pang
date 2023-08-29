#pragma once

#include <stdbool.h>

#define INVISIBLE_COLOR 218
#define MAX_LEVEL 25

#define CHEAT 0
#define GRAV 0.5

#define MAX_ECHELLE 10
#define MAX_BONUS 5
#define MAX_OBJECTS 10

#define MAX_SHOOT 15
#define BIG 1
#define NORMAL 2
#define SMALL 3
#define MICRO 4
#define WEAPON_NORMAL_SHOOT 1
#define WEAPON_DOUBLE_SHOOT 2
#define WEAPON_GLUE_SHOOT 3
#define WEAPON_GUN_SHOOT 4

#define ANIM_SHOOT 10
#define ANIM_LEFT1 11
#define ANIM_LEFT2 12
#define ANIM_LEFT3 13
#define ANIM_RIGHT1 14
#define ANIM_RIGHT2 15
#define ANIM_RIGHT3 16
#define ANIM_DEAD 17
#define ANIM_STOP 18
#define ANIM_LADDER1 30
#define ANIM_LADDER2 31

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

#define PF_INCASSABLE 20
#define PF_CASSABLE 21
#define PF_CASSABLEV 22
#define PF_INCASSABLEV 23
#define PF_MOYEN_INCASSABLE 24
#define PF_MOYEN_CASSABLE 25
#define PF_MICRO_INCASSABLE 26
#define PF_MICRO_CASSABLE 27

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
  int posx;
  int posy;
  int type;
  int cpt;
  bool active;
  int value;
} object;

typedef struct sechelle
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
} ladder;

typedef struct sjoueur
{
  int posx;
  int posy;
  int xbox;
  int ybox;
  int hbox; /* Hauteur et largeur de la boite de collision */
  int lbox;
  int nblive;
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

typedef struct stir
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
} tir;

typedef struct sb
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
} b;

extern tir shoot[MAX_SHOOT];
extern ladder ech[MAX_ECHELLE];
extern b bonus[MAX_BONUS];
extern joueur player;
extern object obj[MAX_OBJECTS];
