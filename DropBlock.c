#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

int DropBlock(int *matrix, int position, int botY, int direction){
  int a = 7;
  int heightM[8] = {70,140,210,280,350,420,490, 560}; 
  for (int k = 1, i = 0; i < 43; i+=7, k++){
    if(*(matrix+(i+position+direction)) != 0){
      a = i/7;
      break;
    }
  } 
  if(botY < heightM[a]) return 1;
  
  return 0;
}