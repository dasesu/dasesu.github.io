---
layout: post
title: "Classic Problems - #1 Fibonacci"
date: 2020-10-03 18:00:00 -0400
categories: [c++] 
---

La función de fibonacci consiste en crear una secuencia numerica en la que cada número es la suma de sus dos anteriores. Asi la secuencia de los 7 primeros numeros sería: 
1 1 2 3 5 8 13 ...

Este problema consiste en crear una función que dado un número entero N imprima los N primeros numeros de la sucesíon 

Versión Iterativa
====

```c++
#include <stdio.h>
using namespace std;

void fibonacci( int N ){
  int first=0;
  int second=1;
  int auxiliar=0;
  for( int i=1;i<=N;i++ ){
    if( i==1 ){
      /* No realizamos ninguna operación sobre las variables
      Tomamos este como un caso base y conocemos el resultado */
      printf("%d ", second);
    }else{
      /* Realizamos la operación de suma de los valores previos
      para obtener el nuevo valor */
      auxiliar=second;
      second=second+first;
      first=auxiliar;
      printf("%d ", second);
    }
  }
}

int main(){
  int num=0;
  scanf("%d", &num);
  fibonacci(num);
  return 0;
}

```

Output
```bash
$ ./a.out
7
1 1 2 3 5 8 13 
```

Versión Recursiva
====
Otra forma de resolver este ejercicio es usando funciones recursivas, en esta versión la función fibonacci se llama a si misma para obtener el valor de los elementos anteriores en la secuencia, al no conseguirlos continua llamandose hasta que cae en el caso base.
```c++
#include <stdio.h>
using namespace std;

int fibonacci(int N){
  if(N<=1){
    return 1;
  }else{
    return fibonacci( N-1 ) + fibonacci(N-2);
  }
}
   
int main(){
  int num=0;
  scanf("%d", &num);
  for (int i = 0; i < num; i++){
    printf("%d ", fibonacci(i) );
  }
  printf("\n");
  return 0;
}
```
