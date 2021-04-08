---
layout: post
title: "Encrypted messages and digital signatures"
date: 2021-04-08 11:22:00 -0400
relatives: gpg-encryptation
categories: [security]
---

GPG la versión GNu de PGP ( Pritty Good Privacy ) nos permite cifrar información mediante el uso de criptografía de clave pública, así como facilitar la autenticación de documentos gracias a firmas digitales.

Entre sus opciones podemos simplemente encriptar datos , cifrar mensajes para una persona en especifico, firmar digitalmente información y que luego pueda verificarse que los datos firmados no han sido modificada, entre otras.


Supongamos un archivo cualquiera que deba ser cifrado:

---

Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus aliquam varius pellentesque. Suspendisse potenti. In euismod fermentum laoreet. Ut vehicula, sapien nec vehicula aliquam, nibh est feugiat nisi, ut iaculis sem libero eget metus. Duis vehicula ultrices felis, eu vulputate purus scelerisque eget. Vivamus in ex commodo ipsum vehicula malesuada. Vestibulum aliquam sit amet risus a sodales. 

---

Cifrado simetrico:
---
La opción `-c` nos permite proteger el archivo con cifrado simetrico, es decir cualquier persona con la misma contraseña podría desencriptar el archivo.

```
gpg -c mensaje.txt
```

Esta opción requiere una contraseña con la cual se va a proteger el archivo, y una vez hecho esto se creará un segundo archivo cifrado con extensión .gpg. 

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/{{page.relatives}}/01_simetrico.png?raw=true">
</p>

Puede verse que el resultado de mensaje.txt.gpg es ilegible, en caso de que queramos un cifrado equivalente legible podríamos usamos la opcion `-a`, la cual crea el cifrado usando caracteres ascii asi:
```
gpg -c -a mensaje.txt
```
Esto crearía un archivo cifrado .asc, al abrirlo se vería asi:
```
-----BEGIN PGP MESSAGE-----

jA0ECQMCfLu69I04w8D/0sBxAeWSJJoW1s62zIPebiZ//UCeoRbj/95U+tI4/XME
w2L1geSffC2hQ98F8sg7edS/HPU+aP7GaJE7al8YwDB53dAp84NJ33m1jUcFtCwX
56l+O//sm6tbkqEK52xDIuRoGfom2k26QJZJ5l8bn2Gg0XMe1Ktp8xvEL1i9O9rX
xXEFvC9d8B6rxBGpTGsPReuA0srjZUMF+F4Du+Qh5K1x11Apqr3ij0COXQb5cjYX
RrlP5bgxTTNb1TA/Kr54yit7a+a/dIRL5zyyM/pNV/k8/HKBCyVhb7aiOtQ9SJBq
AmNZua+W2J3voqBSOaRHzrcQNKUUFe58l8WdEc6rNVjAhG8vBIbZz1/ceRGydkGe
8ZbzYvKgBTsVy+d8dJHhvedPcAootFNlAnfO7DZFe8LsG6M=
=Gq/o
-----END PGP MESSAGE-----

```

Para descifrar el contenido del archivo usamos la opción -d. Lo que retornaria el contenido del archivo original.
```
gpg -d mensaje.txt.asc
```
<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/{{page.relatives}}/02_simetrico.png?raw=true">
</p>



Cifrado Asimétrico
---
La criptografía de clave publica usa un par de claves, una clave pública y una privada. En pocas palabras la clave pública se comporta como una dirección hacia donde otras personas pueden cifrar mensajes, y unicamente el poseedor de la clave privada asociada a esa clave pùblica pueda descifrar.

Es necesario definir algunos comandos antes de continuar con el cifrado de nuestro mensaje esta vez de forma asimetrica.

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
Imaginemos que Alice quiere compartir el mensaje con Bob. Alice necesita tener la clave pública de Bob, importarla a su directorio de claves públicas y cifrar el mensaje hacia esa clave pública con el comando:
```
gpg --armor --output file_to_send.gpg --encrypt --recipient "Bob Name"
```

Bob al recibir el mensaje lo descifraría con el comando
```
gpg --output file --decrypt file_to_send.gpg
```

**Firmar documentos:** 
Para evitar  modificaciones del mensaje que puedan comprometer a Alice. Se puede firmar el mensaje para dar fe de que es versión válida, para eso utiliza las firmas digitales, esto crea una huella digital de los datos que contiene la mensaje y su firma asociada generada a partir de la clave privada de Alice, luego cualquiera puede verificar que Alice ha firmado esos datos, no importa si están cifrados o no.

Firma digital y cifrado en binario, esto genera un archivo ilegible como el que vimos anteriormente.
```
gpg --output doc.sig --sign mensaje.txt
```

Si queremos firmar en ascii usamos
```
gpg --clearsign mensaje.txt
```

Esto genera un archivo dividido en dos partes, la primera es el mensaje exacto que se esta firmando, cualquier modificación por pequeña que sea hara que la firma sea inválida, la segunda es la firma de dicho mensaje.
```
-----BEGIN PGP SIGNED MESSAGE-----
Hash: SHA512
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Phasellus aliquam varius pellentesque. Suspendisse potenti. In euismod fermentum laoreet. Ut vehicula, sapien nec vehicula aliquam, nibh est feugiat nisi, ut iaculis sem libero eget metus. Duis vehicula ultrices felis, eu vulputate purus scelerisque eget. Vivamus in ex commodo ipsum vehicula malesuada. Vestibulum aliquam sit amet risus a sodales. 

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
gpg: WARNING: not a detached signature; file 'mensaje.txt' was NOT verified!
```

En caso de que exista una modificación, diría algo asi:
```
gpg: Signature made sáb 11 jul 2020 21:28:13 -04
gpg:                using RSA key 090AC3788C96381DF1D44756B7DF24809002EC90
gpg: BAD signature from "Some name <someemail@gmail.com>" [ultimate]
```

Si queremos verificar la firma y decriptar un archivo.
```
gpg --output doc --decrypt mensaje.sig
```
