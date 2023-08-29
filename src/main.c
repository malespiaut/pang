#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ball.h"
#include "bonus.h"
#include "gfx.h"
#include "ladder.h"
#include "levels.h"
#include "main.h"
#include "objects.h"
#include "platform.h"
#include "player.h"
#include "shoot.h"
#include "sound.h"
#include "structures.h"

bool g_quit = false;
int fond_loaded = 0;

void
showScore(char* string, unsigned int x, unsigned int y)
{
  int positionxduzero = 148;
  int positionyduzero = 226;

  size_t temp = strlen(string);
  for (size_t i = 0; i < temp; i++)
  {
    if (((*string - 48) * 13) == 0)
    {
      blitBMPImageToScreen(1, ((*string - 48) * 14) + positionxduzero, positionyduzero, 13, 13, x + (i * 6), y, 13, 13);
    }
    else
    {
      blitBMPImageToScreen(1, ((*string - 48) * 14) + positionxduzero + 1, positionyduzero, 13, 13, x + (i * 6), y, 13, 13);
    }

    string++;
  }
}

void
showFond(int level)
{
  if ((level == 1) && (fond_loaded != 1))
  {
    loadBmp("romdisk/fond1.png", 0);
    fond_loaded = 1;
  }
  else if ((level == 4) && (fond_loaded != 4))
  {
    loadBmp("romdisk/fond2.png", 0);
    fond_loaded = 4;
  }
  else if ((level == 7) && (fond_loaded != 7))
  {
    loadBmp("romdisk/fond3.png", 0);
    fond_loaded = 7;
  }
  else if ((level == 10) && (fond_loaded != 10))
  {
    loadBmp("romdisk/fond4.png", 0);
    fond_loaded = 10;
  }
  else if ((level == 13) && (fond_loaded != 13))
  {
    loadBmp("romdisk/fond5.png", 0);
    fond_loaded = 13;
  }
  else if ((level == 16) && (fond_loaded != 16))
  {
    loadBmp("romdisk/fond6.png", 0);
    fond_loaded = 16;
  }
  else if ((level == 19) && (fond_loaded != 19))
  {
    loadBmp("romdisk/fond7.png", 0);
    fond_loaded = 19;
  }
  else if ((level == 22) && (fond_loaded != 22))
  {
    loadBmp("romdisk/fond8.png", 0);
    fond_loaded = 22;
  }
  else if ((level == 25) && (fond_loaded != 25))
  {
    loadBmp("romdisk/fond9.png", 0);
    fond_loaded = 25;
  }
  else if ((level == 28) && (fond_loaded != 28))
  {
    loadBmp("romdisk/fond10.png", 0);
    fond_loaded = 28;
  }
  else if ((level == 31) && (fond_loaded != 31))
  {
    loadBmp("romdisk/fond11.png", 0);
    fond_loaded = 31;
  }
  else if ((level == 34) && (fond_loaded != 34))
  {
    loadBmp("romdisk/fond12.png", 0);
    fond_loaded = 34;
  }
  else if ((level == 37) && (fond_loaded != 37))
  {
    loadBmp("romdisk/fond13.png", 0);
    fond_loaded = 37;
  }

  blitBMPImageToScreen(0, 0, 0, 320, 240, 0, 0, 320, 240);
}

void
showfps(void)
{
  static float lasttime = NAN;
  static uint16_t framespersecond = 0;
  static char strframespersecond[16] = {0};

  float currenttime = SDL_GetTicks64() * 0.001f;
  ++framespersecond;

  if (currenttime - lasttime > 1.0)
  {
    lasttime = currenttime;
    sprintf(strframespersecond, "FPS %d", framespersecond);
    framespersecond = 0;
  }
  showScore(strframespersecond, 10, 10);
}

static void
game(void)
{
  int nbBall = 0;
  int pause = 0;

  gbl_evt = EVT_TITLE;

  srand(36547); /* seed random numbers */

  initGfxEngine();
  initSpriteEngine();
  sound_init();

  sound_load(kSound_InGame);
  sound_load(kSound_NextLevel);
  sound_load(kSound_GameOver);
  sound_load(kSound_Shoot);
  sound_load(kSound_BallPop);

  loadBmp("romdisk/sprites.png", 1);

  getImage(ANIM_RIGHT1, 70, 117, 31, 32, 1);
  getImage(ANIM_RIGHT2, 118, 117, 31, 32, 1);
  getImage(ANIM_RIGHT3, 164, 117, 31, 32, 1);
  getImage(ANIM_LEFT1, 70, 153, 31, 32, 1);
  getImage(ANIM_LEFT2, 118, 153, 31, 32, 1);
  getImage(ANIM_LEFT3, 164, 153, 31, 32, 1);
  getImage(ANIM_SHOOT, 67, 70, 31, 32, 1);
  getImage(ANIM_STOP, 67, 70, 31, 32, 1);
  getImage(ANIM_DEAD, 168, 54, 48, 40, 1);
  getImage(BIG, 10, 7, 48, 40, 1);
  getImage(NORMAL, 70, 6, 32, 26, 1);
  getImage(SMALL, 109, 20, 16, 14, 1);
  getImage(MICRO, 131, 28, 8, 7, 1);
  getImage(PF_CASSABLE, 20, 78, 32, 8, 1);
  getImage(PF_INCASSABLE, 20, 88, 32, 8, 1);
  getImage(PF_CASSABLEV, 11, 102, 8, 32, 1);
  getImage(PF_INCASSABLEV, 21, 102, 8, 32, 1);
  getImage(PF_MOYEN_INCASSABLE, 38, 102, 16, 8, 1);
  getImage(PF_MOYEN_CASSABLE, 38, 112, 16, 8, 1);
  getImage(PF_MICRO_INCASSABLE, 45, 122, 8, 8, 1);
  getImage(PF_MICRO_CASSABLE, 45, 132, 8, 8, 1);
  getImage(ANIM_LADDER1, 200, 191, 26, 32, 1);
  getImage(ANIM_LADDER2, 230, 191, 26, 32, 1);

  initBalls();
  initPlatforms();
  initPlayer();
  initLadders();
  initShoot();

  // XXX: Game loop
  while (!g_quit)
  {
    if (gbl_evt == EVT_TITLE)
    {
      releaseAllSprite();

      loadBmp("romdisk/title.png", 2);

      blitBMPImageToScreen(2, 0, 0, 320, 240, 0, 0, 320, 240);

      present_frame();
      while (keyAction1 == 0 && keyQuit == 0)
      {
        checkController();
      }
      while (keyAction1 == 1 && keyQuit == 0)
      {
        checkController();
      }

      gbl_evt = EVT_NULL;
      initPlayer();
      initLevel(currentLevel);
    }
    else if (gbl_evt == EVT_NULL)
    {
      while (keyAction4 == 1)
      {
        pause = 1;
        checkController();
      }

      while (pause == 1)
      {
        checkController();
        if (keyAction4 == 1)
        {
          while (keyAction4 == 1)
          {
            checkController();
          }
          pause = 0;
        }
      }

      sound_play(kSound_InGame, -1);

      int old_score = player.score;
      showFond(currentLevel);
      if (player.bonus_protection == 1)
      {
        if (player.bonus_protection_timer == -1)
        {
          blitBMPImageToScreen(1, 231, 123, 43, 43, player.posx - (5), player.posy - (5), 43, 43);
        }
        else
        {
          if (gbl_timer % 2 == 0)
          {
            blitBMPImageToScreen(1, 231, 123, 43, 43, player.posx - (5), player.posy - (5), 43, 43);
          }
        }
      }

      for (size_t i = 0; i < MAX_PLATFORMS; i++)
      {
        showPlatform(i);
      }
      for (size_t i = 0; i < MAX_LADDER; i++)
      {
        showLadder(i);
      }
      updatePlayer();
      for (size_t i = 0; i < MAX_SHOOT; i++)
      {
        updateShoot(i);
        showShoot(i);
      }
      nbBall = 0;
      for (size_t i = 0; i < MAX_BALL; i++)
      {
        nbBall += ball[i].active;

        if ((onetwo == 0) || (onetwo == 2) || (onetwo == 4))
          updateBalls(i);

        if ((player.bonus_freeze > 0) && (player.bonus_freeze < 81))
        {
          if (gbl_timer % 2 == 0)
            showBall(i);
        }
        else
        {
          showBall(i);
        }
      }
      for (size_t i = 0; i < MAX_BONUS; i++)
      {
        updateBonus(i);
        showBonus(i);
      }
      if (nbBall == 0)
      {
        gbl_evt = EVT_NEXT_LEVEL;
      }
      showPlayer();
      for (size_t i = 0; i < MAX_OBJECTS; i++)
      {
        showObject(i);
      }
      for (size_t i = 0; i < player.nblive; i++)
      {
        if (i < 3)
        {
          blitBMPImageToScreen(1, 179, 191, 18, 18, (10 + i * 20), 214, 18, 18);
        }
      }
      char chaine[10];
      sprintf(chaine, "%d", player.score);
      blitBMPImageToScreen(1, 242, 65, 38, 11, (110 + 20), 210, 38, 11); // Affiche SCORE:
      showScore(chaine, 170, 209);
      sprintf(chaine, "%d", currentLevel);
      blitBMPImageToScreen(1, 99, 44, 36, 14, 130, 224, 36, 14); // Affiche LEVEL:
      showScore(chaine, 170, 224);
      sprintf(chaine, "%d", chrono);

      sprintf(debug, "%s", "");
      if ((old_score < 600) && (player.score >= 600))
      {
        createObject(OBJ_1UP, player.posx, player.posy, 0);
        player.nblive++;
      }
      if ((old_score < 1500) && (player.score >= 1500))
      {
        createObject(OBJ_1UP, player.posx, player.posy, 0);
        player.nblive++;
      }
      if ((old_score < 5000) && (player.score >= 5000))
      {
        createObject(OBJ_1UP, player.posx, player.posy, 0);
        player.nblive++;
      }
      if (gbl_timer == 1)
        chrono--;
      if (chrono < 0)
        chrono = 0;
    }
    else if (gbl_evt == EVT_LOOSE_LIFE)
    {
      /* Animation de perte de vie ! */
      int cpt = 0;
      while (cpt != 70)
      {
        showFond(currentLevel);
        for (size_t i = 0; i < MAX_LADDER; i++)
        {
          showLadder(i);
        }
        for (size_t i = 0; i < MAX_BALL; i++)
        {
          showBall(i);
        }
        for (size_t i = 0; i < MAX_PLATFORMS; i++)
        {
          showPlatform(i);
        }

        showPlayer();
        if (cpt > 20)
          player.anim_courante = ANIM_DEAD;
        if ((cpt > 20) && (cpt < 40))
          player.posy--;
        if (cpt > 40)
        {
          player.posy++;
          player.posx++;
        }
        cpt++;
        present_frame();
      }
      sound_clear(kSound_InGame, kSoundClear_Force);
      releaseAllSprite();
      /* Réinitialiser d'abord le joueur avant les niveaux pour histoire de sprite ! */
      reInitPlayer();
      initLevel(currentLevel);
      gbl_evt = EVT_NULL;
      if (player.nblive <= 0)
        gbl_evt = EVT_GAME_OVER;
    }
    else if (gbl_evt == EVT_NEXT_LEVEL)
    {
      sound_clear(kSound_InGame, kSoundClear_Force);
      releaseAllSprite();
      sound_play(kSound_NextLevel, 0);
      if ((currentLevel % 2) == 0)
      {
        loadBmp("romdisk/nextlevel1.png", 2);
        blitBMPImageToScreen(2, 0, 0, 320, 240, 0, 0, 320, 240);
      }
      else
      {
        loadBmp("romdisk/nextlevel2.png", 2);
        blitBMPImageToScreen(2, 0, 0, 320, 240, 0, 0, 320, 240);
      }
      char chaine[10];
      sprintf(chaine, "%d", player.score);
      blitBMPImageToScreen(1, 242, 65, 38, 11, 110, 217, 38, 11); // Affiche SCORE:
      showScore(chaine, 183, 217);

      present_frame();

      checkController();
      while (keyAction1 == 0)
      {
        checkController();
      }
      while (keyAction1 == 1)
      {
        checkController();
      }

      currentLevel++;
      if (currentLevel > MAX_LEVEL)
        currentLevel = 1;
      reInitPlayer();
      initLevel(currentLevel);
      gbl_evt = EVT_NULL;
      sound_clear(kSound_NextLevel, kSoundClear_Force);
    }
    else if (gbl_evt == EVT_GAME_OVER)
    {
      sound_clear(kSound_InGame, kSoundClear_Force);
      sound_play(kSound_GameOver, 0);
      releaseAllSprite();
      /* Animation de perte de gameOver ! */
      int cpt = 0;
      while (cpt < 230)
      {
        /* reaffiche le fond */
        showFond(currentLevel);
        /* anime le game over */
        blitBMPImageToScreen(1, 8, 218, 130, 15, (320 - cpt), 100, 130, 15);
        cpt += 3;
        char chaine[10];
        sprintf(chaine, "%d", player.score);
        blitBMPImageToScreen(1, 242, 65, 38, 11, (110 + 20), 210, 38, 11); // Affiche SCORE:
        showScore(chaine, (80 + 70 + 20), 209);
        sprintf(chaine, "%d", currentLevel);
        blitBMPImageToScreen(1, 99, 44, 36, 14, (110 + 20), 224, 36, 14); // Affiche LEVEL:
        showScore(chaine, (80 + 70 + 20), 224);

        present_frame();
      }
      while (keyAction1 == 0)
      {
        checkController();
      }
      while (keyAction1 == 1)
      {
        checkController();
      }
      sound_clear(kSound_GameOver, kSoundClear_Force);
      initPlayer();
      initLevel(1);
      gbl_evt = EVT_TITLE;
      currentLevel = 1;
    }
    if (fpsshow == 1)
      showfps();
    present_frame();
    sound_clear(kSound_Shoot, kSoundClear_DontForce);
    sound_clear(kSound_BallPop, kSoundClear_DontForce);
    onetwo++;
    if (onetwo > 5)
      onetwo = 0;
    gbl_timer++;
    if (gbl_timer == 51)
      gbl_timer = 1;

    checkController();
    if (keyQuit == 1)
      g_quit = true;
  }
}

int
main(void)
{
  game();
  sound_deinit();

  return 0;
}
