#include "ball.h"
#include "bonus.h"
#include "collisions.h"
#include "gfx.h"
#include "objects.h"
#include "platform.h"
#include "shoot.h"
#include "sound.h"
#include "structures.h"

Ball ball[MAX_BALL];

void
showBall(int i)
{
  if (ball[i].active)
  {
    sprite_move(ball[i].spriteno, (int)ball[i].x, (int)ball[i].y);
    sprite_id_set(ball[i].spriteno, ball[i].type);
    sprite_blit(ball[i].spriteno);
  }
}

/*
  Renvoie TOUCH_HORIZONTAL ou TOUCH_VERTICAL pour savoir si
  la balle à touché une plateforme sur le coté ou sur les surfaces horizontales
  sprite1 = sprite de la balle numéro b
  sprite2 = sprite de la plateforme
  b = n° de la balle
*/
int
ballCollideWithPlatform(int sprite1, int sprite2, int b)
{
  int collided = 0;
  int rect1_x, rect1_y;
  int rect2_x, rect2_y;
  int i, j, k, l;
  int coorx_1 = g_sprites[sprite1].x;
  int coory_1 = g_sprites[sprite1].y;
  int coorx_2 = g_sprites[sprite2].x;
  int coory_2 = g_sprites[sprite2].y;
  int sprite1w = g_images[g_sprites[sprite1].index].width;
  int sprite1h = g_images[g_sprites[sprite1].index].height;
  int sprite2w = g_images[g_sprites[sprite2].index].width;
  int sprite2h = g_images[g_sprites[sprite2].index].height;

  if (!g_sprites[sprite1].active)
    return 0;
  if (!g_sprites[sprite2].active)
    return 0;

  /*Détection par bounding box
  Retourne 0 et sort de la fonction
  si les sprites ne possédent pas de zones superposées*/
  if (coorx_1 > coorx_2 + g_images[g_sprites[sprite2].index].width)
    return 0;
  if (coorx_1 + g_images[g_sprites[sprite1].index].width < coorx_2)
    return 0;
  if (coory_1 > coory_2 + g_images[g_sprites[sprite2].index].height)
    return 0;
  if (coory_1 + g_images[g_sprites[sprite1].index].height < coory_2)
    return 0;

  /*Le but des lignes suivantes est de définir un
  rectangle qui englobe la zone d'affichage
  commune aux deux sprites
  On traite les coordonnées x du rectangle*/

  if (coorx_1 < coorx_2)
  {
    rect1_x = coorx_2;
    if (coorx_1 + sprite1w >= coorx_2 + sprite2w)
      rect2_x = coorx_2 + sprite2w;
    else
      rect2_x = coorx_1 + sprite1w;
  }
  else
  {
    rect1_x = coorx_1;
    if (coorx_2 + sprite2w >= coorx_1 + sprite1w)
      rect2_x = coorx_1 + sprite1w;
    else
      rect2_x = coorx_2 + sprite2w;
  }

  /*On traite les coordonnées y du rectangle*/
  if (coory_1 < coory_2)
  {
    rect1_y = coory_2;
    if (coory_1 + sprite1h >= coory_2 + sprite2h)
      rect2_y = coory_2 + sprite2h;
    else
      rect2_y = coory_1 + sprite1h;
  }
  else
  {
    rect1_y = coory_1;
    if (coory_2 + sprite2h > coory_1 + sprite1h)
      rect2_y = coory_1 + sprite1h;
    else
      rect2_y = coory_2 + sprite2h;
  }

  if (SDL_MUSTLOCK(g_images[g_sprites[sprite1].index].surface))
    SDL_LockSurface(g_images[g_sprites[sprite1].index].surface);
  if (SDL_MUSTLOCK(g_images[g_sprites[sprite2].index].surface))
    SDL_LockSurface(g_images[g_sprites[sprite2].index].surface);

  /*Il ne reste plus qu'à tester pour chaque

  pixel du rectangle précèdemment défini si ses pixels

  sont transparents

  Un pixel non transparent signifie qu'un bout de sprite

  est present dans le rectangle

  et donc que les sprites sont en collision*/

  for (i = rect1_x - coorx_1, j = rect1_x - coorx_2; i < rect2_x - coorx_1; i++, j++)
  {
    for (k = rect1_y - coory_1, l = rect1_y - coory_2; k < rect2_y - coory_1; k++, l++)
    {

      if ((CollideTransparentPixelTest(g_images[g_sprites[sprite1].index].surface, i, k) != 0) && (CollideTransparentPixelTest(g_images[g_sprites[sprite2].index].surface, j, l)) != 0)
      {
        if (SDL_MUSTLOCK(g_images[g_sprites[sprite1].index].surface))
          SDL_UnlockSurface(g_images[g_sprites[sprite1].index].surface);
        if (SDL_MUSTLOCK(g_images[g_sprites[sprite2].index].surface))
          SDL_UnlockSurface(g_images[g_sprites[sprite2].index].surface);

        collided = 1;
      }
    }
  }

  if (SDL_MUSTLOCK(g_images[g_sprites[sprite1].index].surface))
    SDL_UnlockSurface(g_images[g_sprites[sprite1].index].surface);
  if (SDL_MUSTLOCK(g_images[g_sprites[sprite2].index].surface))
    SDL_UnlockSurface(g_images[g_sprites[sprite2].index].surface);

  int lfinal = rect2_x - rect1_x;
  int hfinal = rect2_y - rect1_y;

  int ligne;    /* 0 - egalite 1 - horizontal  2 - vertical */
  int cote = 0; /* 3 -gauche 4 - droite */

  if (collided == 1)
  {

    if (lfinal < hfinal)
      ligne = 2;
    else if (lfinal > hfinal)
      ligne = 1;
    else
      ligne = 0;

    /* Coté droit ou gauche ? */
    if (ligne == 2)
    {
      if (rect1_x == g_sprites[sprite2].x)
        cote = 3;
      else
        cote = 4;
    }
  }
  else
  {
    return 0;
  }

  /* si la balle va à droite*/
  if (ball[b].move > 0)
  {
    if (cote == 4)
      return TOUCH_HORIZONTAL; /* elle touche un coté droit */
    if (cote == 3)
      return TOUCH_VERTICAL;
  }
  else
  {
    if (cote == 3)
      return TOUCH_HORIZONTAL;
    if (cote == 4)
      return TOUCH_VERTICAL;
  }

  if (ligne == 1)
    return TOUCH_HORIZONTAL;
  if (ligne == 2)
    return TOUCH_VERTICAL;

  if (ligne == 0)
    return TOUCH_VERTICAL;

  /* D'après les tests fait plus haut ya forcément une collision; mais bon on en renvoie une par défaut */
  return TOUCH_VERTICAL;
}

/*
   Teste les collisions avec les bords de l'écran
*/

void
initBalls()
{
  int i;
  for (i = 0; i < MAX_BALL; i++)
  {
    ball[i].active = 0;
  }
}

void
explodeABall(int a)
{
  sound_play(kSound_BallPop, 1);
  /* Crée une nouvelle balle plus petite qui ira à gauche */
  int tmp2;
  tmp2 = createBall(ball[a].x, ball[a].y, ball[a].type + 1, LEFT, UP);
  ball[tmp2].hauteurmax_cpt = ball[tmp2].hauteurmax - (20);
  ball[tmp2].vel = 2.0;
  if (ball[a].bonus_parent != 0)
    ball[tmp2].bonus = ball[a].bonus_parent;
  /* Crée une nouvelle balle plus petite qui ira à droite */
  tmp2 = createBall(ball[a].x, ball[a].y, ball[a].type + 1, RIGHT, UP);
  ball[tmp2].hauteurmax_cpt = ball[tmp2].hauteurmax - (20);
  ball[tmp2].vel = 2.0;
  /* Si la balle <a> qui explose contient un bonus, on le crée */
  if (ball[a].bonus != 0)
  {
    createBonus(ball[a].bonus, (int)ball[a].x + 10, (int)ball[a].y + 10);
  }
  /* On libère la balle (et le sprite associé) qui vient d'exploser */
  ball[a].active = 0;
  sprite_free_set(ball[a].spriteno);
}

void
explodeAllBall()
{
  /* On trouve une grosse boule, si elle existe on l'explose */
  int sortie = 0;
  int trouve = -1;
  int b = 0;
  while (sortie == 0)
  {
    if ((ball[b].type == BIG) && (ball[b].active))
    {
      trouve = b;
      sortie = 1;
    }
    b++;
    if (b == MAX_BALL)
      sortie = 1;
  }

  /* Si on l'a trouvé, on l'explose ! */
  if (trouve != -1)
  {
    /* BOOM */
    explodeABall(trouve);
  }
  else /* Sinon on continue de chercher pour une normale */
  {
    b = 0;
    sortie = 0;
    while (sortie == 0)
    {
      if ((ball[b].type == NORMAL) && (ball[b].active))
      {
        trouve = b;
        sortie = 1;
      }
      b++;
      if (b == MAX_BALL)
        sortie = 1;
    }

    if (trouve != -1)
    {
      /* BOOM */
      explodeABall(trouve);
    }
    else
    {
      b = 0;
      sortie = 0;
      while (sortie == 0)
      {
        if ((ball[b].type == SMALL) && (ball[b].active))
        {
          trouve = b;
          sortie = 1;
        }
        b++;
        if (b == MAX_BALL)
          sortie = 1;
      }
      if (trouve != -1)
      {
        /* BOOM */
        explodeABall(trouve);
      }
      else
      {
        /* Plus rien à exploser */
        player.bonus_boom = 0;
      }
    }
  }
}

int
createBigBall(float x, float y, int hdirection, int vdirection)
{
  int i;
  i = 0;
  while ((ball[i].active) && (i < MAX_BALL))
  {
    i++;
  }

  ball[i].x = x;
  ball[i].y = y;
  ball[i].hauteurmax = 180;
  ball[i].hauteurmax_cpt = 160;
  ball[i].speedx = 1;
  ball[i].speedy = 3;
  ball[i].lr = RIGHT;
  ball[i].ud = DOWN;
  ball[i].coefdivaccell = 10;
  ball[i].speed_cpt = 0;
  ball[i].active = 1;
  ball[i].xbox = 6;
  ball[i].ybox = 4;
  ball[i].hbox = (40 - 6);
  ball[i].lbox = (48 - 10);
  ball[i].type = BIG;
  ball[i].suspend = 0;
  ball[i].bonus = 0;
  ball[i].bonus_parent = 0;
  ball[i].spriteno = sprite_init_free((int)ball[i].x, (int)ball[i].y, BIG);
  ball[i].last_x = x;
  ball[i].last_y = y;

  ball[i].vel = -10.0;
  ball[i].vel_cst = 12.5;
  ball[i].move = 2;

  if (hdirection == LEFT)
  {
    ball[i].lr = LEFT;
    ball[i].move = -ball[i].move;
  }
  if (vdirection == UP)
  {
    ball[i].ud = UP;
    ball[i].vel = -ball[i].vel;
  }

  ball[i].nbtouch = 0;
  ball[i].y_a_til_eu_collision_avant = 0;

  return i;
}

int
createNormalBall(float x, float y, int hdirection, int vdirection)
{
  int i;
  i = 0;
  while ((ball[i].active) && (i < MAX_BALL))
  {
    i++;
  }

  ball[i].x = x;
  ball[i].y = y;
  ball[i].hauteurmax = 120;
  ball[i].hauteurmax_cpt = 100;
  ball[i].speedx = 1;
  ball[i].speedy = 3;
  ball[i].lr = RIGHT;
  ball[i].ud = DOWN;
  ball[i].coefdivaccell = 20;
  ball[i].speed_cpt = 0;
  ball[i].active = 1;
  ball[i].xbox = 3;
  ball[i].ybox = 3;
  ball[i].hbox = (26 - 6);
  ball[i].lbox = (32 - 6);
  ball[i].type = NORMAL;
  ball[i].suspend = 0;
  ball[i].bonus = 0;
  ball[i].bonus_parent = 0;
  ball[i].spriteno = sprite_init_free((int)x, (int)y, NORMAL);

  ball[i].vel = -10.0;
  ball[i].vel_cst = 10.0;
  ball[i].move = 2;

  ball[i].last_x = x;
  ball[i].last_y = y;

  if (hdirection == LEFT)
  {
    ball[i].lr = LEFT;
    ball[i].move = -ball[i].move;
  }
  if (vdirection == UP)
  {
    ball[i].ud = UP;
    ball[i].vel = -ball[i].vel;
  }
  ball[i].nbtouch = 0;
  ball[i].y_a_til_eu_collision_avant = 0;
  return i;
}

int
createSmallBall(float x, float y, int hdirection, int vdirection)
{
  int i;
  i = 0;
  while ((ball[i].active) && (i < MAX_BALL))
  {
    i++;
  }

  ball[i].x = x;
  ball[i].y = y;
  ball[i].hauteurmax = 80;
  ball[i].hauteurmax_cpt = 60;
  ball[i].speedx = 1;
  ball[i].speedy = 3;
  ball[i].lr = RIGHT;
  ball[i].ud = DOWN;
  ball[i].coefdivaccell = 30;
  ball[i].speed_cpt = 0;
  ball[i].active = 1;
  ball[i].xbox = 1;
  ball[i].ybox = 1;
  ball[i].hbox = (14 - 3);
  ball[i].lbox = (16 - 3);
  ball[i].type = SMALL;
  ball[i].suspend = 0;
  ball[i].bonus = 0;
  ball[i].bonus_parent = 0;
  ball[i].spriteno = sprite_init_free((int)ball[i].x, (int)ball[i].y, SMALL);

  ball[i].vel = -8.0;
  ball[i].vel_cst = 8.0;
  ball[i].move = 2;

  ball[i].last_x = x;
  ball[i].last_y = y;

  if (hdirection == LEFT)
  {
    ball[i].lr = LEFT;
    ball[i].move = -ball[i].move;
  }
  if (vdirection == UP)
  {
    ball[i].ud = UP;
    ball[i].vel = -ball[i].vel;
  }
  ball[i].nbtouch = 0;
  ball[i].y_a_til_eu_collision_avant = 0;
  return i;
}

int
createMicroBall(float x, float y, int hdirection, int vdirection)
{
  int i;

  i = 0;
  while ((ball[i].active) && (i < MAX_BALL))
  {
    i++;
  }

  ball[i].x = x;
  ball[i].y = y;
  ball[i].hauteurmax = 60;
  ball[i].hauteurmax_cpt = 30;
  ball[i].speedx = 1;
  ball[i].speedy = 3;
  ball[i].lr = RIGHT;
  ball[i].ud = DOWN;
  ball[i].coefdivaccell = 40;
  ball[i].speed_cpt = 0;
  ball[i].active = 1;
  ball[i].xbox = 1;
  ball[i].ybox = 1;
  ball[i].hbox = (5);
  ball[i].lbox = (6);
  ball[i].type = MICRO;
  ball[i].suspend = 0;
  ball[i].bonus = 0;
  ball[i].bonus_parent = 0;
  ball[i].spriteno = sprite_init_free((int)ball[i].x, (int)ball[i].y, MICRO);

  ball[i].vel = -6.5;
  ball[i].vel_cst = 6.5;

  ball[i].move = 2;

  ball[i].last_x = x;
  ball[i].last_y = y;

  if (hdirection == LEFT)
  {
    ball[i].lr = LEFT;
    ball[i].move = -ball[i].move;
  }
  if (vdirection == UP)
  {
    ball[i].ud = UP;
    ball[i].vel = -ball[i].vel;
  }
  ball[i].nbtouch = 0;
  ball[i].y_a_til_eu_collision_avant = 0;
  return i;
}

int
createBall(float x, float y, int typeBall, int hdirection, int vdirection)
{
  if (typeBall == BIG)
    return (createBigBall(x, y, hdirection, vdirection));
  if (typeBall == NORMAL)
    return (createNormalBall(x, y, hdirection, vdirection));
  if (typeBall == SMALL)
    return (createSmallBall(x, y, hdirection, vdirection));
  if (typeBall == MICRO)
    return (createMicroBall(x, y, hdirection, vdirection));
  return 0;
}

void
updateBalls(int i)
{
  /*
       Si (ball[i].active)
       {
          Tester si on est en collision de plateforme
          {
          }
          Tester si on est en collision de bordure
          {
          }
          Tester si on est en collision de balle
          {
          }

          Si (il n'y à pas eu de collision)
          {
              ball[i].last_x = ball[i].x;
                          ball[i].last_y = ball[i].y;
          }

          Si (le joueur n'a pas de bonus freeze)
          {
                 bouger la balle <i>
          }
       }
  */

  int p = 0;
  int sortie2 = 0;
  int collide = 0;
  int totalcollide = 0;

  int y_a_t_il_eu_collision_de_bord = 0;

  int y_a_t_il_eu_collision = 0;

  if (ball[i].active)
  {
    /* il faut récupérer la derniere position sans aucune collision
Pour cela on teste si on est en collision, si ce n'est pas le
cas, on mets à jour last_x et last_y. Sinon, on ne mets
rien à jour et on à les bonnes dernières coordonnées de la position
sans collision.
*/

    for (p = 0; p < kPlatform_COUNT; p++)
    {
      if (platforms[p].active)
      {
        collide += ballCollideWithPlatform(ball[i].spriteno, platforms[p].spriteno, i);
      }
    }

    if (collide != 0)
    {
      y_a_t_il_eu_collision = 1;
    }

    for (p = 0; p < MAX_SHOOT; p++)
    {
      if (shoot[p].active)
      {
        collide = isCollide(ball[i].xbox + (int)ball[i].x, ball[i].ybox + (int)ball[i].y, ball[i].hbox, ball[i].lbox, shoot[p].x + shoot[p].xbox, shoot[p].y + shoot[p].ybox, shoot[p].hbox, shoot[p].lbox);
        if (collide != 0)
        {
          shoot[p].active = 0;
          player.nbtir--;
          if (ball[i].type < MICRO)
          {
            int tmp;
            tmp = createBall(ball[i].x, ball[i].y, ball[i].type + 1, LEFT, UP);

            if (player.bonus_freeze > 0)
            {
              int old_x = ball[i].x;
              int old_y = ball[i].y;
              ball[tmp].x = ball[i].x + g_images[g_sprites[ball[tmp].spriteno].index].width;
              sprite_move(ball[tmp].spriteno, (int)ball[i].x + g_images[g_sprites[ball[tmp].spriteno].index].width, (int)ball[i].y);
              int plate;
              int platec = 0;
              for (plate = 0; plate < kPlatform_COUNT; plate++)
              {
                platec -= ballCollideWithPlatform(ball[tmp].spriteno, platforms[plate].spriteno, tmp);
              }
              if (platec != 0)
                sprite_move(ball[tmp].spriteno, (int)old_x, (int)old_y);
            }

            ball[tmp].hauteurmax_cpt = ball[tmp].hauteurmax - 20;
            ball[tmp].vel = 2.0;
            if (ball[i].bonus_parent != 0)
              ball[tmp].bonus = ball[i].bonus_parent;
            tmp = createBall(ball[i].x, ball[i].y, ball[i].type + 1, RIGHT, UP);
            ball[tmp].hauteurmax_cpt = ball[tmp].hauteurmax - 20;
            ball[tmp].vel = 2.0;
          }
          /* score ! */
          if (player.derniere_balle == ball[i].type)
          {
            player.multiplicateur++;
          }
          else
          {
            player.multiplicateur = 1;
          }
          if (ball[i].type == MICRO)
          {
            player.score = player.score + (4 * player.multiplicateur);
          }
          else if (ball[i].type == SMALL)
          {
            player.score = player.score + (3 * player.multiplicateur);
          }
          else if (ball[i].type == NORMAL)
          {
            player.score = player.score + (2 * player.multiplicateur);
          }
          else if (ball[i].type == BIG)
          {
            player.score = player.score + (1 * player.multiplicateur);
          }
          player.derniere_balle = ball[i].type;
          if (player.multiplicateur > 1)
          {
            createObject(OBJ_MUL, (int)ball[i].x, (int)ball[i].y, player.multiplicateur);
          }
          /* il fo détruire la balle EN DERNIER ! Sinon une autre sera reprise à ça position */
          ball[i].active = 0;
          if (ball[i].bonus != 0)
          {
            if (ball[i].bonus == BONUS_LIFE)
            {
              if ((player.bonus_life == 0) && (player.bonus_life_level != currentLevel))
              {
                createBonus(ball[i].bonus, (int)ball[i].x + 5, (int)ball[i].y + 5);
              }
            }
            else
            {
              createBonus(ball[i].bonus, (int)ball[i].x + 5, (int)ball[i].y + 5);
            }
          }
          sprite_free_set(ball[i].spriteno);
          sound_play(kSound_BallPop, 0);
        }
      }
    }

    if (player.bonus_freeze == 0)
    {
      sortie2 = 0;
      totalcollide = 0;
      p = 0;
      while (sortie2 == 0)
      {
        if (platforms[p].active)
        {
          collide = ballCollideWithPlatform(ball[i].spriteno, platforms[p].spriteno, i);
          totalcollide = collide;
          if (collide != 0)
          {
            y_a_t_il_eu_collision = 1;
            ball[i].x = ball[i].last_x;
            ball[i].y = ball[i].last_y;
            sprite_move(ball[i].spriteno, (int)ball[i].x, (int)ball[i].y);
            sortie2 = 1;
          }
        }
        p++;
        if (p == kPlatform_COUNT)
          sortie2 = 1;
      }

      if (totalcollide == TOUCH_HORIZONTAL)
      {
        ball[i].vel = -ball[i].vel;
        if (ball[i].vel == 0)
          ball[i].move = -ball[i].move;
      }

      if (totalcollide == TOUCH_VERTICAL)
      {
        ball[i].move = -ball[i].move;
      }

      y_a_t_il_eu_collision_de_bord = checkBallCollisionWithBorder(i);
      if (y_a_t_il_eu_collision_de_bord != 0)
        y_a_t_il_eu_collision = 1;

      if (y_a_t_il_eu_collision == 0)
      {
        ball[i].last_x = ball[i].x;
        ball[i].last_y = ball[i].y;
        ball[i].y_a_til_eu_collision_avant = 0;
        ball[i].nbtouch = 0;
      }
      else
      {
        if (ball[i].y_a_til_eu_collision_avant == 1)
        {
          ball[i].nbtouch++;
        }
        if (ball[i].y_a_til_eu_collision_avant == 0)
        {
          ball[i].y_a_til_eu_collision_avant = 1;
        }
      }

      if (ball[i].nbtouch > 5)
        ball[i].x = ball[i].x + ball[i].move;

      ball[i].x = ball[i].x + ball[i].move;
      ball[i].vel = ball[i].vel - GRAV;
      ball[i].y = ball[i].y - ball[i].vel;
    }
  }
}
