#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>


int inicialize(){
  if(!al_init())
    {
        printf("ERRO na inicialização\n");
        return 1;
    }

    if(!al_install_keyboard())
    {
        printf("ERRO teclado não encontrado\n");
        return 1;
    }

    if(!al_install_mouse()){
        printf("ERRO mouse não encontrado\n");
        return 1;
    }
    al_init_primitives_addon();

    
    return 0;
}
