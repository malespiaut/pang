#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#define MAX_SPRITE 500
#define MAX_IMAGE 30
#define MAX_TILE 500
#define MAX_MAP 2
#define MAX_MAP_WIDTH 100
#define MAX_MAP_HEIGHT 100

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern SDL_Surface* screen;
extern SDL_Surface* imagesBMP[10];
extern int mapTiles[MAX_MAP][MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
extern int currentWorldMapX[MAX_MAP];
extern int currentWorldMapY[MAX_MAP];
extern SDL_Joystick* joy;

extern int posxjoy;
extern int posyjoy;

extern Uint32 sstart;
extern Uint32 ssend;

extern int keyRight;
extern int keyLeft;
extern int keyUp;
extern int keyDown;
extern int keyQuit;

extern int keyAction1;
extern int keyAction2;
extern int keyAction3;
extern int keyAction4;
extern int fpsshow;
extern int keyActionPause;
extern int myEvent;

typedef struct si
{
  int imageh;         // Hauteur
  int imagel;         // Largeur
  SDL_Surface* image; // L'image en elle mème
} simage;

typedef struct ss
{
  bool active;
  int posx;
  int posy;
  int image;

  int animation[10][20];   // 10 animations de 20 frames (-1 = on boucle )
  int animation_speed[10]; // vitesse de l'animation
  int current_animation;   // animation courante -1 non animé
  int current_animation_frame;

  int intern1;
} ssprite;

typedef struct st
{
  int image;
  int attr1;
  int attr2;
  int attr3;
} stile;

extern ssprite sprite[MAX_SPRITE];
extern simage imageBank[MAX_IMAGE];
extern stile tiles[MAX_TILE];

void initTileEngine(void);
void present_frame(void);
void blitBMPImageToScreen(int imageNo, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh);
void createTile(int n, int imageNo, int a1, int a2, int a3);
void setTileInMap(int mapNo, int x, int y, int tileNo);
void setWorldView(int mapNo, int x, int y);
void mapDraw(int mapNo);
void initGfxEngine(void);
int loadBmp(char* pathfilename, int noImage);
void checkController(void);
void initSpriteEngine(void);
void getImage(int n, int x, int y, int l, int h, int imageNo);
void initSprite(int n, int x, int y, int i);
int initFreeSprite(int x, int y, int i);
void releaseSprite(int n);
void releaseAllSprite(void);
void animateSprite(int s, int a);
void setSpriteAnimation(int s, int a, int speed, int f0, int f1, int f2, int f3, int f4, int f5, int f6, int f7, int f8, int f9, int f10, int f11, int f12, int f13, int f14, int f15, int f16, int f17, int f18, int f19);
void moveSprite(int n, int x, int y);
void changeSpriteImage(int n, int i);
void pasteImage(int n, int x, int y);
void showSprite(int n);
void stopAnimateSprite(int s);
void showAllSprite(void);
int isSpriteCollide(int sprite1, int sprite2);
int CollideTransparentPixelTest(SDL_Surface* surface, int u, int v);
