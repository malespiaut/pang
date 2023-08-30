#include "ball.h"
#include "gfx.h"
#include "structures.h"

int
checkBallCollisionWithBorder(int i)
{
  int isCollide = 0;
  /* Collision avec le bas ? */
  if (ball[i].posy >= 200 - images[sprite[ball[i].spriteno].image].imageh)
  {
    ball[i].vel = ball[i].vel_cst;
    ball[i].posy = 200 - images[sprite[ball[i].spriteno].image].imageh;
    isCollide = 1;
  }

  /* Collision avec le haut ? */
  if (ball[i].posy < 8)
  {
    ball[i].posy = 8;
    isCollide = 1;
  }

  /* Gauche */
  if (ball[i].posx <= 8)
  {
    ball[i].move = -ball[i].move;
    ball[i].posx = 8;
    isCollide = 1;
  }

  /* Droite */
  if (ball[i].posx >= (320 - 8) - images[sprite[ball[i].spriteno].image].imagel)
  {
    ball[i].move = -ball[i].move;
    ball[i].posx = (320 - 8) - images[sprite[ball[i].spriteno].image].imagel;
    isCollide = 1;
  }

  return isCollide;
}

int
isCollide(int XRectangle1, int YRectangle1, int HRectangle1, int LRectangle1, int XRectangle2, int YRectangle2, int HRectangle2, int LRectangle2)
{
  if (XRectangle1 + LRectangle1 < XRectangle2)
    return (0);
  if (XRectangle1 > XRectangle2 + LRectangle2)
    return (0);
  if (YRectangle1 + HRectangle1 < YRectangle2)
    return (0);
  if (YRectangle1 > YRectangle2 + HRectangle2)
    return (0);

  return (1);
}
