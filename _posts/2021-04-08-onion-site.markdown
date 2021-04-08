---
layout: post
title: "Creating an .onion site"
date: 2021-04-08 15:28:10 -0400
relatives: onion-site
categories: [security]
---


# Como instalar un servidor .onion en TOR
**TOR:**
**1.- Instalar Un servidor Debian, Ubuntu o similar** El primer paso para instalar un servidior .onion es tener un servidor donde alojarlo, un servidor debian que podamos administrar de forma local o remota funciona bien.

**2.- Instalar los servicios Web en Debian (LAMP)** Para poder visualizar una página web, un sitio web o cualquier cosa que queramos ver en nuestro dominio .onion debemos hacerlo por medio de un servidor Web como Apache, pero también es posible que deseemos un sitio mas sofisticado que utilice PHP y tal vez que use una base de datos MySQL lo que se llama un servidor LAMP (Linux, Apache, MySQL, PHP).

**3.- Como Instalar TOR y poner el domino .onion en marcha** La instalación de un servicio de este tipo involucra mucho elementos y en este post solo me enfocaré en los necesarios para que se pueda poner en funcionamiento un dominio .onion y que el servicio web se publique mediante este dominio para hacer un Hidden Service accesible mediante la red TOR.

Este post no contempla aspectos de seguridad por lo que no se debe asumir que siguiendo estos pasos se puede implementar un sitio totalmente anónimo y totalmente seguro, para lograr esto se deben considerar otros temas como seguridad del servidor, servicios activos, detectores de intrusos,  VPNs, PROXYs y otros conceptos que no se abordan en este post.

**Instalando TOR en Debian**
Para instalar TOR en Debian requerimos tener instalados algunos paquetes que permitan la compilación, instalación y funcionamiento de TOR. Recuerda que para instalar estos paquetes necesitas estar logueado como root

Instalar los paquetes:
```
sudo apt-get install screen build-essential libevent-dev openssl zlib1g-dev libssl-dev
```
Una vez que tengas estos paquetes instalados debes crear un usuarios al que yo llamaré toruser
```
sudo adduser toruser
```
luego ingresa como el usuario toruser, si estas como root usa el comando su para hacer esto.
``` 
su toruser
cd ~
```
Cuando estés en el directorio del usuario, es decir en la carpeta /home/toruser/ debes crear una carpeta para realizar la instalación de Tor, crea esta carpeta con comando mkdir y luego ubícate en esta carpeta.
```
mkdir tor
cd tor
```
Una vez ahí debes descargar el código fuente de Tor para compilarlo e instalarlo. Para hacer esto, descarga la versión mas reciente desde la siguiente URL: https://www.torproject.org/dist/
En este post manejaré la versión 0.2.4.20 así que descargue el archivo tor-0.2.4.20.tar.gz, te debes descargar la versión mas reciente que encuentres en este sitio. utiliza el comando wget para descargarlo.
```
wget https://www.torproject.org/dist/tor-0.2.4.20.tar.gz
```
Luego descomprime el archivo con el siguiente comando:
```
tar zxf tor-0.2.4.20.tar.gz
```
cambia al directorio que se ha creado en mi caso es este:
```
cd  tor-0.2.4.20
```
luego debes compilar e instalar tor con los comandos siguientes:
```
./configure && make
```
luego debes ejecuta la instalación como root, así que teclea el comando exit para ser de nuevo root.
```
$ exit
#
```
al ver el promt # te indica que estás como usuario root y ahí debes ejecutar el comando make install en la carpeta en la que nos encontrábamos
```
cd /home/toruser/tor/tor-0.2.4.20/
make install
```
El siguiente paso es crear el archivo de configuración de tor
```
cd /usr/local/etc/tor/
cp torrc.sample torrc
```
y editar el archivo torrc con el comando vi
```
vi torrc 
```
en este archivo buscarás la sección donde se definen los hidden services y se lee algo como esto:
```
###This section is just for location-hidden services ###

## Once you have configured a hidden service, you can look at the
## contents of the file ".../hidden_service/hostname" for the address
## to tell people.
##
## HiddenServicePort x y:z says to redirect requests on port x to the
## address y:z.

#HiddenServiceDir /usr/local/var/lib/tor/hidden_service/
#HiddenServicePort 80 127.0.0.1:80

#HiddenServiceDir /usr/local/var/lib/tor/other_hidden_service/
#HiddenServicePort 80 127.0.0.1:80
#HiddenServicePort 22 127.0.0.1:22
```
Luego de estas líneas agregarás lo siguiente:
```
HiddenServiceDir /home/toruser/tor/hidden_service/
HiddenServicePort 80 127.0.0.1:13713
```
configura el puerto que tu quieras en este caso 13713 puedes cambiarlo por un puerto al azar. Una vez que hayas agregado estos cambios presiona Ctrl+X luego  presiona la tecla Y y luego Enter. Con esto grabarás los cambios.
El siguiente paso es modificar el archivo de configuración de apache para responder al mismo puerto, para esto edita el archivo default
```
nano /etc/apache2/sites-available/default
```
y en la linea cambia el valor del puerto por el configurado en el archivo torrc
```
<VirtualHost *:13713>
```
graba el archivo con la misma secuencia Ctrl+X luego la tecla Y y luego Enter. Luego edita el archivo ports.conf
```
nano /etc/apache2/ports.conf
```
y cambia el puerto 80 por el puerto configurado en torrc y configura el servidor apache para que solo responda a solicitudes echas desde el mismo equipo es decir desde 127.0.0.1. La configuración debe quedar asi:
```
NameVirtualHost 127.0.0.1:13713
Listen 127.0.0.1:13713
```
graba los cambios con la misma secuencia de teclas Ctrl+X luego Y y luego Enter. El siguiente paso es probar el servicio apache y arrancar tor
```
service apache2 restart
```
**Poniendo en Marcha tu sitio .onion**
Para arrancar tor te recomiendo que lo hagas con el usuario toruser, así que ejecuta:
```
su toruser
screen tor
```
Para verificar el dominio .onion que se ha creado. Para hacerlo puedes ir a la carpeta /home/toruser/tor/hidden_service/ y ver el contenido del archivo hostname, ahi encontraras tu dominio .onion
```
cat /home/toruser/tor/hidden_service/hostname
imxte3j66fhna6z6.onion
```
Para verificar que tu servicio en TOR esta funcionando puedes abrir tu Tor Browser y teclear o pegar tu dominio en la barra de dirección y aparecerá lo siguiente:   Un punto importante es que para tener un hidden service operando no necesitas tener una IP pública, solo tienes que tener un servicio sin puertos bloqueados por tu ISP y tu servicio estará funcionando en TOR.

