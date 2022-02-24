#include <stdio.h>
#include "rooms.c"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>


int main(){

   //9x9 Game Board initialization. 
   struct Room* bed1 = allocate_room("Bedroom1\n");
   struct Room* bed2 = allocate_room("Bedroom2\n");
   struct Room* bed3 = allocate_room("Bedroom3\n");
   struct Room* art =  allocate_room("Art room\n");
   struct Room* living = allocate_room("Living room\n");
   struct Room* gaming = allocate_room("Gaming room\n"); 
   struct Room* tools = allocate_room("Tool room\n");
   struct Room* kitchen = allocate_room("Kitchen\n");
   struct Room* doorway = allocate_room("Doorway\n");
  
   //POINTER NETWORK FOR ALL THE ROOMS ( North, South, East, West ).
   bed1->north = NULL; bed1->south = art; bed1->east = bed2; bed1->west = NULL;
   bed2->north = NULL; bed2->south = living; bed2->west = bed1; bed2->east = bed3;
   bed3->north = NULL; bed3->south = gaming; bed3->east = NULL; bed3->west = bed2;
   art->north = bed1; art->south = tools; art->east = living; art->west = NULL;
   living->north = bed2; living->south = kitchen; living->west = art; living->east = gaming;
   gaming->north = bed3; gaming->south = doorway; gaming->west = living; gaming->east = NULL;
   tools->north = art; tools->south = NULL; tools->west = NULL; tools->east = kitchen;
   kitchen->north = living; kitchen->south = NULL; kitchen->west = tools; kitchen->east = doorway;
   doorway->north = gaming; doorway->south = NULL; doorway->west = kitchen; doorway->east = NULL;

   //Attributes for the Player
   struct Room* current = bed2; //Start in bedroom2.
   struct Item* userInv = allocate_itemlist("none"); //Player's own inventory

   //Game Attributes
   bool safeLocked = true;

   //Linked list of all the characters/Avatars in this game
   struct Avatar* characters = allocate_avlist("Fiance\n");
   add_character( &characters, "Snorlax\n" ); 
   add_character( &characters, "Genie\n" ); 
   add_character( &characters, "Bob the Builder\n");
   add_character( &characters, "Lightning McQueen\n" );
   int numberofpitches = 0;




   //Game Introduction 1
   printf("\nWelcome to the pitcher. use the commands: help and list to get more information!\n\n");
   printf("Oh no! It's 8:00 am already, I am supposed to pitch my startup idea to an investor in an hour, should not have partied last night\n");
   printf("\n");
   printf("I better leave now, I don't have time to get ready\n");
   printf("\n");
   printf("type doorway to run to the doorway\n\n");

   char input[100]; //character buffer for fgets.

   printf( " --> " );
   do{
   fgets(input,sizeof(input),stdin);
   if ( strcmp(input, "doorway\n") != 0 ) { 
      printf("\nI don't have time to explore,I need to leave now!\n");
      printf("type doorway to run to the doorway\n\n");
      printf( " --> " );
   }
   }while( strcmp(input, "doorway\n") != 0 );

   current = doorway; //switch current room position to doorway.

   //Game Introduction 2
   printf(".\n.\n.\n");
   printf("*You get in the car*\n");
   printf(".\n.\n");
   printf("Oh no, I forgot I kept all my documents that I need for the pitch in a safe in the living room, I can't seem to recall the code, I drank a lot yesterday night.\n");
   printf(".\n.\n");
   printf("*You get out of the car*\n");
   printf(".\n.\n");
   printf("OBJECTIVE: Figure out the code and leave as soon as possible!\n");
   printf(".\n.\n.\n");

   char newinput[100]; //buffer for the main while loop.
   print_description(&current);
   printf( " --> " );

   //Main input loop
   while (fgets(newinput,sizeof(newinput), stdin) != NULL ){

      if ( strcmp(newinput,"look\n") == 0){
         print_description(&current);
         printf("\n --> ");
         continue;
      }
      else if ( strcmp(newinput,"go\n")==0){

         char insiderinput[10];
         printf("where would you like to go ? - - >  ");

         while ( fgets(insiderinput, sizeof(insiderinput), stdin) != NULL ){
            if ( strcmp(insiderinput, "north\n" ) ==0 ){
               if ( current->north == NULL ) { printf("That is not a valid direction\n"); continue; }
               current = current->north; print_description(&current); break;
            }
            else if ( strcmp(insiderinput, "south\n") ==0 ) {
               if ( current->south == NULL ) { printf("That is not a valid direction\n"); continue; }
               current = current->south; print_description(&current); break;
            }

             else if ( strcmp(insiderinput, "east\n")==0){
                if ( current->east == NULL ) { printf("That is not a valid direction\n"); continue; }
                current = current->east; print_description(&current); break;
             }
             else if ( strcmp(insiderinput, "west\n")==0){
                if ( current->west = NULL ) { printf("That is not a valid direction\n"); continue; }
                current = current->west; print_description(&current); break;
             }
             else { printf("Unable to recognize command"); continue; }
          }
          printf("\n --> ");
      }
      else if ( strcmp(newinput,"help\n")==0){
         printf("Here are the commands you can use:\n");
         printf("look: Look around the room you are currently in\n");
         printf("go: to move towards a direction\n");
         printf("take: take an item into your inventory\n");
         printf("drop: drop an item from your inventory\n");
         printf("inventory: check items in your inventory\n");
         printf("pitch: Once ready, you can try leaving your house in the game ( If you have all the required items you win\n");
         printf("interact: There are multiple objects you can interact with\n");
         printf("\n --> ");
      }
      else if ( strcmp(newinput, "list\n") == 0 ) {
         printf("Items: Paper, Pen, CKey, GKey, Pitchdeck Tea\n");
         printf("Rooms: Bedroom1, Bedroom2, Bedroom3, Art room, Living room, Gaming room, Tools room, Kitchen, Doorway\n");
         printf("Characters: Snorlax, Fiance, Genie, Lightning McQueen, Bob the Builder\n");
         printf("\n --> ");
      }
      else if ( strcmp(newinput,"take\n")==0){
         char itemtaken[20];
         printf("What would you like to take ?: ");
         while( fgets(itemtaken, sizeof(itemtaken), stdin) != NULL ) {
            bool itemExists = search_item( &(current->itemList), itemtaken );
            if ( itemExists ) {
               if ( strcmp(itemtaken, "Pitchdeck\n" ) == 0 && !safeLocked ) { printf("The pitchdeck is inside the safe, I need to open that first\n"); break; }
               add_item( &userInv, remove_item(&(current->itemList),itemtaken) );
               printf("Added to Inventory: %s",itemtaken);
               printf("\n --> ");
               break; 
            }
            printf("I don't recognize that item\n");
            printf("\n\n");
            printf("What would you like to take ?: ");
            continue;
         }
      continue;
      }
      else if ( strcmp(newinput,"drop\n")==0){
         char itemtodrop[20];
         printf("What would you like to drop ?\n");
         while( fgets(itemtodrop, sizeof(itemtodrop), stdin)!= NULL ){
            bool itemExists = search_item( &userInv, itemtodrop );
            if ( itemExists ) {
               printf("Dropped %s from inventory\n", itemtodrop );
               add_item( &(current->itemList), remove_item( &userInv, itemtodrop) );
               break;
            }
            printf("I don't recognize that item\n\n\n\nWhat would you like to take ?\n");
            continue;
         }
      }
      else if ( strcmp(newinput,"inventory\n")==0){ print_inv( &userInv ); printf("\n --> "); continue;}
      else if ( strcmp(newinput,"pitch\n")==0){
          numberofpitches++;
          if ( numberofpitches == 11 ){

             //Losing State
             printf("You get a call from your investor\n");
             printf("The Investor: Unfortunately I cannot further discuss on investing for your startup since you missed your appointment today\n");
             printf("Good luck for your future endeavors!\n");
             printf("You lost since you ran out of time,TRY AGAIN ?\n");
          }
          bool correctRoom = (strcmp(current->name, "Doorway\n")==0);
          bool hasPitchdeck = search_item(&userInv, "Pitchdeck\n" );
          bool hasCKey =  search_item(&userInv, "CKey\n");

          if ( !correctRoom && !hasPitchdeck && !hasCKey ) { printf("I need to explore a bit first\n"); }
          if ( !correctRoom ) { printf("I don't see my Car anywhere in this room\n"); }
          if ( !hasPitchdeck ) { printf("I need to get my Pitchdeck from the safe before leaving!\n"); }
          if ( !hasCKey ) { printf("I need the key to my Car to leave\n"); }
          if ( correctRoom, hasPitchdeck, hasCKey ) {

             //Winning State
             printf("With the pitchdeck you run to you car, Lightning McQueen and drive it to make your pitch to the investor");
             printf("\n\n\n");
             printf("At the investor's office: I really like your pitch and I am willing to invest a million dollars in exchange for 10 percent of your equity\n");
             printf("The Pitcher: Oh my god, I can't believe this! I take the offer sir!");
             printf("\n\n\n");
             printf("The Pitcher, by Raajveer\n");
             printf("\n\n");
             printf("Thank you for playing and congratulations for securing such a good deal for your startup!");
             break;
          }
      }
      else if ( strcmp ( newinput, "interact\n")==0 ) {
         printf("Who/Whatt would you like to interact with ?: ");
         char interactwith[20];
         while( fgets(interactwith, sizeof(interactwith), stdin) != NULL ){
            if ( strcmp( interactwith, "Kitchen\n")==0 ) {
               if ( !search_item( &userInv, "Tea" ) ) { printf("I need to get Tea first!"); }
                  printf("Honeyy!, I made some Tea for you\n");
                  printf("./n./n");
                  printf("Fiance: Thank you so much, working from home is killing me, by the way, what are we doing for my birthday the day after tomorrow ?\n");
                  printf("Just let me know soon, I am heading back to my room, I have a lot of work to do, Byeeeeeee!\n");
                  break;
            }
            else if ( strcmp( interactwith, "Safe\n") ==0 ) {
               if ( strcmp( current->name, "Living Room") != 0 ) { printf("The safe is in the living room, I need to go there first\n"); break; }
               char combination[10];
               printf("Combination ?: ");
               while ( fgets(combination, sizeof(combination), stdin ) != NULL ) {
                  if ( strcmp( combination, "7831\n") ==0 ) { safeLocked = false; printf("Safe Unlocked\n"); break; }
                  printf("Incorrect combination\ntry again: ");
               }
            }
            else if ( strcmp( interactwith, "Wall\n" )== 0 ) {
               if ( search_item( &userInv, "Pen" ) && search_item( &userInv, "Paper") ){
                  printf("8x + 4y = 12 where y = 1\n");
                  printf("8x + 4(1) = 12\n");
                  printf("8x = 12 - 4\n");
                  printf("8x = 8\n");
                  printf("x=1\n");
                  printf("That was easy\n");
                  break;
               }
               printf("I can't calculate this mentally, I need a pen and a paper\n");
            }
            else if (  strcmp( interactwith, "Snorlax\n" )==0 ) {
               if ( search_characters( &current->characters, "Snorlax" ) ) {
                  printf("Snorlax: Hi! Do you watch pokemon ? ofcourse you do! I am Snorlax, pokedex # 143\n");break;
               }
               printf("%s is not in this room\n", interactwith);
            }
            else if ( strcmp( interactwith, "Fiance\n" ) == 0 ) {
               if ( search_characters( &current->characters, "Fiance" ) ) {
                  printf("Fiance: I am working right now, I'll get back to you babe\n"); break;
               }
               printf("%s is not in this room\n", interactwith );
            }
            else if ( strcmp ( interactwith, "Bob the Builder\n") == 0) {
               if ( search_characters( &current->characters, "Bob the Builder") ){
                 printf("Bob the Builder: Hi! Do you need me to paint over the equation in your Fiance's work room ?\n"); break;
              }
              printf("%s is not in this room\n", interactwith );
            }
            else if ( strcmp(interactwith, "Genie\n") ==0 ) {
               if ( search_characters( &current->characters, "Genie") ){
                  printf("Genie: I know you very well, you love your fiance more than snorlax and snorlax more than your car, and you hate math the most\n"); break;
               }
               printf("%s is not in this room\n", interactwith); 
            }
            else if ( strcmp( interactwith, "Lightning McQueen\n") ==0 ) {
               if ( search_characters( &current->characters, "Lightning McQueen\n")  ) {
                  printf("Lightning McQueen: I wanna go race somewhere, I want my fancy numberplate [COOL10137] to be seen in the world!\n"); break;
               }
               printf("%s is not in this room\n", interactwith);
            }
         }
      }
      else {
         printf("Unrecognized command, type help for a list of valid commands\n");
         printf("\n\n");
         printf(" --> ");
      }
   }
}

