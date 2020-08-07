#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

int help(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_DISPLAY* disp, 
              ALLEGRO_EVENT event, ALLEGRO_FONT* font){

    
  al_clear_to_color(al_map_rgb(20,20,20));
  al_draw_multiline_text(font, al_map_rgb(255,255,255), 250, 150, 300, 20, ALLEGRO_ALIGN_CENTRE, "Drop The Number é um jogo"
   "no qual o objetivo é juntar os blocos iguais, cada vez que você junta você ganha pontos. Pode usar o mouse ou as setas"
   "para controlar onde o bloco vai cair.");

  al_draw_rectangle(50, 50, 150, 100, al_map_rgba_f(.2, .2, .2, 1), 0);
  al_draw_text(font, al_map_rgb(255,255,255), 100, 70, ALLEGRO_ALIGN_CENTRE, "Voltar");


  al_flip_display();
  if(!al_is_event_queue_empty(queue)){
    al_wait_for_event(queue, &event);

    if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE){
      return 1;
    }else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
      if(event.mouse.x >= 50 && event.mouse.x <= 150 && event.mouse.y >= 50 && event.mouse.y <= 100){
        return 0;
      }
    }
    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
      if(event.mouse.x >= 50 && event.mouse.x <= 150 && event.mouse.y >= 50 && event.mouse.y <= 100){
        al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_LINK);
      }else{
        al_set_system_mouse_cursor(disp, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT); 
      }
    }
  }
  return 2;
}
