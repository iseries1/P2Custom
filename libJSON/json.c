/**
 * @brief Convert Json data to values
 * @author Michael Burmeister
 * @date December 29, 2018
 * @version 1.5
 * 
*/

#include <stdlib.h>
#include <propeller.h>
#include "json.h"

short json_getItem(void);

char ItemName[64];
char ItemValue[64];
char ItemPath[15][24];
short ItemLevel;
short ItemPointer;
short ItemArray;
short Arrays[16];
char ItemT[64];
char *ItemData;
char ItemE[64];
char Quote = '\"';
char jStart = '{';
char jEnd = '}';
int _Length;
char quote = 0;

void json_init(char *d)
{
  ItemLevel = 0;
  ItemPointer = 0;
  ItemArray = 0;
  ItemE[0] = 0;
  ItemT[0] = 0;
  ItemData = d;
  _Length = strlen(ItemData)-1;
  Arrays[0] = 0;
  quote = 0;
}  

char *json_find(char *e)
{
  while (json_getItem() > 0)
  {
    if (strcmp(e, ItemName) == 0)
      return ItemValue;
  }
  return "N/A";
}

short json_getItem()
{
  int i = 0;
  int Parse = 1;
  quote = 0;
  while (Parse)
  {
    if (ItemPointer++ >= _Length)
      return 0;
    switch (ItemData[ItemPointer])
    {
      case '{':
        if ((ItemE[0] > 0) && (quote == 0))
          strcpy(ItemPath[ItemLevel++], ItemE);
        break;
      case '\"':
        if (quote == 0)
          i = 0;
        quote = 1 - quote;
        break;
      case ':':
        if (quote == 0)
        {
          strcpy(ItemE, ItemT);
          ItemName[0] = 0;
          for (i=0;i<ItemLevel;i++)
          {
            strcat(ItemName, ItemPath[i]);
            strcat(ItemName, ".");
          }
          strcat(ItemName, ItemE);
          i = 0;
        }
        else
        {
          ItemT[i++] = ItemData[ItemPointer];
          ItemT[i] = 0;
          if (i > 63)
            i = 62;
        }                    
        break;
      case '}':
        if (quote != 0)
          break;
        if (ItemLevel > Arrays[ItemArray])
          ItemLevel--;
        strcpy(ItemValue, ItemT);
        i = 0;
        Parse = 0;
        break;
      case ',':
        if (quote != 0)
          break;
        if (i == 0)
        {
          if (ItemArray > 0)
          {
            ItemE[0] = 0;
            //ItemLevel++;
          }
          break;
        }
        strcpy(ItemValue, ItemT);
        i = 0;
        Parse = 0;
        break;
      case '[':
        ItemArray++;
        Arrays[ItemArray] = ItemLevel + 1;
        break;
      case ']':
        Arrays[ItemArray] = 0;
        ItemArray--;
        ItemLevel--;
        break;                      
      default:
        ItemT[i++] = ItemData[ItemPointer];
        ItemT[i] = 0;
        break;
    }
  }
  return 1;    
}

int json_putStr(char *item, char *value)
{
  int i;
  
  if (quote == 0)
    ItemData[ItemPointer++] = jStart;
  else
  {
      ItemData[ItemPointer++] = ',';
      ItemData[ItemPointer++] = ' ';
  }
  
  quote = 1;
  ItemData[ItemPointer++] = Quote;
  strcpy(&ItemData[ItemPointer], item);
  ItemPointer += strlen(item);
  ItemData[ItemPointer++] = Quote;
  ItemData[ItemPointer++] = ':';
  ItemData[ItemPointer++] = Quote;
  i = strlen(value);
  for (int j=0;j<i;j++)
  {
    switch (value[j])
    {
      case '\r' :
        ItemData[ItemPointer++] = '\\';
        ItemData[ItemPointer++] = 'r';
        break;
      case '\n' :
        ItemData[ItemPointer++] = '\\';
        ItemData[ItemPointer++] = 'n';
        break;
      case '\t' :
        ItemData[ItemPointer++] = '\\';
        ItemData[ItemPointer++] = 't';
        break;
      case '\\' :
        ItemData[ItemPointer++] = '\\';
        ItemData[ItemPointer++] = '\\';
        break;
      case '\"' :
        ItemData[ItemPointer++] = '\\';
        ItemData[ItemPointer++] = '\"';
        break;
      default:
        ItemData[ItemPointer++] = value[j];
    }
  }
  ItemData[ItemPointer++] = Quote;
  ItemData[ItemPointer] = jEnd;
  ItemData[ItemPointer+1] = 0;
  return ItemPointer+1;
}

int json_putDec(char *item, char *value)
{
  if (quote == 0)
    ItemData[ItemPointer++] = jStart;
  else
  {
      ItemData[ItemPointer++] = ',';
      ItemData[ItemPointer++] = ' ';
  }
  
  quote = 1;
  ItemData[ItemPointer++] = Quote;
  strcpy(&ItemData[ItemPointer], item);
  ItemPointer += strlen(item);
  ItemData[ItemPointer++] = Quote;
  ItemData[ItemPointer++] = ':';
  strcpy(&ItemData[ItemPointer], value);
  ItemPointer += strlen(value);
  ItemData[ItemPointer] = jEnd;
  ItemData[ItemPointer+1] = 0;
  return ItemPointer+1;
}

int json_putArray(char* item)
{
    if (item == NULL)
    {
        ItemData[ItemPointer++] = jEnd;
        ItemData[ItemPointer++] = ']';
        ItemData[ItemPointer] = jEnd;
        ItemData[ItemPointer+1] = 0;
        return ItemPointer+1;
    }

    if (Quote == 0)
        ItemData[ItemPointer++] = jStart;
    else
    {
        ItemData[ItemPointer++] = ',';
        ItemData[ItemPointer++] = ' ';
    }

    quote = 0;
    ItemData[ItemPointer++] = Quote;
    strcpy(&ItemData[ItemPointer], item);
    ItemPointer += strlen(item);
    ItemData[ItemPointer++] = Quote;
    ItemData[ItemPointer++] = ':';
    ItemData[ItemPointer++] = ' ';
    ItemData[ItemPointer++] = '[';
    ItemData[ItemPointer] = jEnd;
    ItemData[ItemPointer+1] = 0;
    return ItemPointer+1;
}

int json_putObject(char* item)
{
    if (item == NULL)
    {
        ItemData[ItemPointer++] = jEnd;
        ItemData[ItemPointer] = jEnd;
        ItemData[ItemPointer+1] = 0;
        return ItemPointer+1;
    }

    if (quote == 0)
        ItemData[ItemPointer++] = jStart;
    else
    {
        ItemData[ItemPointer++] = ',';
        ItemData[ItemPointer++] = ' ';
    }

    quote = 0;
    ItemData[ItemPointer++] = Quote;
    strcpy(&ItemData[ItemPointer], item);
    ItemPointer += strlen(item);
    ItemData[ItemPointer++] = Quote;
    ItemData[ItemPointer++] = ':';
    ItemData[ItemPointer++] = ' ';
    ItemData[ItemPointer] = jEnd;
    ItemData[ItemPointer+1] = 0;
    return ItemPointer+1;
}

int json_putMore()
{
    ItemData[ItemPointer++] = jEnd;
    ItemData[ItemPointer++] = ',';
    ItemData[ItemPointer++] = ' ';
    ItemData[ItemPointer] = jEnd;
    ItemData[ItemPointer+1] = 0;
    quote = 0;
    return ItemPointer+1;
}

int json_putItem(char* item)
{
  
  if (quote != 0)
  {
      if (item == NULL)
      {
        ItemData[ItemPointer++] = ']';
        ItemData[ItemPointer] = jEnd;
        ItemData[ItemPointer+1] = 0;
        quote = 0;
        return ItemPointer+1;
      }
      ItemData[ItemPointer++] = ',';
      ItemData[ItemPointer++] = ' ';
  }
  
  ItemData[ItemPointer++] = Quote;
  strcpy(&ItemData[ItemPointer], item);
  ItemPointer += strlen(item);
  ItemData[ItemPointer++] = Quote;
  ItemData[ItemPointer] = ' ';
  ItemData[ItemPointer+1] = 0;
  quote = 1;
  return ItemPointer+1;
}

int json_putBool(char* item, int state)
{
  if (quote == 0)
    ItemData[ItemPointer++] = jStart;
  else
  {
      ItemData[ItemPointer++] = ',';
      ItemData[ItemPointer++] = ' ';
  }
  
  quote = 1;
  ItemData[ItemPointer++] = Quote;
  strcpy(&ItemData[ItemPointer], item);
  ItemPointer += strlen(item);
  ItemData[ItemPointer++] = Quote;
  ItemData[ItemPointer++] = ':';
  if (state == 0)
    strcpy(&ItemData[ItemPointer], "false");
  else
    strcpy(&ItemData[ItemPointer], "true ");

  ItemPointer += 5;
  ItemData[ItemPointer] = jEnd;
  ItemData[ItemPointer+1] = 0;
  return ItemPointer+1;
}
