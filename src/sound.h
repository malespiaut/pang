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

void sound_init(void);
void sound_load(eSound i);
void sound_play(eSound i, int loops);
void sound_clear(eSound i, eSoundClearFlag force);
void sound_deinit(void);
