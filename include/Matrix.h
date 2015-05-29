#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

typedef struct matrix* Matrix;

Matrix createMatrix(int length);
double getMatrixMaximum(Matrix m);
double getMatrixValue(Matrix m, int x, int y);
void setMatrixValue(Matrix m, int x, int y, double d);
int getMatrixLength(Matrix m);
void setMatrixArray(Matrix m, double* a, int size);
void destructMatrix(Matrix m);

void showMatrix(Matrix m);

#endif