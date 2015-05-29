#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <Matrix.h>
#include <unistd.h>
#include <TSP.h>

#define TAILLE_BUFFER 120





/* Description: Cette fonction va, à partir d'un fichier *.tsp, récupérer la dimension ainsi que la matrice des distances.
Parametres: Elle prend en paramètre le nom du fichier d'extension .tsp dont l'on cherche à récupérer les données.
Retour: Elle renvoie une matrice contenant les distances entre toutes les villes.
*/

Matrix ouvrirTSP(char* nomDuFichier){
  int dimension;  //declarations des variables
  Matrix distances;
  FILE* fichier;
  fichier = fopen(nomDuFichier,"r");// ouverture du fichier nomDuFichier
  if(fichier == NULL){
    perror(nomDuFichier);
    return NULL;
  }		// on vérfie si le fichier existe bien par le biais d'un assert

  char *buffer=malloc(sizeof(char)*TAILLE_BUFFER);
  buffer[0] = '\0';// buffer servant a lire les parametres, initialisation
  dimension = 0;
  while (!(buffer == strstr(buffer,"EDGE_WEIGHT_SECTION"))){ // Lecture des parametres
    fgets(buffer,20,fichier);
    dimension=lectureParam(dimension,buffer);
  }
  distances = createMatrix(dimension);
  if (buffer == strstr(buffer,"EDGE_WEIGHT_SECTION"))
    {
      for (int i = 0; i<dimension ; i++) { // lecture des distances
	for (int j=0; j<dimension; j++){
	  fscanf(fichier,"%s",buffer);
	  setMatrixValue(distances,i,j,atof(buffer));
	}
      }
    }
  fclose(fichier);
  free(buffer);
  return(distances);
}

int** getCitiesFromTSP(char* name){
  int dimension;  //declarations des variables
  FILE* fichier;
  int ** values;
  fichier = fopen(name,"r");// ouverture du fichier nomDuFichier
  if(fichier == NULL)
    return NULL;    // on vérfie si le fichier existe bien par le biais d'un assert

  char *buffer=malloc(sizeof(char)*TAILLE_BUFFER);
  buffer[0] = '\0';// buffer servant a lire les parametres, initialisation
  dimension = 0;
  while (strcmp(buffer,"DISPLAY_DATA_SECTION") != 0){ // Lecture des parametres
    fgets(buffer,21,fichier);
    dimension=lectureParam(dimension,buffer);
  }

  values = malloc(sizeof(int*)*dimension);

  if (strcmp(buffer,"DISPLAY_DATA_SECTION") == 0){
    for (int i = 0; i<dimension ; i++) { // lecture des distances
      *(values + i) = malloc(sizeof(int)*3);
      for (int j=0; j<3; j++){
        fscanf(fichier,"%s",buffer);
        *(*(values+i)+j) = (int)atof(buffer);
      }
    }
  }

  fclose(fichier);
  free(buffer);
  return(values);
}

// le buffer est il un param? si modifit les champs de dataTMP associés

int lectureParam(int data,char* buffer){
  if (buffer == strstr(buffer,"DIMENSION")){
    data = atoi(buffer+9+spaceDecalage(buffer+9));
    
  }
  return data;
}


//decale le pointeur pour pointer sur la premiere lettre du param(on peut avoir a:b, a : b, ...)
int spaceDecalage(char* p){
	int i = 0;
	while (p[i]==' ' || p[i]==':')
		i++;
	return i;
}
