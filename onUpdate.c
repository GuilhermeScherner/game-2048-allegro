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




void drawnBlock(int *matrix, PosUpdate *posUpdate, ALLEGRO_FONT* font, int value, int *positionYX){
  //char *string = atol(value);
  char *str;
  asprintf (&str, "%d", value);
  
  al_clear_to_color(al_map_rgb(20,20,20));
  al_draw_filled_rectangle(0, 0, 70, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(140, 0, 210, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(280, 0, 350, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(420, 0, 490, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(*(positionYX+2), *(positionYX), *(positionYX+3), *(positionYX+1), al_map_rgba_f(1, 1, 0.5, 1));
  al_draw_text(font, al_map_rgb(0,0,0), *(positionYX+2)+30, *(positionYX)+30, ALLEGRO_ALIGN_CENTRE, str);
  
  free(str);

  for (int k = 1, i = 0; i < 43; i+=7, k++){
    for(int j=0; j<7; j++){
      if(*(matrix+(i+j)) != 0){
        al_draw_filled_rectangle(posUpdate->x1[j]+5, k*70+5,  posUpdate->x2[j]-5, 70+k*70-5, al_map_rgba_f(1, 1, 0.5, 1));
        asprintf (&str, "%d", *(matrix+(i+j)));
        al_draw_text(font, al_map_rgb(0,0,0), posUpdate->x1[j]+35, k*70+35, ALLEGRO_ALIGN_CENTRE, str);
        free(str);
      }
    }
  }
}

int isFirst(int *matrix){
  for (int i = 0; i < 7; i++){
    for(int j=i*7; j<(i*7)+7; j++){
      if(*(matrix+(j)) > 0){
        return 0;
      }
    }
  }
  return 1;
}




int onUpdate(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp, 
              ALLEGRO_EVENT event, ALLEGRO_FONT* font, PosUpdate *pos, int *matrix, 
              int fstBlock, int next, int reset, int *positionYX){

    
  PosUpdate *posUpdate = pos; 

  if(isFirst(matrix) && reset==1){
    drawnBlock(matrix, posUpdate , font, fstBlock, positionYX);
  }   else{
    drawnBlock(matrix, posUpdate , font, next, positionYX);

  }

  al_flip_display();

  if(*(positionYX+1) < PositionLastBock(matrix, posUpdate->posCurrent)-5){
    *(positionYX) = *(positionYX) + 1;
    *(positionYX+1) = *(positionYX+1) + 1;
  }else{
    *(positionYX+1)  = PositionLastBock(matrix, posUpdate->posCurrent)-5;
    *(positionYX) = *(positionYX+1) - 60;
    int a = isFirst(matrix) ? fstBlock : next;
    *(matrix+(((*(positionYX)-5)/70)-1)*7+(posUpdate->posCurrent)) = a;
    return 2;
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
            if(posUpdate->posCurrent < 6 && DropBlock(matrix, posUpdate->posCurrent, *(positionYX+1), 1)){
              posUpdate->posCurrent++;
              *(positionYX+2) = posUpdate->x1[posUpdate->posCurrent]+5;
              *(positionYX+3) = posUpdate->x2[posUpdate->posCurrent]-5;
            }
            break;
          case (ALLEGRO_KEY_LEFT):
            if(posUpdate->posCurrent > 0 && DropBlock(matrix, posUpdate->posCurrent, *(positionYX+1), -1)){
              posUpdate->posCurrent--;
              *(positionYX+2) = posUpdate->x1[posUpdate->posCurrent]+5;
              *(positionYX+3) = posUpdate->x2[posUpdate->posCurrent]-5;
            }
            break;
          default:
            break;
        }
      }
      else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
        for(int i=0; i<7; i++){
          if(event.mouse.x > posUpdate->x1[i] && event.mouse.x < posUpdate->x2[i]){
            if(DropBlock(matrix, i, *(positionYX+1), 0)){
              *(positionYX+2) = posUpdate->x1[i]+5;
              *(positionYX+3) = posUpdate->x2[i]-5;
              posUpdate->posCurrent = i;
            }
          }
        }
      }
  }

return 0;
}