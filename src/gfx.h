#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#define kSprite_COUNT 500
#define kImage_COUNT 30

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern SDL_Surface* screen;
extern SDL_Surface* bitmaps[10];

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

/*
typedef struct si {
        int height;	// Hauteur
        int width; // Largeur
        SDL_Surface *image; // L'image en elle mème
} simage;

typedef struct ss{
        bool active;	// Sprite utilisé ?
        int x;		// Position x
        int y;		// Position y
        int image;		// Image courante
        int animation[10][20]; // 10 animations de 20 frames (-1 = on boucle )
        int animation_speed[10];   // vitesse de l'animation
        int current_animation; // animation courante -1 non animé
        int current_animation_frame; // image courante
        int intern1;	// interne
} ssprite;
*/

typedef struct image Image;
struct image
{
  int height;         // Hauteur
  int width;         // Largeur
  SDL_Surface* image; // L'image en elle mème
};

typedef struct sprite Sprite;
struct sprite
{
  bool active;
  int x;
  int y;
  int image;

  int animation[10][20];   // 10 animations de 20 frames (-1 = on boucle )
  int animation_speed[10]; // vitesse de l'animation
  int current_animation;   // animation courante -1 non animé
  int current_animation_frame;

  int intern1;
};

extern Sprite sprites[kSprite_COUNT];
extern Image images[kImage_COUNT];

void present_frame(void);
void bmp_blit(int i, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh);
void graphics_init(void);
int bmp_load(char* filename, int i);
void events_process(void);
void image_get(int n, int x, int y, int l, int h, int i);
void sprite_init(int n, int x, int y, int i);
int sprite_init_free(int x, int y, int i);
void sprite_free_set(int n);
void sprite_free_all(void);
void sprite_move(int n, int x, int y);
void sprite_id_set(int n, int i);
void sprite_blit(int n);
int sprite_collides(int sprite1, int sprite2);
int CollideTransparentPixelTest(SDL_Surface* surface, int u, int v);
