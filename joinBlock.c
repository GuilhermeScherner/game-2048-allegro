#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

void redefineBlock(int *matrix){ 
  for (int i = 6; i > 0; i--){
    for(int j=i*7; j<(i*7)+7; j++){
      if(*(matrix+(j)) == 0){
        *(matrix+(j)) = *(matrix+(j-7));
        *(matrix+(j-7)) = 0;
      }
    }
  }  
}

void sumBlock(int *matrix, int equals[3], int numOpe, int pos){

  switch (numOpe)
  {
  case 1:
    *(matrix+(pos)) = *(matrix+(pos)) * 2;
    break;
  case 2:
    *(matrix+(pos)) = *(matrix+(pos)) * 4;
    
    break;
  case 3:
    *(matrix+(pos)) = *(matrix+(pos)) * 8;
    break;
  default:
    *(matrix+(pos)) = *(matrix+(pos));
    break;
  }

  for (int i = 0; i<3; i++){
    if(equals[i] != 0){
      *(matrix+(pos+equals[i])) = 0;
    }
  }
  redefineBlock(matrix);
  
}

int joinBlock(int *matrix){
  int redefine = false;
  int equals[3] ={0,0,0};
  int numOpe = 0;

  for (int i = 0; i < 7; i++){
      for(int j=i*7; j<(i*7)+7; j++){
        memset(equals, 0, sizeof equals);
        numOpe = 0;
        if(*(matrix+(j)) == 0) continue;
        if(i==0){
          if(j==i*7){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = 1;
              numOpe ++;
            }
          }
          if(j==(i*7)+6){
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }
          }
          if(*(matrix+(j)) == *(matrix+(j+7))){
            equals[numOpe] = +7;
            numOpe ++;
          }
        }



        else if(i==6){
          if(j==i*7){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = 1;
              numOpe ++;
            }
          }
          if(j==(i*7)+6){
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }
          }
          if(*(matrix+(j)) == *(matrix+(j-7))){
            equals[numOpe] = -7;
            numOpe ++;
          }
        }


        else{
          if(j==(i*7)){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = +1;
              numOpe ++;
            } 
            if(*(matrix+(j)) == *(matrix+(j+7))){
              equals[numOpe] = +7;
              numOpe ++;
            }
            if(*(matrix+(j)) == *(matrix+(j-7))){
              equals[numOpe] = -7;
              numOpe ++;
            }
          }


          else if(j==(i*7)+6){
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            } 
            if(*(matrix+(j)) == *(matrix+(j+7))){
              equals[numOpe] = +7;
              numOpe ++;
            }
            if(*(matrix+(j)) == *(matrix+(j-7))){
              equals[numOpe] = -7;
              numOpe ++;
            }
          }
          else{
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = +1;
              numOpe ++;
            } 
            if(*(matrix+(j)) == *(matrix+(j-7))){
              equals[numOpe] = -7;
              numOpe ++;
            }
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }
            if(*(matrix+(j)) == *(matrix+(j+7))){
              equals[numOpe] = +7;
              numOpe ++;
            }
          }
        }
        if(numOpe > 0){
          sumBlock(matrix, equals, numOpe, j);
          redefine = true;
        }
      }
    }
    if(redefine)
      joinBlock(matrix);
}



