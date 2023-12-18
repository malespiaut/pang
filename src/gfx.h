#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#define kScreenWidth 320
#define kScreenHeight 240

#define kSprite_COUNT 500

extern SDL_Window* g_window;
extern SDL_Renderer* g_renderer;
extern SDL_Texture* g_texture;
extern SDL_Surface* g_screen;
extern SDL_Surface* g_bitmaps[10];

enum eImage
{
  kImage_Big,
  kImage_Normal,
  kImage_Small,
  kImage_Micro,
  kImage_AnimShoot,
  kImage_AnimLeft1,
  kImage_AnimLeft2,
  kImage_AnimLeft3,
  kImage_AnimRight1,
  kImage_AnimRight2,
  kImage_AnimRight3,
  kImage_AnimDead,
  kImage_AnimStop,
  kImage_PlatformBreakable,
  kImage_PlatformUnbreakable,
  kImage_PlatformBreakableVertical,
  kImage_PlatformUnbreakableVertical,
  kImage_PlatformMediumBreakable,
  kImage_PlatformMediumUnbreakable,
  kImage_PlatformMicroBreakable,
  kImage_PlatformMicroUnbreakable,
  kImage_AnimLadder1,
  kImage_AnimLadder2,
  kImage_COUNT,
};
typedef enum eImage eImage;

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
  uint16_t height;      // Hauteur
  uint16_t width;       // Largeur
  SDL_Surface* surface; // L'image en elle mème
};

typedef struct sprite Sprite;
struct sprite
{
  bool active;
  int x;
  int y;
  size_t index;

  int animation[10][20];   // 10 animations de 20 frames (-1 = on boucle )
  int animation_speed[10]; // vitesse de l'animation
  int current_animation;   // animation courante -1 non animé
  int current_animation_frame;

  int intern1;
};

extern Sprite g_sprites[kSprite_COUNT];
extern Image g_images[kImage_COUNT];

void present_frame(void);
void bmp_blit(int i, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh);
void sdl_init(void);
void sdl_deinit(void);
int bmp_load(char* filename, int i);
void image_get(int n, int x, int y, int l, int h, int i);
void sprite_init(int n, int x, int y, int i);
int sprite_init_free(int x, int y, int i);
void sprite_free_set(int n);
void sprite_free_all(void);
void sprite_move(int n, int x, int y);
void sprite_id_set(int n, int i);
void sprite_blit(int n);
bool sprite_collides(int sprite1, int sprite2);
int CollideTransparentPixelTest(SDL_Surface* surface, int u, int v);
