/*On reprend le coe du Bruteforce
 *mais on conserve toutes les routes qui sont égales au poids optimales déjà 
 *trouvé dans la fonction clacPathRecursivity
 *
 *Pour cela, on modifie calcWeightForPath pour lui rajouter une troisième variable sizeOf et une condition
 * if (sizeOf==pathSize)
 *donc si la route est complète
 */
#include <stdio.h>
#include <malloc.h>

#include <BranchAndBound.h>
#include <Matrix.h>
#include <Bruteforce.h>

int pathSize;

// Variables pour le poids minimale de la route
double currentMinWeight;
double weight;

// Variable pour voir le nombre de routes testées
static int nbPaths;


// Variable pour contenir les routes optimales trouvées
int** optimalPaths;
static int nbMaxOptimalPaths;
static int nbCurrentOptimalPaths;

/* - FONCTIONS POUR GARDER LES ROUTES OPTIMALES EN MEMOIRE -
* On conserve les routes optimales trouvées en mémoire
* Chaque route est considérée comme un tableau (= int*)
* Pour conserver, on utilise donc un tableau de tableau (= int**)
*/

/** createPathCopyFrom
* Crée une copie d'une route
* -> Permet de passer d'un stockage statique à un stockage dynamique
*/
static int* createPathCopyFrom(int* a){
	int* aRes = malloc(pathSize * sizeof(int));

	for (int i=0; i<pathSize; i++)
		*(aRes + i) = a[i];

	return aRes;
}

/** initOptimalPaths
* Initialise le pointeur et ses variables associées
*/
void initOptimalPathsBB(){
	nbCurrentOptimalPaths = 0;
	nbMaxOptimalPaths = 100;
	optimalPaths = malloc(nbMaxOptimalPaths * sizeof(int*));
}

/** addOptimalPath
* Ajoute une route optimale aux routes optimales
*/
static void addOptimalPath(int* path){
	// On transforme la route en pointeur
	int* rTmp = createPathCopyFrom(path);

	// On ajoute la route aux routes optimales
	*(optimalPaths + nbCurrentOptimalPaths) = rTmp;
	nbCurrentOptimalPaths++;

	// On agrandit le nombre de routes optimales possibles si on a atteint le maximum de routes stockables
	if (nbCurrentOptimalPaths == nbMaxOptimalPaths){
		nbMaxOptimalPaths += 100;
		optimalPaths = (int**) realloc(optimalPaths, nbMaxOptimalPaths);
	}
}

/** removeAllOptimalPaths
* Supprime toutes les routes stockées
*/
static void removeAllOptimalPaths(){
	for (int i =0; i< nbCurrentOptimalPaths; i++)
		free(*(optimalPaths + i));
	nbCurrentOptimalPaths = 0;
}

/** removeOptimalePaths
* Supprime le stockage des routes
*/
void deleteOptimalPathsBB(){
	removeAllOptimalPaths();
	free(optimalPaths);
}

/** showOptimalPaths
* Affiche les routes optimales trouvées
*/
static void showOptimalPaths(){
	printf("Affichage des routes optimales : \n");
	for (int i=0; i<nbCurrentOptimalPaths; i++){
		showArray(*(optimalPaths+i), pathSize);
	}
}

/** getOptimalWeight
* Renvoie le poids optimal
*/
int getOptimalWeightBB(){
	return currentMinWeight;
}

/** getOptimalPaths
* Renvoie les chemins optimaux
*/
int** getOptimalPathsBB(){
	return optimalPaths;
}

/** getNbOptimalPaths
* Renvoie le nombre de chemins optimaux
*/
int getNbOptimalPathsBB(){
	return nbCurrentOptimalPaths;
}

/** calcWeightForPath
* Calcule le poids de la route fournie en paramètre
* Demande : la matrice des distances, la route, la taille de la route
*/
static double calcWeightForPath(Matrix m, int* path, int sizeOf){
	double weight = 0;
	if (sizeOf<=1) {
		return 0;
	}
	// ajouter la dernière ville

	for (int i=0; i<sizeOf -1; i++)
		weight += getMatrixValue(m, *(path+i), *(path+i+1)); 
	// Si la route est 0 2 1, a[0][2] puis a[2][1]
	//On renvoi la valeur du dernier point mais comme on utlise des routes à tailles variable, on y met une condition
	if (sizeOf==pathSize){
	        weight += getMatrixValue(m, *(path + pathSize -1), *(path));
	}

	return weight;
}

/** calcPathByRecursivity
* Recherche les routes optimales par récursivité
*/
static void calcPathByRecursivityBB(Matrix m, int nbRemainingPoints, int* path){
	// Si il n'y a plus de path à trouver = si la route est complète
	if (nbRemainingPoints == 0){
		// On incrémente le compteur de routes testées
		nbPaths++;

		// On calcule le poids de la route
		weight = calcWeightForPath(m, path, pathSize);

		// Si le poids trouvé est inférieur au poids minimal actuel
		if (weight < currentMinWeight){
			// On supprime toutes les précédentes routes
			removeAllOptimalPaths();
			// On ajoute la nouvelle route
			addOptimalPath(path);
			// On modifie le poids minimal
			currentMinWeight = weight;

			printf("Nouveau poids trouvé : %f pour la route ", weight);
			showArray(path, pathSize);
		}
		// Sinon si on trouve une route avec un poids équivalent
		else if (weight == currentMinWeight){
			// On ajoute la route aux routes optimales
			addOptimalPath(path);

			printf("Nouvelle route avec le poids %f : ", weight);
			showArray(path, pathSize);
		}

		// Décommenter pour voir les routes créées
		// printf("Poids : %f pour route : ", weight);
		// showArray(path, pathSize);
	}
	//Si le poids est toujours inférieur au poids minimal actuel, on continue la route
	else if (calcWeightForPath(m, path, pathSize-nbRemainingPoints) < currentMinWeight)

	// On teste si le tableau de path contient le point 0, puis le point 1, puis ...
	// Si le point n'est pas contenu dans le tableau, on l'ajoute et on appelle
	// la fonction récursive à nouveau
	// Exemple : 0 1 2 3 4 5 6 7 8 9 puis 0 1 2 3 4 5 6 7 9 8 puis 0 1 2 3 4 5 6 8 7 9 etc. 

    
	for (int i=0; i<pathSize; i++){
		if (!isInArray(i, path, pathSize)){
				path[pathSize - nbRemainingPoints] = i; 
				calcPathByRecursivityBB(m, nbRemainingPoints-1, path);

	    // On supprime le point du tableau après toutes les routes dans 
	    //cette configuration trouvées
				path[pathSize - nbRemainingPoints] = -1;
		}
	}
}


/** searchOptimalPath
* Effectue la recherche de la route optimale
* Renvoie un tableau de routes
*/
int** searchOptimalPathBB(Matrix m){
	// Initialisation
	currentMinWeight = 0x7FFFFFFF;
	weight = 0;
	nbPaths = 0;
	pathSize = getMatrixLength(m);
	initOptimalPaths();

	// On fournie un tableau défini ici pour éviter de recréer le tableau
	// à chaque appel de la fonction récursif = économie de mémoire
	int* path = malloc(sizeof(int)*pathSize);
	initPath(path);

	// Démarrage de l'algorithme
	path[0] = 0;
	calcPathByRecursivityBB(m, pathSize - 1, path);

	// On affiche le nombre de routes testées
	printf("Nombre de routes possibles testées : %d\n" , nbPaths);
	showOptimalPaths();

	free(path);
	return optimalPaths;
}
