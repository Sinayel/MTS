# Clonage de Ressources Minecraft (MTS)

## Description

<span style="color: #ff5733">## Titre en couleur</span>

Ce projet est un utilitaire en langage C conçu pour simplifier le processus de clonage de ressources dans un ressource pack Minecraft. Il est utile pour les développeurs qui travaillent sur des packs de ressources pour le jeu.

## Fonctionnalités

- Cloner des fichiers depuis un ressource pack source vers un ressource pack de destination.
- Séparer les ressources en plusieurs catégories telles que "blocks", "items", "particle", et "font".

## Comment ça marche

1. **Configuration des chemins :** Définissez les chemins source et de destination dans le code pour votre projet spécifique.

2. **Exécution du programme :** Compilez et exécutez le programme en spécifiant les chemins source et de destination.

3. **Clonage des ressources :** Le programme copie les fichiers depuis les dossiers source vers les dossiers de destination appropriés, en conservant la structure de catégories.

## Utilisation

### Prérequis

- Un environnement de développement C configuré sur votre système.

### Clonage et exécution

1. Clonez ce référentiel sur votre machine locale.

2. Compilez le code source à l'aide d'un compilateur C de votre choix.

3. Exécutez le programme en spécifiant les chemins source et de destination appropriés.

Exemple :

```bash
$ ./cloner-ressources chemin/source chemin/destination
```

## À Rajouter

Ce tableau présente les fonctionnalités et les améliorations prévues pour l'avenir de ce projet :

| Fonctionnalité           | Description                                                                                              |
|--------------------------|----------------------------------------------------------------------------------------------------------|
| Interface Graphique (GUI)| Ajouter une interface graphique conviviale pour faciliter la sélection des dossiers source et de destination.   |
| Nouvelles Catégories     | Étendre les catégories de ressources pour permettre l'ajout de nouvelles catégories personnalisées.     |
| Prise en Charge des Autres Objets | Prendre en charge d'autres objets du jeu Minecraft, tels que les modèles d'entités, les sons, les fichiers de langues, etc. |

