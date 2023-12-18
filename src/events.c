#include <stdbool.h>
#include <stdint.h>

#include "events.h"

KeyState gKeyStates[kKey_NUM_KEYS];

int gKeyMap[kKey_NUM_KEYS] =
  {
    [kKey_U] = SDL_SCANCODE_UP,
    [kKey_D] = SDL_SCANCODE_DOWN,
    [kKey_L] = SDL_SCANCODE_LEFT,
    [kKey_R] = SDL_SCANCODE_RIGHT,
    [kKey_Confirm] = SDL_SCANCODE_RETURN,
};

void
UpdateKeyState(KeyState* state, bool downNow)
{
  switch (*state) // look at prev state
  {
    case kKeyState_Held:
    case kKeyState_Pressed:
      *state = downNow ? kKeyState_Held : kKeyState_Up;
      break;
    case kKeyState_Off:
    case kKeyState_Up:
    default:
      *state = downNow ? kKeyState_Pressed : kKeyState_Off;
      break;
  }
}

void
events_process(void)
{
  SDL_PumpEvents();
  SDL_Event event = {0};
  while (SDL_PollEvent(&event))
  {
    switch (event.type)
    {
      case SDL_QUIT:
        exit(EXIT_SUCCESS);
        return;

      case SDL_WINDOWEVENT:
        if (SDL_WINDOWEVENT_CLOSE == event.window.event)
        {
          exit(EXIT_SUCCESS);
          return;
        }
        break;
    }
  }

  int numkeys = 0;
  const uint8_t* keystate = SDL_GetKeyboardState(&numkeys);

  for (size_t i = 0; i < kKey_NUM_KEYS; ++i)
  {
    const int scancode = gKeyMap[i];

    bool downNow = false;

    if (scancode && scancode < numkeys)
    {
      downNow |= 0 != keystate[scancode];
    }

    UpdateKeyState(&gKeyStates[i], downNow);
  }
}

bool
GetNewKey(Key key)
{
  return gKeyStates[key] == kKeyState_Pressed;
}
