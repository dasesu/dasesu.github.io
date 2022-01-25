---
layout: post
title: "Docker-compose"
date: 2021-06-10 21:42:11 -0400
relatives: docker
categories: [linux]
---

Fuentes importantes:  

[!https://docs.docker.com/compose/compose-file/compose-file-v3/](https://docs.docker.com/compose/compose-file/compose-file-v3/)  
[!https://takacsmark.com/docker-compose-tutorial-beginners-by-example-basics/](https://takacsmark.com/docker-compose-tutorial-beginners-by-example-basics/)


## Docker compose
Orquestra un conjunto de contenedores que trabajan en conjunto para realizar una tarea, tal como ocurre con aplicaciones reales en ejecución, por ejemplo un sitio web requiere de archivos, de un servidor que interprete esos archivos pero tambien de consultas a bases de datos. en la practica como se junta todo esto? gracias a docker compose.

Supongamos que queremos ejecutar los siguientes contenedores
```
docker run mmumshad/simple-webapp  
docker run mongodb  
docker run redis:alpine  
docker run ansible  
```

Docker entiende cada uno de estos contenedores como servicios y los agrupa en una etiqueta `servicios` asi  
ejemplo de un archivo docker-compose-yml:
<pre>
services:
  web:_
    imaage:"mmumshad/simple-webapp"
  database:
    image: "mongodb"
  messaging:
    image: "redis:alpine"
  orchestration:
    image: "ansible"
</pre>

Luego ejecutamos el comando:  
`docker-compose up`  

Veamos otro ejemplo:  
Supongamos la ejecución de los siguientes contenedores:  

```
docker run -d --name=redis redis  
docker run -d --name=db postgres:9.4  
docker run -d --name=vote -o 5000:80 voting-app  
docker run -d --name=result -p 5001:80  
docker run -d --name=worker worker  
```

Para conseguir que los contenedores se vean entre si podemos asociar vinculos entre ellos con la opcion links, asi:

docker run --links 
====

```
docker run -d --name=redis redis  
docker run -d --name=db  --link=db:db postgres:9.4  
docker run -d --name=vote -o 5000:80 --link redis:redis voting-app  
docker run -d --name=result -p 5001:80  
docker run -d --name=worker  --link db:db -link redis:redis  worker  
```

Esto que hacemos por comandos está desactualizado (deprecated), lo que se recomienda hacer es incluir esto mismo en el archivo compose-yml asi:

docker-compose.yml
<pre>
redis:
  image: redis
db:
  image: postgres:9.4
vote:
  image: voting-app
  ports:
    - 5000:80
  links:
    - redis
result:
  image: result-app
  ports:
    - 5001:80
  links:
    - db
worker:
  image: worker
  links:
    - redis
    - db
</pre>

a lo que luego ejecutamos el comando:
`docker-compose up`

El archivo anterior corresponde a la versión 1 de docker-compose, en versiones recientes estos parametros se incluyen a un campo llamado servicio y se crea por defecto una red comun a los contenedores, asi que lo siguiente seria mas correcto:

<pre>
service:
  redis:
    image: redis
  db:
    image: postgres:9.4
  vote:
    image: voting-app
    ports:
      - 5000:80
    depends_on:
      - redis
</pre>

En la versión 2 docker crea un contenedor especifico para el proyecto lo que evita tener que hacer la definicion de links. Además si debe espeficarse que servicio debe cargarse primero esto se consigue con el parametro depends_on.

Docker compose herada muchos de los comandos de Docker, muchos de ellos deben ser ejecutados en el directorio que contiene el docker-compose.yml o no será reconocido.

Por ejemplo si queremos listar los procesos del contenedor, dentro del directorio que contiene el proyecto hacemos:  
`docker-compose ps`

Si queremos entrar en la termial de algun servicio:  
`docker-compose exec nombre_servicio /bin/bash`

si queremos listar las redes lo hacemos directamente con comandos docker  
`docker network ls` 

Si queremos ver la estructura de una red en particular. pero debems tener en cuenta que la red por defecto se crea con el nombre del proyecto con el sufijo `_default` a menos que le indiquemos explicitamente el nombre. por ejemplo:  
`docker  network inspect dctest_default`

Un aspecto importante de docker compose es que podemos referirnos al servicio directamente con el nombre del servicio que definamos por ejemplo en el caso 
```
version: "3"

services:
  webserver:
    image: nginx
    restart: always
    ports:
      - "8000:80"
    volumes:
      - ./websites:/usr/share/nginx/html
    depends_on:
      - db
    links:
      - db

  db:
    image: mysql
    environment:
      - MYSQL_ROOT_PASSWORD=redes123
    restart: always
    volumes:
      - db_vol:/var/lib/mysql

volumes:
  db_vol:
```

El servidor puede llamar a la base de datos directamente haciendo referencia a `db` que es  el nombre que hemos indicado para el servicio de base de datos.

Si queremos especificar nuestra propia red definimos la red asi:

```
version: "3"

services:
  app:
    build:
      context: .
      args:
        - IMAGE_VERSION=3.7.0-alpine3.8
    image: takacsmark/flask-redis:1.0
    environment:
      - FLASK_ENV=development
    ports:
      - 80:5000
    networks:
      - mynet
  redis:
    image: redis:4.0.11-alpine
    networks:
      - mynet

networks:
  mynet:
```


Otra cosa que nos permite docker compose es escalar los servicios, por jeemplo en situaciones donde un servicio funcione como un worker podemos indicarle que escale el numero de servicios. Esto dependerá tambien de la configuración de puertos o e que el servicio en cuestión no necesite hacer uso de un puerto en particular, por ejemplo, el siguiente comando lanza el servicio escalando el servicio app a 3 replicas:  
`docker-compose up --scale app=3`

Si queremos relizar algun cambio o sobreescribir alguna configuracion, docker-compose admite el uso de `docker-compose.override.yaml` que basicamente hereda los atributos definidos en docker-compose.yaml pero si se agregan cambios en docker-compose.override.yaml estos se escriben por encima de lo que se encuentra en docker-compose.yaml, es decir los cambios en override tienen mayor precedencia, esto se usa cuando se estan haciendo pruebas en entornos de desarrollo y no se querien modificar los valores de producción.


Fuentes importantes:  

[!https://docs.docker.com/compose/compose-file/compose-file-v3/](https://docs.docker.com/compose/compose-file/compose-file-v3/)  
[!https://takacsmark.com/docker-compose-tutorial-beginners-by-example-basics/](https://takacsmark.com/docker-compose-tutorial-beginners-by-example-basics/)