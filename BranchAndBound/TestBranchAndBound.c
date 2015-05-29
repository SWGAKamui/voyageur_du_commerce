#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <BranchAndBound.h>
#include <Matrix.h>

#define MATRIX_SIZE 10

double distanceArray[MATRIX_SIZE][MATRIX_SIZE]={
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

int main(int argc, char** argv){
  double * pArray= (double*)distanceArray;
  bool success = false;

  Matrix m = createMatrix(MATRIX_SIZE);
  setMatrixArray(m, pArray, MATRIX_SIZE);

	searchOptimalPathBB(m);

  if (getOptimalWeightBB() == 42){
    printf("\n-> BranchAndBound : Poids optimal trouvé et correct\n");
    success = true;
  }
  else
    printf("\n-> BranchAndBound : Erreur sur le poids optimal\n");

	deleteOptimalPathsBB();

  destructMatrix(m);
  
  if (success)
	  return EXIT_SUCCESS;
  return EXIT_FAILURE;
}
