#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include "DropBlock.c"
#include "joinBlock.c"
#include <math.h>

typedef struct positionsUpdate{
  int posCurrent;
  int x1[7];
  int x2[7]; 
} PosUpdate;



int gamePaused(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_FONT* font){
              
  al_draw_filled_rectangle(105, 200, 385, 400, al_map_rgba_f(.3, .3, .3, 1));
  al_draw_filled_rectangle(210, 300, 285, 325, al_map_rgba_f(.9, .9, .9, 1));
  al_draw_filled_rectangle(210, 350, 285, 375, al_map_rgba_f(.9, .9, .9, 1));
  al_draw_text(font, al_map_rgb(255,255,255), 250, 230, ALLEGRO_ALIGN_CENTRE, "Game Paused");
  al_draw_text(font, al_map_rgb(0,0,0), 250, 310, ALLEGRO_ALIGN_CENTRE, "Resume");
  al_draw_text(font, al_map_rgb(0,0,0), 250, 360, ALLEGRO_ALIGN_CENTRE, "Restart");
  al_flip_display(); 
  
  al_wait_for_event(queue, &event);

  if(!al_is_event_queue_empty(queue)){
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      return 1;
    }if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
      if(event.mouse.y > 300 && event.mouse.y < 325 && event.mouse.x > 210 && event.mouse.x < 285){
        return 2;
      }
    }
  }
    return 0; 
}

void drawnBlock(int *matrix, PosUpdate *posUpdate, ALLEGRO_FONT* font, int value, int *positionYX, int current){
  char *str;
  asprintf (&str, "%d", value);
  
  al_clear_to_color(al_map_rgb(0,0,0));
  al_draw_filled_rectangle(200, 5, 250, 55, al_map_rgba_f(.9, .9, .9, 1));
  al_draw_text(font, al_map_rgb(0,0,0), 225, 27, ALLEGRO_ALIGN_CENTRE, str);
  al_draw_filled_rectangle(0, 70, 70, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(140, 70, 210, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(280, 70, 350, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_filled_rectangle(420, 70, 490, 560, al_map_rgba_f(.2, .2, .2, 1));
  al_draw_rectangle(400, 10, 450, 40, al_map_rgba_f(.9, .9, .9, 1),0);
  al_draw_text(font, al_map_rgb(255,255,255), 425, 20, ALLEGRO_ALIGN_CENTRE, "||");
  al_draw_filled_rectangle(*(positionYX+2), *(positionYX), *(positionYX+3), *(positionYX+1), al_map_rgba_f(1, 1, 0.5, 1));
  
  free(str);
  
  asprintf (&str, "%d", current);
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


int speedBlock(int *matrix){
  int maior = 0;
  for (int i = 0; i < 7; i++){
    for(int j=i*7; j<(i*7)+7; j++){
      if(*(matrix+(j)) > maior){
        maior = *(matrix+(j));
      }
    }
  }

  int exp = sqrt(maior);

  int speed = (exp/7)+1;
  return speed;
}


int *colorBlock(){

}


int onUpdate(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp, 
              ALLEGRO_EVENT event, ALLEGRO_FONT* font, PosUpdate *pos, int *matrix, 
              int next, int *positionYX, int isPaused, int current){
  


  if(isPaused){
    int paused = gamePaused(queue, event, font);
    if(paused == 1) return 1;
    if(paused == 2) return 4;
    return 0;
  }

  //if(se a linha do poscurrent nao tiver mais espaço e o ultimo bloco for diferente do bloco current )
    
  PosUpdate *posUpdate = pos; 

  drawnBlock(matrix, posUpdate, font, next, positionYX, current);

  al_flip_display();

  if(*(positionYX+1) < PositionLastBock(matrix, posUpdate->posCurrent)-5){
    int speed = speedBlock(matrix);
    *(positionYX) = *(positionYX) + speed;
    *(positionYX+1) = *(positionYX+1) + speed;
  }else{
    *(positionYX+1)  = PositionLastBock(matrix, posUpdate->posCurrent)-5;
    *(positionYX) = *(positionYX+1) - 60;
    *(matrix+(((*(positionYX)-5)/70)-1)*7+(posUpdate->posCurrent)) = current;
    joinBlock(matrix);
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
            *(positionYX+1)  = PositionLastBock(matrix, posUpdate->posCurrent)-5;
            *(positionYX) = *(positionYX+1) - 60;
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
          if(event.mouse.y > 70 && event.mouse.y < 560){
            if(event.mouse.x > posUpdate->x1[i] && event.mouse.x < posUpdate->x2[i]){
              if(DropBlock(matrix, i, *(positionYX+1), 0)){
                *(positionYX+2) = posUpdate->x1[i]+5;
                *(positionYX+3) = posUpdate->x2[i]-5;
                posUpdate->posCurrent = i;
              }
            }
          }else if(event.mouse.y > 10 && event.mouse.y < 40 && event.mouse.x > 400 && event.mouse.x < 450){
              return 3;
          }
        }
      }
  }

return 0;
}