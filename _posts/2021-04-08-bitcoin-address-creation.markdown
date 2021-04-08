---
layout: post
title: "Create Bitcoin Address with python"
date: 2021-04-08 10:18:00 -0400
relatives: bitcoin-address-creation
categories: [bitcoin,python]
---

Wallets
---
Las Wallets llamadas también Carteras o monederos, son algo asi como el sitio donde "almacenamos" criptomonedas, en realidad las criptomonedas no se almacenan en la cartera, la propiedad de criptomonedas queda registrada en la red bitcoin que se encuentra distribuida alrededor del mundo en forma de registros de transacciones.


Bitcoin y otras criptomonedas usan protocolos y algoritmos reconocidos internacionalmente para el cifrado de la información. Bitcoin usa el crifrado de clave pública, es decir que para garantizar la pertenencia de criptomonedas y realizar transferencias de estas, se necesitan dos claves únicas: clave pública y clave privada. Básicamente un wallet es poseer estas dos claves.


Podemos ver la clave pública como una dirección que podemos compartir libremente y que nos permite la recepción de monedas. Es como el número de cuenta del banco, cualquiera que lo tenga puede enviarte dinero, pero no puede disponer de lo que tengas allí ahorrado.


La clave privada se parece mas a la contraseña que nos da total acceso a las criptomonedas transferidas hacia una clave pública. La clave pública se genera a partir de la clave privada, y solo con la clave privada pueden firmarse las transacciones salientes desde una clave pública.


Los usuarios comunmente no necesitan comprender como funcionan estos algoritmos, de la misma forma que no necesitmos comprender la tecnología magnetica o chip asociada a las tarjetas de debito o crédito, sin embargo, si queremos desarrollar aplicaciones o sacar el maximo provecho de las que existen es importante conocer mejor su funcionamiento.



Como se genera una dirección bitcoin
---

**Claves Privadas**   
Las claves privadas son usadas para comprobar la pertenencia de los fondos usados en una transacción, estas claves permiten crear firmas que son requeridas para transferir fondos.

Es importante que estas claves se mantengan secretas de lo contrario cualquier persona puede retirar los fondos.

Es importante generar las claves de forma realmente aleatoria, basicamente la clave privada consiste en un número entre 1 y 2^256

**Wallet Import Format (WIF)**   
Las Wallet Import Format(`WIF`) son una manera mas compacta de representar las claves privadas. consisten en la codificación Base58 de `Prefijo` + `clave privada` + `checksum`.

Este incorpora dígitos de control para la detección de errores, que en el formato hexadecimal no podrían ser detectados. El WIF es la notación mas habitual para las claves privadas Bitcoin.

Las claves privadas asociadas a claves públicas no comprimidas constan de 51 caracteres que comienzan siempre por el número 5. Las claves privadas asociadas a claves públicas comprimidas constan de 52 caracteres y comienzan por una L o K mayúscula.

Cuando se importa una clave privada, esta corresponde siempre exactamente a una dirección Bitcoin. Cualquier herramienta que lleve a cabo la conversión ha de ser capaz de mostrar la dirección Bitcoin correspondiente. Las reglas matemáticas de conversión son complicadas y es mejor dejar el cálculo en manos de un ordenador, pero todo programa que sepa manejar claves privadas y direcciones Bitcoin deducirá exactamente la misma dirección Bitcoin a partir de una clave privada dada.

**Codificación Base58**   
Es una codificación para representar grandes numeros enteros como texto alfanumerico. Es similar a Base64, pero ha sido modificado para evitar ambiguedades de caracteres que pueden parecer el mismo, por lo tanto está diseñado para facilitar su lectura una vez ha sido impreso. Comparado con Base64 se excluyen los caracteres 0 (cero), O (o mayuscula), I (i mayuscula) y l (L minuscula) además de caracteres no alfanumericos como el + y el /.

**Clave Pública**   
 La clave pública es generada a partir de la clave privada usando algoritmos de curvas elipticas. Lo importante de estos algoritmos es que es facil generar una clave pública a partir de la clave privada pero la operación inversa es prácticamente imposible. Bitcoin usa el algoritmo de curva eliptica de `secp256k1`.

Veamos el proceso y que otras cosas ocurren para la generación de un par de claves pùblica y privada.

<p align="center">
<img src="{{site.baseurl}}/assets/img/posts/{{page.relatives}}/Address_map.jpg?raw=true">
</p>

Generando una clave Privada
---
Generamos una clave privada aleatoria a partir de 32 bytes.   

```python
import os, binascii, hashlib, base58, ecdsa

# Generar la clave privada
priv_key = os.urandom(32)
print(priv_key.encode('hex'))
```

Esto retorna una clave aleatoria similar a esta: `5af0367c0a9c051a973c8718b2c94cfed82df17dff79994211145643fe24f492`

Se agrega el prefijo respectivo, para una Main Network en Bitcoin se usa el prefijo "`0x80`", en el caso de una testnet el prefijo es `0xEF`.   

 ```python
import os, binascii, hashlib, base58, ecdsa

# Generar la clave privada
priv_key = os.urandom(32)
print(priv_key.encode('hex'))

# Se agrega el prefijo correspondiente, ver el listado de prefijos.
ptwifprefix = '\x80' + priv_key
print(ptwifprefix.encode('hex'))
```

Obtenemos el código de comprobación obtenido de realizar la operación hash sha256 2 veces consecutivas sobre la clave privada con su prefijo. Este código de comprobación consiste en tomar los primeros 4 bytes (8 dígitos del hexadecimal).   

 ```python
import os, binascii, hashlib, base58, ecdsa

# Generar la clave privada
priv_key = os.urandom(32)
print(priv_key.encode('hex'))

# Se agrega el prefijo correspondiente, ver el listado de prefijos.
ptwifprefix = '\x80' + priv_key
print(ptwifprefix.encode('hex'))

# SHA-256 hash del resultado de la operacion anterior
wif1sha256 = hashlib.sha256(ptwifprefix)
print(wif1sha256.digest().encode('hex'))

# SHA-256 hash del resultado de la operacion anterior                                                 4
wif2sha256 = hashlib.sha256(wif1sha256.digest())                                         
print(wif2sha256.digest().encode('hex'))

 # Se toman los 4 primeros bytes como checksum
wifchecksum = wif2sha256.digest()[:4]
print( wifchecksum.encode('hex') )

# Concatenamos la clave privada que incluye el prefijo mas el checksum obtenido previamente
addwifchecksum = ptwifprefix + wifchecksum
print( addwifchecksum.encode('hex') )

```

Finalmente codificamos a Base58 la clave privada con su prefijo + código de comprobación, el resultado de esto es la clave privada en notación WIF.   

```python
...
# Convertimos a base58 el resultado del paso anterior
WIF = base58.b58encode( addwifchecksum )
print("Wallet Import Format " + WIF)
...
```

Obteniendo por ejemplo una clave similar la siguiente: `529r39Bz9hgY2Wb7JWjxdFbk6aFtmhxP9wa234GfXAwmrPuWZgH`, notese que esta clave comienza por 5


Generando una clave Pública
---
Continuando a partir del resultado anterior veamos como es el proceso de generar una clave pública.

Obtenemos la firma de la clave privada aplicando el algoritmo de curva elíptica a la representación hexadecimal de original sin prefijo agregado ni modificación de formato.

```python
import os, binascii, hashlib, base58, ecdsa

# Generar la clave privada
priv_key = os.urandom(32)
print(priv_key.encode('hex'))

sk = ecdsa.SigningKey.from_string(priv_key, curve=ecdsa.SECP256k1)
vk = sk.verifying_key
pubKey=('\04'+sk.verifying_key.to_string())
print( pubKey.encode('hex') )
```

Los algoritmos usados para obtener la dirección bitcoin a partir de la clave pública son el Secure Hash Algorithm (SHA) y el RACE Integrity Primitives Evolution Message Digest (RIPEMD), especificamente `SHA256` y `RIPEMD160`.

Realizamos una operación hash sha256 sobre la clave pública obtenida en el paso anterior 

```python
...

# 2 SHA-256 hash de pubKey
ptafirstsha256 = hashlib.sha256(pubKey)
print( ptafirstsha256.digest().encode('hex') )
...
```


Al resultado anterior se le aplica la función hash ripem160.   

```python
...
# 3 RIPEMD-160 Hash a la variable ptafirstsha256
hash160 = ripemd160( ptafirstsha256.digest() )
print( hash160.digest().encode('hex') )
...
```

Agregamos el prefijo asociado al tipo de dirección que queramos generar ( ver la lista de prefijos ), y aplicamos la función hash sha256 una segunda y una tercera vez.   

```python
...
# Agregamos el prefijo para la red que estemos usando. por ejemplo en el caso de la Main Network el prefijo es "0x00"
ptaprefix = '\x00'+hash160.digest()   # cambiar el prefijo dependiendo de la red
print( ptaprefix.encode('hex') )
...
```

Calculamos el checksum aplicando la función hash una segunda y tercera vez al resultado anterio   

```python
...
# 5  SHA-256 hash aplicado a ptaprefix
ptasecondsha256 = hashlib.sha256(ptaprefix)
print(ptasecondsha256.digest().encode('hex'))

# SHA-256 hash aplicado a ptasecondsha256
ptathirdsha256 = hashlib.sha256(ptasecondsha256.digest())
print(ptathirdsha256.digest().encode('hex') )

# Tomamos los primeros 4 bytes como checksum
checksum = ptathirdsha256.digest()[:4]
print( checksum.encode('hex') )
...
```

Concatenamos la clave publica `ptaprefix` al checksum obtenido y convertimos lo obtenido a base58.   

```python
...
addchecksum = ptaprefix + checksum
print( addchecksum.encode('hex') )

public_address = base58.b58encode( addchecksum )
print( public_address )
...
```

[Full Code]({{site.baseurl}}/codes/{{page.relatives}}/generador_claveprivada_direccionbitcoin.py)