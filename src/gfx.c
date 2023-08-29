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

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;
SDL_Surface* screen;
SDL_Joystick* stick;
SDL_Surface* imagesBMP[10];

extern bool g_quit;

int mapTiles[MAX_MAP][MAX_MAP_WIDTH][MAX_MAP_HEIGHT];
int currentWorldMapX[MAX_MAP];
int currentWorldMapY[MAX_MAP];

Uint32 sstart;
Uint32 ssend;

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

/*
typedef struct si {
        int imageh;	// Hauteur
        int imagel; // Largeur
        SDL_Surface *image; // L'image en elle mème
} simage;

typedef struct ss{
        bool active;	// Sprite utilisé ?
        int posx;		// Position x
        int posy;		// Position y
        int image;		// Image courante
        int animation[10][20]; // 10 animations de 20 frames (-1 = on boucle )
        int animation_speed[10];   // vitesse de l'animation
        int current_animation; // animation courante -1 non animé
        int current_animation_frame; // image courante
        int intern1;	// interne
} ssprite;

typedef struct st {
        int image;	// Image représentant la tile
        int attr1;	// Attribut 1
        int attr2;	// Attribut 2
        int attr3;	// Attribut 3
} stile;
*/
ssprite sprite[MAX_SPRITE];  // Les sprites
simage imageBank[MAX_IMAGE]; // Les images découpées des BMP chargés
stile tiles[MAX_TILE];       // Les tiles

void
blitBMPImageToScreen(int imageBMPNo, int sx, int sy, int sw, int sh, int dx, int dy, int dw, int dh)
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

  SDL_BlitSurface(imagesBMP[imageBMPNo], &src, screen, &dest);
}

void
blitImageBankToScreen(int imageBankNo, int dx, int dy)
{
  SDL_Rect dest;
  dest.x = dx;
  dest.y = dy;
  dest.h = imageBank[imageBankNo].imageh;
  dest.w = imageBank[imageBankNo].imagel;

  SDL_Rect src;
  src.x = 0;
  src.y = 0;
  src.h = imageBank[imageBankNo].imageh;
  src.w = imageBank[imageBankNo].imagel;

  SDL_BlitSurface(imageBank[imageBankNo].image, &src, screen, &dest);
}

void
initGfxEngine(void)
{
  if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
  {
    fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    exit(1);
  }
  stick = SDL_JoystickOpen(0);
  fprintf(stdout, "Found %d joysticks\n", SDL_NumJoysticks());

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
loadBmp(char* pathfilename, int noImage)
{
  SDL_FreeSurface(imagesBMP[noImage]);
  SDL_Surface* temp;

  if ((temp = IMG_Load(pathfilename)) == NULL)
  {
    fprintf(stderr, "Error: %s\n", SDL_GetError());
    exit(1);
  }

  imagesBMP[noImage] = SDL_ConvertSurface(temp, screen->format, SDL_SWSURFACE);
  SDL_FreeSurface(temp);

  if ((noImage == 1) || (noImage == 3))
  {
    SDL_SetColorKey(imagesBMP[noImage], SDL_TRUE, 0xff00ff);
  }

  return 0;
}

void
checkController(void)
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

void
initSpriteEngine(void)
{
  int i;
  for (i = 0; i < MAX_SPRITE; i++)
  {
    sprite[i].active = 0;
  }
}

// Recupère une image n° n en x,y de taille h,l dans l'image BMP n° imageNo
// void getImage(int n,int x,int y,int l,int h,int imageNo)
void
getImage(int n, int x, int y, int l, int h, int imageNo)
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
  SDL_FreeSurface(imageBank[n].image);
  imageBank[n].image = SDL_CreateRGBSurface(SDL_SWSURFACE, l, h, 32, rmask, gmask, bmask, amask);

  // On copie une portion de la BMP dans la nouvelle surface
  SDL_Rect src;
  src.x = x;
  src.y = y;
  src.h = h;
  src.w = l;
  SDL_BlitSurface(imagesBMP[imageNo], &src, imageBank[n].image, NULL);

  imageBank[n].imageh = h;
  imageBank[n].imagel = l;
}

void
initSprite(int n, int x, int y, int i)
{
  sprite[n].posx = x;
  sprite[n].posy = y;
  sprite[n].image = i;
  sprite[n].active = 1;
  sprite[n].current_animation = -1;
  sprite[n].intern1 = 0;
  sprite[n].current_animation_frame = -1;
}

int
initFreeSprite(int x, int y, int i)
{
  int s = 0;

  while ((sprite[s].active) && (s < MAX_SPRITE))
  {
    s++;
  }
  sprite[s].posx = x;
  sprite[s].posy = y;
  sprite[s].image = i;
  sprite[s].active = 1;
  sprite[s].current_animation = -1;
  sprite[s].intern1 = 0;
  sprite[s].current_animation_frame = -1;

  return s;
}

void
releaseSprite(int n)
{
  sprite[n].active = 0;
}

void
releaseAllSprite(void)
{
  int i;

  for (i = 0; i < MAX_SPRITE; i++)
  {
    sprite[i].active = 0;
  }
}

void
moveSprite(int n, int x, int y)
{
  sprite[n].posx = x;
  sprite[n].posy = y;
}

void
changeSpriteImage(int n, int i)
{
  sprite[n].image = i;
}

void
showSprite(int n)
{
  if (sprite[n].active)
  {
    if (sprite[n].current_animation != -1)
    {
      if (sprite[n].intern1 <= 0)
      {
        sprite[n].current_animation_frame++;
        if (sprite[n].current_animation_frame > 19)
          sprite[n].current_animation_frame = 0;
        if (sprite[n].animation[sprite[n].current_animation][sprite[n].current_animation_frame] == -1)
          sprite[n].current_animation_frame = 0;
        sprite[n].image = sprite[n].animation[sprite[n].current_animation][sprite[n].current_animation_frame];
        sprite[n].intern1 = sprite[n].animation_speed[sprite[n].current_animation];
      }
      sprite[n].intern1--;
    }
    else
    {
      sprite[n].intern1 = 0;
    }

    blitImageBankToScreen(sprite[n].image, sprite[n].posx, sprite[n].posy);
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

int
isSpriteCollide(int sprite1, int sprite2)
{

  int rect1_x, rect1_y;
  int rect2_x, rect2_y;
  int i, j, k, l;
  int coorx_1 = sprite[sprite1].posx;
  int coory_1 = sprite[sprite1].posy;
  int coorx_2 = sprite[sprite2].posx;
  int coory_2 = sprite[sprite2].posy;
  int sprite1w = imageBank[sprite[sprite1].image].imagel;
  int sprite1h = imageBank[sprite[sprite1].image].imageh;
  int sprite2w = imageBank[sprite[sprite2].image].imagel;
  int sprite2h = imageBank[sprite[sprite2].image].imageh;

  if (!sprite[sprite1].active)
    return 0;
  if (!sprite[sprite2].active)
    return 0;

  /*Détection par bounding box
  Retourne 0 et sort de la fonction
  si les sprites ne possédent pas de zones superposées*/
  if (coorx_1 > coorx_2 + imageBank[sprite[sprite2].image].imagel)
    return 0;
  if (coorx_1 + imageBank[sprite[sprite1].image].imagel < coorx_2)
    return 0;
  if (coory_1 > coory_2 + imageBank[sprite[sprite2].image].imageh)
    return 0;
  if (coory_1 + imageBank[sprite[sprite1].image].imageh < coory_2)
    return 0;

  /*Le but des lignes suivantes est de définir un
  rectangle qui englobe la zone d'affichage
  commune aux deux sprites
  On traite les coordonnées x du rectangle*/

  if (coorx_1 < coorx_2)
  {
    rect1_x = coorx_2;
    if (coorx_1 + sprite1w >= coorx_2 + sprite2w)
      rect2_x = coorx_2 + sprite2w;
    else
      rect2_x = coorx_1 + sprite1w;
  }
  else
  {
    rect1_x = coorx_1;
    if (coorx_2 + sprite2w >= coorx_1 + sprite1w)
      rect2_x = coorx_1 + sprite1w;
    else
      rect2_x = coorx_2 + sprite2w;
  }

  /*On traite les coordonnées y du rectangle*/
  if (coory_1 < coory_2)
  {
    rect1_y = coory_2;
    if (coory_1 + sprite1h >= coory_2 + sprite2h)
      rect2_y = coory_2 + sprite2h;
    else
      rect2_y = coory_1 + sprite1h;
  }
  else
  {
    rect1_y = coory_1;
    if (coory_2 + sprite2h > coory_1 + sprite1h)
      rect2_y = coory_1 + sprite1h;
    else
      rect2_y = coory_2 + sprite2h;
  }

  if (SDL_MUSTLOCK(imageBank[sprite[sprite1].image].image))
    SDL_LockSurface(imageBank[sprite[sprite1].image].image);
  if (SDL_MUSTLOCK(imageBank[sprite[sprite2].image].image))
    SDL_LockSurface(imageBank[sprite[sprite2].image].image);

  /*Il ne reste plus qu'à tester pour chaque

  pixel du rectangle précèdemment défini si ses pixels

  sont transparents

  Un pixel non transparent signifie qu'un bout de sprite

  est present dans le rectangle

  et donc que les sprites sont en collision*/

  for (i = rect1_x - coorx_1, j = rect1_x - coorx_2; i < rect2_x - coorx_1; i++, j++)
  {
    for (k = rect1_y - coory_1, l = rect1_y - coory_2; k < rect2_y - coory_1; k++, l++)
    {

      if ((CollideTransparentPixelTest(imageBank[sprite[sprite1].image].image, i, k) != 0) && (CollideTransparentPixelTest(imageBank[sprite[sprite2].image].image, j, l)) != 0)
      {
        if (SDL_MUSTLOCK(imageBank[sprite[sprite1].image].image))
          SDL_UnlockSurface(imageBank[sprite[sprite1].image].image);
        if (SDL_MUSTLOCK(imageBank[sprite[sprite2].image].image))
          SDL_UnlockSurface(imageBank[sprite[sprite2].image].image);

        return 1;
      }
    }
  }

  if (SDL_MUSTLOCK(imageBank[sprite[sprite1].image].image))
    SDL_UnlockSurface(imageBank[sprite[sprite1].image].image);
  if (SDL_MUSTLOCK(imageBank[sprite[sprite2].image].image))
    SDL_UnlockSurface(imageBank[sprite[sprite2].image].image);

  return 0;
}
