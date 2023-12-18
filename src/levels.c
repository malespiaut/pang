#include "ball.h"
#include "bonus.h"
#include "gfx.h"
#include "ladder.h"
#include "objects.h"
#include "platform.h"
#include "shoot.h"
#include "structures.h"

void
initLevel(size_t n)
{
  initLadders();
  initShoot();
  initBalls();
  initBonus();
  initPlatforms();
  initObjects();

  // Pour l'instant testé jusko 21
  // n=21;

  if (n == 1)
  {
    size_t i = createBall((39 - 32), 19, kImage_Big, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();

    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 2)
  {
    size_t i = createBall((120 - 32), 18, kImage_Big, LEFT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    i = createPlatform((161 - 32), 81, kImage_PlatformBreakable);
    platforms[i].bonus = getRandomBonus();
    i = createPlatform((193 - 32), 81, kImage_PlatformBreakable);
    platforms[i].bonus = getRandomBonus();
  }
  if (n == 3)
  {
    createBall((76 - 32), 32, kImage_Big, LEFT, DOWN);
    size_t i = createBall((176 - 32), 101, kImage_Small, RIGHT, DOWN);
    ball[i].vel = 0.5;
    i = createPlatform((177 - 32), 81, kImage_PlatformBreakable);
    platforms[i].bonus = getRandomBonus();
    i = createPlatform((177 - 32), 138, kImage_PlatformBreakable);
    platforms[i].bonus = getRandomBonus();
    createPlatform((73 - 32), (81 - 8), kImage_PlatformUnbreakable);
    createPlatform((281 - 32), (81 - 8), kImage_PlatformUnbreakable);
  }

  if (n == 4)
  {
    size_t i = createBall((39 - 32), 19, kImage_Big, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    createLadder((162 - 32), 153, 12);
    createLadder((202 - 32), 153, 12);
    createPlatform((185 - 32), (153 - 1), kImage_PlatformUnbreakableVertical);
    createPlatform((193 - 32), (153 - 1), kImage_PlatformUnbreakableVertical);
    player.x = player.x + 16;
  }
  if (n == 5)
  {
    size_t i = createBall((49 - 32), 70, kImage_Big, LEFT, DOWN);
    ball[i].bonus = WEAPON_DOUBLE_SHOOT;
    i = createBall(241, 120, kImage_Normal, LEFT, DOWN);
    ball[i].bonus_parent = BONUS_FREEZE;
    createPlatform((97 - 32), 56, kImage_PlatformBreakableVertical);
    createPlatform((97 - 32), 81, kImage_PlatformBreakableVertical);
    i = createPlatform((289 - 32), 56, kImage_PlatformBreakableVertical);
    platforms[i].bonus = BONUS_BOOM;
    createPlatform((289 - 32), 81, kImage_PlatformBreakableVertical);
    createPlatform((193 - 32), 57, kImage_PlatformBreakableVertical);
  }
  if (n == 6)
  {
    createPlatform((81 - 32), 65, kImage_PlatformMediumUnbreakable);
    createPlatform((297 - 32), 65, kImage_PlatformMediumUnbreakable);
    createPlatform((185 - 32), 65, kImage_PlatformMediumBreakable);
    size_t i = createBall((154 - 32), 16, kImage_Big, LEFT, DOWN);
    ball[i].bonus = WEAPON_DOUBLE_SHOOT;
    createBall(192 - 32, 16, kImage_Big, RIGHT, DOWN);
  }
  if (n == 7)
  {
    createPlatform(97 - 32 - 16, 49, kImage_PlatformMicroUnbreakable);
    createPlatform(105 - 32 - 16, 57, kImage_PlatformMicroUnbreakable);
    createPlatform(113 - 32 - 16, 65, kImage_PlatformMicroUnbreakable);
    createPlatform(129 - 32 - 16, 105, kImage_PlatformMicroUnbreakable);
    createPlatform(137 - 32 - 16, 121, kImage_PlatformMicroUnbreakable);
    createPlatform(305 - 32 - 16, 49, kImage_PlatformMicroUnbreakable);
    createPlatform(297 - 32 - 16, 57, kImage_PlatformMicroUnbreakable);
    createPlatform(289 - 32 - 16, 65, kImage_PlatformMicroUnbreakable);
    createPlatform(273 - 32 - 16, 105, kImage_PlatformMicroUnbreakable);
    createPlatform(265 - 32 - 16, 121, kImage_PlatformMicroUnbreakable);
    createPlatform(281 - 32 - 16, 73, kImage_PlatformUnbreakableVertical);
    createPlatform(121 - 32 - 16, 73, kImage_PlatformUnbreakableVertical);
    createPlatform(193 - 32 - 16 - 5, 121, kImage_PlatformBreakable);
    createPlatform(161 - 32 - 16, 121, kImage_PlatformMediumBreakable);
    createPlatform(232 - 32 - 16, 121, kImage_PlatformMediumBreakable);
    size_t i = createBall(205 - 32, 31, kImage_Big, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(161 - 32, 85, kImage_Normal, RIGHT, DOWN);
    ball[i].bonus_parent = WEAPON_DOUBLE_SHOOT;
  }
  if (n == 8)
  {
    createPlatform(65 - 32, 97, kImage_PlatformUnbreakable);
    createPlatform(65 + 32 - 32, 97, kImage_PlatformUnbreakable);
    createPlatform(65 - 32, 97 + 8, kImage_PlatformUnbreakable);
    createPlatform(65 + 32 - 32, 97 + 8, kImage_PlatformUnbreakable);

    createPlatform(257 - 32, 97, kImage_PlatformUnbreakable);
    createPlatform(257 + 32 - 32, 97, kImage_PlatformUnbreakable);
    createPlatform(257 - 32, 97 + 8, kImage_PlatformUnbreakable);
    createPlatform(257 + 32 - 32, 97 + 8, kImage_PlatformUnbreakable);
    createPlatform(185 - 32, 49, kImage_PlatformUnbreakableVertical);
    createPlatform(193 - 32, 49, kImage_PlatformUnbreakableVertical);
    createPlatform(185 - 32, 129, kImage_PlatformUnbreakableVertical);
    createPlatform(193 - 32, 129, kImage_PlatformUnbreakableVertical);
    size_t i = createBall(150 - 32, 79, kImage_Normal, RIGHT, DOWN);
    ball[i].bonus = BONUS_FREEZE;
    i = createBall(209 - 32, 79, kImage_Normal, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
  }

  if (n == 9)
  {
    size_t i = createBall(134 - 32 - 10, 61, kImage_Big, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(209 - 32 + 10, 61, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();

    createLadder(51, 184, 4);
    createPlatform(73, 183, kImage_PlatformMediumUnbreakable);
    createPlatform(73, 183 + 8, kImage_PlatformMediumUnbreakable);
    createLadder(90, 184, 4);

    createLadder(129, 184, 4);
    createPlatform(151, 183, kImage_PlatformMediumUnbreakable);
    createPlatform(151, 183 + 8, kImage_PlatformMediumUnbreakable);
    createLadder(169, 184, 4);

    createLadder(213, 184, 4);
    createPlatform(235, 183, kImage_PlatformMediumUnbreakable);
    createPlatform(235, 183 + 8, kImage_PlatformMediumUnbreakable);
    createLadder(253, 184, 4);
    player.x = player.x + 15;
  }
  if (n == 10) /* BUG DE COLLISION A ANALYSER */
  {

    createPlatform(57 - 32, 89, kImage_PlatformMicroBreakable);
    createPlatform(81 - 32, 113, kImage_PlatformMicroBreakable);
    createPlatform(153 - 32, 89, kImage_PlatformMicroBreakable);
    size_t i = createPlatform(177 - 32, 113, kImage_PlatformMicroBreakable);
    platforms[i].bonus = getRandomBonus();
    createPlatform(249 - 32, 89, kImage_PlatformMicroBreakable);
    createPlatform(273 - 32, 113, kImage_PlatformMicroBreakable);

    createPlatform(105 - 32, 89, kImage_PlatformMicroUnbreakable);
    createPlatform(128 - 32, 113, kImage_PlatformMicroUnbreakable);
    createPlatform(201 - 32, 89, kImage_PlatformMicroUnbreakable);
    createPlatform(225 - 32, 113, kImage_PlatformMicroUnbreakable);
    createPlatform(296 - 32, 89, kImage_PlatformMicroUnbreakable);
    createPlatform(320 - 32, 113, kImage_PlatformMicroUnbreakable);

    i = createBall(42 - 32, 54, kImage_Normal, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    i = createBall(279 - 32, 45, kImage_Big, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 11)
  {
    createPlatform(41 - 32, 57 + 5, kImage_PlatformMediumBreakable);
    createPlatform(105 - 32, 48 + 5, kImage_PlatformMediumBreakable);
    size_t i = createPlatform(185 - 32, 33 + 5, kImage_PlatformMediumBreakable);
    platforms[i].bonus = BONUS_LIFE;
    createPlatform(265 - 32, 49 + 5, kImage_PlatformMediumBreakable);
    i = createPlatform(329 - 32, 57 + 5, kImage_PlatformMediumBreakable);
    platforms[i].bonus = getRandomBonus();
    createPlatform(81 - 32, 89 + 5, kImage_PlatformMediumBreakable);
    createPlatform(160 - 32, 81 + 5, kImage_PlatformMediumBreakable);
    createPlatform(209 - 32, 81 + 5, kImage_PlatformMediumBreakable);
    i = createPlatform(289 - 32, 89 + 5, kImage_PlatformMediumBreakable);
    platforms[i].bonus = getRandomBonus();
    createPlatform(121 - 32, 121 + 5, kImage_PlatformMediumBreakable);
    i = createPlatform(250 - 32, 121 + 5, kImage_PlatformMediumBreakable);
    platforms[i].bonus = getRandomBonus();
    createPlatform(161 - 32, 145 + 5, kImage_PlatformMediumBreakable);
    createPlatform(209 - 32, 145 + 5, kImage_PlatformMediumBreakable);
    createBall(119 - 32, 20, kImage_Normal, RIGHT, DOWN);
    i = createBall(217 - 32, 37, kImage_Big, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 12)
  {
    size_t i = createBall(39 - 32, 19, kImage_Big, LEFT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(276 - 32, 19, kImage_Big, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    createLadder(177 - 32, 56, 36);
    createPlatform(177 - 32 - 32, 55, kImage_PlatformUnbreakable);
    createPlatform(199 - 32, 55, kImage_PlatformUnbreakable);

    createPlatform(88 - 32 + 6, 160 - 4, kImage_PlatformMediumUnbreakable);
    createPlatform(88 - 32 + 6, 168 - 4, kImage_PlatformMediumUnbreakable);
    createPlatform(280 - 32 - 6, 160 - 4, kImage_PlatformMediumUnbreakable);
    createPlatform(280 - 32 - 6, 168 - 4, kImage_PlatformMediumUnbreakable);
  }
  if (n == 13)
  {
    createPlatform(8, 139, kImage_PlatformUnbreakable);
    createPlatform(50, 139, kImage_PlatformUnbreakable);
    createPlatform(104, 139, kImage_PlatformUnbreakable);
    createPlatform(136, 139, kImage_PlatformUnbreakable);
    createPlatform(180, 139, kImage_PlatformUnbreakable);
    createPlatform(234, 139, kImage_PlatformUnbreakable);
    createPlatform(280, 139, kImage_PlatformUnbreakable);

    createPlatform(49, 80, kImage_PlatformMediumUnbreakable);
    createPlatform(248, 80, kImage_PlatformMediumUnbreakable);
    createPlatform(108, 38, kImage_PlatformMediumUnbreakable);
    createPlatform(192, 38, kImage_PlatformMediumUnbreakable);

    createLadder(212, 140, 5);
    createLadder(82, 140, 15);

    size_t i = createBall(134, 60, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = WEAPON_GLUE_SHOOT;
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;

    i = createBall(20, 105, kImage_Normal, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = WEAPON_GLUE_SHOOT;
    ball[i].vel = ball[i].vel / 2;
  }

  if (n == 14)
  {
    createPlatform(65, 118, kImage_PlatformUnbreakable);
    createPlatform(119, 118, kImage_PlatformUnbreakable);
    createPlatform(151, 118, kImage_PlatformUnbreakable);
    createPlatform(183, 118, kImage_PlatformUnbreakable);
    createPlatform(215, 118, kImage_PlatformUnbreakable);
    createPlatform(8, 66, kImage_PlatformUnbreakable);
    createPlatform(40, 66, kImage_PlatformUnbreakable);
    createPlatform(248, 55, kImage_PlatformUnbreakable);
    createPlatform(280, 55, kImage_PlatformUnbreakable);

    createLadder(97, 119, 5);
    createLadder(247, 119, 20);

    createPlatform(75, 28, kImage_PlatformBreakableVertical);
    createPlatform(54, 81, kImage_PlatformBreakableVertical);

    size_t i = createBall(9, 9, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();

    i = createBall(222, 76, kImage_Normal, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 15)
  {
    size_t i = createBall(68, 128, kImage_Normal, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(68, 22, kImage_Normal, LEFT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
    i = createBall(246, 20, kImage_Normal, RIGHT, DOWN);
    ball[i].vel = ball[i].vel / 2;
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(246, 135, kImage_Normal, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();

    createPlatform(8, 109, kImage_PlatformUnbreakable);
    createPlatform(62, 109, kImage_PlatformUnbreakable);
    createPlatform(94, 109, kImage_PlatformUnbreakable);
    createPlatform(147, 109, kImage_PlatformUnbreakable);
    createPlatform(179, 109, kImage_PlatformUnbreakable);
    createPlatform(211, 109, kImage_PlatformUnbreakable);
    createPlatform(265, 109, kImage_PlatformUnbreakable);

    createLadder(243, 109, 23);
    createLadder(125, 109, 6);
    createLadder(40, 109, 23);
  }

  if (n == 16)
  {
    size_t i = createBall(21, 14, kImage_Micro, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    createBall(25, 30, kImage_Micro, RIGHT, DOWN);
    createBall(29, 46, kImage_Micro, RIGHT, DOWN);
    createBall(33, 62, kImage_Micro, RIGHT, DOWN);
    createBall(36, 77, kImage_Micro, RIGHT, DOWN);
    createBall(41, 92, kImage_Micro, RIGHT, DOWN);
    createBall(45, 110, kImage_Micro, RIGHT, DOWN);
    createBall(50, 127, kImage_Micro, RIGHT, DOWN);

    i = createBall(320 - 21, 14, kImage_Micro, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    createBall(320 - 25, 30, kImage_Micro, LEFT, DOWN);
    createBall(320 - 29, 46, kImage_Micro, LEFT, DOWN);
    createBall(320 - 33, 62, kImage_Micro, LEFT, DOWN);
    createBall(320 - 36, 77, kImage_Micro, LEFT, DOWN);
    createBall(320 - 41, 92, kImage_Micro, LEFT, DOWN);
    createBall(320 - 45, 110, kImage_Micro, LEFT, DOWN);
    createBall(320 - 50, 127, kImage_Micro, LEFT, DOWN);

    for (size_t j = 0; j < MAX_BALL; ++j)
    {
      if (ball[j].active)
      {
        ball[j].vel_cst = 10.0;
      }
    }
  }

  if (n == 17)
  {
    int tmp;
    for (size_t i = 0; i < 9; ++i)
    {
      createPlatform((17 + (i * 32)), 29, kImage_PlatformBreakable);
    }

    size_t i = createPlatform(9, 29, kImage_PlatformMicroBreakable);
    platforms[i].bonus = BONUS_LIFE;
    i = createPlatform(297 + 8, 29, kImage_PlatformMicroBreakable);
    platforms[i].bonus = getRandomBonus();

    for (size_t j = 0; j < 8; ++j)
    {
      tmp = createBall((18 + (j * 8)), 18, kImage_Micro, RIGHT, DOWN);
      ball[tmp].vel = 0.5;
    }
    for (size_t j = 0; j < 8; ++j)
    {
      tmp = createBall((230 + (j * 8)), 18, kImage_Micro, RIGHT, DOWN);
      ball[tmp].vel = 0.5;
    }

    i = createBall(69, 56, kImage_Big, LEFT, DOWN);
    ball[i].bonus_parent = WEAPON_DOUBLE_SHOOT;
    ball[i].vel = 1.0;
    ball[i].vel_cst = 11.0;
    i = createBall(194, 64, kImage_Normal, RIGHT, DOWN);
    ball[i].bonus_parent = WEAPON_DOUBLE_SHOOT;
    ball[i].vel = 1.0;
  }
  if (n == 18)
  {
    int tmp;
    for (size_t i = 0; i < 4; ++i)
    {
      tmp = createBall((18 + (i * 8)), 150, kImage_Micro, LEFT, DOWN);
      ball[tmp].vel_cst = 8.0;
      if (i == 4)
        ball[tmp].bonus = WEAPON_DOUBLE_SHOOT;
    }
    for (size_t i = 0; i < 4; ++i)
    {
      tmp = createBall((230 + (i * 8)), 150, kImage_Micro, RIGHT, DOWN);
      ball[tmp].vel_cst = 8.0;
      if (i == 4)
        ball[tmp].bonus = WEAPON_DOUBLE_SHOOT;
    }

    tmp = createPlatform(65, 85, kImage_PlatformBreakable);
    platforms[tmp].bonus = WEAPON_DOUBLE_SHOOT;
    tmp = createPlatform(220, 85, kImage_PlatformBreakable);
    platforms[tmp].bonus = getRandomBonus();
  }

  if (n == 19)
  {
    size_t i = createBall(77, 17, kImage_Big, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(229, 19, kImage_Normal, LEFT, DOWN);
    ball[i].bonus_parent = getRandomBonus();

    createLadder(8, 100, 25);
    createLadder(290, 100, 25);

    for (size_t j = 0; j < 7; ++j)
    {
      createPlatform((47 + (j * 32)), 136, kImage_PlatformUnbreakable);
    }
  }
  if (n == 20)
  {
    createPlatform(64 - 32, 48, kImage_PlatformMediumBreakable);
    createPlatform(304 - 32, 48, kImage_PlatformMediumBreakable);
    createPlatform(160 - 32, 140, kImage_PlatformUnbreakable);
    createPlatform(160, 140, kImage_PlatformUnbreakable);
    size_t i = createBall(124 - 32, 27, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
    i = createBall(225 - 32, 27, kImage_Big, LEFT, DOWN);
    ball[i].vel = ball[i].vel / 2;
  }
  if (n == 21)
  {
    createPlatform(175 - 32 - 16, 127, kImage_PlatformBreakable);
    createPlatform(175 - 16, 127, kImage_PlatformBreakable);

    createPlatform(185 - 32, 65, kImage_PlatformMediumUnbreakable);

    createPlatform(90 - 32, 80, kImage_PlatformMediumUnbreakable);
    createPlatform(286 - 32, 80, kImage_PlatformMediumUnbreakable);

    size_t i = createBall(124 - 32, 27, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
    i = createBall(225 - 32, 27, kImage_Big, LEFT, DOWN);
    ball[i].vel = ball[i].vel / 2;
  }
  if (n == 22)
  {
    for (size_t i = 0; i < 7; ++i)
    {
      createPlatform((112 - 64 + (i * 32)), 104, kImage_PlatformUnbreakable);
    }

    size_t i = createBall((92 - 32), 27, kImage_Big, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
    i = createBall((250 - 32), 27, kImage_Big, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
  }
  if (n == 23)
  {
    for (size_t i = 0; i < 4; ++i)
    {
      createPlatform(81 - 32, (33 + (i * 32)), kImage_PlatformUnbreakableVertical);
      createPlatform(153 - 32, (33 + (i * 32)), kImage_PlatformBreakableVertical);
      createPlatform(225 - 32, (33 + (i * 32)), kImage_PlatformBreakableVertical);
      createPlatform(297 - 32, (33 + (i * 32)), kImage_PlatformUnbreakableVertical);
    }
    player.x = player.x + 64;
    size_t i = createBall(197 - 64, 20, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 24)
  {
    for (size_t i = 0; i < 4; ++i)
    {
      createPlatform(81 - 32, (33 + (i * 32)), kImage_PlatformUnbreakableVertical);
      createPlatform(297 - 32, (33 + (i * 32)), kImage_PlatformUnbreakableVertical);
    }
    size_t i = createBall(197 + 8, 20, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(197 - 64 - 64, 20, kImage_Big, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 25)
  {
    size_t i = createBall(50, 10, kImage_Big, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(50, 10, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    createBall(200, 10, kImage_Micro, LEFT, DOWN);
    createBall(205, 15, kImage_Micro, LEFT, UP);
    createBall(210, 20, kImage_Micro, RIGHT, DOWN);
    createBall(215, 22, kImage_Micro, RIGHT, DOWN);
    createBall(220, 25, kImage_Micro, RIGHT, UP);
    createBall(225, 30, kImage_Micro, LEFT, DOWN);

    for (size_t j = 0; j < 6; ++j)
    {
      if (j > 2)
      {
        createPlatform(((337 - 32) - (j * 8)), (41 + (j * 8)), kImage_PlatformMicroUnbreakable);
        createPlatform(((41 - 32) + (j * 8)), (41 + (j * 8)), kImage_PlatformMicroUnbreakable);
      }
    }

    createLadder((332 - 32 - 22 + 10), (41 + (2 * 8)), 36);
    createLadder(((41 - 32) + 2), (41 + (2 * 8)), 36);

    createPlatform((337 - 32 - 16) - (6 * 8) - 8, 41 + (6 * 8), kImage_PlatformBreakable);
    i = createPlatform((41 - 32) + (6 * 8), 41 + (5 * 8), kImage_PlatformBreakable);

    createPlatform((41 - 32) + (6 * 8) + 32, 41 + (6 * 8), kImage_PlatformMediumUnbreakable);
    platforms[i].bonus = getRandomBonus();
    createPlatform((337 - 32) - (6 * 8) - 32 - 8, 41 + (6 * 8), kImage_PlatformMediumUnbreakable);
    platforms[i].bonus = BONUS_LIFE;

    for (size_t j = 0; j < 3; ++j)
    {
      createPlatform((248 - 32 - 8) - (j * 8), 97 + (j * 8), kImage_PlatformMicroUnbreakable);
      createPlatform((137 - 32) + (j * 8), 97 + (j * 8), kImage_PlatformMicroUnbreakable);
    }

    createPlatform(161 - 32, 121, kImage_PlatformMediumUnbreakable);
    createPlatform(209 - 32, 121, kImage_PlatformMediumUnbreakable);
  }
  if (n == 26)
  {
    createBall(39 - 32, 19, kImage_Big, LEFT, DOWN);
    for (size_t i = 0; i < 3; ++i)
    {
      createPlatform(34 + (i * 32) - 22 + 16, 159, kImage_PlatformBreakable);
      createPlatform(184 + (i * 32), 159, kImage_PlatformBreakable);
    }
    createPlatform(34 + (3 * 32) - 22 + 16, 159, kImage_PlatformUnbreakable);
    createPlatform(152, 159, kImage_PlatformUnbreakable);
    createPlatform(280, 159, kImage_PlatformUnbreakable);

    createLadder(130, 155 + 4, 10);

    createPlatform(8, 102, kImage_PlatformBreakable);
    for (size_t i = 0; i < 6; ++i)
    {
      createPlatform(41 + (i * 32), 102, kImage_PlatformUnbreakable);
    }
    createPlatform(232, 102, kImage_PlatformMediumUnbreakable);
    createPlatform(249, 102, kImage_PlatformBreakable);
    createPlatform(281, 102, kImage_PlatformUnbreakable);

    createLadder(162, 99 + 4, 14);
  }
  if (n == 30)
  {
    for (size_t i = 0; i < 4; ++i)
    {
      createPlatform(81 - 32, 33 + (i * 32), kImage_PlatformUnbreakableVertical);
      createPlatform(153 - 32, 33 + (i * 32), kImage_PlatformBreakableVertical);
      createPlatform(225 - 32, 33 + (i * 32), kImage_PlatformBreakableVertical);
      createPlatform(297 - 32, 33 + (i * 32), kImage_PlatformUnbreakableVertical);
    }
    player.x = player.x + 64;
    size_t i = createBall(197 - 64, 20, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(197 - 64 - 64, 20, kImage_Big, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 38)
  {
    for (size_t i = 0; i < 4; ++i)
    {
      createPlatform(81 - 32, 33 + (i * 32), kImage_PlatformUnbreakableVertical);
      createPlatform(153 - 32, 33 + (i * 32), kImage_PlatformBreakableVertical);
      createPlatform(225 - 32, 33 + (i * 32), kImage_PlatformBreakableVertical);
      createPlatform(297 - 32, 33 + (i * 32), kImage_PlatformUnbreakableVertical);
    }
    player.x = player.x + 64 + 32 + 16;
    size_t i = createBall(197 + 8, 20, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(197 - 64, 20, kImage_Big, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(197 - 64 - 64, 20, kImage_Big, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
}
