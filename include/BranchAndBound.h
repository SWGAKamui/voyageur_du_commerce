#ifndef BRANCHANDBOUND_H
#define BRANCHANDBOUND_H

#include <stdbool.h>
#include <Matrix.h>

int** searchOptimalPathBB(Matrix m);

int getOptimalWeightBB();
int** getOptimalPathsBB();
int getNbOptimalPathsBB();

void initOptimalPathsBB();
void deleteOptimalPathsBB();
#endif
