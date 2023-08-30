#pragma once

#include <stdbool.h>

typedef struct ball Ball;
struct ball
{
  double x;        /* Position x dans l'écran (à initialiser) */
  double y;        /* Position y dans l'écran (à initialiser) */
  double last_x;   /* Dernière position x sans collision à l'écran */
  double last_y;   /* Dernière position y sans collision à l'écran */
  int hauteurmax;     /* Hauteur maximum en pixel que peut prendre une boule (à initialiser)*/
  int hauteurmax_cpt; /* Compteur interne (à initialiser à 0) */
  int speedx;         /* Vitesse de déplacement horizontal */
  int speedy;         /* Vitesse de déplacement verticale (+ la valeur est grande + c lent) */
  int speed_cpt;      /* Compteur interne (à initialiser à 0) */
  int lr;             /* Direction horizontale -1 = droite    +1 = gauche */
  int ud;             /* Direction verticale -1 = haut    +1 = bas */
  int coefdivaccell;  /* Coefficient d'accélération (+ la valeur est grande + c lent) */
  bool active;        /* 0 = libre */
  int xbox;           /*Position x dans l'image de la boite de collision */
  int ybox;           /* Position y dans l'image de la boite de collision */
  int hbox;           /* Hauteur et largeur de la boite de collision */
  int lbox;
  int type;         /* Type de balle : MICRO,SMALL,NORMAL,BIG */
  int suspend;      /* Suspend la balle en l'air si atteind de max */
  int bonus;        /* Bonus que contient la balle */
  int bonus_parent; /* bonus que contiendra la balle suivante ! */
  int spriteno;     /* Cette balle est représentée par le sprite numéero <spriteno> */
  double vel;
  double vel_cst;
  int move;

  int nbtouch; /* variable qui évite les balles d'êtres bloquées */
  int y_a_til_eu_collision_avant;
};

#define MAX_BALL 32

extern Ball ball[MAX_BALL];

void showBall(int i);
int ballCollideWithPlatform(int sprite1, int sprite2, int b);
void initBalls(void);
void explodeABall(int a);
void explodeAllBall(void);
int createBigBall(double x, double y, int hdirection, int vdirection);
int createNormalBall(double x, double y, int hdirection, int vdirection);
int createSmallBall(double x, double y, int hdirection, int vdirection);
int createMicroBall(double x, double y, int hdirection, int vdirection);
int createBall(double x, double y, int typeBall, int hdirection, int vdirection);
void updateBalls(int i);
