#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>

int expoOpe(int num){
    int i;
    for(i = 0; num > 1; i++){
        num = num / 2;
    }
    return i;
}


int checkPowerofTwo(int x)
{
   if ((x == 0) || (x == 1)){
      return 0;
   }
    
   while( x != 1)
   {
        if(x % 2 != 0){
            return 0;
        }
        x /= 2;
   }
   return 1;
}
int frstnext(int *matrix){
    int value = 0;
    while(1){
        value = rand() % 33; 
        if(checkPowerofTwo(value))
        break;
    }
    return value;  
}

int nextBlock(int *matrix, int value){

    int maior = 0;
    int blockValue=2;
    srand(time(0)+value);

  for (int i = 0; i < 7; i++){
    for(int j=i*7; j<(i*7)+7; j++){
      if(*(matrix+(j)) > maior){
        maior = *(matrix+(j));
            }
        }
    }
 
    if(maior == 0){
        blockValue = frstnext(matrix);
        return blockValue;
    }
    else if(maior > 0 && maior < 32){
        while(1){
            blockValue = rand() % 32; 
            if(checkPowerofTwo(blockValue)) break;  
        }
        
        return blockValue;
    }
    else{
        int exp = expoOpe(maior);
        if(exp > 1)
            exp = exp - 1;
        int value  = pow(2, exp);
        while(1){
            blockValue = rand() % value+1; 
            if(checkPowerofTwo(blockValue)) break;  
        }
        
        return blockValue;
    }
    return blockValue;   
}