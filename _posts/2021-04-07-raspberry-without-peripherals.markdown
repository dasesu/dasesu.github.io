---
layout: post
title: "Connect to a Raspberry Pi without any aditional peripheral devices"
date: 2021-04-07 09:10:00 -0400
relatives: raspberry-without-peripherals
categories: [raspberry]
---

Se asume una raspberry con interfaz de red inalámbrica, y una microsd con una distro raspbian (2020-02-13-raspbian-buster ) aunque esto funciona también en otras distros de raspbian.
   


Insertamos la microsd en nuestro sistema operativo para realizar algunos cambios previos, observamos dos particiones boot y rootfs, dentro de la partición boot y crearmos un archivo llamandolo ssh, y agregamos el valor "1" como contenido. Esto habilitará el protocolo ssh para poder acceder remotamente cuando se cargue el sistema operativo.

```bash
$ cd /media/myuser/boot/
$ sudo touch ssh
$ echo "1" > ssh
```


Dentro de la partición rootfs, editamos el archivo wpa_supplicant.conf que se encuentra dentro del directorio /etc/wpa_supplicant
```bash
$ cd /media/myuser/rootfs/etc/wpa_supplicant
$ sudo vi wpa_supplicant.conf
```


Agregamos la configuración de red para que se conecte a nuestra red wifi automaticamente al iniciar el sistema operativo.
```vim
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
country=VE

network={
   ssid="NETWORK-NAME"
   psk="NWTWORK-PASSWORD"
   key_mgmt=WPA-PSK
}
```


Extraemos la microsd y la insertamos en nuestra raspberry pi, conectamos la raspberry a la corriente para que inicie el sistema operativo, esperamos un momento hasta que haya terminado de cargar, aproximadamente 2 minutos


Para poder conectarnos a la raspberry tenemos que encontrar que dirección ha tomado, hay muchas formas de hacer esto, podemos acceder a la configuración de nuestro router y buscar la raspberry entre los dispositivos conectados, probar con varias direcciones IPs hasta encontrar la correcta, en redes pequeñas esto no deberia toma mucho. Nosotros usaremos el comando nmap, cambiando la dirección de red por la que tenga nuestra red, en mi caso la dirección de red es 192.168.0.1
```bash
sudo nmap 192.168.0.100-255
```

Entre el resultado que arroja este comando podemos ver algo parecido a lo siguiente, lo que nos indica que la raspberry se encuentra en la dirección `192.168.0.101`
```
Nmap scan report for 192.168.0.101
Host is up (0.019s latency).
Not shown: 999 closed ports
PORT   STATE SERVICE
22/tcp open  ssh
MAC Address: B8:27:EB:FF:3A:EC (Raspberry Pi Foundation)
```

Nos conectamos usando ssh a la raspberry desde nuestro pc, usando el usuario `pi` y contraseña `raspberry`
```bash 
$ ssh pi@192.168.0.101
```

Ya conectados a la raspberry podemos realizar el resto de configuraciones con el comando:
```
sudo raspi-config
```


