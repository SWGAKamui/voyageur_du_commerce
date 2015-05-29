#include <Drawer.h>
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <TSPDrawer.h>

static char nChar[3];
static int size;
static int** colors;
static int xWindow, yWindow;
static int xMin, yMin;
static double xScale, yScale;
static City* citiesArray;
static int maxCities, currentCity;

struct city{
	int num;
	int x;
	int y;
};

static void initCitiesArray(){
	citiesArray = malloc(sizeof(City)*10);
	maxCities = 10;
	currentCity = 0;
}

static void addCityInArray(int num, int x, int y){
	City city = malloc(sizeof(struct city));
	city->num = num;
	city->x = x;
	city->y = y;

	if (currentCity == maxCities){
		citiesArray = (City*) realloc(citiesArray, (maxCities + 20)*sizeof(City));

		if (citiesArray == NULL){
			printf("Erreur de réallocation\n");
			exit(1);
		}
		maxCities +=20;
	}

	citiesArray[currentCity] = city;
	currentCity++;
}

static void destructCitiesArray(){
	for (int i=0; i< currentCity; i++){
		free(*(citiesArray + i));
	}

	free(citiesArray);
}

static int* getColor(int n){
	int* colors = malloc(sizeof(int)*3);
	for (int i=0; i<3; i++)
		*(colors + i) = (n * i * 60) % 256;

	return colors;
}

static int calcXOnMap(int x){
	int res = (int)((x-xMin) * xScale);

	if (res > xWindow - (size + size/20))
		res = xWindow - (size + size/20);

	return res;
}

static int calcYOnMap(int y){
	int res = yWindow - (int)((y-yMin) * yScale);

	if (res > yWindow - (size + size/20))
		res = yWindow - (size + size/20);

	return res;
}

static City findCity(int n){
	for (int i=0; i<currentCity; i++){
		City c = *(citiesArray + i);
		if (c->num == n)
			return *(citiesArray + i);
	}

	return NULL;
}

void initTSPDrawer(int s, int xMini, int yMini, int xMax, int yMax, int xWin, int yWin){
	initCitiesArray();

	setCitySize(s);

	xScale = (double)(xWin) / ((double)(xMax) - (double)(xMini));
	yScale = (double)(yWin) / ((double)(yMax) - (double)(yMini));

	xWindow = xWin;
	yWindow = yWin;
	xMin = xMini;
	yMin = yMini;
}

void setCitySize(int s){
	if (s < 20)
		size = 20;
	else
		size = s;
}

void addCity(int n, int x, int y){

	x = calcXOnMap(x);
	y = calcYOnMap(y);

	addCityInArray(n, x, y);
}

void drawCities(){
	for (int i =0; i<currentCity; i++){
		City c = *(citiesArray + i);
		char * strChar;

		strChar = nChar;
		sprintf(strChar, "%d", c->num);
		
		int * colors = getColor(c->num);
		double a = 1 - ( 0.299 * *(colors) + 0.587 * *(colors +1) + 0.114 * *(colors + 2))/255;
		if (a < 0.5)
			drawTextWithRectFilled(nChar, c->x, c->y, size, size, size/20, 0, 0, 0, *(colors), *(colors + 1), *(colors +2));
		else
			drawTextWithRectFilled(nChar, c->x, c->y, size, size, size/20, 255, 255, 255, *(colors), *(colors + 1), *(colors +2));

		free(colors);
	}
}

void drawRoadBetween(int n, int n2){
	City c1 = findCity(n);
	City c2 = findCity(n2);

	int * colors1 = getColor(c1->num);
	int * colors2 = getColor(c2->num);

	int xC1 = c1->x + (size + size/20)/2;
	int yC1 = c1->y + (size + size/20)/2;
	int xC2 = c2->x + (size + size/20)/2;
	int yC2 = c2->y + (size + size/20)/2;

	drawLines(xC1, yC1, xC2, yC2, *(colors1), *(colors1 + 1), *(colors1 + 2));
	drawLines(xC1+3, yC1+3, xC2+3, yC2+3, *(colors2), *(colors2 + 1), *(colors2 + 2));

	free(colors1);
	free(colors2);
}

void stopTSPDrawer(){
	destructCitiesArray();
}