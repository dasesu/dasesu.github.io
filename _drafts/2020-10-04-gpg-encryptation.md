---
layout: post
title: "Encrypted messages and digital signatures"
date: 2020-10-04 22:00:00 -0400
categories: [security]
---

GPG la versión GNu de PGP ( Pritty Good Privacy ) nos permite cifrar información mediante el uso de criptografía de clave pública, así como facilitar la autenticación de documentos gracias a firmas digitales.

Entre sus opciones podemos simplemente encriptar datos , cifrar mensajes para una persona en especifico, firmar digitalmente información y que luego pueda verificarse que los datos firmados no han sido modificada, entre otras.


Supongamos el archivo de una receta familiar muy secreta, por ejemplo:

---
**Ingredientes:**  
  * 1 huevo  
  * 125 g de mantequilla  
  * 1 taza de azúcar mascabado  
  * 1 y media tazas de harina leudante  
  * 1 pizca de sal  
  * 1 taza de chispas de chocolate  

**Preparación:**
  * Precalienta el horno a 180°C.  
  * Bate el huevo y el azúcar juntos hasta lograr una consistencia espumosa y espesa.  
  * Derrite la mantequilla y añade a la mezcla de huevo.  
  * Agrega el harina, sal y chispas de chocolate. Mezcla bien.  
  * Coloca la masa a cucharadas (una cucharada colmada por galleta) sobre una charola para hornear forrada con papel encerado.  
  * Hornea durante 10 minutos. Deja que las galletas se enfríen en la charola.  

---

Cifrado simetrico:
---
La opción `-c` nos permite proteger el archivo con cifrado simetrico, es decir cualquier persona con la misma contraseña podría desencriptar el archivo.
```
gpg -c receta.txt
```

Esta opción nos pide que introduzcamos la contraseña con la cual vamos a proteger el archivo, y una vez hecho esto se creará un segundo archivo cifrado con extensión .gpg que si lo abrimos se verá así

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/gpg-encryptation/simetrico02.png?raw=true">
</p>

como podemos ver es ilegible en caso de que queramos un cifrado equivalente legible podríamos usar la opcion -a, la cual crea el cifrado usando caracteres ascii asi:
```
gpg -c -a receta.txt
```
Esto crearía un archivo cifrado .asc, al abrirlo se vería asi:
```
-----BEGIN PGP MESSAGE-----

jA0ECQMCL0smK1PVFcb/0sDkAWvIQ08thmsojC+2mXtkei/JKaKkdF4DwNTGUzlj
2mDnW1LNWiTfVBDsf+KxUl8KtMYDjq+P+z9RCe/fHxrH+XgvfPD0j/xmepmuzlmE
HcWRhS3Ndu006S7QkoKOl254fdS2zv+4kdPk4EojE3N5M2kPUQ6A19z1pNCn1ghD
Mm58kBFB9LIce2USQx/6iOATAioAu0OjDTDbvgAd+MtwI4R4s/pu4DA2/1rkW8/O
TRp8bO8gkb4lo0bqvSgbb9tDatNwrhpbhu5mau8uge5dI1x8Nnh5tz8HH1F8xlIC
2Y+s1StJZBeY8jBCoLHqWgtCigZRe2Pe9i4sfkBy9F4VuuykK+pC+gUoPBRtD2pQ
0ZQQwhQJko5IVa2NLF95Jhj9mFYRKjysZYK+XzFcUsqt1TisNqi6vmUvgkyMxkoK
l/lLPfPQ374AV1b2TyB5NAR2JoYmPNquR25D/IIylc2mTER6QcmA7YTK0rWWV9Sk
PwjsgQa6cFjBQ8XLXPFuK1yDAX2R9uwEiaoHdF/IQWHLcp1+5SCddn83qY9bWr1g
v2BMrV6/
=uxvT
-----END PGP MESSAGE-----
```

Para descifrar el contenido del archivo usamos la opción -d
```
gpg -d receta.txt.asc
```

Lo que nos mostraria el contenido del archivo original.


  
Cifrado Asimétrico
---
La criptografía de clave publica usa un par de claves, una clave pública y una privada. En pocas palabras la clave pública se comporta como una dirección hacia donde otras personas pueden cifrar mensajes, y unicamente el poseedor de la clave privada asociada a esa clave pùblica pueda descifrar.

Antes de continuar usando el ejemplo de nuestra receta familiar, veamos algunos comandos previos.
Debemos crear un par de claves pùblica y privada.

Generar par de claves publica y privada
```
gpg --gen-key
```

Podemos ver las claves pùblicas que tenemos almacenadas o han sido creadas con el comando:
```
gpg --list-keys
```

Para ver ver las claves privadas que tenemos almacenadas:
```
gpg --list-secret-keys
```

Para exportar la clave publica para almacenarla o compartirla con otras personas
```
gpg --armor --output output_file.asc --export "Some name"
```

Para exportar la clave privada para almacenarla o guardarla de forma segura
```
gpg --armor --output output_file_secret.asc --secret-key --export "Some name"
```

En caso de que tengamos claves previamente guardadas y queramos importarlas hacemos
```
gpg --import public.asc
gpg --import private.asc
```


**Cifrar documento**  
Imaginemos que Alice quiere compartir la receta con Bob, digamos para conservar la paz familiar que ambos son parientes y Alice no esta divulgando tan protegida receta. Alice necesita tener la clave pública de Bob, importarla a su directorio de claves públicas y cifrar el mensaje hacia esa clave pública con el comando:
```
gpg --armor --output file_to_send.gpg --encrypt --recipient "Bob Name"
```

Bob al recibir el mensaje lo descifraría con el comando
```
gpg --output file --decrypt file_to_send.gpg
```

**Firmar documentos:** Con el tiempo la receta puede modificarse accidentalmente, con el temor de que eso ocurra  Alice quiere firmar la receta como la versión original, la única que ella reconoce como válida, para eso utiliza las firmas digitales, esto crea una huella digital de los datos que contiene la receta y su firma asociada generada a partir de la clave privada de Alice, luego cualquiera puede verificar que Alice ha firmado esos datos, no importa si están cifrados o no.

Firma digital y cifrado en binario, esto genera un archivo ilegible como el que vimos anteriormente.
```
gpg --output doc.sig --sign receta.txt
```


Si queremos firmar en ascii usamos
```
gpg --clearsign receta.txt
```

Esto genera un archivo dividido en dos partes, la primera es el mensaje exacto que se esta firmando, cualquier modificación por pequeña que sea hara que la firma sea inválida, la segunda es la firma de dicho mensaje.
```
-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512

Ingredientes:

    1 huevo
    125 g de mantequilla
    1 taza de azúcar mascabado
    1 y media tazas de harina leudante
    1 pizca de sal
    1 taza de chispas de chocolate

Preparación:

    Precalienta el horno a 180°C.
    Bate el huevo y el azúcar juntos hasta lograr una consistencia espumosa y espesa.
    Derrite la mantequilla y añade a la mezcla de huevo.
    Agrega el harina, sal y chispas de chocolate. Mezcla bien.
    Coloca la masa a cucharadas (una cucharada colmada por galleta) sobre una charola para hornear forrada con papel encerado.
    Hornea durante 10 minutos. Deja que las galletas se enfríen en la charola.
-----BEGIN PGP SIGNATURE-----

iQGzBAEBCgAdFiEECQrDeIyWOB3x1EdWt98kgJAC7JAFAl8KZy0ACgkQt98kgJAC
7JBBdAwAwSZqYodiL2AgB35JCQoon4QJKedoNS8PrtpetVoH+c/JeNUNi5HD4c6M
brWLglZKMSdgkIBr5QE841a249Ujy5eAN7y9+PpOJm+Q6LdeSx/IZ1j89bRscacP
0BV6qExgoCNE7xmbvNjCwdIoeyvA6/SVpfqRDhdI3yM8BJVPLCep+70Yv4sM6TY7
06lCTtNSAq2vSYHnsRBhbZZ2hsx7kYvPa6ScfXNyBAl0bBJNeCdZJ3Iu7ofA47Rk
kL/7l4md9jO2H6LSR1aVVmlv4ApiB1PK+PmqtLiY6ortd2bTU5YrRsCwk7j99Hst
vpcTAn48fVgSeQM9Uay7S0xpWM/LSDE4kGvjvb3OeKcTcga5+GzOGf7KeUlc5rdg
NyT45BQHQkqf8SsvGTuf/5nhL3I+c9dIiBAdRB5Av2YdpTJJA94XuT+NmAEQjA+2
bgNC0frPtj1rpvjgjTYY59cN/rf5930o2Ey+fEikRcH03PzRAX8vgOWShilu0ZJD
5PiBbCrF
=J6sM
-----END PGP SIGNATURE-----
```

Si unicamente queremos verificar la firma se usa la opción
```
gpg --verify doc.sig
```
Esto mostraría algo como lo siguiente:
```
gpg: Signature made sáb 11 jul 2020 21:28:13 -04
gpg:                using RSA key 090AC3788C96381DF1D44756B7DF24809002EC90
gpg: Good signature from "Some name <someemail@gmail.com>" [ultimate]
gpg: WARNING: not a detached signature; file 'receta.txt' was NOT verified!
```

En caso de que exista una modificación, por ejemplo cambiamos la cantidad de huevos que lleva la receta diría algo asi:
```
gpg: Signature made sáb 11 jul 2020 21:28:13 -04
gpg:                using RSA key 090AC3788C96381DF1D44756B7DF24809002EC90
gpg: BAD signature from "Some name <someemail@gmail.com>" [ultimate]
```

Si queremos verificar la firma y decriptar un archivo.
```
gpg --output doc --decrypt receta.sig
```
