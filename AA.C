#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
extern int WIDTH;
int a = 0;
int b = 60;

int x1 = 5;
int x2 = 65;

int onUpdate(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER* timer, ALLEGRO_DISPLAY* disp, 
              ALLEGRO_EVENT event, bool redraw, ALLEGRO_FONT* font){

    char snum[10];

    al_wait_for_event(queue, &event);
    
    if(event.type == ALLEGRO_EVENT_TIMER)
      redraw = true;
    else if((event.type == ALLEGRO_EVENT_KEY_DOWN) || (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE))
      return 1;

    else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){    
      redraw = true;
     sprintf(snum, "%d", event.mouse.y);
    }

    else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
      redraw = true;
      if(event.mouse.x > 70 && event.mouse.x < 140){
        x1 = 75;
        x2 = 135;
      } 
    }
    //al_get_window_constraints(disp, )


    
    
    if(redraw && al_is_event_queue_empty(queue)){
      al_clear_to_color(al_map_rgb(20,20,20));
      al_draw_filled_rectangle(0, 0, 70, 560, al_map_rgba_f(.2, .2, .2, 1));
      al_draw_filled_rectangle(140, 0, 210, 560, al_map_rgba_f(.2, .2, .2, 1));
      al_draw_filled_rectangle(280, 0, 350, 560, al_map_rgba_f(.2, .2, .2, 1));
      al_draw_filled_rectangle(420, 0, 490, 560, al_map_rgba_f(.2, .2, .2, 1));

      al_draw_text(font, al_map_rgb(255,255,255), 0,0,0, snum);
    if(b < 558){
      a = a +3;
      b = b + 3;
    }
      al_draw_filled_rectangle(x1, a, x2, b, al_map_rgba_f(1, 1, 0.5, 1));
      al_flip_display();
      redraw = false;
    }
    return 0;
}