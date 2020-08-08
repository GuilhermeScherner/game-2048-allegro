#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

int finish(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp, 
              ALLEGRO_EVENT event, ALLEGRO_FONT* font){

    
  al_clear_to_color(al_map_rgb(20,20,20));
  al_draw_multiline_text(font, al_map_rgb(255,255,255), 250, 150, 300, 20, ALLEGRO_ALIGN_CENTRE, 
  "Sua posição no Rank foi:");

  al_draw_rectangle(200, 450, 300, 500, al_map_rgba_f(.2, .2, .2, 1), 0);
  al_draw_text(font, al_map_rgb(255,255,255), 250, 470, ALLEGRO_ALIGN_CENTRE, "Restart");


  al_flip_display();
  if(!al_is_event_queue_empty(queue)){
    al_wait_for_event(queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      return 1;
    }else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
      if(event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 450 && event.mouse.y <= 500){
        return 2;
      }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
      if(event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 450 && event.mouse.y <= 500){
        al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
      }else{
        al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT); 
      }
    }
  }
  return 0;
}
