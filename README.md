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
    <li><a href="#Code">💻 Code</a></li>
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

<p align="right">(<a href="#readme-top">retour en haut</a>)</p>

## 💻 Code <a name="code"></a>

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
