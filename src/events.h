#pragma once

#include <stdint.h>
#include <stdbool.h>

#include <SDL.h>

enum Key
{
	kKey_U,
	kKey_D,
	kKey_L,
	kKey_R,
	kKey_Confirm,
	kKey_NUM_KEYS,
};
typedef enum Key Key;


enum KeyState
{
	kKeyState_Off		= 0b00,
	kKeyState_Up		= 0b01,
	kKeyState_Pressed	= 0b10,
	kKeyState_Held		= 0b11,
	kKeyState_ActiveBit	= 0b10,
};
typedef enum KeyState KeyState;

extern uint8_t gKeyStates[kKey_NUM_KEYS];


void events_process(void);
bool GetNewKey(int key);
