#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <Matrix.h>
#include <NearestNeighbour.h>

#define TAILLE_MATRICE 10

//On rentre la matrice solution en brut
double tab_distance[TAILLE_MATRICE][TAILLE_MATRICE]={
  {0, 9, 4, 11, 10, 8, 8, 13, 10, 16},
  {9, 0, 7, 2, 7, 9, 13, 10, 15, 11},
  {4, 7, 0, 7, 6, 4, 6, 9, 8, 12},
  {11, 2, 7, 0, 5, 7, 11, 8, 13, 9}, 
  {10, 7, 6, 5, 0, 2, 6, 3, 8, 6},
  {8, 9, 4, 7, 2, 0, 4, 5, 6, 8},
  {8, 13, 6, 11, 6, 4, 0, 5, 2, 8}, 
  {13, 10, 9, 8, 3, 5, 5, 0, 5, 3},
  {10, 15, 8, 13, 8, 6, 2, 5, 0, 6}, 
  {16, 11, 12, 9, 6, 8, 8, 3, 6, 0}
};

//on rentre le chemin exact liée à la matrice précédente, en brut
double tab_chemin_exact[TAILLE_MATRICE]={1,3,6,5,8,10,9,7,4,2};

/*Description:Ce test va copier la matrice, et utiliser l'algorithme 'parcoursVoy' de NN afin de générer un tableau de double, qui sera le cheminoptimal NN.
Paramètres: Le main ne prend aucun paramètre, il n'y en a aucune utilité.
Retour:Retourne "EXIT_SUCCESS" si le chemin trouvé est identique au chemin rentré en brut(comparaison grâce à un bool 'success' et à la fonction 'egalite'), et "EXIT_FAILURE" dans el cas contraire.
*/
int main(){
  bool success=false;
  double * matrice_distance= (double*)tab_distance;
  Matrix matrice_test=createMatrix(TAILLE_MATRICE);
  setMatrixArray(matrice_test, matrice_distance,TAILLE_MATRICE);
  double* resultat=parcoursVoy(matrice_test);
  afficher(resultat,TAILLE_MATRICE);
  if (egalite(tab_chemin_exact,resultat)){
    printf("L'algorithme fonctionne bien!\n");
    success=true;}
  else{
    printf("L'algorithme ne fonctionne pas bien!\n\n");
    success=false;}
  printf("\n");
  destructMatrix(matrice_test);
  free(resultat);
  if (success==true)
    return EXIT_SUCCESS;
  else{
    return EXIT_FAILURE;
  }
}
