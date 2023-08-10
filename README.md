<a name="readme-top"></a>

<!-- PROJECT LOGO -->
<br />
<div align="center">
  <a href="https://github.com/Slinkyman12345/IR209-projet-dev/blob/main/Bash_Logo_Colored.png">
    <img src="https://github.com/Slinkyman12345/IR209-projet-dev/raw/main/Bash_Logo_Colored.png" alt="Logo" width="80" height="80">
  </a>

  <h1 align="center">🚀 Projet C (Seconde session): Implémentation d’un Remote Shell</h1>
</div>

<div align="center">
  <i><b>Auteur:</b> Kyllian Louis</i><br>
  <i><b>Cours:</b> Développement - IR209</i><br>
  <i><b>Institution:</b> Henallux</i><br>
  <i><b>Année académique:</b> 2022-2023</i>
</div>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>📑 Table des matières</summary>
  <ol>
    <li><a href="#introduction">📝 Introduction</a></li>
    <li><a href="#architecture-dun-remote-shell">🏛️ Architecture d'un remote shell</a></li>
    <li><a href="#utilisation-des-sockets">🔌 Utilisation des sockets</a></li>
    <li><a href="#évaluation">📋 Évaluation</a></li>
    <li><a href="#avertissement">⚠️ Avertissement</a></li>
    <li><a href="#modalités-pratiques">📜 Modalités pratiques</a></li>
    <li><a href="#délivrable">📦 Délivrable</a></li>
    <li><a href="#le-plagiat">⚖️ Le plagiat</a></li>
    <li><a href="#instruction">📝 Instruction</a></li>
    <li><a href="#code">💻 Code</a></li>
    <li><a href="#roadmap">🗺️ Roadmap</a></li>
  </ol>
</details>

## 📝 Introduction <a name="introduction"></a>
Le projet consiste à implémenter un **Remote Shell** en langage C. L'objectif est de créer une interface permettant à un attaquant d'exécuter des commandes à distance sur une machine infectée, en utilisant un serveur (côté victime) et un client (côté attaquant). Ce projet vise à démontrer la compréhension de l'utilisation des sockets pour la communication réseau, ainsi que la mise en œuvre de commandes système de base.

## 🏛️ Architecture d'un remote shell <a name="architecture-dun-remote-shell"></a>
Le système se compose d'un serveur en boucle d'écoute sur un port défini, et d'un client qui se connecte au serveur. Le client envoie des commandes au serveur, qui les exécute et renvoie les résultats.

## 🔌 Utilisation des sockets <a name="utilisation-des-sockets"></a>
La communication entre le client et le serveur se fait à l'aide de sockets. Les messages échangés sont des flux de bytes, nécessitant une conversion appropriée en chaînes de caractères. Cette communication se fait en **TCP**.

## 📋 Évaluation <a name="évaluation"></a>
### Acquis d'apprentissage
Ce projet vise à évaluer les compétences suivantes :
- Développement d'une application C dans le domaine de la sécurité informatique.
- Compréhension des enjeux de gestion de la mémoire en C.
- Argumentation des choix d'implémentation.

### Critères minimum de réussite
Le projet doit respecter les contraintes suivantes :
- Compilation et fonctionnement sans erreurs.
- Implémentation des programmes serveur et client avec communication via les sockets.
- Exécution des commandes de base (whoami, ifconfig, cat /etc/passwd) et renvoi des résultats.

## ⚠️ Avertissement <a name="avertissement"></a>
La compréhension du code est primordiale. Il est recommandé de privilégier un code simple et propre, capable d'être expliqué en détail. L'ajout de fonctionnalités supplémentaires doit être justifié et compris.

## 📜 Modalités pratiques <a name="modalités-pratiques"></a>
- Projet individuel.
- L'étudiant doit être capable de défendre chaque partie du système.
- L'étudiant sera interrogé individuellement sur des concepts théoriques liés au projet.
- Le plagiat est strictement interdit et sera sanctionné.

## 📦 Délivrable <a name="délivrable"></a>
Le projet doit être soumis sur Moodle avant le 13/08/2023 à 23h59. Le délivrable doit inclure :
- Le code source des programmes.
- Documentation détaillée sur le fonctionnement et les choix d'implémentation.
- Référence éventuelle à un dépôt Git.

## ⚖️ Le plagiat <a name="le-plagiat"></a>
Tout code emprunté doit être dûment référencé. Le plagiat est inacceptable et entraînera une note de zéro.

## 📝 Instruction <a name="instruction"></a>

### Compilation: 

afin de compilé correctement le programme vous devez :

1. Changer les chemins de dossier dans les fichiers :
  - ./CMakeLists.txt
  - ./cmake-build-debug/CMakeCache.txt

2. Vous rendre dans le dossier build et exécuter les deux commandes suivante :

```bash

kali: cmake ..
kali: make

```
En cas d'erreur lors du "cmake ..", cela veux dire qu'un chemin de dossier n'est pas le même que le votre, vous devrez aller le changer. 

Une fois compiler, vous trouverez dans le dossier build un programme client et un programme serveur.

### Utilisation: 

Pour utilisé ses programmes, vous aurez besoin de deux machines kali linux connecté entre elles.

Une machine sera la victime, la où le programme "server" tournera. Pour le lancer, utiliser la commande suivante :

```bash

sudo ./server [PORT]

```

Une foix exécuté, le serveur sera en mode écoute. Il est important de le lancer en premier.

L'autre machine, sera la machine attaquant, la où le programme "client" tournera. Pour le lancer, utiliser la commande suivante :

```bash

sudo ./client [IP SERVEUR] [PORT]

```

Une foix exécuté, si la connexion entre les deux machines focntionnes correctement, vous pourrez exécuter les commandes comme "whoami, ls, etc".

utilisé la commande "exit" pour arrêter le programme.


<p align="right">(<a href="#readme-top">retour en haut</a>)</p>

## 💻 Code <a name="code"></a>

### Server.c 


Serveur de Commandes Sécurisé en C
Ce code source représente un programme en langage C qui met en œuvre un serveur de commandes sécurisé. Voici une explication détaillée des fonctionnalités du code :

Contenu
Inclusions de Bibliothèques : Le code débute en incluant plusieurs bibliothèques nécessaires pour les manipulations de sockets, les opérations sur les chaînes de caractères, la gestion des fichiers et le chiffrement. Les fichiers d'en-tête inclus sont <stdio.h>, <stdlib.h>, <string.h>, <unistd.h>, <sys/socket.h>, <netinet/in.h>, <arpa/inet.h> et <errno.h>. En outre, il intègre les fichiers d'en-tête personnalisés "sender.h", "receiver.h" et "encryption.h".

Redefinition de stderr : Le code redéfinit stderr comme stdout. Cela signifie que les erreurs standard seront affichées sur la sortie standard plutôt que sur la sortie d'erreur standard.

Définition des Constantes : Il définit une constante BUFFER_SIZE avec la valeur 1024. Cette constante est utilisée pour déterminer la taille des tampons de données.

Clés de Chiffrement : Le code définit deux tableaux de caractères, KEY et IV, qui servent respectivement de clé et de vecteur d'initialisation (IV) pour les opérations de chiffrement et de déchiffrement. Ces valeurs sont fournies à titre d'exemple et devraient être gérées de manière plus sécurisée dans un environnement de production.

Fonction Principale (main) :

Vérification des Arguments : Le programme commence par vérifier si le nombre d'arguments passés en ligne de commande est différent de 2. Si ce n'est pas le cas, il affiche comment utiliser le programme et se termine avec le code de sortie 1.

Vérification des Privilèges de Root : Ensuite, il vérifie si le programme est exécuté avec les privilèges de root en utilisant la fonction getuid(). Si ce n'est pas le cas, il affiche un message d'erreur et se termine avec le code de sortie 1.

La suite du code gère la mise en place d'un serveur TCP qui écoute les connexions entrantes et traite les commandes reçues des clients :

Création de la Socket : Il crée une socket en utilisant socket(AF_INET, SOCK_STREAM, 0) et vérifie si la création réussit.

Configuration de l'Adresse du Serveur : Il configure l'adresse du serveur en utilisant une structure sockaddr_in (serverAddress) et initialise le port et l'adresse IP.

Réutilisation de l'Adresse et du Port : Il configure la socket pour réutiliser l'adresse et le port même en cas de déconnexion brutale en utilisant setsockopt.

Liaison de la Socket : Il lie la socket à l'adresse IP et au port en utilisant bind() et vérifie si l'opération réussit.

Mise en Écoute : Il met la socket en mode écoute en utilisant listen() et vérifie si l'opération réussit.

Acceptation de Connexion : Il accepte une connexion entrante en utilisant accept(). Une fois la connexion établie, il affiche l'adresse IP et le port du client connecté.

La boucle principale du programme (marquée par while (1)) traite les commandes reçues du client :

Réception de la Commande : Il reçoit une commande du client en utilisant une fonction appelée receive_command() (définie dans "receiver.h").

Déchiffrement de la Commande : Il déchiffre la commande reçue en utilisant la fonction decrypt() (définie dans "encryption.h") avec la clé et le vecteur d'initialisation définis précédemment.

Vérification de la Commande "exit" : Il vérifie si la commande contient le mot "exit". Si c'est le cas, il envoie une réponse au client indiquant que le serveur a reçu la commande "exit".

Exécution de la Commande : Si la commande ne contient pas "exit", il exécute la commande reçue en utilisant la fonction popen(), ce qui permet d'exécuter la commande en tant que processus. Ensuite, il lit la sortie de la commande et l'envoie au client.

Chiffrement et Envoi de la Réponse : Avant d'envoyer la réponse au client, il chiffre la sortie de la commande à l'aide de la fonction encrypt() et envoie la réponse chiffrée au client en utilisant une fonction appelée send_response() (définie dans "sender.h").

Le code continue de boucler et de traiter les commandes jusqu'à ce qu'une erreur se produise ou que le programme soit arrêté manuellement.

#### En cours de rédaction 

<p align="right">(<a href="#readme-top">retour en haut</a>)</p>

## 🗺️ Roadmap <a name="roadmap"></a>

- [x] Création d'un code de base pour le projet
- [x] Modification du code poure le rendre plus lisible
- [x] Avoir un code client
- [x] Avoir un code server
- [x] Gestion propre de l'arrêt du malware 
- [x] Gestion des versions
- [x] Gestion intelligente des erreurs
- [ ] Déplacement d'un répertoire à un autre
- [ ] Chiffrement des communications
    - [x] Chiffrement avec clé fixe
    - [ ] Chiffrement avec clé générée

<p align="right">(<a href="#readme-top">retour en haut</a>)</p>
