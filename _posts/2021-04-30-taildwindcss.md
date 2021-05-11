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