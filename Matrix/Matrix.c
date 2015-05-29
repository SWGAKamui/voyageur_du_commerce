#include <Matrix.h>

#include <stdbool.h>
#include <malloc.h>

/** Structure définissant la matrice 
* int length : longueur du tableau
* double ** array : matrice
*/
struct matrix{
	int length;
	double** array;
};

/** initArrayMatrix
* Initialise les cases d'une matrice à 0
* Matrix m : matrice à initialiser
*/
static void initArrayMatrix(Matrix m){
	for (int i=0; i<m->length; i++){
		for (int j=0; j<m->length; j++){
			m->array[i][j] = 0.0;
		}
	}
}

/** destructArrayMatrix
* Libère la mémoire utilisée par le tableau de la matrice
* Matrix m : matrice à libérer
*/
static void destructArrayMatrix(Matrix m){
	for (int i=0; i<m->length; i++){
		free(*(m->array+i));
	}
	free(m->array);
}

/** createMatrix
* Alloue une nouvelle matrice
* int length : taille de la matrice à créer
* RETURN m : la matrice allouée
*/
Matrix createMatrix(int length){
	Matrix m = malloc(sizeof(struct matrix));
	m->length = length;
	m->array = malloc(sizeof(double*) * length);

	for (int i =0; i<length; i++){
		*(m->array + i)= malloc(sizeof(double)*length);
	}

	initArrayMatrix(m);

	return m;
}

/** getMatrixValue
* Récupère une valeur précise de la matrice
* Matrix m : la matrice à utiliser
* int x, y : les coordonnées de la valeur à lire
* RETURN : la valeur lue
*/
double getMatrixValue(Matrix m, int x, int y){
	return m->array[x][y];
}

/** getMatrixMaximum
* Récupère la valeur maximale de la matrice
* Matrix m : la matrice à utiliser
* RETURN : la valeur maximale
*/
double getMatrixMaximum(Matrix m){
	double max = 0;

	for (int i=0; i<m->length; i++){
		for (int j=0; j<m->length; j++){
			if (m->array[i][j] > max)
				max = m->array[i][j];
		}
	}

	return max;
}

/** setMatrixValue
* Ecrit une valeur dans la matrice
* Matrix m : la matrice à utiliser
* int x, y : les coordonnées de la valeur à écrire
* double d : la valeur à écrire
*/
void setMatrixValue(Matrix m, int x, int y, double d){
	m->array[x][y] = d;
}

/** setMatrixArray
* Ecrit un tableau à 2 dimension statique dans la matrice
* Matrix m : la matrice à utiliser
* double* a : le tableau à 2 dimensions statique
* int size : la taille de la matrice
*/
void setMatrixArray(Matrix m, double* a, int size){
	for (int i=0; i<m->length && i<size; i++){
		for (int j=0; j<m->length && j<size; j++){
			m->array[i][j] = *(a+i*size + j);
		}
	}
}

/** getMatrixLength
* Retourne la taille de la matrice
*/
int getMatrixLength(Matrix m){
	return m->length;
}

/* destructMatrix
* Libère l'espace alloué pour la matrice
* Matrix m : matrice à supprimer
*/
void destructMatrix(Matrix m){
	destructArrayMatrix(m);
	free(m);
}

/** showMatrix
* Affiche la matrice
* Matrix m : matrice à afficher
*/
void showMatrix(Matrix m){
	printf("Matrice : \n");
	printf("Taille : %d\n", m->length);
	printf("Contenu : \n");
	for (int i=0; i<m->length; i++){
		for (int j=0; j<m->length; j++){
			printf("%f  ", m->array[i][j]);
		}
		printf("\n");
	}
}
