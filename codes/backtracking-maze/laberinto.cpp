#include <stdio.h>
#include <stdlib.h>

int mapa[10][10] = { {0, 1, 0, 0, 0, 0, 0, 1, 0, 1},
                     {0, 1, 0, 1, 1, 1, 0, 1, 0, 1},
                     {0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
                     {1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
                     {2, 0, 0, 1, 0, 0, 0, 1, 0, 1},
                     {1, 1, 0, 1, 1, 1, 0, 1, 0, 0},
                     {0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
                     {0, 1, 1, 1, 1, 1, 0, 1, 0, 1},
                     {0, 0, 0, 0, 0, 0, 0, 0, 0, 1} };




int horz[4] = { 1, 0, -1, 0 };
int vert[4] = { 0, 1, 0, -1 };

bool encontro = false;

void imprime(){
system("sleep 0.2");
system("clear");
   for( int j=0; j<10; j++ ){
      printf(" --- --- --- --- --- --- --- --- --- ---\n");
      for( int i=0; i<10; i++ ){

         if(mapa[j][i] == 1 ){
         printf("| # ");
         }
         if(mapa[j][i] == 2 ){
         printf("| \033[31;1mX\033[m ");
         }
         if(mapa[j][i] == 0 ){
         printf("|   ");
         }
         if(mapa[j][i] == 3 ){
         printf("| \033[34;1m.\033[m ");
         }
         if(mapa[j][i] == 4 ){
         printf("| \033[34;1m@\033[m ");
         }

      }
      printf("|\n");
   }
   printf(" --- --- --- --- --- --- --- --- --- --- \n");
}

void camina( int Ai, int Aj ){
  int I=0;

  while( I<4 && encontro == false){
    if( mapa[Aj + vert[I] ][Ai + horz[I]] == 0 && Ai + horz[I] < 10 && Ai + horz[I] >= 0 && Aj + vert[I] < 10 && Aj + vert[I] >= 0 || mapa[Aj + vert[I] ][Ai + horz[I]] == 2 )
    {
      if( mapa[Aj + vert[I] ][Ai + horz[I]] == 0 ){
        mapa[Aj][Ai] = 3; 
        mapa[Aj + vert[I] ][Ai + horz[I]] = 4;
        imprime();
        camina( Ai + horz[I], Aj + vert[I]  );
      }else{
        mapa[Aj][Ai] = 3; 
        mapa[Aj + vert[I] ][Ai + horz[I]] = 4;
        imprime();
        encontro = true;
        printf("LLEGADA!\n");
      }
      if(encontro == false ){
        mapa[Aj][Ai] = 4; 
        mapa[Aj + vert[I] ][Ai + horz[I]] = 0;
        imprime();
      }
    }
    I++;
  }
}

void camina(){
  imprime();
  camina( 0,0 );
}

int main(){
  camina();
  return 0;
}

