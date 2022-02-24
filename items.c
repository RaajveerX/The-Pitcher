#include "rooms.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

//Add item to a given list.
void add_item( struct Item** itemList, char* itemName ) {
   struct Item* new_item = (struct Item*)malloc(sizeof( struct Item ));
   new_item->name = itemName;
   new_item->next = (*itemList);
   (*itemList) = new_item;
}

//Remove the specified item from the list.
char* remove_item( struct Item** itemList, char* toDelete ) {

   if ( itemList == NULL ) { return NULL;}
   struct Item *cur,*prev;
   cur = (*itemList);
   if ( strcmp(cur->name,toDelete) == 0 ) { (*itemList) = cur->next; free(cur); return toDelete; }

   while( cur!= NULL && strcmp(cur->name,toDelete) != 0 ) {
      prev = cur;
      cur  = cur->next;
   }
   if ( cur == NULL ) { return NULL; } 
   prev->next = cur->next;
   free(cur);
   return toDelete;
}

//Returns true if the given item is in the given list, false otherwise.
bool search_item( struct Item** itemList, char* toFind ) {

   if ( itemList == NULL ) { return false; }
   struct Item* cur = *itemList;
   while(cur != NULL ) {
      if ( strcmp(cur->name, toFind ) == 0 ) { return true; }
      cur = cur->next;
   }
   return false;
}

//Print the items present in the given list.
void print_inv( struct Item** itemList ) {
   if ( (*itemList) == NULL ) { printf("Inventory Empty!\n"); }
   struct Item *tracker = (*itemList);
   printf( "Items in inventory:");
   while ( tracker != NULL ) {
      printf("%s", tracker->name );
      tracker = tracker->next;
   }
   printf("\n");
}

void print_items( struct Item** itemList ) {
   if ( itemList == NULL ) { printf("None!\n"); }
   struct Item* tracker = *itemList;
   printf("Items in this room:");
   while ( tracker != NULL ) { printf("%s", tracker->name); tracker = tracker->next; }
  printf("\n");
}

//Allocates a linked list of avatars given the initial value.
struct Avatar* allocate_avlist(char* initial){
   struct Avatar* newAv = (struct Avatar*)malloc(sizeof(struct Avatar));
   newAv = NULL;
   if ( strcmp(initial, "none")!=0) { add_character(&newAv,initial);}
   return newAv;
}

//Allocates a linked list of items given the initial value.
struct Item* allocate_itemlist(char* initial){
   struct Item* newIt = (struct Item*)malloc(sizeof(struct Item));
   newIt = NULL;
   if ( strcmp( initial, "none")!=0){ add_item(&newIt, initial);} 
   return newIt;
}
