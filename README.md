# EDD - Problème du voyageur de commerce

Le but du projet est de fournir une interface permettant de répondre au problème du voyageur de commerce.  
Au minimum, le programme doit calculer des solutions au problème du voyageur de commerce métrique.  

### Spécifications techniques

Pour le fonctionnement de l'interface graphique, il est nécessaire d'avoir installer [SDL2 (>2.0.3)](http://www.libsdl.org/download-2.0.php), [SDL2-TTF (>2.0.12)](http://www.libsdl.org/projects/SDL_ttf/) et [FreeType (>2.5.3)](http://www.freetype.org/download.html).

### Fonctionnalités du projet
  - [x] Développer une heuristique simple
  - [x] Développer un algorithme d'approximation
  - [x] Développer un algorithme exact par recherche exhaustive
  - [x] Développer un algorithme exact utilisant la technique de *branch and bound*
  - [x] Pouvoir charger des instances de problèmes au format *TSPLIB*
  - [x] Compilation et installation simple
  - [x] Tester chaque partie du code
  - [x] Automatiser les tests
  - [x] Réaliser le compte-rendu intermédiaire
  - [x] Optionnel - Réaliser une interface graphique

### Personnes composant le groupe de projet
  - Kinda Al Chahid (DakKamui)
  - Florian Kauder (Lumi-Bjorn)
  - Amélie Guemon (pouwapouwa)
  - Lilian Champroy (PurpleSeaSigma)

### Partage des tâches

#### Heuristique simple - Nearest Neighbour

    Amelie - Création algorithme en un fichier unique  
    Florian - Répartition de l'algorithme en 3 fichiers (header,test,module)

#### Algorithme d'approximation - Minimum Spanning Tree

    Amelie - Création nouvelle branche MST  
    Lilian - Création de l'algorithme - Code - Tests
    
#### Algorithme exact par recherche exhaustive - Bruteforce

    Florian - Création de l'algorithme - Code - Tests

#### Algorithme exact via *branch and bound*

    Kinda - Création de l'algorithme - Code - Tests

#### Développer une interface de lecture/écriture de fichier TSP

    Lilian - Amélie
    
#### Makefiles génériques

    Kinda
    
#### Gestion de Git

    Florian

Cf : http://dept-info.labri.fr/ENSEIGNEMENT/edd/projet/sujet.pdf
