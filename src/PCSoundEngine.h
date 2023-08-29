#pragma once

#include <SDL.h>
void initSoundEngine(void);
void loadSound(char* filenameDreamcast, char* filenamePC, int soundNumber);
void playSound(int soundNumber, int number);
void cvlearSound(int soundNumber);
void forceClearSound(int soundNumber);
void quitSoundEngine(void);
int clearSound(int soundNumber);
