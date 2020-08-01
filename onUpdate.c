#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "DropBlock.c"


typedef struct positionsUpdate{
  int posCurrent;
  int x1[7];
  int x2[7]; 
} PosUpdate;



int a = 0;
int b = 60;

int x1 = 5;
int x2 = 65;


void drawnBlock(int *matrix, PosUpdate *posUpdate){

  al_clear_to_color(al_map_rgb(20,20,20));
  al_draw_filled_rectangle(0, 0, 70, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(140, 0, 210, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(280, 0, 350, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(420, 0, 490, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(x1, a, x2, b, al_map_rgba_f(1, 1, 0.5, 1));
  for (int k = 1, i = 0; i < 43; i+=7, k++){
    for(int j=0; j<7; j++){
      if(*(matrix+(i+j)) != 0){
        al_draw_filled_rectangle(posUpdate->x1[j]+5, k*70+5,  posUpdate->x2[j]-4, 70+k*70-4, al_map_rgba_f(1, 1, 0.5, 1));
      }
    }
  }
}




int onUpdate(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp, 
              ALLEGRO_EVENT event, ALLEGRO_FONT* font, PosUpdate *pos, int *matrix){
    
    PosUpdate *posUpdate = pos; 

  drawnBlock(matrix, posUpdate);
  al_flip_display();

  if(b < 556){
    a = a + 1;
    b = b + 1;
  }

  if(!al_is_event_queue_empty(queue)){

    al_wait_for_event(queue, &event);
    if(event.type == ALLEGRO_EVENT_TIMER){

    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
      return 1;
    else if(event.type == ALLEGRO_EVENT_KEY_DOWN){
        switch (event.keyboard.keycode)
        {
          case (ALLEGRO_KEY_DOWN):
            break;
          case (ALLEGRO_KEY_RIGHT):
            if(posUpdate->posCurrent < 6 && DropBlock(matrix, posUpdate->posCurrent, b, 1)){
              posUpdate->posCurrent++;
              x1 = posUpdate->x1[posUpdate->posCurrent]+5;
              x2 = posUpdate->x2[posUpdate->posCurrent]-4;
            }
            break;
          case (ALLEGRO_KEY_LEFT):
            if(posUpdate->posCurrent > 0 && DropBlock(matrix, posUpdate->posCurrent, b, -1)){
              posUpdate->posCurrent--;
              x1 = posUpdate->x1[posUpdate->posCurrent]+5;
              x2 = posUpdate->x2[posUpdate->posCurrent]-4;
            }
            break;
          default:
            break;
        }
      }
      else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        for(int i=0; i<7; i++){
          if(event.mouse.x > posUpdate->x1[i] && event.mouse.x < posUpdate->x2[i]){
            x1 = posUpdate->x1[i]+5;
            x2 = posUpdate->x2[i]-4;
            posUpdate->posCurrent = i;
          }
        }
      }
  }

return 0;
}