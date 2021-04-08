#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

int visitado[8][8];

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void print_map(){
system("clear");
	for(int j=0;j<8;j++){
	printf(" --- --- --- --- --- --- --- --- \n");
	printf("|");
		for(int i=0;i<8;i++){
		  if(visitado[i][j]==0){
	  	  printf("   |", visitado[i][j]);
                  }
		  if(visitado[i][j]==1){
	  	  printf(" \033[31;1mC\033[m |", visitado[i][j]);
                  }
		  if(visitado[i][j]==2){
	  	  printf(" - |", visitado[i][j]);
                  }
		}
	printf("\n");
	}
	printf(" --- --- --- --- --- --- --- --- \n");
system("sleep 0.3s");
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

int recorrido(int paso, int X, int Y){
 if(paso==64){
 return 1;
 }else{
   if(visitado[X+2][Y+1]==0 && X+2 < 8 && X+2 >= 0 && Y+1 < 8 && Y+1 >= 0 ){
       visitado[X+2][Y+1]=1;
       print_map();
       visitado[X+2][Y+1]=2;
       paso = paso + 1;
       recorrido(paso, X+2, Y+1);
    }

   if(visitado[X+2][Y-1]==0 && X+2 < 8 && X+2 >= 0 && Y-1 < 8 && Y-1 >= 0 ){
       visitado[X+2][Y-1]=1;
       print_map();
       visitado[X+2][Y-1]=2;
       paso = paso + 1;
       recorrido(paso, X+2, Y-1);
    }

   if(visitado[X+1][Y+2]==0 && X+1 < 8 && X+1 >= 0 && Y+2 < 8 && Y+2 >= 0 ){
       visitado[X+1][Y+2]=1;
       print_map();
       visitado[X+1][Y+2]=2;
       paso = paso + 1;
       recorrido(paso, X+1, Y+2);
    }

   if(visitado[X-1][Y+2]==0 && X-1 < 8 && X-1 >= 0 && Y+2 < 8 && Y+2 >= 0 ){
       visitado[X-1][Y+2]=1;
       print_map();
       visitado[X-1][Y+2]=2;
       paso = paso + 1;
       recorrido(paso, X-1, Y+2);
    }

   if(visitado[X-2][Y+1]==0 && X-2 < 8 && X-2 >= 0 && Y+1 < 8 && Y+1 >= 0 ){
       visitado[X-2][Y+1]=1;
       print_map();
       visitado[X-2][Y+1]=2;
       paso = paso + 1;
       recorrido(paso, X-2, Y+1);
    }

   if(visitado[X-2][Y-1]==0 && X-2 < 8 && X-2 >= 0 && Y-1 < 8 && Y-1 >= 0 ){
       visitado[X-2][Y-1]=1;
       print_map();
       visitado[X-2][Y-1]=2;
       paso = paso + 1;
       recorrido(paso, X-2, Y-1);
    }

   if(visitado[X-1][Y-2]==0 && X-1 < 8 && X-1 >= 0 && Y-2 < 8 && Y-2 >= 0 ){
       visitado[X-1][Y-2]=1;
       print_map();
       visitado[X-1][Y-2]=2;
       paso = paso + 1;
       recorrido(paso, X-1, Y-2);
    }
   
   if(visitado[X +1][Y-2]==0 && X + 1 < 8 && X + 1 >= 0 && Y-2 < 8 && Y-2 >= 0 ){
       visitado[X + 1][Y-2]=1;
       print_map();
       visitado[X + 1][Y-2]=2;
       paso = paso + 1;
       recorrido(paso, X + 1, Y-2);
    }

  visitado[X][Y]=0;
  paso = paso - 1;
  

  return 0;
 }
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

int main(){
	for(int j=0;j<8;j++){
		for(int i=0;i<8;i++){
		visitado[i][j]=0;
		}
	}

int paso=0;
visitado[0][0]=1;
print_map();
visitado[0][0]=2;
recorrido(paso,0,0);	
return 0;
}

