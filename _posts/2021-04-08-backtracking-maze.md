---
layout: post
title: "Backtracking - Maze solver"
date: 2021-04-08 12:50:00 -0400
relatives: backtracking-maze
categories: [data_structure, c++]
---

Backtracking
===

Algunos algoritmos complicados de resolver pueden plantearse como un conjunto operaciones faciles de realizar, pero que se ejecutan de forma sistematica hasta cumplir una condición. Backtracking es un método que permite buscar la o las soluciones posibles de un problema, aunque no necesariamente sea una forma de eficiente de resolver los problemas generalmente es muy intuitiva y fácil de desarrollar.   



Este metodo tambíen conocido como de busqueda hacia atrás, consiste un una técnica recursiva que explora los elementos de un conjunto de posibilidades en cada ambiente recursivo, seleccionando o descartando subconjuntos de canditatos dependiendo de si cumplen o no una determinada condición.   



Si bien la recursión nos permite encontrar soluciones "lineales" o en una dimensión partiendo de un determinado punto, el backtracking puede verse como un paso mas allá, permitiendonos encontrar soluciones recursivas con multiples caminos de decisión.   


Veamos por ejemplo la solución recursiva de la función factorial para un valor 4.

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/{{page.relatives}}/01.svg?raw=true">
</p>

Como puede verse el algoritmo hace las preguntas en una dirección adentrandose en cada paso a un nuevo ambiente recursivo, y cuando encuentra la condición de parada recorre el camino inverso trayendo consigo la solución a cada sub problema.

La idea general del Backtracking es hacer lo mismo que hemos visto con la recursión, pero en cada ambiente recursivo se evaluan las diferentes posibilidades de un problema. Supongamos que queremos encontrar la solución de un laberinto, en cada paso las posibilidades serían subir, movernos a la derecha, bajar o movernos a la izquierda siempre que no hayan paredes.

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/{{page.relatives}}/amb01.svg?raw=true">
</p>

Cada una de estas decisiones implica la entrada a un ambiente recursivo, asi que para 4 opciones, nuestra función recursiva tendrá 4 llamadas a si misma y cada llamada inicia desde la posición hacia la que nos hemos desplazado tal como ocurre al caminar.

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/{{page.relatives}}/amb02.svg?raw=true">
</p>

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/{{page.relatives}}/amb03.svg?raw=true">
</p>

En cada ambiente se evaluaran estas opciones en orden secuencial, en caso de no poder entrar por una opción, o al retornar a un ambiente recursivo, el algoritmo probará con la opción inmediatamente siguiente hasta que se agoten las opciones 

Desde el punto de vista de una matriz, tenemos dos coordenadas, las cordenadas en X y las coordenadas en Y, los desplazamientos consisten en modificar estas coordenadas para ubicarnos en una nueva posición, asi un desplazamiento hacia arriba seria restar 1 a la coordenada Y, veamos mejor esta idea.

![backtracking]({{site.baseurl}}/assets/img/posts/{{page.relatives}}/desplaz01.svg?raw=true "backtracking")

Supongamos ahora que en lugar de 4 opciones ( arriba, derecha, abajo, izquierda ) fuese un número muy alto, digamos 100, crear 100 condicionales seria igaulmente sencillo como problema pero dificil de escribir y mantener. Si quisieramos evaluar cada una de estas opciones resultaría mas comodo iterar sobre estas opciones que escribir cada una de ellas.

Si pensemos en la opciones como una simple configuración de elementos, podríamos crear una representación fàcil de iterar, por ejemplo podemos ver los desplazamientos arriba, derecha, abajo izquierda como la posición actual mas el valor de desplazamiento:

```c++
int horz[4] = { 1, 0, -1, 0 };
int vert[4] = { 0, 1, 0, -1 };
```

Con esto en mente veamos una forma en la que podríamos desarrollar esta idea.

```c++
#include <stdio.h>
#include <stdlib.h>

int mapa[5][5] = {  { 0, 0, 0, 0, 0 },  
                    { 1, 1, 1, 0, 1 },  
                    { 1, 2, 1, 0, 0 },  
                    { 0, 0, 0, 1, 0 },  
                    { 0, 1, 0, 0, 0 }  };

int horz[4] = { 1, 0, -1, 0 };
int vert[4] = { 0, 1, 0, -1 };

bool encontro = false;

void imprime(){
system("sleep 1");
system("clear");
   for( int j=0; j<5; j++ ){
      printf(" --- --- --- --- --- \n");
      for( int i=0; i<5; i++ ){

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
   printf(" --- --- --- --- --- \n");
}

void camina( int Ai, int Aj ){
  int I=0;

  while( I<4 && encontro == false){
    if( mapa[Aj + vert[I] ][Ai + horz[I]] == 0 && Ai + horz[I] < 5 && Ai + horz[I] >= 0 && Aj + vert[I] < 5 && Aj + vert[I] >= 0 || mapa[Aj + vert[I] ][Ai + horz[I]] == 2 )
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

```

El resultado de este código se muestra a continuación.
<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/{{page.relatives}}/path.gif?raw=true">
</p>

[Full Code]({{site.baseurl}}/codes/{{page.relatives}}/laberinto.cpp)