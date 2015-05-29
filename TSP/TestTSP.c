#include <stdio.h>
#include <stdlib.h>
#include <Matrix.h>
#include <TSP.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char*argv[]){
  printf("Test de l'algorithme de TSP\n");

  char  cwd[1024];

  getcwd (cwd, sizeof(cwd));

  char cwd2[1024];
  strcpy(cwd2, cwd);
  strcat(cwd, "/resources/exemple10.tsp");
  strcat(cwd2, "/resources/exemple14.tsp");

  Matrix data = ouvrirTSP(cwd);
  int dimension=getMatrixLength(data);
  showMatrix(data);
  destructMatrix(data);
  printf("\n");

  Matrix data2=ouvrirTSP(cwd2);
  int dimension2=getMatrixLength(data2);
  showMatrix(data2);
  destructMatrix(data2);
  printf("\n");

  return EXIT_SUCCESS;

}
