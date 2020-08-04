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
    value = rand() % 33; 
    if(checkPowerofTwo(value)) return value;  
    else frstnext(matrix);  
}

int nextBlock(int matrix[7][7]){
    int maior = 0;
    int blockValue;
    srand(time(0));

    for (int i = 0; i < 7; i++){
        for(int j=0; j<7; j++){
            if((matrix[i][j]) > maior){
                maior = (matrix[i][j]);
            }
        }
    }
 
    if(maior == 0){
        blockValue = frstnext(matrix);
        return blockValue;
    }

    
    
    else{
        int exp = expoOpe(maior);
        exp = exp - 1;
        int value  = pow(2, exp);
        while(1){
            blockValue = rand() % value+1; 
            if(checkPowerofTwo(blockValue)) break;  
        }
        
        return blockValue;
    }
    return 0;   
}