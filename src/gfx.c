#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <SDL.h>
#include <SDL2_rotozoom.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "gfx.h"
#include "structures.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;
SDL_Surface* screen = NULL;
SDL_Surface* bitmaps[10] = {0};

extern bool g_quit;

int keyRight = 0;
int keyLeft = 0;
int keyUp = 0;
int keyDown = 0;
int keyQuit = 0;

int keyAction1 = 0;
int keyAction2 = 0;
int keyAction3 = 0;
int keyAction4 = 0;

int keyActionPause = 0;

int fpsshow = 0;

Sprite sprites[kSprite_COUNT] = {0}; // Les sprites
Image images[kImage_COUNT] = {0};    // Les images découpées des BMP chargés

void
bmp_blit(int i, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
{
  SDL_Rect dest;
  dest.x = dx;
  dest.y = dy;
  dest.h = dh;
  dest.w = dw;

  SDL_Rect src;
  src.x = sx;
  src.y = sy;
  src.h = sh;
  src.w = sw;

  SDL_BlitSurface(bitmaps[i], &src, screen, &dest);
}

void
image_blit(int i, int dx, int dy)
{
  SDL_Rect dest;
  dest.x = dx;
  dest.y = dy;
  dest.h = images[i].height;
  dest.w = images[i].width;

  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.h = images[i].height;
  src.w = images[i].width;

  SDL_BlitSurface(images[i].surface, &src, screen, &dest);
}

void
graphics_init(void)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
  {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }

  atexit(SDL_Quit);

  window = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_UTILITY);

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
  SDL_RenderSetLogicalSize(renderer, 320, 240);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, 320, 240);

  screen = SDL_CreateRGBSurface(0, 320, 240, 32, 0, 0, 0, 0);

  SDL_ShowCursor(0);
  if (screen == NULL)
  {
    fprintf(stderr, "Failed to create the \"screen\" surface, exiting now\n");
    exit(1);
  }
}

void
present_frame(void)
{
  SDL_UpdateTexture(texture, NULL, screen->pixels, sizeof(Uint32) * 320);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}

// image 1 et 3 transparente
int
bmp_load(char* filename, int i)
{
  SDL_FreeSurface(bitmaps[i]);
  SDL_Surface* temp;

  if ((temp = IMG_Load(filename)) == NULL)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }

  bitmaps[i] = SDL_ConvertSurface(temp, screen->format, SDL_SWSURFACE);
  SDL_FreeSurface(temp);

  if ((i == 1) || (i == 3))
  {
    SDL_SetColorKey(bitmaps[i], SDL_TRUE, 0xff00ff);
  }

  return 0;
}

void
events_process(void)
{
  SDL_Event event = {0};
  while (SDL_PollEvent(&event))
  {
    switch (event.key.keysym.sym)
    {
      case SDLK_LEFT:
        keyLeft = 1;
        break;

      case SDLK_RIGHT:
        keyRight = 1;
        break;

      case SDLK_UP:
        keyUp = 1;
        break;

      case SDLK_DOWN:
        keyDown = 1;
        break;

      case SDLK_c:
        keyAction1 = 1;
        break;

      case SDLK_v:
        keyAction2 = 1;
        break;

      case SDLK_b:
        keyAction3 = 1;
        break;

      case SDLK_n:
        keyAction4 = 1;
        break;

      case SDLK_p:
        keyActionPause = 1;
        keyAction4 = 1;
        break;

      case SDLK_ESCAPE:
        g_quit = true;
        break;

      default:
        break;
    }

    switch (event.type)
    {
      case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
          case SDLK_f:
            fpsshow = (fpsshow + 1) % 2;
            printf("fpsshow: %d\n", fpsshow);
            break;

          default:
            break;
        }
        break;

      case SDL_KEYUP:
        switch (event.key.keysym.sym)
        {
          case SDLK_LEFT:
            keyLeft = 0;
            break;

          case SDLK_RIGHT:
            keyRight = 0;
            break;

          case SDLK_UP:
            keyUp = 0;
            break;

          case SDLK_DOWN:
            keyDown = 0;
            break;

          case SDLK_c:
            keyAction1 = 0;
            break;

          case SDLK_v:
            keyAction2 = 0;
            break;

          case SDLK_b:
            keyAction3 = 0;
            break;

          case SDLK_n:
            keyAction4 = 0;
            break;

          case SDLK_p:
            keyActionPause = 0;
            keyAction4 = 0;
            break;

          case SDLK_ESCAPE:
            g_quit = true;
            break;

          default:
            break;
        }
        break;

      case SDL_QUIT:
        keyQuit = 1;
        g_quit = true;
        break;

      default:
        break;
    }
  }
}

// Recupère une image n° n en x,y de taille h,l dans l'image BMP n° i
// void image_get(int n,int x,int y,int l,int h,int i)
void
image_get(int n, int x, int y, int l, int h, int i)
{
  Uint32 rmask, gmask, bmask, amask;

  /* SDL interprets each pixel as a 32-bit number, so our masks must depend
     on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0xff000000;
#endif

  // Si l'image est déja alloué, on la libère.
  SDL_FreeSurface(images[n].surface);
  images[n].surface = SDL_CreateRGBSurface(SDL_SWSURFACE, l, h, 32, rmask, gmask, bmask, amask);

  // On copie une portion de la BMP dans la nouvelle surface
  SDL_Rect src;
  src.x = x;
  src.y = y;
  src.h = h;
  src.w = l;
  SDL_BlitSurface(bitmaps[i], &src, images[n].surface, NULL);

  images[n].height = h;
  images[n].width = l;
}

void
sprite_init(int n, int x, int y, int i)
{
  sprites[n].x = x;
  sprites[n].y = y;
  sprites[n].index = i;
  sprites[n].active = 1;
  sprites[n].current_animation = -1;
  sprites[n].intern1 = 0;
  sprites[n].current_animation_frame = -1;
}

int
sprite_init_free(int x, int y, int i)
{
  int s = 0;

  while ((sprites[s].active) && (s < kSprite_COUNT))
  {
    s++;
  }
  sprites[s].x = x;
  sprites[s].y = y;
  sprites[s].index = i;
  sprites[s].active = 1;
  sprites[s].current_animation = -1;
  sprites[s].intern1 = 0;
  sprites[s].current_animation_frame = -1;

  return s;
}

void
sprite_free_set(int n)
{
  sprites[n].active = 0;
}

void
sprite_free_all(void)
{
  int i;

  for (i = 0; i < kSprite_COUNT; i++)
  {
    sprites[i].active = 0;
  }
}

void
sprite_move(int n, int x, int y)
{
  sprites[n].x = x;
  sprites[n].y = y;
}

void
sprite_id_set(int n, int i)
{
  sprites[n].index = i;
}

void
sprite_blit(int n)
{
  if (sprites[n].active)
  {
    if (sprites[n].current_animation != -1)
    {
      if (sprites[n].intern1 <= 0)
      {
        sprites[n].current_animation_frame++;
        if (sprites[n].current_animation_frame > 19)
          sprites[n].current_animation_frame = 0;
        if (sprites[n].animation[sprites[n].current_animation][sprites[n].current_animation_frame] == -1)
          sprites[n].current_animation_frame = 0;
        sprites[n].index = sprites[n].animation[sprites[n].current_animation][sprites[n].current_animation_frame];
        sprites[n].intern1 = sprites[n].animation_speed[sprites[n].current_animation];
      }
      sprites[n].intern1--;
    }
    else
    {
      sprites[n].intern1 = 0;
    }

    image_blit(sprites[n].index, sprites[n].x, sprites[n].y);
  }
}

int
CollideTransparentPixelTest(SDL_Surface* surface, int u, int v)
{

  SDL_Color Color;

  int bpp = surface->format->BytesPerPixel;
  Uint8* p = (Uint8*)surface->pixels + v * surface->pitch + u * bpp;

  Uint32 pixelcolor;

  switch (bpp)
  {
    case (1):
      pixelcolor = *p;
      break;

    case (2):
      pixelcolor = *(Uint16*)p;
      break;

    case (3):
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        pixelcolor = p[0] << 16 | p[1] << 8 | p[2];
      else
        pixelcolor = p[0] | p[1] << 8 | p[2] << 16;
      break;

    case (4):
      pixelcolor = *(Uint32*)p;
      break;

    default:
      pixelcolor = *p;
  }

  SDL_GetRGB(pixelcolor, surface->format, &Color.r, &Color.g, &Color.b);

  if (((Color.r == 255) && (Color.g == 255) && (Color.b == 255)) || ((Color.r == 0) && (Color.g == 0) && (Color.b == 0)))
    return 0;
  else
    return 1;
}

bool
sprite_collides(int spriteindex1, int spriteindex2)
{
  Sprite* spr1 = &sprites[spriteindex1];
  Sprite* spr2 = &sprites[spriteindex2];
  Image* img1 = &images[spr1->index];
  Image* img2 = &images[spr2->index];

  int rect1_x, rect1_y;
  int rect2_x, rect2_y;
  int i, j, k, l;

  if (!spr1->active)
  {
    return false;
  }
  if (!spr2->active)
  {
    return false;
  }

  /*Détection par bounding box
  Retourne 0 et sort de la fonction
  si les sprites ne possédent pas de zones superposées*/
  if (spr1->x > spr2->x + img2->width)
  {
    return false;
  }
  if (spr1->x + img1->width < spr2->x)
  {
    return false;
  }
  if (spr1->y > spr2->y + img2->height)
  {
    return false;
  }
  if (spr1->y + img1->height < spr2->y)
  {
    return false;
  }

  /*Le but des lignes suivantes est de définir un
  rectangle qui englobe la zone d'affichage
  commune aux deux sprites
  On traite les coordonnées x du rectangle*/

  if (spr1->x < spr2->x)
  {
    rect1_x = spr2->x;
    if (spr1->x + img1->width >= spr2->x + img2->width)
    {
      rect2_x = spr2->x + img2->width;
    }
    else
    {
      rect2_x = spr1->x + img1->width;
    }
  }
  else
  {
    rect1_x = spr1->x;
    if (spr2->x + img2->width >= spr1->x + img1->width)
    {
      rect2_x = spr1->x + img1->width;
    }
    else
    {
      rect2_x = spr2->x + img2->width;
    }
  }

  /*On traite les coordonnées y du rectangle*/
  if (spr1->y < spr2->y)
  {
    rect1_y = spr2->y;
    if (spr1->y + img1->height >= spr2->y + img2->height)
    {
      rect2_y = spr2->y + img2->height;
    }
    else
    {
      rect2_y = spr1->y + img1->height;
    }
  }
  else
  {
    rect1_y = spr1->y;
    if (spr2->y + img2->height > spr1->y + img1->height)
    {
      rect2_y = spr1->y + img1->height;
    }
    else
    {
      rect2_y = spr2->y + img2->height;
    }
  }

  if (SDL_MUSTLOCK(img1->surface))
  {
    SDL_LockSurface(img1->surface);
  }
  if (SDL_MUSTLOCK(img2->surface))
  {
    SDL_LockSurface(img2->surface);
  }

  /*Il ne reste plus qu'à tester pour chaque
  pixel du rectangle précèdemment défini si ses pixels
  sont transparents
  Un pixel non transparent signifie qu'un bout de sprite
  est present dans le rectangle
  et donc que les sprites sont en collision*/

  for (i = rect1_x - spr1->x, j = rect1_x - spr2->x; i < rect2_x - spr1->x; i++, j++)
  {
    for (k = rect1_y - spr1->y, l = rect1_y - spr2->y; k < rect2_y - spr1->y; k++, l++)
    {

      if ((CollideTransparentPixelTest(img1->surface, i, k) != 0) && (CollideTransparentPixelTest(img2->surface, j, l)) != 0)
      {
        if (SDL_MUSTLOCK(img1->surface))
        {
          SDL_UnlockSurface(img1->surface);
        }
        if (SDL_MUSTLOCK(img2->surface))
        {
          SDL_UnlockSurface(img2->surface);
        }

        return true;
      }
    }
  }

  if (SDL_MUSTLOCK(img1->surface))
  {
    SDL_UnlockSurface(img1->surface);
  }
  if (SDL_MUSTLOCK(img2->surface))
  {
    SDL_UnlockSurface(img2->surface);
  }

  return false;
}
