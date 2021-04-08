---
layout: post
title: "Assembler rough reference - #1 GAS"
date: 2020-10-20 14:39:00 -0400
categories: assembler
---
Estos apuntes no tienen el proposito de explicar ni transmitir las cosas "bonito" ni en orden, sólo de ser una rápida referencia comandos y funcionalidades.


GAS 
===
Para trabajar con **código de 32 bits en equipos de 64 bits** instalamos libc6-dev-i386.
```
$ sudo apt-get install libc6-dev-i386
```
y compilamos con la opción -m32, la opción -g almacena información adicional para poder debuggear posteriormente el archivo ejecutable generado, esta opción es opcional.
```
gcc -m32 -g -o foo code.s
```

Si queremos generar el **archivo objeto relocalizable** compilamos con la opcioón -c
```
gcc -c code.s
```

**Ver código de un programa C en ensamblador**
```
gcc -g -c foo.c
objdump -d -M suffix foo.o
```

**Ver código de un programa C en ensamblador** (metodo 2)
```
$ gcc -S foo.c # genera un archivo de ensamblador .s
$ cat archivo.s # Muestra el contenido de archivo.s
```

**Código en ensabmblador de funciones especificas**
```
$ gcc -g -o foo foo.c
$ gdb foo
(gdb) dissasemble main # Donde main es el nombre de una función
```
