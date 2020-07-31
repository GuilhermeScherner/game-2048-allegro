#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include "inicialize.c"
#include "onUpdate.c"
#include "nextBlock.c"
#include "menu.c"


int WIDTH = 490;
int HEIGHT = 560;

typedef struct positionsInWindow{
  int posCurrent;
  int x1[7];
  int x2[7]; 
} positions;





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
  int startGame = 0;
  static int d[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0,  16, 0, 0},
                        {16, 0, 2, 16, 8, 4, 2},
                        {8,  0, 4,  8, 2, 8, 4},};

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


  bool redraw = true;
  
  ALLEGRO_EVENT event;

  al_start_timer(timer);

  //int a = nextBlock(matrix);

  //fillPos

  while(1){
    int returnMenu = (menu(queue, timer, disp, event,redraw, font, input));
    if(returnMenu == 1){
      startGame = 0;
      break;
    }else if(returnMenu == 0 ){
      startGame = 1;
      break;
    }
  
   
  }
  while(1){
    if(!startGame) break;
    if(onUpdate(queue, timer, disp, event,redraw, font, &pos, d)) break;
  }

  closeGame(queue, timer, disp, font);

  return 0;
}
//gcc -Wall main.c -o main -lm `pkg-config --cflags --libs allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5`

 
