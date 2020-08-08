#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <time.h>
#include "inicialize.c"
#include "onUpdate.c"
#include "nextBlock.c"
#include "menu.c"
#include "helpMenu.c"
#include "rankMenu.c"
#include "pause.c"


int WIDTH = 490;
int HEIGHT = 560;

typedef struct positionsInWindow{
  int posCurrent;
  int x1[7];
  int x2[7]; 
} positions;



enum state{Menu, Game, Help, Rank};
enum game{Play, Paused, Finish};


void registerEvents(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp){
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
  al_register_event_source(queue, al_get_display_event_source(disp));


}


void closeGame(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp, ALLEGRO_FONT* font){
  al_destroy_font(font);
  al_destroy_display(disp);
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
  
  ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
  
  ALLEGRO_DISPLAY* disp = al_create_display(WIDTH, HEIGHT);
  
  ALLEGRO_FONT* font = al_create_builtin_font();
  

  registerEvents(queue, disp);

  
  ALLEGRO_EVENT event;



  while(1){
    if(stateCurrent == Menu){
      
      int returnMenu = (menu(queue, disp, event, font, input));
       
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
      int helpMenu = help(queue, disp, event, font);
      if(helpMenu == 0){
        stateCurrent = Menu;
        continue;
      }
      else if(helpMenu == 1)break;
    }

    else if(stateCurrent == Rank){
      int rankMenu = rank(queue, disp, event, font);
      if(rankMenu == 0){
        stateCurrent = Menu;
        continue;
      }
      else if(rankMenu == 1)break;
    }
    
  }


  int current = nextBlock(d, -10);
  int next = nextBlock(d, 0);
  
  
  int score = 0;
  int *pointerScore;
  pointerScore = &score;
  
  unsigned int countTime = 0;

  time_t initTime = time(0);
  time_t lastTime;

  time_t initPause = 0;
  time_t lastPause = 0;

  static int positionYX[4] = {0, 60, 5, 65};
  
  while(1){
      
    if(stateCurrent != Game) break;


    if(stateGame == Paused){
      int returnPuase = gamePaused(queue, event, font);
      if(returnPuase == 1){
        break;
      }
      else if(returnPuase == 2){
        lastPause = time(0);
        stateGame = Play;
      }else if(returnPuase == 3){
        initTime = time(0);
        lastTime = 0;
        initPause = 0;
        lastPause = 0;
        memset(d, 0, sizeof d);
        score = 0;
        positionYX[0] = 0;
        positionYX[1] = 60;
        positionYX[2] = 5;
        positionYX[3] = 65;
        pos.posCurrent = 0;
        stateGame = Play;
      }
    }else{
      
      int returnUpdate = onUpdate(queue, disp, event, font, &pos, d, next, positionYX, 
                                current, pointerScore, countTime);

    
      
      if(returnUpdate == 1) break;
    
      else if(returnUpdate == 2){
        current = next;
        next = nextBlock(d, 0);
        positionYX[0] = 0;
        positionYX[1] = 60;
        positionYX[2] = 5;
        positionYX[3] = 65;
        pos.posCurrent = 0;
      }
      else if(returnUpdate==3) {
        initPause = time(0);
        stateGame = Paused;
      }

      lastTime = time(0);
      countTime = (lastTime-initTime)-(lastPause-initPause);

    }
    

  
  }

  closeGame(queue, disp, font);

  return 0;
}
//gcc -Wall main.c -o main -lm `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

 
