#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <stdbool.h>
#include <Matrix.h>

bool isInArray(int , int* , int );
void showArray(int* t, int size);
void initPath(int*);
int** searchOptimalPath(Matrix m);
void calcPathByRecursivity(Matrix m, int level, int* prev);

int getOptimalWeight();
int** getOptimalPaths();
int getNbOptimalPaths();

void initOptimalPaths();
void deleteOptimalPaths();
#endif