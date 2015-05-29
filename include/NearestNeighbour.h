#ifndef NEAREST_NEIGHBOUR_H
#define NEAREST_NEIGHBOUR_H

#include <stdbool.h>


double* parcoursVoy(Matrix tab_distance);
void initMoinsUn(double* t, int longueur_tableau );
bool testAppartenance(double *t, double x, int longueur_tableau);
void afficher(double* t,int longueur_tableau);
bool egalite(double *t1,double * t2);

#endif