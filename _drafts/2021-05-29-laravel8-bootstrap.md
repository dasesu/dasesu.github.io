---
layout: post
title: "Laravel 8 bootstrap"
date: 2021-05-29 12:23:10 -0400
relatives: livewire
categories: [php]
---

## Metodo 1 Livewire with Bootstrap

``` 
composer create-project laravel/laravel testbootstrap
cd testbootstrap
composer require livewire/livewire
```

creamos un archivo el archivo resources/Views/layout.blade.php
```php
<!DOCTYPE html>
<html lang="{ { str_replace('_', '-', app()->getLocale()) }}">
    <head>
        <meta charset="utf-8">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <title>Laravel</title>

        <!-- Fonts -->
        <link href="https://fonts.googleapis.com/css2?family=Nunito:wght@400;600;700&display=swap" rel="stylesheet">

        <!-- Styles -->
        
        @livewireStyles
        <style>
            body {
                font-family: 'Nunito', sans-serif;
            }
        </style>
    </head>
    <body>
        
        @yield('content')
        
        @livewireScripts
    </body>
</html>

```

Modificamos las rutas para que carguen la vista post en lugar de la vista welcome
```php
Route::get('/', function () {
    return view('posts');
});
```

y Cramos el archivo resources/Views/psot.blade.php
```php
@extends('layout')

@section('content')

<div class="container">
  <h1>Hola Livewire</h1>
</div>

@endsection
```

Si vamos a package.json vemos que no se incluye bootstrap
```php
npm install
npm install --save-dev bootstrap
``` 

Si volvemos a package.json podemos ver que ahora si se incluye bootstrap

abrimos el archivo resources/css/app.css e importamos ~bootstrap/dist/css/bootstrap.css
```php
@import "~bootstrap/dist/css/bootstrap.css"
```

y luego hacemos

```
npm run dev
```


## Metodo 2 ( este metodo instal bootstrap 4.6 )
Ademas este metodo ya tiene un sitio preconstruido de login 
```
composer create-project laravel/laravel laravel-bootstrap-metodo2
cd laravel-bootstrap-metodo2
composer require laravel/ui
php artisan ui bootstrap
php artisan ui bootstrap --auth
npm install && npm run dev
```

```
php artisan migrate
```

## Metodo 3 ( Jetstrap )
[https://github.com/nascent-africa/jetstrap](https://github.com/nascent-africa/jetstrap)
```
composer create-project laravel/laravel site-jetstrap
cd site-jetstrap
composer require nascent-africa/jetstrap --dev
php artisan jetstrap:swap livewire
npm install && npm run dev
npm install && npm run dev
php artisan migrate
```