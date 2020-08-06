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
  return;
}


void sumBlock(int *matrix, int equals[3], int numOpe, int pos, int *sumScore){
  *sumScore += *(matrix+(pos)) * (numOpe+1);
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

int joinAll(int *matrix, int * score){

  int redefine = false;
  int equals[3] ={0,0,0};
  int numOpe = 0;

  for (int i = 0; i < 7; i++){
      for(int j=i*7; j<(i*7)+7; j++){
        memset(equals, 0, sizeof equals);
        numOpe = 0;
        if(*(matrix+(j)) == 0) continue;
//line top
        if(i==0){
          if(*(matrix+(j)) == *(matrix+(j+7))){
            equals[numOpe] = 7;
            numOpe ++;
          }
          if(j == 0){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = 1;
              numOpe ++;
            }
          }
          else if(j==6){
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }
          }
          else if(j!= 0 && j !=6){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = 1;
              numOpe ++;
            }
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }
          }
        }
//line bot
        else if(i==6){
          if(*(matrix+(j)) == *(matrix+(j-7))){
            equals[numOpe] = -7;
            numOpe ++;
          }
          if(j == 35){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = 1;
              numOpe ++;
            }
          }
          else if(j==42){
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }
          }
          else if(j!= 35 && j != 42){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = 1;
              numOpe ++;
            }
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }
          }
        }
//another line
        else{
        if(*(matrix+(j)) == *(matrix+(j+7))){
            equals[numOpe] = +7;
            numOpe ++;
          }
          if(*(matrix+(j)) == *(matrix+(j-7))){
              equals[numOpe] = -7;
              numOpe ++;
          }
          if(j==(i*7)){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = +1;
              numOpe ++;
            }
          }
          else if(j==(i*7)+6){
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }
          }
          else if(j!=(i*7) && j!=(i*7)+6){
            if(*(matrix+(j)) == *(matrix+(j+1))){
              equals[numOpe] = +1;
              numOpe ++;
            }
            if(*(matrix+(j)) == *(matrix+(j-1))){
              equals[numOpe] = -1;
              numOpe ++;
            }   
          }
        }

        if(numOpe > 0){
          sumBlock(matrix, equals, numOpe, j, score);
          redefine = true;
        }
      }
    }
    if(redefine)
      joinAll(matrix, score);
    else
      return 0;
  return 1;
    
}



void joinBlock(int *matrix, int column, int row, int *score){

  int equals[3] ={0,0,0};
  int numOpe = 0;
  int reset = 1;
  row = ((row/70)-2)*7;

  int position = column+row;

 
  //line top
  if(column==0){
    if(*(matrix+(position)) == *(matrix+(position+7))){
      equals[numOpe] = 7;
      numOpe ++;
    }
    if(position == 0){
      if(*(matrix+(position)) == *(matrix+(position+1))){
        equals[numOpe] = 1;
        numOpe ++;
      }
    }
    else if(position==6){
      if(*(matrix+(position)) == *(matrix+(position-1))){
        equals[numOpe] = -1;
        numOpe ++;
      }
    }
    else if(position!= 0 && position !=6){
      if(*(matrix+(position)) == *(matrix+(position+1))){
        equals[numOpe] = 1;
        numOpe ++;
      }
      if(*(matrix+(position)) == *(matrix+(position-1))){
        equals[numOpe] = -1;
        numOpe ++;
      }
    }
  }
   
  //line bot
  else if(column==6){
    if(*(matrix+(position)) == *(matrix+(position-7))){
      equals[numOpe] = -7;
      numOpe ++;
    }
    if(position == 35){
      if(*(matrix+(position)) == *(matrix+(position+1))){
        equals[numOpe] = 1;
        numOpe ++;
      }
    }
    else if(position==42){
      if(*(matrix+(position)) == *(matrix+(position-1))){
        equals[numOpe] = -1;
        numOpe ++;
      }
    }
    else if(position!= 35 && position != 42){
      if(*(matrix+(position)) == *(matrix+(position+1))){
        equals[numOpe] = 1;
        numOpe ++;
      }
      if(*(matrix+(position)) == *(matrix+(position-1))){
        equals[numOpe] = -1;
        numOpe ++;
      }
    }
  }
  //another line
  else{
  if(*(matrix+(position)) == *(matrix+(position+7))){
      equals[numOpe] = +7;
      numOpe ++;
    }
    if(*(matrix+(position)) == *(matrix+(position-7))){
        equals[numOpe] = -7;
        numOpe ++;
    }
    if(position==(column*7)){
      if(*(matrix+(position)) == *(matrix+(position+1))){
        equals[numOpe] = +1;
        numOpe ++;
      }
    }
    else if(position==(column*7)+6){
      if(*(matrix+(position)) == *(matrix+(position-1))){
        equals[numOpe] = -1;
        numOpe ++;
      }
    }
    else if(position!=(column*7) && position!=(column*7)+6){
      if(*(matrix+(position)) == *(matrix+(position+1))){
        equals[numOpe] = +1;
        numOpe ++;
      }
      if(*(matrix+(position)) == *(matrix+(position-1))){
        equals[numOpe] = -1;
        numOpe ++;
      }   
    }
  }
  
  if(numOpe > 0){
    sumBlock(matrix, equals, numOpe, position, score);
  }

  if(reset)
    reset = joinAll(matrix, score);
  return;

}



