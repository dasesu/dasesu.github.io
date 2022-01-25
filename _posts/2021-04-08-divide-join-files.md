---
layout: post
title: "Divide and join files"
date: 2021-04-08 15:11:00 -0400
relatives: divide-join-files
categories: [linux,commands]
---

## Cortar y volver a unir archivos

Cortar: Corta un archivo en partes de 10mb
```
split -b 10m archivo prefijo
```

Unir
```
cat prefijo* > archivo
```
