# 🚀 Projet C (Seconde session): Implémentation d’un Remote Shell

**Auteur:** Kyllian Louis  
**Cours:** Développement - IR209  
**Institution:** Henallux  
**Année académique:** 2022-2023  

## 📑 Table des matières
1. [Introduction](#introduction)
2. [Architecture d'un remote shell](#architecture-dun-remote-shell)
3. [Utilisation des sockets](#utilisation-des-sockets)
4. [Évaluation](#évaluation)
5. [Avertissement](#avertissement)
6. [Modalités pratiques](#modalités-pratiques)
7. [Délivrable](#délivrable)
8. [Le plagiat](#le-plagiat)

## 📝 Introduction
Le projet consiste à implémenter un **Remote Shell** en langage C. L'objectif est de créer une interface permettant à un attaquant d'exécuter des commandes à distance sur une machine infectée, en utilisant un serveur (côté victime) et un client (côté attaquant). Ce projet vise à démontrer la compréhension de l'utilisation des sockets pour la communication réseau, ainsi que la mise en œuvre de commandes système de base.

## 🏛️ Architecture d'un remote shell
Le système se compose d'un serveur en boucle d'écoute sur un port défini, et d'un client qui se connecte au serveur. Le client envoie des commandes au serveur, qui les exécute et renvoie les résultats.

## 🔌 Utilisation des sockets
La communication entre le client et le serveur se fait à l'aide de sockets. Les messages échangés sont des flux de bytes, nécessitant une conversion appropriée en chaînes de caractères. Cette communication se fait en **TCP**.

## 📋 Évaluation
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

## ⚠️ Avertissement
La compréhension du code est primordiale. Il est recommandé de privilégier un code simple et propre, capable d'être expliqué en détail. L'ajout de fonctionnalités supplémentaires doit être justifié et compris.

## 📜 Modalités pratiques
- Projet individuel.
- L'étudiant doit être capable de défendre chaque partie du système.
- L'étudiant sera interrogé individuellement sur des concepts théoriques liés au projet.
- Le plagiat est strictement interdit et sera sanctionné.

## 📦 Délivrable
Le projet doit être soumis sur Moodle avant le 13/08/2023 à 23h59. Le délivrable doit inclure :
- Le code source des programmes.
- Documentation détaillée sur le fonctionnement et les choix d'implémentation.
- Référence éventuelle à un dépôt Git.

## ⚖️ Le plagiat
Tout code emprunté doit être dûment référencé. Le plagiat est inacceptable et entraînera une note de zéro.
