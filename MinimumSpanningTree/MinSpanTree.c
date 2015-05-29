#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <Graph.h>
#include <stdbool.h>

#include "MinSpanTree.h"
#include "Matrix.h"

//structure : arête
struct edge{
  int start;
  int end;
  double weightEdge;
};

int pathSize;

// Variables pour le poids minimale de la route
double weightTotal;
Edge* banishedEdge;
int banishedEdgeSize;
Edge* ensemble;
int tailleEnsemble, caseActuelleEnsemble;

//Créé et initialise une arête
static Edge createEdge(int s, int en, double w){ //Createur de edge
  Edge e=malloc(sizeof(struct edge));
  e->start=s;
  e->end=en;
  e->weightEdge=w;
  return e;
}

//Getteurs
int getStart(Edge e){
  return e->start;
}

int getEnd(Edge e){
  return e->end;
}

double getWeight(Edge e){
  return e->weightEdge;
}


//libere toutes les allocation.
void travelCrush(Matrix a,Edge* e, int size){
  free(e);
  weightTotal=0;
}


//marche avec Edge* traveled.
double calculWeightTravel(Edge* e, int size){  
  for(int i=0;i<size;i++){
    double w=getWeight(e[i]);
    weightTotal+=w;
  }
  return weightTotal;
}

/** isInArray
* Vérifie si la variable x est contenue dans le tableau t
* Renvoie true si la variable est trouvée
*/
static bool isInIntArray(int x, int* a, int size){
  for (int i=0; i< size; i++){
    if (x == *(a+i)) return true;
  }
  return false;
}

//Permet d'afficher les valeurs d'une arête.
void printEdgeValues(Edge e){
  printf("Start : %d - End : %d - Weight : %f\n", e->start, e->end, e->weightEdge);
}

static int createNodeFor(Edge* e, int size, Node n, int* placedPoints, int nbPlacedPoints){
  for (int i = 0; i < size-1; i++){
    if (e[i]->start == getNodeValue(n) && !isInIntArray(e[i]->end, placedPoints, nbPlacedPoints)){
      Node next = createChildToNode(n, e[i]->end);
      *(placedPoints + nbPlacedPoints) = getNodeValue(next);
      nbPlacedPoints++;
      nbPlacedPoints = createNodeFor(e, size, next, placedPoints, nbPlacedPoints);
    }
    else if (e[i]->end == getNodeValue(n) && !isInIntArray(e[i]->start, placedPoints, nbPlacedPoints)){
      Node next = createChildToNode(n, e[i]->start);
      *(placedPoints + nbPlacedPoints) = getNodeValue(next);
      nbPlacedPoints++;
      nbPlacedPoints = createNodeFor(e, size, next, placedPoints, nbPlacedPoints);
    }
  }

  return nbPlacedPoints;
}

static Node transformEdgeArrayToGraph(Edge* e, int size, int rootNum){
  Node root = createNode();
  setNodeValue(root, rootNum);

  int* placedPoints = malloc(sizeof(int)*size);
  for (int i=0; i<size; i++)
    *(placedPoints + i) = -1;
  *placedPoints = rootNum;

  createNodeFor(e, size, root, placedPoints, 1);

  return root;
}

static void showGraph(Node n){
  printf("Noeud %d\n", getNodeValue(n));

  if (hasChild(n)){
    showGraph(getChild(n));
  }

  if (hasBrother(n)){
    showGraph(getBrother(n));
  }
}

static int getGraph(Node n, double* array, int nbPlacedPoints){
  *(array + nbPlacedPoints) = getNodeValue(n);
  nbPlacedPoints++;

  if (hasChild(n)){
    nbPlacedPoints = getGraph(getChild(n), array, nbPlacedPoints);
  }

  if (hasBrother(n)){
    nbPlacedPoints = getGraph(getBrother(n), array, nbPlacedPoints);
  }

  return nbPlacedPoints;
}

double* edgeArrayToDoubleArray(Edge* e, int size){
  double* res = malloc(sizeof(double)*size);

  Node n = transformEdgeArrayToGraph(e, size, 0);

  showGraph(n);

  getGraph(n, res, 0);

  /**res[0] = (double)e[0]->start;
  for (int i=1; i<size -1; i++)
    if (res[i-1] != e[i]->start)
      res[i] = (double)e[i]->start;
    else 
      res[i] = (double)e[i]->end;

  if (res[size-2] != e[size-3]->start)
      res[size-1] = (double)e[size-2]->end;
    else 
      res[size-1] = (double)e[size-2]->end;*/

  return res;
}

static int somme(int n){
  int res = 0;
  for (int i=0; i<n; i++)
    res += i;

  return res;
}

//Lecture d'une matrice et transformation en arêtes.
static void readMatrixAndCreateEdges(Matrix m){
  // On crée un tableau contenant toutes les arêtes.
  ensemble = malloc(sizeof(Edge)*somme(getMatrixLength(m)));
  tailleEnsemble = somme(getMatrixLength(m));
  int numCase = 0;
  Edge tmp;
  caseActuelleEnsemble = 0;

  for (int i=0; i<getMatrixLength(m); i++){
    for (int j=i+1; j<getMatrixLength(m); j++){
      ensemble[numCase] = createEdge(i, j, getMatrixValue(m, i, j));

      if (numCase > 0){
        // Si la case actuelle a un poids plus léger que la précédente
        if (ensemble[numCase]->weightEdge < ensemble[numCase-1]->weightEdge){
          int n = numCase;
          // On la fait reculer tant qu'elle est plus légère que la case précédente, qui effectue un tri du tableau en le remplissant.
          while (n > 0 && ensemble[n]->weightEdge < ensemble[n-1]->weightEdge){
            tmp = ensemble[n];
            ensemble[n] = ensemble[n-1];
            ensemble[n-1] = tmp;
            n--;
          }
        }
      }
      numCase++;
    }
  }

  //Affiche le tableau des arêtes de la matrice, trié.
  //for (int i=0; i<tailleEnsemble; i++){
  //  printEdgeValues(ensemble[i]);
  //}
}

void freeEnsemble(){
  for (int i=0; i<tailleEnsemble; i++)
    free(ensemble[i]);
  free(ensemble);
}


/** isInArray
* Vérifie si la variable x est contenue dans le tableau t
* Renvoie true si la variable est trouvée
*/
static bool isInArray(int x, int* a, int size){
  for (int i=0; i< size; i++){
    if (x == *(a+i)) return true;
  }
  return false;
}

/** searchRecur
* Les variables sont représentés ainsi.
* e : la route actuelle
* size : la taille de la route
* currentPoint : la ville sur laquelle nous sommes actuellement
* prevPoint : la ville de laquelle nous venons
* previousPoints : les villes que l'on a traversé
* nbPreviousPoints : le nombre de villes que l'on a traversé
*/

static bool searchRecur(Edge* e, int size, int currentPoint, int prevPoint, int* previousPoints, int nbPreviousPoints){
  bool returnRecur = false;

  // Pour chaque arête du tableau et tant qu'on a pas de retour à vrai
  for (int i=0; i<size && returnRecur == false; i++){
    // Si on trouve une arête du type (pointActuel, pointDifferentDuPrecedent)
    if (e[i]->start == currentPoint && e[i]->end != prevPoint){
      // On regarde si on a déjà traversé cette ville
      if (isInArray(e[i]->end, previousPoints, nbPreviousPoints))
        return true;
      
      // Sinon, on avance vers la prochaine ville
      previousPoints[nbPreviousPoints] = e[i]->end;
      nbPreviousPoints++;
      returnRecur = searchRecur(e, size, e[i]->end, e[i]->start, previousPoints,nbPreviousPoints);
      // On retire la ville des villes visitées
      nbPreviousPoints--;
    }
    // Si on trouve une arête du type (pointDifferentDuPrecedent, pointActuel)
    else if (e[i]->end == currentPoint && e[i]->start != prevPoint){
      if (isInArray(e[i]->start, previousPoints, nbPreviousPoints))
        return true;
      
      previousPoints[nbPreviousPoints] = e[i]->start;
      nbPreviousPoints++;
      returnRecur = searchRecur(e, size, e[i]->start,e[i]->end, previousPoints,nbPreviousPoints);
      nbPreviousPoints--;
    }
  }

  return returnRecur;
}

// isCyclic
// Les variables sont représentés ainsi. 
// e : la route actuelle
// actual : nombre de villes dans la route actuellement
// size : la taille de la route max : le nombre maximum de villes
// edge : l'arête à tester si elle forme un cycle
//
// isCyclic vérifie si une arête selectionnée permet de créer un cycle entre 3 points au moins.
static bool isCyclic(Edge* e, int actual, int size, int max, Edge edge){
  // On ajoute temporairement l'arête au tableau
  e[actual] = edge;

  int previousPoints[size];
  int nbPreviousPoints = 0;

  // Pour chaque ville
  for (int i=0; i<max; i++){
    // Pour chaque arête de la route actuelle
    for (int j=0; j<actual+1; j++){
      // Pour une arête (u, v) de la route, si u correspond à une ville
      if (e[j]->start == i) {
        // On traverse la ville
        *(previousPoints + nbPreviousPoints) = e[j]->start;
        nbPreviousPoints++;
        // Puis on teste tous les chemins possibles prenant la route actuelle et la ville actuelle,
        // pour vérifier qu'aucun cycle existe
        if(searchRecur(e, actual+1, e[j]->end, e[j]->start, previousPoints,nbPreviousPoints)){
          return true;
        }
        // On retire la ville des villes visitées
        nbPreviousPoints--;
      }
      // Pour une arête (u, v) de la route, si v correspond à une ville
      else if (e[j]->end == i){
        *(previousPoints + nbPreviousPoints) = e[j]->end;
        nbPreviousPoints++;
        if(searchRecur(e, actual+1, e[j]->start, e[j]->end, previousPoints,nbPreviousPoints)){
          return true;
        }
        nbPreviousPoints--;
      }
    }
  }
  e[actual] = NULL;

  return false;
}

// getNextEdge
// Les variables représentent.
// e : route actuelle
// size : taille de la route
// current : nombres de villes actuellement dans la route


static Edge getNextEdge(Edge* e, int size, int current){
  // Tant que nous n'avons pas testés toutes les arêtes
  while (caseActuelleEnsemble<tailleEnsemble){
    // Si l'ajout d'une nouvelle arête ne fait pas de cycle
    if (!isCyclic(e, current, size, 10, ensemble[caseActuelleEnsemble])){
      // On fournit l'arête qui est considérée comme correcte
      caseActuelleEnsemble++;
      return ensemble[caseActuelleEnsemble-1];
    }
    caseActuelleEnsemble++;
  }
  return NULL;
}


void parcoursMST(Matrix m, Edge* e){
  int alpha=getMatrixLength(m);
  int currentSize = 0;

  // On crée un tableau contenant toutes les arêtes triées
  readMatrixAndCreateEdges(m);

  // Pour chaque arrêt de la route tant que l'on a pas attein la fin du tableau
  for (int j=0;j<(alpha-1) && caseActuelleEnsemble < tailleEnsemble;j++){

    // On récupère une arête correcte
    e[j]=getNextEdge(e, currentSize, j);
    
    //Affiche les arêtes rajoutés (sert de test)
    //printf("L'arete de trajet : [%d,%d] a été rajouté\n", e[j]->start, e[j]->end);

    currentSize++;
  }
}


