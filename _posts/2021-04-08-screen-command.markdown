---
layout: post
title: "Screen Command"
date: 2021-04-08 15:16:00 -0400
relatives: screen-command
categories: [linux,commands]
---

Para crear una sub terminal por nombre:
```
screen -S name
```
por ejemplo:
```
screen -S sshterminal
```

Para minimizar esa sesión
```
Ctrl + a + d 
```

Para recuperar esa sesión por nombre, buscamos entre las terminales screen abiertas
```
screen -r [tab][tab] 
```

por ejemplo:
```
screen -S codigo
Ctrl + a + d
screen -r codigo
```