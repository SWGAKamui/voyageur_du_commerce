#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include <stdbool.h>
#include <Matrix.h>

Matrix ouvrirTSP(char*);
int** getCitiesFromTSP(char* name);
int lectureParam(int,char*);
int spaceDecalage(char*);

#endif
