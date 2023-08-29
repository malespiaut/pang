#include "gfx.h"
#include "main.h"
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
      blitBMPImageToScreen(1, ((*string - 48) * 14) + positionxduzero, positionyduzero, 13, 13, x + (i * 13), y, 13, 13, 320, 240);
    }
    else
    {
      blitBMPImageToScreen(1, ((*string - 48) * 14) + positionxduzero + 1, positionyduzero, 13, 13, x + (i * 13), y, 13, 13, 320, 240);
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
  obj[i].posx = x;
  obj[i].posy = y;
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
        blitBMPImageToScreen(1, 247, 90, 7, 9, obj[i].posx, obj[i].posy, 7, 9, 320, 240);

        showNumber(chaine, obj[i].posx + 8, obj[i].posy);

        obj[i].posy--;
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
        blitBMPImageToScreen(1, 240, 12, 21, 13, obj[i].posx, obj[i].posy, 21, 13, 320, 240);
        obj[i].cpt--;
        obj[i].posy--;
      }
      else
      {
        obj[i].active = 0;
      }
    }
  }
}
