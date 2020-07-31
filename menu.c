#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

int menu(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp, 
              ALLEGRO_EVENT event, ALLEGRO_FONT* font, ALLEGRO_USTR* input){

    
  al_clear_to_color(al_map_rgb(20,20,20));
  al_draw_text(font, al_map_rgb(255,255,255), 250, 100,ALLEGRO_ALIGN_CENTRE, "Drop The Number");
  al_draw_rectangle(200, 150, 300, 200, al_map_rgba_f(.2, .2, .2, 1), 0);
  al_draw_text(font, al_map_rgb(255,255,255), 250, 169,ALLEGRO_ALIGN_CENTRE, "Iniciar");
  al_draw_rectangle(200, 250, 300, 300, al_map_rgba_f(.2, .2, .2, 1), 0);
  al_draw_text(font, al_map_rgb(255,255,255), 250, 269,ALLEGRO_ALIGN_CENTRE, "Ranking");
  al_draw_rectangle(200, 350, 300, 400, al_map_rgba_f(.2, .2, .2, 1), 0);
  al_draw_text(font, al_map_rgb(255,255,255), 250, 369,ALLEGRO_ALIGN_CENTRE, "Help");
  al_draw_rectangle(200, 450, 300, 500, al_map_rgba_f(.2, .2, .2, 1), 0);
  al_draw_text(font, al_map_rgb(255,255,255), 250, 469,ALLEGRO_ALIGN_CENTRE, "Sair");


  al_draw_ustr(font, al_map_rgb(255,255,255), 30,10,0, input);
  al_flip_display();
  if(!al_is_event_queue_empty(queue)){
    al_wait_for_event(queue, &event);

    if(event.type == ALLEGRO_EVENT_KEY_CHAR){
    int unichar = event.keyboard.unichar;

    if(unichar >= 32 && unichar <= 126 && al_get_ustr_width(font, input) < 120)
      al_ustr_append_chr(input, unichar);
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      return 1;
    }else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
      if(event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 150 && event.mouse.y <= 200){
        return 0;
      }
      else if(event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 250 && event.mouse.y <= 300){
        return 2;
      }
      else if(event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 350 && event.mouse.y <= 400){
        return 3;
      }
      else if(event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 450 && event.mouse.y <= 500){
        return 1;
      }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
      if((event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 150 && event.mouse.y <= 200) ||
      (event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 250 && event.mouse.y <= 300) || 
      (event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 350 && event.mouse.y <= 400) || 
      (event.mouse.x >= 200 && event.mouse.x <= 300 && event.mouse.y >= 450 && event.mouse.y <= 500)){
        al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
      }else{
        al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT); 
      }
    }
  }
  return 4;
}
