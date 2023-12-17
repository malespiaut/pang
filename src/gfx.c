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

SDL_Window* g_window = NULL;
SDL_Renderer* g_renderer = NULL;
SDL_Texture* g_texture = NULL;
SDL_Surface* g_screen = NULL;
SDL_Surface* g_bitmaps[10] = {0};

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

Sprite g_sprites[kSprite_COUNT] = {0}; // Les sprites
Image g_images[kImage_COUNT] = {0};    // Les images découpées des BMP chargés

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

  SDL_BlitSurface(g_bitmaps[i], &src, g_screen, &dest);
}

void
image_blit(int i, int dx, int dy)
{
  SDL_Rect dest;
  dest.x = dx;
  dest.y = dy;
  dest.h = g_images[i].height;
  dest.w = g_images[i].width;

  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.h = g_images[i].height;
  src.w = g_images[i].width;

  SDL_BlitSurface(g_images[i].surface, &src, g_screen, &dest);
}

void
graphics_init(void)
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
  {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  g_window = SDL_CreateWindow("Pang! for Linux", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, kScreenWidth, kScreenHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_UTILITY);
  if (!g_window)
  {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_PRESENTVSYNC);
  if (!g_renderer)
  {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if (SDL_RenderSetLogicalSize(g_renderer, kScreenWidth, kScreenHeight) != 0)
  {
    SDL_Log("Unable to set a device independant resolution for rendering: %s", SDL_GetError());
  }

  if (SDL_SetRenderDrawColor(g_renderer, 0, 0, 0, 255) != 0)
  {
    SDL_Log("Unable to set the color used for drawing operations: %s", SDL_GetError());
  }

  g_texture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, kScreenWidth, kScreenHeight);
  if (!g_texture)
  {
    SDL_Log("Unable to create texture: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  // TODO: Remove RGB Surface later, use textures only.
  g_screen = SDL_CreateRGBSurface(0, kScreenWidth, kScreenHeight, 32, 0, 0, 0, 0);
  if (!g_screen)
  {
    SDL_Log("Unable to create surface: %s", SDL_GetError());
    exit(EXIT_FAILURE);
  }

  if (SDL_ShowCursor(SDL_DISABLE) < 0)
  {
    SDL_Log("Unable to toggle cursor visibility: %s", SDL_GetError());
  }
}

void
present_frame(void)
{
  SDL_UpdateTexture(g_texture, NULL, g_screen->pixels, sizeof(Uint32) * kScreenWidth);
  SDL_RenderClear(g_renderer);
  SDL_RenderCopy(g_renderer, g_texture, NULL, NULL);
  SDL_RenderPresent(g_renderer);
}

// image 1 et 3 transparente
int
bmp_load(char* filename, int i)
{
  SDL_FreeSurface(g_bitmaps[i]);
  SDL_Surface* temp;

  if ((temp = IMG_Load(filename)) == NULL)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }

  g_bitmaps[i] = SDL_ConvertSurface(temp, g_screen->format, SDL_SWSURFACE);
  SDL_FreeSurface(temp);

  if ((i == 1) || (i == 3))
  {
    SDL_SetColorKey(g_bitmaps[i], SDL_TRUE, 0xff00ff);
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
  SDL_FreeSurface(g_images[n].surface);
  g_images[n].surface = SDL_CreateRGBSurface(SDL_SWSURFACE, l, h, 32, rmask, gmask, bmask, amask);

  // On copie une portion de la BMP dans la nouvelle surface
  SDL_Rect src;
  src.x = x;
  src.y = y;
  src.h = h;
  src.w = l;
  SDL_BlitSurface(g_bitmaps[i], &src, g_images[n].surface, NULL);

  g_images[n].height = h;
  g_images[n].width = l;
}

void
sprite_init(int n, int x, int y, int i)
{
  g_sprites[n].x = x;
  g_sprites[n].y = y;
  g_sprites[n].index = i;
  g_sprites[n].active = 1;
  g_sprites[n].current_animation = -1;
  g_sprites[n].intern1 = 0;
  g_sprites[n].current_animation_frame = -1;
}

int
sprite_init_free(int x, int y, int i)
{
  int s = 0;

  while ((g_sprites[s].active) && (s < kSprite_COUNT))
  {
    s++;
  }
  g_sprites[s].x = x;
  g_sprites[s].y = y;
  g_sprites[s].index = i;
  g_sprites[s].active = 1;
  g_sprites[s].current_animation = -1;
  g_sprites[s].intern1 = 0;
  g_sprites[s].current_animation_frame = -1;

  return s;
}

void
sprite_free_set(int n)
{
  g_sprites[n].active = 0;
}

void
sprite_free_all(void)
{
  int i;

  for (i = 0; i < kSprite_COUNT; i++)
  {
    g_sprites[i].active = 0;
  }
}

void
sprite_move(int n, int x, int y)
{
  g_sprites[n].x = x;
  g_sprites[n].y = y;
}

void
sprite_id_set(int n, int i)
{
  g_sprites[n].index = i;
}

void
sprite_blit(int n)
{
  if (g_sprites[n].active)
  {
    if (g_sprites[n].current_animation != -1)
    {
      if (g_sprites[n].intern1 <= 0)
      {
        g_sprites[n].current_animation_frame++;
        if (g_sprites[n].current_animation_frame > 19)
          g_sprites[n].current_animation_frame = 0;
        if (g_sprites[n].animation[g_sprites[n].current_animation][g_sprites[n].current_animation_frame] == -1)
          g_sprites[n].current_animation_frame = 0;
        g_sprites[n].index = g_sprites[n].animation[g_sprites[n].current_animation][g_sprites[n].current_animation_frame];
        g_sprites[n].intern1 = g_sprites[n].animation_speed[g_sprites[n].current_animation];
      }
      g_sprites[n].intern1--;
    }
    else
    {
      g_sprites[n].intern1 = 0;
    }

    image_blit(g_sprites[n].index, g_sprites[n].x, g_sprites[n].y);
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
  Sprite* spr1 = &g_sprites[spriteindex1];
  Sprite* spr2 = &g_sprites[spriteindex2];
  Image* img1 = &g_images[spr1->index];
  Image* img2 = &g_images[spr2->index];

  if (!spr1->active || !spr2->active)
  {
    return false; // Invalid input
  }

  // Check if sprites' bounding rectangles overlap
  if (!SDL_HasIntersection(&(SDL_Rect){.x = spr1->x, .y = spr1->y, .w = img1->width, .h = img1->height}, &(SDL_Rect){.x = spr2->x, .y = spr2->y, .w = img2->width, .h = img2->height}))
  {
    return false;
  }

  SDL_Surface* surface1 = img1->surface;
  SDL_Surface* surface2 = img2->surface;

  int start_x = SDL_max(spr1->x, spr2->x);
  int end_x = SDL_min(spr1->x + img1->width, spr2->x + img2->width);
  int start_y = SDL_max(spr1->y, spr2->y);
  int end_y = SDL_min(spr1->y + img1->height, spr2->y + img2->height);

  for (int y = start_y; y < end_y; ++y)
  {
    for (int x = start_x; x < end_x; ++x)
    {
      // Check if pixels at (x, y) in both sprites are non-transparent
      Uint32 pixel1 = *(Uint32*)((Uint8*)surface1->pixels + y * surface1->pitch + x * sizeof(Uint32));
      Uint32 pixel2 = *(Uint32*)((Uint8*)surface2->pixels + y * surface2->pitch + x * sizeof(Uint32));

      if ((pixel1 & surface1->format->Amask) != 0 && (pixel2 & surface2->format->Amask) != 0)
      {
        return true;
      }
    }
  }

  return false;
}
