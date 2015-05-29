#ifndef MINSPANTREE_H
#define MINSPANTREE_H

#include <stdbool.h>
#include <Matrix.h>

typedef struct edge* Edge;

int getStart(Edge e);
int getEnd(Edge e);
double getWeight(Edge e);
void freeEnsemble();
void printEdgeValues(Edge e);
void travelCrush(Matrix a,Edge* e, int size);
double calculWeightTravel(Edge* e, int size);
void parcoursMST(Matrix m, Edge* e);
double* edgeArrayToDoubleArray(Edge* e, int size);
#endif
