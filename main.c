#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "inicialize.c"
#include "onUpdate.c"
#include "nextBlock.c"
#include "menu.c"
#include "helpMenu.c"
#include "rankMenu.c"


int WIDTH = 490;
int HEIGHT = 560;

typedef struct positionsInWindow{
  int posCurrent;
  int x1[7];
  int x2[7]; 
} positions;



enum state{Menu, Game, Help, Rank};
enum game{Play, Paused, Finish};


void registerEvents(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp){
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));
  al_register_event_source(queue, al_get_timer_event_source(timer));
}


void closeGame(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* font){
  al_destroy_font(font);
  al_destroy_display(disp);
  al_destroy_timer(timer);
  al_destroy_event_queue(queue);
}

int main(int argc, char *argv[])
{
  enum state stateCurrent = Menu;
  enum game stateGame;
  static int e[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0,  16, 0, 0},
                        {16, 0, 2, 16, 8, 4, 2},
                        {8,  0, 4,  8, 2, 8, 4}};
  
  static int d[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0,  0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0,  0, 0,  0, 0, 0, 0}};


  positions pos;
  pos.posCurrent = 0;

  for(int i=0; i<7; i++){
    pos.x1[i] = (WIDTH/7)*i;
    pos.x2[i] = (WIDTH/7)*i+69;
  }

  

  if(inicialize()) return -1;

  ALLEGRO_USTR *input = al_ustr_new("");
  ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
  
  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  
  ALLEGRO_DISPLAY* disp = al_create_display(WIDTH, HEIGHT);
  
  ALLEGRO_FONT* font = al_create_builtin_font();
  

  registerEvents(queue, timer, disp);

  
  ALLEGRO_EVENT event;

  al_start_timer(timer);



  while(1){
    if(stateCurrent == Menu){
      
      int returnMenu = (menu(queue, timer, disp, event, font, input));
       
      if(returnMenu == 0){
        stateCurrent = Game;
        stateGame = Play;
        break;
      }
      else if(returnMenu == 2){
        stateCurrent = Rank;
        continue;
      }
      else if(returnMenu == 3){
        stateCurrent = Help;
        continue;
      }else if(returnMenu == 1) break;
    }


    else if(stateCurrent == Help){
      int helpMenu = help(queue, timer, disp, event, font);
      if(helpMenu == 0){
        stateCurrent = Menu;
        continue;
      }
      else if(helpMenu == 1)break;
    }

    else if(stateCurrent == Rank){
      int rankMenu = rank(queue, timer, disp, event, font);
      if(rankMenu == 0){
        stateCurrent = Menu;
        continue;
      }
      else if(rankMenu == 1)break;
    }
    
  }
  int current = nextBlock(d);
  static int positionYX[4] = {0, 60, 5, 65};
  int next = nextBlock(d);
  int reset = 1;
  while(1){
    if(stateCurrent != Game) break;
    int isPaused = (stateGame == Paused) ? 1 : 0;
   
    int returnUpdate = onUpdate(queue, timer, disp, event, font, &pos, d, next, positionYX, isPaused, current);

    if(returnUpdate==4) stateGame = Play;

    if(stateGame == Play || returnUpdate == 1){

      if(returnUpdate == 1) break;
      
      else if(returnUpdate == 2){
        current = next;
        next = nextBlock(d);
        positionYX[0] = 0;
        positionYX[1] = 60;
        positionYX[2] = 5;
        positionYX[3] = 65;
        pos.posCurrent = 0;
      }

      else if(returnUpdate==3) stateGame = Paused;
      
    }
  }

  closeGame(queue, timer, disp, font);

  return 0;
}
//gcc -Wall main.c -o main -lm `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

 
