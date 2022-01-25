---
layout: post
title: "Docker Kubernetes"
date: 2022-01-3 21:42:11 -0400
relatives: docker
categories: [linux]
---


Como vamos a trabajar en un cluster, necesitaremos un cluster de servidores, para eso podemos usar cualquiera de los que hay en el mercado por ejemplo AWS, Digital Ocean, Hetzner, etc. Claro que para pruebas podemos usar nuestro pc local.

Existen tambien diferentes clientes para usar Kubernetes por ejemplo k3s, k0s, kubectl.


Usando el cliente Kubectl
===
descargamos e instalamos kubectl
```
curl -LO "https://storage.googleapis.com/kubernetes-release/release/$(curl -s https://storage.googleapis.com/kubernetes-release/release/stable.txt)/bin/linux/amd64/kubectl"
```

Para instalarlo agregamos el kubectl al path
Habilita los permisos de ejecución del binario kubectl.
```
chmod +x ./kubectl
```
Mueve el binario dentro de tu PATH.
```
sudo mv ./kubectl /usr/local/bin/kubectl
```

Para practicar los principios que debemos dominar en kibernetes vamos a usar Minikube
minikube is local Kubernetes, focusing on making it easy to learn and develop for Kubernetes.


All you need is Docker (or similarly compatible) container or a Virtual Machine environment, and Kubernetes is a single command away: `minikube start`

requisitos:  
2 CPUs or more  
2GB of free memory  
20GB of free disk space  
Internet connection  
Container or virtual machine manager, such as: Docker  

1 Installation de minikube
```
curl -LO https://storage.googleapis.com/minikube/releases/latest/minikube-linux-amd64
sudo install minikube-linux-amd64 /usr/local/bin/minikube
```

2 Start your cluster
```
minikube start
```
```
 minikube v1.24.0 on Ubuntu 18.04
 Automatically selected the docker driver
 Starting control plane node minikube in cluster minikube
 Pulling base image ...
 Downloading Kubernetes v1.22.3 preload ...
 > preloaded-images-k8s-v13-v1...: 501.73 MiB / 501.73 MiB  100.00% 154.79 K
 > gcr.io/k8s-minikube/kicbase: 0 B [______________________] ?% ? p/s 57m55s
 Creating docker container (CPUs=2, Memory=2200MB) ...
 Preparing Kubernetes v1.22.3 on Docker 20.10.8 ...
 ▪ Generating certificates and keys ...
 ▪ Booting up control plane ...
 ▪ Configuring RBAC rules ...
 Verifying Kubernetes components...
 ▪ Using image gcr.io/k8s-minikube/storage-provisioner:v5
 Enabled addons: default-storageclass, storage-provisioner
 Done! kubectl is now configured to use "minikube" cluster and "default" name
ce by default
```

3 Interact with your cluster
If you already have kubectl installed, you can now use it to access your shiny new cluster:
```
kubectl get po -A
```

Alternatively, minikube can download the appropriate version of kubectl and you should be able to use it like this:
```
minikube kubectl -- get po -A
```

You can also make your life easier by adding the following to your shell config:
```
alias kubectl="minikube kubectl --"
```
Initially, some services such as the storage-provisioner, may not yet be in a Running state. This is a normal condition during cluster bring-up, and will resolve itself momentarily. For additional insight into your cluster state, minikube bundles the Kubernetes Dashboard, allowing you to get easily acclimated to your new environment:
```
minikube dashboard
```

Deploy applications
---
Create a sample deployment and expose it on port 8080:
```
kubectl create deployment hello-minikube --image=k8s.gcr.io/echoserver:1.4
kubectl expose deployment hello-minikube --type=NodePort --port=8080
```
It may take a moment, but your deployment will soon show up when you run:
```
kubectl get services hello-minikube
```
The easiest way to access this service is to let minikube launch a web browser for you:
```
minikube service hello-minikube
```
Alternatively, use kubectl to forward the port:
```
kubectl port-forward service/hello-minikube 7080:8080
```
Tada! Your application is now available at http://localhost:7080/.

You should be able to see the request metadata from nginx such as the CLIENT VALUES, SERVER VALUES, HEADERS RECEIVED and the BODY in the application output. Try changing the path of the request and observe the changes in the CLIENT VALUES. Similarly, you can do a POST request to the same and observe the body show up in BODY section of the output.

