#include "items.c"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>



void add_character( struct Avatar** charList, char* charName ) {
   struct Avatar* new_char = (struct Avatar*)malloc(sizeof( struct Avatar ));
   new_char->name = charName;
   new_char->next = (*charList);
   (*charList) = new_char;
}

char* remove_character( struct Avatar** charList, char* toDelete ) {

   if ( charList == NULL ) { return NULL; }
   struct Avatar *cur,*prev;
   cur = *charList;
   if ( strcmp(cur->name,toDelete) == 0 ) { *charList = cur->next; free(cur); return toDelete; } //in case of one node

   while( cur!= NULL && strcmp(cur->name,toDelete) != 0 ) {
      prev = cur;
      cur  = cur->next;
   }

   if ( cur == NULL ) { return NULL; } // element not found
   prev->next = cur->next;
   free(cur);
   return toDelete;
}

bool search_characters( struct Avatar** charList, char* toFind ) {

   if ( charList == NULL ) { return false; }
   struct Avatar* cur = (*charList);
   while(cur != NULL ) {
      if ( strcmp(cur->name, toFind ) == 0 ) { return true; }
      cur = cur->next;
   }
   return false;
}

void print_characters( struct Avatar** charList ) {
   struct Avatar* tracker = *charList;
   printf("Characters in this room: ");
   while ( tracker != NULL ) { printf("%s", (*charList)->name); tracker = tracker->next;}
   printf("\n");
}

void print_description( struct Room** room ) {
   printf("\n%s\n",(*room)->description);
   print_characters(&((*room)->characters));
   print_items(&((*room)->itemList));
   printf("\n");
}

//Allocates and initializes a room based on the given name.
struct Room* allocate_room(char* name){
   struct Room* new_room =  (struct Room*)malloc(sizeof(struct Room));
   if ( strcmp(name, "Bedroom1\n")==0 ) {
      new_room->name = "Bedroom1\n";
      new_room->itemList = allocate_itemlist("none");
      new_room->characters = allocate_avlist("Fiance\n");
      new_room->description = "Bedroom1: Fiance's work room, Art room is to the south and Bedroom2 is to the east\n";
   }
   else if ( strcmp( name, "Bedroom2\n")==0 ){
      new_room->name = "Bedroom2\n";
      new_room->itemList = allocate_itemlist("Tea\n");
      new_room->characters = allocate_avlist("none");
      new_room->description = "Bedroom2: There is some Tea kept on the table beside the bed, Living room is to the south, Bedroom1 is to the west and Bedroom3 is to the east\n";
   }
   else if ( strcmp( name, "Bedroom3\n")==0 ){
      new_room->name = "Bedroom3\n";
      new_room->itemList = allocate_itemlist("Paper\n");
      new_room->characters = allocate_avlist("Snorlax\n");
      new_room->description = "Bedroom3: Empty room with colourful walls, Gaming room is to the south and Bedroom 2 is to the west\n";
   }
   else if ( strcmp( name, "Art room\n")==0 ){
      new_room->name = "Art room\n";
      new_room->itemList = allocate_itemlist("Pen\n");
      new_room->characters = allocate_avlist("none");
      new_room->description = "Art room: Art and art equipment everywhere, Bedroom1 is the north,Tool room is to the south and the Living room is to the east\n"; 
   } 
   else if ( strcmp( name, "Living room\n")==0){
      new_room->name = "Living room\n";
      new_room->itemList = allocate_itemlist("Pitchdeck\n");
      new_room->characters = allocate_avlist("none");
      new_room->description = "Living room: There is a safe kept on the showcase,Art room is to the west, Gaming room is to the east, Bedroom2 is to the north, Kitchen is to the south\n";
   }
   else if ( strcmp( name, "Gaming room\n")==0){
      new_room->name = "Gaming room\n";
      new_room->itemList = allocate_itemlist("none");
      new_room->characters = allocate_avlist("Genie\n");
      new_room->description ="Gaming room: The best room in this house packed with futuristic gaming equipment. Bedroom3 is to the north, the Doorway is to the south and the Living room is to the west\n";
   }
   else if ( strcmp( name, "Tool room\n")==0 ){
      new_room->name = "Tool room\n";
      new_room->itemList = allocate_itemlist("CKey\n");
      new_room->characters = allocate_avlist("Bob the Builder\n");
      new_room->description = "Tool room: A mini home depot, you can find anything here, Art room is to the north and Kitchen is to the east\n";
   }
   else if ( strcmp( name, "Kitchen\n")==0 ) {
      new_room->name = "Kitchen\n";
      new_room->itemList = allocate_itemlist("none");
      new_room->characters = allocate_avlist("none");
      new_room->description = "Ahh, the Kitchen. This is where delicious indian food is made everyday. You can use the stove to make some Tea. Tool room is to the west, Living room is to the north and Doorway is to the east\n";
   }
   else if ( strcmp( name, "Doorway\n")==0 ) {
      new_room->name = "Doorway\n";
      new_room->itemList = allocate_itemlist("SKey\n");
      new_room->characters = allocate_avlist("Lighning McQueen\n");
      new_room->description = "The entrance to a wonderful house. Kitchen is to your west and Gaming room is to your north";
   }
   return new_room;
}
