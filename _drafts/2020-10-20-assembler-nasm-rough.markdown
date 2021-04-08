---
layout: post
title: "Assembler rough reference - #2 NASM"
date: 2020-10-20 15:29:00 -0400
categories: assembler
---
Estos apuntes no tienen el proposito de explicar ni transmitir las cosas "bonito" ni en orden, sólo de ser una rápida referencia comandos y funcionalidades.

NASM
===
Para generar el archivo objeto
```
nasm -f elf64 helloworld.asm
```

Para enlazar ese archivo objeto, es decir hacerlo ejecutable
```
ld -o helloworld helloworld.o
```

Para ejecutar el archivo helloworld
```
./helloworld
```

Modos de operación
---
Los procesadores actuales soportan diferentes modos de operación, pero como mínimo disponen de un modo protegido y de un modo supervisor.

 
El modo de **supervisor** es utilizado por el núcleo del sistema para las tareas de bajo nivel que necesitan un acceso sin restricciones al hardware, como puede ser el control de la memoria o la comunicación con otros dispositivos. El modo **protegido**, en cambio, se utiliza para casi todo el resto de las tareas.

El modo de gestión de sistema
---
En este modo se suspende la ejecución normal (incluyendo el sistema operativo) y se ejecuta un software especial de alto privilegio diseñado para controlar el sistema. Tareas habituales de este modo son la gestión de energía, tareas de depuración asistidas por hardware, ejecución de micro hardware o un software asistido por hardware. Este modo es utilizado básicamente por la BIOS y por los controladores de dispositivo de bajo nivel.

Accedemos al SMM mediante una interrupción de gestión del sistema (SMI,system management interrupt). Una SMI puede ser generada por un acontecimiento independiente o ser disparada por el software del sistema por el acceso a una dirección de E/S considerada especial por la lógica de control del sistema.

Registros
---
Son contenedores que usa el procesador para cumplir diferentes tareas la mas general es almacenar datos que se usan frecuentemente.

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/assembler-rough/registros.svg?raw=true">
</p>

Entre estos registros tenemos los de propósito general, indices o apuntadores, de segmento y especiales.

**Registros de propósito general**  
\_AX **(Registro acumulador)**: Es el registro principal, muy utilizado para operaciones de Entrada/salida y operaciones aritmeticas.

\_BX **(Registro Base)**: Usado como puntero a datos o a primer elemento de un vector.

\_CX **(Registro Contador)**: Usado en las instrucciones de repetición o ciclos, almacena el número de veces que se repite una instrucción. Similar al uso que se da a variable `i` en las iteraciones de c++.

\_DX **(Registro datos)**: Utilizado para operaciones de Entrada/salida y operaciones aritmeticas.

**Registros de índices o apuntadores**  
\_SI **(Índice fuente)**: Indica la dirección donde comienzan los datos que se quieren leer de un segmento de datos.  
  
\_DI **(Índice destino)**: Indica la dirección donde terminan los datos que se quieren leer de un segmento de datos.  

\_BP **(Base Pointer)**: Puntero a la cima de la pila.  Utilizado por instrucciones que quieren acceder a datos en la pila.

**Registros de propósito especial**  
\_IP **(Instruction Pointer)**: Apunta a la dirección de la siguiente instrucción que debe ejecutarse.

\_SP **(Stack Pointer)**: Puntero a la cima de la pila, tiene especificamente ese proposito y no puede usarse para almacenar datos pues se perdería la posición de la pila.

FLAGS **(Stack Pointer)**: Es un registro de 64 bits, que es utilizado para indicar el resultado del procesamiento de instrucciones

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/assembler-rough/eflags.svg?raw=t">
</p>

El uso habitual del registro de estado cconsiste en consultar el valor de los bits de forma individual, la información que puede obtenerse de estos bits es la siguiente:
<table border="1">
<tbody><tr>
<th> Bit(s) </th>
<th> Label </th>
<th> Description </th>
</tr>
<tr>
<td> 0 </td>
<td> CF </td>
<td> Carry Flag </td></tr>
<tr>
<td> 1 </td>
<td> 1 </td>
<td> Reserved </td>
</tr>
<tr>
<td> 2 </td>
<td> PF </td>
<td> Parity Flag </td>
</tr>
<tr>
<td> 3 </td>
<td> 0 </td>
<td> Reserved </td>
</tr>
<tr>
<td> 4 </td>
<td> AF </td>
<td> Auxiliary Carry Flag </td>
</tr>
<tr>
<td> 5 </td>
<td> 0 </td>
<td> Reserved </td>
</tr>
<tr>
<td> 6 </td>
<td> ZF </td>
<td> Zero Flag </td>
</tr>
<tr>
<td> 7 </td>
<td> SF </td>
<td> Sign Flag </td></tr>
<tr>
<td> 8 </td>
<td> TF </td>
<td> Trap Flag </td></tr>
<tr>
<td> 9 </td>
<td> IF </td>
<td> Interrupt Enable Flag </td></tr>
<tr>
<td> 10 </td>
<td> DF </td>
<td> Direction Flag </td></tr>
<tr>
<td> 11 </td>
<td> OF </td>
<td> Overflow Flag </td></tr>
<tr>
<td> 12-13 </td>
<td> IOPL </td>
<td> I/O Privilege Level </td></tr>
<tr>
<td> 14 </td>
<td> NT </td>
<td> Nested Task </td></tr>
<tr>
<td> 15 </td>
<td> 0 </td>
<td> Reserved </td></tr>
<tr>
<td> 16 </td>
<td> RF </td>
<td> Resume Flag </td></tr>
<tr>
<td> 17 </td>
<td> VM </td>
<td> Virtual-8086 Mode </td></tr>
<tr>
<td> 18 </td>
<td> AC </td>
<td> Alignment Check / Access Control </td></tr>
<tr>
<td> 19 </td>
<td> VIF </td>
<td> Virtual Interrupt Flag </td></tr>
<tr>
<td> 20 </td>
<td> VIP </td>
<td> Virtual Interrupt Pending </td></tr>
<tr>
<td> 21 </td>
<td> ID </td>
<td> ID Flag </td></tr>
<tr>
<td> 22-63 </td>
<td> 0 </td>
<td> Reserved </td></tr>
</tbody></table>


Representación de los datos
---
db: define una variable de tipo byte, 8 bits.  
dw: define una variable de tipo palabra (word), 2 bytes = 16 bits.  
dd: define una variable de tipo doble palabra (double word), 2 palabras = 4 bytes = 32 bits.  
dq: define una variablede tipo cuádruple palabra (quad word), 4 palabras = 8 bytes = 64 bits.  

La forma de definir variables usando las directivas anteriores es:  
```
nombre_variable directiva valor_inicial
```

También se pueden usar constantes al inicializar variables pero la constante debe haber sido definida antes
```
tamañoVec equ 5
indexVec db tamañoVec
```

Si en lugar de usar valores en decimal quiere usarse valores en hexadecimal deben empezar por 0x, 0h o $ o finalizar con la letra h.
```
var db 0xFF
var dw 0hA3
var db $43
```

Los valores octales deben empezar por 0o o 0q o finalizar con el caracter o o q

Igualmente cuando se realizan operaciones con estos tipos de datos debe agregarse la terminación adecuada, por ejemplo **movq**, **movl**, etc.


