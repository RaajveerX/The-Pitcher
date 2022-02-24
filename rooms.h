#include "items.h"

#define MAX_CHARACTER 5

//Room structure that the 9x9 gameboard would utilize
struct Room {
  char* name;
  struct Room* north;
  struct Room* south;
  struct Room* east;
  struct Room* west;
  struct Item* itemList;
  struct Avatar* characters;
  char *description;
};

void add_character( struct Avatar** charList, char* charName );
