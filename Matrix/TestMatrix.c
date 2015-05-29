/* Cette fonction ne sert qu'a savoir si la fonction Matrix marche seul avec 
 *une matrice de dimension 2, en effet, matrix est utilisé par les différentes 
 *fonction pour générer des matrices à partir des test et des données de chaque
 *fonction de calcul de parcours.
 *
 *Par conséquent, une fois le test effectué, 
 *la matrice générer par TestMatrix sera supprimé.
 *
 */
#include "Matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

double tab[2][2] = {
	{4, 6},
	{7, 5}
};

int main(){
	bool success = false;
  // On créé une matrice de dimension 2
	Matrix m = createMatrix(2);
	// Valeur de test
	double testValue = 2.8;

	setMatrixValue(m, 0, 0, 1.5);
	setMatrixValue(m, 0, 1, testValue);
	// testvalue est mise dans la matrice

	// Si la matrice dans la position (m,0,1) est la même valeur que le testvalue,
	// cela signifie que la matrice marche
	if (getMatrixValue(m, 0, 1) == testValue)
		printf("-> Matrix : Setters et Getters -> Fonctionnement correct\n");
	else
		printf("-> Matrix : Setters et Getters -> Résultat non correct\n");

	setMatrixArray(m, (double*)tab, 2);
	// On effectue le même test que précédemment, sauf que c'est avec la matrice
	// statique que l'on fait le test
	if (getMatrixValue(m, 1, 1) == tab[1][1]){
		printf("-> Matrix : SetMatrixArray -> Fonctionnement correct\n");
		success = true;
	}
	else
		printf("-> Matrix : SetMatrixArray -> Résultat non correct\n");

	// On affiche la matrice
	printf("Affichage de la matrice (showMatrix()) : \n");
	printf("\n");
	showMatrix(m);

	// Comme il s'agit d'une matrice de test, une fois les contrôles effectués,
	// on peux la supprimer
	destructMatrix(m);
	printf("\n");
	if (success)
		return EXIT_SUCCESS;
	return EXIT_FAILURE;
}
