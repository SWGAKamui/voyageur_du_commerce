#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <Matrix.h>
#include <NearestNeighbour.h>

/*Descrption: Cette fonction va parcourrir une matrice, en partant de la 1ère ville, et en choisissant toujours la ville la plus proche, à condition que celle-ci ne soit pas une ville déjà parcourue. Les villes parcourues seront alors inscrites dans un tableau.
Paramètre: Prend en paramètre une matrice de double, qui est la matrice des distances entre les villes.
Retour: Elle renvoie un tableau de double,contenant l'ordre des villes à parcourrir.
*/
double* parcoursVoy(Matrix tab_distance){
  int length_tab_distance=getMatrixLength(tab_distance);
  double* tab_chemin= malloc(sizeof(double)*length_tab_distance);
  initMoinsUn(tab_chemin,length_tab_distance); //initialisation tableau des villes parcourues
  int i=0;
  int indice_tab_chemin=1;
  while (tab_chemin[length_tab_distance-1]==-1){ //tant que l'on a pas visité toutes les villes
    double distance_min=getMatrixMaximum(tab_distance);
    int indiceMin=0;
    for (int colonne=0; colonne<length_tab_distance; colonne++){  //pour toutes les villes d'une colonne
      if (getMatrixValue(tab_distance,i,colonne)<distance_min && i!=colonne //si distance entre 2 villes est plus petite que la distance précédemment trouvée
	  && !testAppartenance(tab_chemin,colonne+1,indice_tab_chemin)){  //et si colonne+1 n'a pas déjà été parcourue  (colonne commence à 0, et les villes sont numérotées à partir de 1)
        distance_min=getMatrixValue(tab_distance,i,colonne);
        indiceMin=colonne;    //on sauvegarde l'indice de la ville
      }
    }
    tab_chemin[indice_tab_chemin]=indiceMin+1; //on rajoute la ville trouvée au tableau des vilels parcourues (ville = indice +1)
    indice_tab_chemin++;  //on avance d'un cran dans le tableau des villes
    i=indiceMin;  //on sauvegarde la dernière ville parcourue
  }
  return tab_chemin;    //retour du tableau contenant les villes parcourues
}

//Initialise un tableau de double à -1 (pour ne pas confondre avec la ville 0)
void initMoinsUn(double* t, int longueur_tableau ){
  t[0]=1;
  for (int i=1; i<longueur_tableau; i++) {
    t[i]=-1;
  }
}

//Teste l'apartenance d'un entier x, à un tableau de double t
bool testAppartenance(double *t, double x, int longueur_tableau){
  for (int i=0; i<longueur_tableau+1; i++){
    if (t[i]==x)
      return true;
  }
  return false;
}

//Affiche, caractère pas caractère, un tableau de double
void afficher(double* t,int longueur_tableau){
  printf("Route trouvée : ");
  for (int i=0; i<longueur_tableau-1; i++){
    printf("%lf - ", t[i]);
  }
  printf("%lf\n", t[longueur_tableau-1]);
}

//Teste l'égalite entre 2 tableaux de doubles
bool egalite(double *t1,double * t2){
  int size1=sizeof(t1)/sizeof(double);
  int size2=sizeof(t2)/sizeof(double);
  if (size1==size2){
    for (int i=0; i<=size1; i++){
      if (t1[i]!=t2[i])
	return false;
    }
    return true;
  }
  return false;
}
