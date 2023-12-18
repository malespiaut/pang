#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <SDL.h>

enum Key
{
  kKey_U,
  kKey_D,
  kKey_L,
  kKey_R,
  kKey_Shoot,
  kKey_Confirm,
  kKey_Quit,
  kKey_NUM_KEYS,
};
typedef enum Key Key;

enum KeyState
{
  kKeyState_Off = 0b00,
  kKeyState_Up = 0b01,
  kKeyState_Pressed = 0b10,
  kKeyState_Held = 0b11,
  kKeyState_ActiveBit = 0b10,
};
typedef enum KeyState KeyState;

extern KeyState gKeyStates[kKey_NUM_KEYS];

void events_process(void);
bool GetNewKey(Key key);
