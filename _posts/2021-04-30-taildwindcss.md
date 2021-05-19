---
layout: post
title: "Tailwindcss"
date: 2021-04-30 16:23:10 -0400
relatives: tailwindcss
categories: [linux]
---


## Taildwind CSS
```
composer create-project laravel/laravel tailwind
npm install
npm install tailwindcss
```

agregamos lo siguiente a nuestro archivo resources/css/app.css
```
@import "tailwindcss/base";
@import "tailwindcss/components";
@import "tailwindcss/utilities";
```

Luego si estamos usando laravel mix agregamos `require("tailwindcss"),` a nuestro archivo `webpack.mix.js` de modo que quede asi:
```js

mix.js('resources/js/app.js', 'public/js')
    .postCss('resources/css/app.css', 'public/css', [
        require("tailwindcss"),
    ]);
```

Luego compilamos, eso va a generar una carpeta css y una js dentro del directorio public
```
npm run dev
```

Para incluirlo en nuestro proyecto usamos la vista welcome.blade.php por ejemplo con el siguiente contenido
```html
<!DOCTYPE html>
<html>
<head>
    <title>Taildwind</title>
    <link rel="stylesheet" type="text/css" href="{ {asset('css/app.css')}}">
</head>
<body>

</body>
</html>
``` 

Para comprobar que funciona agregamos las etiquetas 
``` 
<body>
  <h1>Este es un h1</h1>    
  <h2>Este es un h2</h2>    
  <h3>Este es un h3</h3>    
  <h4>Este es un h4</h4>    
  <h5>Este es un h5</h5>    
  <h6>Este es un h6</h6>    
</body>
``` 

## Clases de Tailwindcss

**clase container**
Funciona similar al container de bootstrap pero no impone su diseño por lo qu ecrea un contenedor que no tiene estilo tampoco esa centrado, para centrar el contenido de un div agregamos la clase `mx-auto`

Para crear nuestro propio archivo de configuración de las clases que vienen por defecto en tailwind usamos el comando, esto crea un archivo de configuracion : tailwind.config.js lo agrega en la raiz del proyecto
```
npx tailwindcss init
```

en ese archivo en el objeto theme agregamos la clase que queremos modificar, por ejemplo para modificar un container
```
  theme: {
    extend: {},
  },
``` 

quedando asi
```
theme: {
    container: {
      center: true,
    },
    extend: {},
  },
```

Para la maquetación de las grid le indicamos a tailwind en cuantas columnas quiero dividir la sección usando la instrucción `grid grid-cols-4` por ejemplo
```
  <div class="container grid grid-cols-4">
    <h1>Este es un h1</h1>
    <h2>Este es un h2</h2>
    <h3>Este es un h3</h3>
    <h4>Este es un h4</h4>
    <h5>Este es un h5</h5>
    <h6>Este es un h6</h6>
  </div>

```


Taildwind ofrece colores por defecto que van por tonalidades [https://tailwindcss.com/docs/background-color](https://tailwindcss.com/docs/background-color)
```
  <div class="container">
    <div class="grid grid-cols-4" >
      <div class="bg-blue-200">A</div>
      <div class="bg-blue-300">B</div>
      <div class="bg-blue-400">C</div>
      <div class="bg-blue-500">D</div>
      <div class="bg-blue-600">D</div>
      <div class="bg-blue-700">D</div>
    </div>
  </div>
```

Si quiero agregar espaciado entre filas y columnas `gap-4` si quiero que sea solo entre las columnas `gap-x-4` si quiero que sea en el eje y `gap-y-4`

Tailwind se apega al principio de mobile first asi que quando definimos vistas responsivas definimos la pequeña primero y luego lo indicamos con las instrucciones 
<pre>
sm  640px @media (min-width: 640px) { ... }
md  768px @media (min-width: 768px) { ... }
lg  1024px  @media (min-width: 1024px) { ... }
xl  1280px  @media (min-width: 1280px) { ... }
2xl 1536px  @media (min-width: 1536px) { ... }
</pre>

asi si queremos definir que se vea con una columna en pequeño pero un poco mas grande con 2 columnas hacemos 
```
grid grid-cols-1 sm:grid-cols-2
```

Tailwind se puede dividir hasta n 12 columnas pero si quisieramos que se divida en mas columnas podemos hacerlo modificando la propieda 
```
  // tailwind.config.js
  module.exports = {
    theme: {
      extend: {
        gridTemplateColumns: {
          // Simple 16 column grid

         '16': 'repeat(16, minmax(0, 1fr))',

          // Complex site-specific column configuration

         'footer': '200px minmax(900px, 1fr) 100px',
        }
      }
    }
  }
```

Luego de realizar los cambios volvemos a compilar con 
```
npm run dev
```

Luego de hacer esto podríamos dividir en 16 columnas

Con la instrucción `ccol-span-x` podemos indicarle a un div que ocupe x cantidad de espacios por ejemplo si tienemos esto
```
  
  <div class="container">
    <div class="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-4 gap-2" >
      <div class="bg-blue-200 lg:col-span-2">A</div>
      <div class="bg-blue-300">B</div>
      <div class="bg-blue-400">C</div>
      <div class="bg-blue-500">D</div>
      <div class="bg-blue-600">D</div>
      <div class="bg-blue-700">D</div>
    </div>
  </div>

```

el campo A ocuparia 2 columnas, a esto tambien le podemos aplicar la especificación md: lg: sm: etc asi podria tomar una cantidad diferente de espacios segun sea la resolución del dispositivo

La etiqueta start le indica desde donde quiero que empiece desde la columna numero 2, taildwind enumera las columnas donde la primera es 1 la segunda es 2 y asi sucesivamente
```
<div class="bg-blue-200 col-span-2 col-start-2">A</div>
```

Si ademas indicamos la cantidad de filas que tiene un campo podemos tambien pedir que un determinado campo ocupe varias filas de la misma forma que hicimos con las columnas por ejemplo el campo C ocuparia 2 filas
```
  <div class="container">
    <div class="grid grid-cols-1  grid-cols-4 grid-rows-2 gap-2" >
      <div class="bg-blue-200">A</div>
      <div class="bg-blue-300">B</div>
      <div class="bg-blue-400 col-span-2 row-span-2">C</div>
      <div class="bg-blue-500">D</div>
      <div class="bg-blue-600">D</div>
      <div class="bg-blue-700">D</div>
    </div>
  </div>
```

La instrucción `grid-fow-col` hace que el contenido se despliegue verticalmente en lugar de horizontalmente
en lugar de quedar 
<pre>
  a b c 
  d e f
</pre>

quedaria 
<pre>
a c e
b d f
</pre>

por ejemplo:
```
  <div class="container">
    <div class="grid grid-flow-col grid-rows-3" >
      <div class="bg-blue-200">A</div>
      <div class="bg-blue-300">B</div>
      <div class="bg-blue-400">C</div>
      <div class="bg-blue-500">D</div>
      <div class="bg-blue-600">E</div>
      <div class="bg-blue-700">F</div>
      <div class="bg-blue-800">G</div>
      <div class="bg-blue-900">H</div>
    </div>
  </div>
``` 

## Formateado y tipografias

Tailwind ofrece 3 tipografias por defecto que se incluyen como clases en nuestras etiquetas
por ejemplo `div class=font-sans` 

* font-sans
font-family: ui-sans-serif, system-ui, -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, "Noto Sans", sans-serif, "Apple Color Emoji", "Segoe UI Emoji", "Segoe UI Symbol", "Noto Color Emoji";

* font-serif
font-family: ui-serif, Georgia, Cambria, "Times New Roman", Times, serif;

* font-mono
font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;



indicamos el tamaño de las fuentes con las directivas
```
text-xs
text-sm
text-base
text-lg
text-xl
text-2xl
text-3xl
text-4xl
text-5xl
```

Supongamos que quiero definir el estilo que deseo que tenga mi h1 asi
``` 
font-sans text-6xl md:text-3xl font-bold mb-4
```

Para estandarizar eso, o colocarlo en un unico sitio nos vamos al archivo resources como si fuese nuestra definición css
en resources/css/app.css aqui originalmente esabamos importando todos los estilos de tailwind  y lo definiriamos similar a como hemos hecho en nuestra etiqueta pero eliminando las indicaciones del responsive sm md lg etc  asi para el ejemplo anterior de un h1 quedaria asi, luego de hacer los cambios es necesario recompilar con `npm run dev`

```
// file resources/css/app.css
@layer base {
  h1 {
    @apply font-sans text-3xl font-bold mb-4;
  }

  h2 {
    @apply text-xl;
  }
}
```

Ahora como podemos hacer para que conserve el responsive al agregar a app.css¿ 

Agregar mis propias fuentes
Una forma rapida es usar las fuentes de google asi [https://fonts.google.com/](https://fonts.google.com/) seleccionar la fuente en sus diferentes grosores y a la derecha tengo la opción `use on the web`, alli selecciono `@import` y selecciono lo que se encuentra dentro de la etiqueta style
``` 
@import url('https://fonts.googleapis.com/css2?family=Roboto:wght@100;300;400;500;700;900&display=swap');
``` 

Esto lo agregamos en resources/css/app.css y luego necesitamos indicar un nombre con el cual vamos a usar esa fuente
esto lo hacemos en el archivo de configuración tailwind `tailwind.config.js` dentro de la instrucción theme asi, Despue de agregar esto es necesario recompilar con `npm run dev`:
```
module.exports = {
  purge: [],
  darkMode: false, // or 'media' or 'class'
  theme: {

    fontFamily: {
      'robot': ['Roboto']
    },

    container: {
      center: true,
    },

    ...
```

Para incluir la fuente en el contenido usamos la clase `font-<nombre-asignado>` por ejemplo `font-robot` asi:
  ```
  <p class="font-robot"> Hola mundo </p>
  ```

Si queremos compilar un archivo adicional por ejemplo nuestro proprio archivo style.css lo incluimos en nuestro archivo app.css asi
```
@import "style.css"
```