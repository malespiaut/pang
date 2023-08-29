#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_mixer.h>

#include "sound.h"

static const char* const sound_path[kSound_COUNT] = {
  [kSound_InGame] = "romdisk/in_game.wav",
  [kSound_NextLevel] = "romdisk/next_level.wav",
  [kSound_GameOver] = "romdisk/game_over.wav",
  [kSound_Shoot] = "romdisk/shoot.wav",
  [kSound_BallPop] = "romdisk/ball_pop.wav",
};

static Sound sounds[kSound_COUNT] = {0};

void
initSoundEngine(void)
{
  if (Mix_Init(0) != 0)
  {
    SDL_Log("Unable to initialize SDL_mixer: %s", Mix_GetError());
    exit(EXIT_FAILURE);
  }

  if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096) != 0)
  {
    SDL_Log("Unable to open the default audio device for playback: %s", Mix_GetError());
    exit(EXIT_FAILURE);
  }
}

void
loadSound(eSound i)
{
  sounds[i].chunk = Mix_LoadWAV(sound_path[i]);

  if (!sounds[i].chunk)
  {
    SDL_Log("Unable to load sound %d into a chunk: %s", i, Mix_GetError());
    exit(EXIT_FAILURE);
  }
}

void
playSound(eSound i, int loops)
{
  assert(sounds[i].chunk);

  if (!sounds[i].is_used)
  {
    int channel = Mix_PlayChannel(i, sounds[i].chunk, loops);
    if (channel == -1)
    {
      SDL_Log("Unable to play sound %d on channel %d: %s", i, i, Mix_GetError());
    }
    sounds[i].is_used = true;
  }
}

void
clearSound(eSound i, eSoundClearFlag force)
{
  if (!Mix_Playing(i) || force)
  {
    if (Mix_HaltChannel(i);)
    {
      SDL_Log("Unable to halt playing on channel %d: %s", i, Mix_GetError());
    }
    sounds[i].is_used = false;
  }
}

void
quitSoundEngine(void)
{
  Mix_CloseAudio();
  Mix_Quit();
}
