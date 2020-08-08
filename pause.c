#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


int gamePaused(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, ALLEGRO_FONT* font){
  al_draw_filled_rectangle(105, 200, 385, 400, al_map_rgba_f(.3, .3, .3, 1));
  al_draw_filled_rectangle(210, 300, 285, 325, al_map_rgba_f(.9, .9, .9, 1));
  al_draw_filled_rectangle(210, 350, 285, 375, al_map_rgba_f(.9, .9, .9, 1));
  al_draw_text(font, al_map_rgb(255,255,255), 250, 230, ALLEGRO_ALIGN_CENTRE, "Game Paused");
  al_draw_text(font, al_map_rgb(0,0,0), 250, 310, ALLEGRO_ALIGN_CENTRE, "Resumo");
  al_draw_text(font, al_map_rgb(0,0,0), 250, 360, ALLEGRO_ALIGN_CENTRE, "Restart");
  al_flip_display(); 

  if(!al_is_event_queue_empty(queue)){
  al_wait_for_event(queue, &event);
    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      return 1;
    }if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
      if(event.mouse.y > 300 && event.mouse.y < 325 && event.mouse.x > 210 && event.mouse.x < 285){
        return 2;
      }
      if(event.mouse.y > 350 && event.mouse.y < 375 && event.mouse.x > 210 && event.mouse.x < 285){
        return 3;
      }
    }
  }
    return 0; 
}

