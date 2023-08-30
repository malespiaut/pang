#include "gfx.h"
#include "string.h"
#include "structures.h"

void
showNumber(char* string, unsigned int x, unsigned int y)

{

  unsigned char i, temp;
  int positionxduzero = 148;
  int positionyduzero = 226;

  temp = strlen(string);
  for (i = 0; i < temp; i++)
  {
    if (((*string - 48) * 13) == 0)
    {
      bmp_blit(1, ((*string - 48) * 14) + positionxduzero, positionyduzero, 13, 13, x + (i * 13), y, 13, 13);
    }
    else
    {
      bmp_blit(1, ((*string - 48) * 14) + positionxduzero + 1, positionyduzero, 13, 13, x + (i * 13), y, 13, 13);
    }

    string++;
  }
}

void
initObjects()
{
  int i;
  for (i = 0; i < MAX_OBJECTS; i++)
  {
    obj[i].active = 0;
  }
}

void
createObject(int type, int x, int y, int value)
{

  int i;
  i = 0;
  while ((obj[i].active) && (i < MAX_OBJECTS))
  {
    i++;
  }

  obj[i].type = type;
  obj[i].x = x;
  obj[i].y = y;
  obj[i].value = value;
  obj[i].active = 1;

  if (type == OBJ_MUL)
  {
    obj[i].cpt = 20;
  }
  else if (type == OBJ_1UP)
  {
    obj[i].cpt = 100;
  }
  else if ((type == OBJ_EXPL_BIG) || (type == OBJ_EXPL_NORMAL) || (type == OBJ_EXPL_SMALL) || (type == OBJ_EXPL_MICRO))
  {
    obj[i].cpt = 20;
  }
}

void
showObject(int i)
{

  if (obj[i].active)
  {
    if (obj[i].type == OBJ_MUL)
    {
      if (obj[i].cpt > 0)
      {
        char chaine[3];
        sprintf(chaine, "%d", obj[i].value);
        bmp_blit(1, 247, 90, 7, 9, obj[i].x, obj[i].y, 7, 9);

        showNumber(chaine, obj[i].x + 8, obj[i].y);

        obj[i].y--;
        obj[i].cpt--;
      }
      else
      {
        obj[i].active = 0;
      }
    }
    else if (obj[i].type == OBJ_1UP)
    {
      if (obj[i].cpt > 0)
      {
        bmp_blit(1, 240, 12, 21, 13, obj[i].x, obj[i].y, 21, 13);
        obj[i].cpt--;
        obj[i].y--;
      }
      else
      {
        obj[i].active = 0;
      }
    }
  }
}
