#pragma once

#include <stdbool.h>
#include <stddef.h>

#include <SDL.h>
#include <SDL_mixer.h>

typedef struct sound Sound;
struct sound
{
  Mix_Chunk* chunk;
  bool is_used;
};

enum eSound
{
  kSound_InGame = 0,
  kSound_NextLevel,
  kSound_GameOver,
  kSound_Shoot,
  kSound_BallPop,
  kSound_COUNT,
};
typedef enum eSound eSound;

enum eSoundClearFlag
{
  kSoundClear_DontForce = 0,
  kSoundClear_Force,
  kSoundClear_COUNT
};
typedef enum eSoundClearFlag eSoundClearFlag;

void initSoundEngine(void);
void loadSound(eSound i);
void playSound(eSound i, int loops);
void clearSound(eSound i, eSoundClearFlag force);
void quitSoundEngine(void);
