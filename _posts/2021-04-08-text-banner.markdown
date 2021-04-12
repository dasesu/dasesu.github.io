---
layout: post
title: "Banner ascii on the terminal"
date: 2021-04-08 15:28:10 -0400
relatives: text-banner
categories: [linux]
---

## Crear banners con caracteres ascii
Usando el programa figlet y fuentes personalizadas
``` 
$ wget http://www.figlet.org/fonts/univers.flf  
$ figlet -f univers.flf "Hello World"  
```
<pre>                  
                                           
88        88            88 88              
88        88            88 88              
88        88            88 88              
88aaaaaaaa88  ,adPPYba, 88 88  ,adPPYba,   
88""""""""88 a8P_____88 88 88 a8"     "8a  
88        88 8PP""""""" 88 88 8b       d8  
88        88 "8b,   ,aa 88 88 "8a,   ,a8"  
88        88  `"Ybbd8"' 88 88  `"YbbdP"'   
                                           
                                           
                                                            
I8,        8        ,8I                      88          88 
`8b       d8b       d8'                      88          88 
 "8,     ,8"8,     ,8"                       88          88 
  Y8     8P Y8     8P  ,adPPYba,  8b,dPPYba, 88  ,adPPYb,88 
  `8b   d8' `8b   d8' a8"     "8a 88P'   "Y8 88 a8"    `Y88 
   `8a a8'   `8a a8'  8b       d8 88         88 8b       88 
    `8a8'     `8a8'   "8a,   ,a8" 88         88 "8a,   ,d88 
     `8'       `8'     `"YbbdP"'  88         88  `"8bbdP"Y8 
                                                             
</pre>