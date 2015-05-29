#ifndef TSPDRAWER_H
#define TSPDRAWER_H

#include <Drawer.h>

typedef struct city* City;

void initTSPDrawer(int size, int, int, int xMax, int yMax, int xWindow, int yWindow);
void setCitySize(int s);
void addCity(int n, int x, int y);
void drawRoadBetween(int n, int n2);
void drawCities();
void stopTSPDrawer();

#endif