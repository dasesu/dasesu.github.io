#cambiar el nombre de red que tiene por defecto el ubuntu desde versiones mas recientes a wlan0

instalar
```
sudo apt-get install firmware-b43-installer
```
luego hacer 
```
sudo modprobe -r b43
sudo modprobe -r bcma
sudo modprobe -r wl
sudo modprobe -r brcmsmac
```
Y luego montamos la interfaz que haga falta
```
modprobe b43
... ( en caso de que hagan falta mas las agregamos )
```
