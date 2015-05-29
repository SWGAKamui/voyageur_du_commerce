#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <MinSpanTree.h>
#include <Matrix.h>

#define MATRIX_SIZE 10

double distanceArray[MATRIX_SIZE][MATRIX_SIZE]={
  {0, 9, 4, 11, 10, 8, 8, 13, 10, 16}, //0
  {9, 0, 7, 6, 7, 9, 13, 10, 15, 11},  //1
  {4, 7, 0, 7, 6, 4, 6, 9, 8, 12},     //2
  {11, 6, 7, 0, 5, 7, 11, 8, 13, 9},   //3
  {10, 7, 6, 5, 0, 2, 6, 3, 8, 6},     //4
  {8, 9, 4, 7, 2, 0, 4, 5, 6, 8},      //5
  {8, 13, 6, 11, 6, 4, 0, 5, 2, 8},    //6
  {13, 10, 9, 8, 3, 5, 5, 0, 5, 3},    //7
  {10, 15, 8, 13, 8, 6, 2, 5, 0, 6},   //8
  {16, 11, 12, 9, 6, 8, 8, 3, 6, 0}    //9
};

int main(int argc, char** argv){
  printf("Initialisation...");
  bool success=false;

  double * pArray= (double*)distanceArray; 
  Matrix m = createMatrix(MATRIX_SIZE);
  setMatrixArray(m, pArray, MATRIX_SIZE);
  printf("Creation de l'arbre\n");
  Edge* traveled=malloc((MATRIX_SIZE-1)*sizeof(Edge)); //Tableau contenant les arêtes
  parcoursMST(m,traveled);
  printf("L'arbre de recouvrement minimal contient :\n");
  for (int i=0;i<(MATRIX_SIZE-1);i++){
    printEdgeValues(traveled[i]);
  }
  double w=calculWeightTravel(traveled,MATRIX_SIZE-1);
  printf("Le poids de l'arbre est : %f \n",w);

  if (w==33){
    printf("L'arbre cree a un poids conforme a celui recherche\n");
    success=true;
  }
  else{
    printf("L'arbre cree est plus lourd/plus leger que le poids attendu...\n");
  }
  printf("\n");


  travelCrush(m,traveled, MATRIX_SIZE-1);
  freeEnsemble();
  if (success==true)
    return EXIT_SUCCESS;
  return EXIT_FAILURE;
}
