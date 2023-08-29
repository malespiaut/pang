#include "ball.h"
#include "bonus.h"
#include "ladder.h"
#include "main.h"
#include "objets.h"
#include "platform.h"
#include "shoot.h"
#include "structures.h"

void
initLevel(int n)
{
  int i;

  initLadders();
  initShoot();
  initBalls();
  initBonus();
  initPlatforms();
  initObjets();

  // Pour l'instant testé jusko 21
  // n=21;

  if (n == 1)
  {
    i = createBall((39 - 32), 19, BIG, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    //		ball[i].bonus = BONUS_LIFE;

    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 2)
  {
    i = createBall((120 - 32), 18, BIG, LEFT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    i = createPlatform((161 - 32), 81, PF_CASSABLE);
    pform[i].bonus = getRandomBonus();
    i = createPlatform((193 - 32), 81, PF_CASSABLE);
    pform[i].bonus = getRandomBonus();
  }
  if (n == 3)
  {
    createBall((76 - 32), 32, BIG, LEFT, DOWN);
    i = createBall((176 - 32), 101, SMALL, RIGHT, DOWN);
    ball[i].vel = 0.5;
    i = createPlatform((177 - 32), 81, PF_CASSABLE);
    pform[i].bonus = getRandomBonus();
    i = createPlatform((177 - 32), 138, PF_CASSABLE);
    pform[i].bonus = getRandomBonus();
    createPlatform((73 - 32), (81 - 8), PF_INCASSABLE);
    createPlatform((281 - 32), (81 - 8), PF_INCASSABLE);
    /*createBall(184,23,BIG,LEFT,DOWN);
    createPlatformCassable(160,100);*/
  }

  if (n == 4)
  {
    i = createBall((39 - 32), 19, BIG, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    createLadder((162 - 32), 153, 12);
    createLadder((202 - 32), 153, 12);
    createPlatform((185 - 32), (153 - 1), PF_INCASSABLEV);
    createPlatform((193 - 32), (153 - 1), PF_INCASSABLEV);
    player.posx = player.posx + 16;
  }
  if (n == 5)
  {
    i = createBall((49 - 32), 70, BIG, LEFT, DOWN);
    ball[i].bonus = WEAPON_DOUBLE_SHOOT;
    i = createBall(241, 120, NORMAL, LEFT, DOWN);
    ball[i].bonus_parent = BONUS_FREEZE;
    createPlatform((97 - 32), 56, PF_CASSABLEV);
    createPlatform((97 - 32), 81, PF_CASSABLEV);
    i = createPlatform((289 - 32), 56, PF_CASSABLEV);
    pform[i].bonus = BONUS_BOOM;
    createPlatform((289 - 32), 81, PF_CASSABLEV);
    createPlatform((193 - 32), 57, PF_CASSABLEV);
  }
  if (n == 6)
  {
    createPlatform((81 - 32), 65, PF_MOYEN_INCASSABLE);
    createPlatform((297 - 32), 65, PF_MOYEN_INCASSABLE);
    createPlatform((185 - 32), 65, PF_MOYEN_CASSABLE);
    i = createBall((154 - 32), 16, BIG, LEFT, DOWN);
    ball[i].bonus = WEAPON_DOUBLE_SHOOT;
    createBall(192 - 32, 16, BIG, RIGHT, DOWN);
  }
  if (n == 7)
  {
    createPlatform(97 - 32 - 16, 49, PF_MICRO_INCASSABLE);
    createPlatform(105 - 32 - 16, 57, PF_MICRO_INCASSABLE);
    createPlatform(113 - 32 - 16, 65, PF_MICRO_INCASSABLE);
    createPlatform(129 - 32 - 16, 105, PF_MICRO_INCASSABLE);
    createPlatform(137 - 32 - 16, 121, PF_MICRO_INCASSABLE);
    createPlatform(305 - 32 - 16, 49, PF_MICRO_INCASSABLE);
    createPlatform(297 - 32 - 16, 57, PF_MICRO_INCASSABLE);
    createPlatform(289 - 32 - 16, 65, PF_MICRO_INCASSABLE);
    createPlatform(273 - 32 - 16, 105, PF_MICRO_INCASSABLE);
    createPlatform(265 - 32 - 16, 121, PF_MICRO_INCASSABLE);
    createPlatform(281 - 32 - 16, 73, PF_INCASSABLEV);
    createPlatform(121 - 32 - 16, 73, PF_INCASSABLEV);
    createPlatform(193 - 32 - 16 - 5, 121, PF_CASSABLE);
    createPlatform(161 - 32 - 16, 121, PF_MOYEN_CASSABLE);
    createPlatform(232 - 32 - 16, 121, PF_MOYEN_CASSABLE);
    i = createBall(205 - 32, 31, BIG, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(161 - 32, 85, NORMAL, RIGHT, DOWN);
    ball[i].bonus_parent = WEAPON_DOUBLE_SHOOT;
  }
  if (n == 8)
  {
    createPlatform(65 - 32, 97, PF_INCASSABLE);
    createPlatform(65 + 32 - 32, 97, PF_INCASSABLE);
    createPlatform(65 - 32, 97 + 8, PF_INCASSABLE);
    createPlatform(65 + 32 - 32, 97 + 8, PF_INCASSABLE);

    createPlatform(257 - 32, 97, PF_INCASSABLE);
    createPlatform(257 + 32 - 32, 97, PF_INCASSABLE);
    createPlatform(257 - 32, 97 + 8, PF_INCASSABLE);
    createPlatform(257 + 32 - 32, 97 + 8, PF_INCASSABLE);
    createPlatform(185 - 32, 49, PF_INCASSABLEV);
    createPlatform(193 - 32, 49, PF_INCASSABLEV);
    createPlatform(185 - 32, 129, PF_INCASSABLEV);
    createPlatform(193 - 32, 129, PF_INCASSABLEV);
    i = createBall(150 - 32, 79, NORMAL, RIGHT, DOWN);
    ball[i].bonus = BONUS_FREEZE;
    i = createBall(209 - 32, 79, NORMAL, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
  }

  if (n == 9)
  {
    i = createBall(134 - 32 - 10, 61, BIG, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(209 - 32 + 10, 61, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();

    createLadder(51, 184, 4);
    createPlatform(73, 183, PF_MOYEN_INCASSABLE);
    createPlatform(73, 183 + 8, PF_MOYEN_INCASSABLE);
    createLadder(90, 184, 4);

    createLadder(129, 184, 4);
    createPlatform(151, 183, PF_MOYEN_INCASSABLE);
    createPlatform(151, 183 + 8, PF_MOYEN_INCASSABLE);
    createLadder(169, 184, 4);

    createLadder(213, 184, 4);
    createPlatform(235, 183, PF_MOYEN_INCASSABLE);
    createPlatform(235, 183 + 8, PF_MOYEN_INCASSABLE);
    createLadder(253, 184, 4);
    player.posx = player.posx + 15;
  }
  if (n == 10) /* BUG DE COLLISION A ANALYSER */
  {

    createPlatform(57 - 32, 89, PF_MICRO_CASSABLE);
    createPlatform(81 - 32, 113, PF_MICRO_CASSABLE);
    createPlatform(153 - 32, 89, PF_MICRO_CASSABLE);
    i = createPlatform(177 - 32, 113, PF_MICRO_CASSABLE);
    pform[i].bonus = getRandomBonus();
    createPlatform(249 - 32, 89, PF_MICRO_CASSABLE);
    createPlatform(273 - 32, 113, PF_MICRO_CASSABLE);

    createPlatform(105 - 32, 89, PF_MICRO_INCASSABLE);
    createPlatform(128 - 32, 113, PF_MICRO_INCASSABLE);
    createPlatform(201 - 32, 89, PF_MICRO_INCASSABLE);
    createPlatform(225 - 32, 113, PF_MICRO_INCASSABLE);
    createPlatform(296 - 32, 89, PF_MICRO_INCASSABLE);
    createPlatform(320 - 32, 113, PF_MICRO_INCASSABLE);

    i = createBall(42 - 32, 54, NORMAL, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    i = createBall(279 - 32, 45, BIG, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 11)
  {
    createPlatform(41 - 32, 57 + 5, PF_MOYEN_CASSABLE);
    createPlatform(105 - 32, 48 + 5, PF_MOYEN_CASSABLE);
    i = createPlatform(185 - 32, 33 + 5, PF_MOYEN_CASSABLE);
    pform[i].bonus = BONUS_LIFE;
    createPlatform(265 - 32, 49 + 5, PF_MOYEN_CASSABLE);
    i = createPlatform(329 - 32, 57 + 5, PF_MOYEN_CASSABLE);
    pform[i].bonus = getRandomBonus();
    createPlatform(81 - 32, 89 + 5, PF_MOYEN_CASSABLE);
    createPlatform(160 - 32, 81 + 5, PF_MOYEN_CASSABLE);
    createPlatform(209 - 32, 81 + 5, PF_MOYEN_CASSABLE);
    i = createPlatform(289 - 32, 89 + 5, PF_MOYEN_CASSABLE);
    pform[i].bonus = getRandomBonus();
    createPlatform(121 - 32, 121 + 5, PF_MOYEN_CASSABLE);
    i = createPlatform(250 - 32, 121 + 5, PF_MOYEN_CASSABLE);
    pform[i].bonus = getRandomBonus();
    createPlatform(161 - 32, 145 + 5, PF_MOYEN_CASSABLE);
    createPlatform(209 - 32, 145 + 5, PF_MOYEN_CASSABLE);
    createBall(119 - 32, 20, NORMAL, RIGHT, DOWN);
    i = createBall(217 - 32, 37, BIG, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 12)
  {
    i = createBall(39 - 32, 19, BIG, LEFT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(276 - 32, 19, BIG, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    createLadder(177 - 32, 56, 36);
    createPlatform(177 - 32 - 32, 55, PF_INCASSABLE);
    createPlatform(199 - 32, 55, PF_INCASSABLE);

    createPlatform(88 - 32 + 6, 160 - 4, PF_MOYEN_INCASSABLE);
    createPlatform(88 - 32 + 6, 168 - 4, PF_MOYEN_INCASSABLE);
    createPlatform(280 - 32 - 6, 160 - 4, PF_MOYEN_INCASSABLE);
    createPlatform(280 - 32 - 6, 168 - 4, PF_MOYEN_INCASSABLE);
  }
  if (n == 13)
  {
    createPlatform(8, 139, PF_INCASSABLE);
    createPlatform(50, 139, PF_INCASSABLE);
    createPlatform(104, 139, PF_INCASSABLE);
    createPlatform(136, 139, PF_INCASSABLE);
    createPlatform(180, 139, PF_INCASSABLE);
    createPlatform(234, 139, PF_INCASSABLE);
    createPlatform(280, 139, PF_INCASSABLE);

    createPlatform(49, 80, PF_MOYEN_INCASSABLE);
    createPlatform(248, 80, PF_MOYEN_INCASSABLE);
    createPlatform(108, 38, PF_MOYEN_INCASSABLE);
    createPlatform(192, 38, PF_MOYEN_INCASSABLE);

    createLadder(212, 140, 5);
    createLadder(82, 140, 15);

    i = createBall(134, 60, BIG, RIGHT, DOWN);
    ball[i].bonus = WEAPON_GLUE_SHOOT;
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;

    i = createBall(20, 105, NORMAL, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = WEAPON_GLUE_SHOOT;
    ball[i].vel = ball[i].vel / 2;
  }

  if (n == 14)
  {
    createPlatform(65, 118, PF_INCASSABLE);
    createPlatform(119, 118, PF_INCASSABLE);
    createPlatform(151, 118, PF_INCASSABLE);
    createPlatform(183, 118, PF_INCASSABLE);
    createPlatform(215, 118, PF_INCASSABLE);
    createPlatform(8, 66, PF_INCASSABLE);
    createPlatform(40, 66, PF_INCASSABLE);
    createPlatform(248, 55, PF_INCASSABLE);
    createPlatform(280, 55, PF_INCASSABLE);

    createLadder(97, 119, 5);
    createLadder(247, 119, 20);

    createPlatform(75, 28, PF_CASSABLEV);
    createPlatform(54, 81, PF_CASSABLEV);

    i = createBall(9, 9, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();

    i = createBall(222, 76, NORMAL, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 15)
  {
    i = createBall(68, 128, NORMAL, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(68, 22, NORMAL, LEFT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
    i = createBall(246, 20, NORMAL, RIGHT, DOWN);
    ball[i].vel = ball[i].vel / 2;
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(246, 135, NORMAL, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();

    createPlatform(8, 109, PF_INCASSABLE);
    createPlatform(62, 109, PF_INCASSABLE);
    createPlatform(94, 109, PF_INCASSABLE);
    createPlatform(147, 109, PF_INCASSABLE);
    createPlatform(179, 109, PF_INCASSABLE);
    createPlatform(211, 109, PF_INCASSABLE);
    createPlatform(265, 109, PF_INCASSABLE);

    createLadder(243, 109, 23);
    createLadder(125, 109, 6);
    createLadder(40, 109, 23);
  }

  if (n == 16)
  {
    int i;
    i = createBall(21, 14, MICRO, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    createBall(25, 30, MICRO, RIGHT, DOWN);
    createBall(29, 46, MICRO, RIGHT, DOWN);
    createBall(33, 62, MICRO, RIGHT, DOWN);
    createBall(36, 77, MICRO, RIGHT, DOWN);
    createBall(41, 92, MICRO, RIGHT, DOWN);
    createBall(45, 110, MICRO, RIGHT, DOWN);
    createBall(50, 127, MICRO, RIGHT, DOWN);

    i = createBall(320 - 21, 14, MICRO, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    createBall(320 - 25, 30, MICRO, LEFT, DOWN);
    createBall(320 - 29, 46, MICRO, LEFT, DOWN);
    createBall(320 - 33, 62, MICRO, LEFT, DOWN);
    createBall(320 - 36, 77, MICRO, LEFT, DOWN);
    createBall(320 - 41, 92, MICRO, LEFT, DOWN);
    createBall(320 - 45, 110, MICRO, LEFT, DOWN);
    createBall(320 - 50, 127, MICRO, LEFT, DOWN);

    for (i = 0; i < MAX_BALL; i++)
    {
      if (ball[i].utilise == 1)
      {
        ball[i].vel_cst = 10.0;
      }
    }
  }

  if (n == 17)
  {
    int i;
    int tmp;
    for (i = 0; i < 9; i++)
    {
      createPlatform((17 + (i * 32)), 29, PF_CASSABLE);
    }

    i = createPlatform(9, 29, PF_MICRO_CASSABLE);
    pform[i].bonus = BONUS_LIFE;
    i = createPlatform(297 + 8, 29, PF_MICRO_CASSABLE);
    pform[i].bonus = getRandomBonus();

    for (i = 0; i < 8; i++)
    {
      tmp = createBall((18 + (i * 8)), 18, MICRO, RIGHT, DOWN);
      ball[tmp].vel = 0.5;
    }
    for (i = 0; i < 8; i++)
    {
      tmp = createBall((230 + (i * 8)), 18, MICRO, RIGHT, DOWN);
      ball[tmp].vel = 0.5;
    }

    i = createBall(69, 56, BIG, LEFT, DOWN);
    ball[i].bonus_parent = WEAPON_DOUBLE_SHOOT;
    ball[i].vel = 1.0;
    ball[i].vel_cst = 11.0;
    i = createBall(194, 64, NORMAL, RIGHT, DOWN);
    ball[i].bonus_parent = WEAPON_DOUBLE_SHOOT;
    ball[i].vel = 1.0;
  }
  if (n == 18)
  {
    int tmp;
    for (i = 0; i < 4; i++)
    {
      tmp = createBall((18 + (i * 8)), 150, MICRO, LEFT, DOWN);
      ball[tmp].vel_cst = 8.0;
      if (i == 4)
        ball[tmp].bonus = WEAPON_DOUBLE_SHOOT;
    }
    for (i = 0; i < 4; i++)
    {
      tmp = createBall((230 + (i * 8)), 150, MICRO, RIGHT, DOWN);
      ball[tmp].vel_cst = 8.0;
      if (i == 4)
        ball[tmp].bonus = WEAPON_DOUBLE_SHOOT;
    }

    tmp = createPlatform(65, 85, PF_CASSABLE);
    pform[tmp].bonus = WEAPON_DOUBLE_SHOOT;
    tmp = createPlatform(220, 85, PF_CASSABLE);
    pform[tmp].bonus = getRandomBonus();
  }

  if (n == 19)
  {
    i = createBall(77, 17, BIG, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(229, 19, NORMAL, LEFT, DOWN);
    ball[i].bonus_parent = getRandomBonus();

    createLadder(8, 100, 25);
    createLadder(290, 100, 25);

    for (i = 0; i < 7; i++)
    {
      createPlatform((47 + (i * 32)), 136, PF_INCASSABLE);
    }
  }
  if (n == 20)
  {
    createPlatform(64 - 32, 48, PF_MOYEN_CASSABLE);
    createPlatform(304 - 32, 48, PF_MOYEN_CASSABLE);
    createPlatform(160 - 32, 140, PF_INCASSABLE);
    createPlatform(160, 140, PF_INCASSABLE);
    i = createBall(124 - 32, 27, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
    i = createBall(225 - 32, 27, BIG, LEFT, DOWN);
    ball[i].vel = ball[i].vel / 2;
  }
  if (n == 21)
  {
    createPlatform(175 - 32 - 16, 127, PF_CASSABLE);
    createPlatform(175 - 16, 127, PF_CASSABLE);

    createPlatform(185 - 32, 65, PF_MOYEN_INCASSABLE);

    createPlatform(90 - 32, 80, PF_MOYEN_INCASSABLE);
    createPlatform(286 - 32, 80, PF_MOYEN_INCASSABLE);

    i = createBall(124 - 32, 27, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
    i = createBall(225 - 32, 27, BIG, LEFT, DOWN);
    ball[i].vel = ball[i].vel / 2;
  }
  if (n == 22)
  {
    for (i = 0; i < 7; i++)
    {
      createPlatform((112 - 64 + (i * 32)), 104, PF_INCASSABLE);
    }

    i = createBall((92 - 32), 27, BIG, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
    i = createBall((250 - 32), 27, BIG, RIGHT, DOWN);
    ball[i].bonus_parent = getRandomBonus();
    ball[i].vel = ball[i].vel / 2;
  }
  if (n == 23)
  {
    for (i = 0; i < 4; i++)
    {
      createPlatform(81 - 32, (33 + (i * 32)), PF_INCASSABLEV);
      createPlatform(153 - 32, (33 + (i * 32)), PF_CASSABLEV);
      createPlatform(225 - 32, (33 + (i * 32)), PF_CASSABLEV);
      createPlatform(297 - 32, (33 + (i * 32)), PF_INCASSABLEV);
    }
    player.posx = player.posx + 64;
    i = createBall(197 - 64, 20, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 24)
  {
    for (i = 0; i < 4; i++)
    {
      createPlatform(81 - 32, (33 + (i * 32)), PF_INCASSABLEV);
      /*createPlatform(153-32,33+(i*32),PF_CASSABLEV);
      createPlatform(225-32,33+(i*32),PF_CASSABLEV);*/
      createPlatform(297 - 32, (33 + (i * 32)), PF_INCASSABLEV);
    }
    /*player.posx = player.posx + 64 + 32 + 16;*/
    i = createBall(197 + 8, 20, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(197 - 64 - 64, 20, BIG, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 25)
  {
    i = createBall(50, 10, BIG, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(50, 10, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    createBall(200, 10, MICRO, LEFT, DOWN);
    createBall(205, 15, MICRO, LEFT, UP);
    createBall(210, 20, MICRO, RIGHT, DOWN);
    createBall(215, 22, MICRO, RIGHT, DOWN);
    createBall(220, 25, MICRO, RIGHT, UP);
    createBall(225, 30, MICRO, LEFT, DOWN);

    for (i = 0; i < 6; i++)
    {
      if (i > 2)
      {
        createPlatform(((337 - 32) - (i * 8)), (41 + (i * 8)), PF_MICRO_INCASSABLE);
        createPlatform(((41 - 32) + (i * 8)), (41 + (i * 8)), PF_MICRO_INCASSABLE);
      }
    }

    createLadder((332 - 32 - 22 + 10), (41 + (2 * 8)), 36);
    createLadder(((41 - 32) + 2), (41 + (2 * 8)), 36);

    i = createPlatform((337 - 32 - 16) - (6 * 8) - 8, 41 + (6 * 8), PF_CASSABLE);
    i = createPlatform((41 - 32) + (6 * 8), 41 + (5 * 8), PF_CASSABLE);

    createPlatform((41 - 32) + (6 * 8) + 32, 41 + (6 * 8), PF_MOYEN_INCASSABLE);
    pform[i].bonus = getRandomBonus();
    createPlatform((337 - 32) - (6 * 8) - 32 - 8, 41 + (6 * 8), PF_MOYEN_INCASSABLE);
    pform[i].bonus = BONUS_LIFE;

    for (i = 0; i < 3; i++)
    {
      createPlatform((248 - 32 - 8) - (i * 8), 97 + (i * 8), PF_MICRO_INCASSABLE);
      createPlatform((137 - 32) + (i * 8), 97 + (i * 8), PF_MICRO_INCASSABLE);
    }

    createPlatform(161 - 32, 121, PF_MOYEN_INCASSABLE);
    createPlatform(209 - 32, 121, PF_MOYEN_INCASSABLE);
  }
  if (n == 26)
  {
    createBall(39 - 32, 19, BIG, LEFT, DOWN);
    for (i = 0; i < 3; i++)
    {
      createPlatform(34 + (i * 32) - 22 + 16, 159, PF_CASSABLE);
      createPlatform(184 + (i * 32), 159, PF_CASSABLE);
    }
    createPlatform(34 + (3 * 32) - 22 + 16, 159, PF_INCASSABLE);
    createPlatform(152, 159, PF_INCASSABLE);
    createPlatform(280, 159, PF_INCASSABLE);

    createLadder(130, 155 + 4, 10);

    createPlatform(8, 102, PF_CASSABLE);
    for (i = 0; i < 6; i++)
    {
      createPlatform(41 + (i * 32), 102, PF_INCASSABLE);
    }
    createPlatform(232, 102, PF_MOYEN_INCASSABLE);
    createPlatform(249, 102, PF_CASSABLE);
    createPlatform(281, 102, PF_INCASSABLE);

    createLadder(162, 99 + 4, 14);
  }
  if (n == 30)
  {
    for (i = 0; i < 4; i++)
    {
      createPlatform(81 - 32, 33 + (i * 32), PF_INCASSABLEV);
      createPlatform(153 - 32, 33 + (i * 32), PF_CASSABLEV);
      createPlatform(225 - 32, 33 + (i * 32), PF_CASSABLEV);
      createPlatform(297 - 32, 33 + (i * 32), PF_INCASSABLEV);
    }
    player.posx = player.posx + 64;
    i = createBall(197 - 64, 20, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(197 - 64 - 64, 20, BIG, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
  if (n == 38)
  {
    for (i = 0; i < 4; i++)
    {
      createPlatform(81 - 32, 33 + (i * 32), PF_INCASSABLEV);
      createPlatform(153 - 32, 33 + (i * 32), PF_CASSABLEV);
      createPlatform(225 - 32, 33 + (i * 32), PF_CASSABLEV);
      createPlatform(297 - 32, 33 + (i * 32), PF_INCASSABLEV);
    }
    player.posx = player.posx + 64 + 32 + 16;
    i = createBall(197 + 8, 20, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(197 - 64, 20, BIG, RIGHT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
    i = createBall(197 - 64 - 64, 20, BIG, LEFT, DOWN);
    ball[i].bonus = getRandomBonus();
    ball[i].bonus_parent = getRandomBonus();
  }
}
