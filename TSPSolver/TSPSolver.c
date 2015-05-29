#include <Matrix.h>
#include <NearestNeighbour.h>
#include <MinSpanTree.h>
#include <Bruteforce.h>
#include <BranchAndBound.h>
#include <TSP.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

#include <unistd.h>

#include <Drawer.h>
#include <Input.h>
#include <TSPDrawer.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

TTF_Font* font;
Printer* printer;
Input* input;

static int takeValueForAlgorithm(char* a){
	if (a == NULL){
		return -1;
	}

	if (a[0] < 48 || a[0] > 51)
		return -1;
	else
		return atoi(&a[0]);
}

static double* nearestNeighbour(Matrix data){	
	double * res = parcoursVoy(data);
	for (int i =0; i<getMatrixLength(data); i++)
		*(res + i)-= 1;

	return res;
}

static double* mst(Matrix data){
	Edge* traveled=malloc((getMatrixLength(data)-1)*sizeof(Edge)); //Tableau contenant les arêtes
	parcoursMST(data,traveled);
	double* res = edgeArrayToDoubleArray(traveled, getMatrixLength(data));

	travelCrush(data,traveled, getMatrixLength(data)-1);

	return res;
}

static double* bruteforce(Matrix data){
	searchOptimalPath(data);
	if(getNbOptimalPaths() >1)
		printf("Plusieurs routes optimales trouvées -> Seule la première est affichée\n");

	int ** opPaths = getOptimalPaths();
	double* res = malloc(sizeof(double)*getMatrixLength(data));

	for (int i=0; i<getMatrixLength(data); i++)
		res[i] = *((*opPaths) + i);

	deleteOptimalPaths();

	return res;
}

static double* branchAndBound(Matrix data){
	searchOptimalPathBB(data);
	if(getNbOptimalPathsBB() >1)
		printf("Plusieurs routes optimales trouvées -> Seule la première est affichée\n");

	int ** opPaths = getOptimalPathsBB();
	double* res = malloc(sizeof(double)*getMatrixLength(data));

	for (int i=0; i<getMatrixLength(data); i++)
		res[i] = *((*opPaths) + i);

	deleteOptimalPathsBB();

	return res;
}

static void init(char * title){
    printer = malloc(sizeof(Printer));
    input = malloc(sizeof(Input));

	printer->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                          SDL_WINDOWPOS_CENTERED,
                          SCREEN_WIDTH, SCREEN_HEIGHT,
                          SDL_WINDOW_SHOWN);

	SDL_SetWindowTitle(printer->window, title);

	printer->renderer = SDL_CreateRenderer(printer->window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (printer->window == NULL || printer->renderer == NULL)
    {
        printf("Impossible d'initialiser la SDL 2 (window ou renderer).");
        exit(1);
    }
 
    // On cache le curseur de la souris
    SDL_ShowCursor(SDL_ENABLE);
}

static void cleanup()
{
    //On fait le ménage
    SDL_DestroyRenderer(printer->renderer);
    SDL_DestroyWindow(printer->window);

    stopTSPDrawer();

    //free(printer);
    //free(input);
 
    TTF_CloseFont(font);
 
    //On Quitte la SDL */
    SDL_Quit();

    exit(0);
}



static int drawTSPPath(double* path, int size, int** cities){
    unsigned int frameLimit = SDL_GetTicks() + 1;
    int go;

    init("Visionneur - TSP");
 
    // Initialisation de la SDL dans une fonction séparée (voir après)
    if(TTF_Init() == -1){
    	fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
   		exit(EXIT_FAILURE);
	}

    font = TTF_OpenFont("/usr/local/bin/fonts/PWBoldScript.ttf", 20);

    if (font == NULL){
        system("ls");
        fprintf(stderr, "Impossible d'ouvrir la police Square.ttf\n");
        exit(EXIT_FAILURE);
    }

    int xMax=*(*(cities)+1);
    int yMax=*(*(cities)+2);
    int xMin = *(*(cities)+1);
    int yMin = *(*(cities)+2);

    for (int i=1; i<size; i++){
    	if (*(*(cities+i)+1) > xMax)
			xMax = *(*(cities+i)+1);
		if (*(*(cities+i)+1) < xMin)
			xMin = *(*(cities+i)+1);
		if (*(*(cities+i)+2) > yMax)
			yMax = *(*(cities+i)+2);
		if (*(*(cities+i)+2) < yMin)
			yMin = *(*(cities+i)+2);
    }

    printf("%d - %d\n", xMax, yMax);
    initTSPDrawer(20, xMin, yMin, xMax, yMax, SCREEN_WIDTH,SCREEN_HEIGHT);

    setPrinter(printer);
    setInput(input);
    setFont(font);

 
    // Appelle la fonction cleanup à la fin du programme
    atexit(cleanup);
 
    go = 1;
 
 
    for (int i=0; i<size; i++){
    	addCity(*(*(cities+i))-1, *(*(cities+i)+1), *(*(cities+i)+2));
    }
 
    while (go == 1)
    {
 
        /* On vérifie l'état des entrées (clavier puis plus tard joystick */
        getInput();
        
        for (int i = 0; i< size-1; i++){
            drawRoadBetween((int)*(path+i), (int)*(path+i+1));
        }
        drawRoadBetween((int)*(path + size-1), (int)*(path));

        drawCities();
        draw();

 
        /* Gestion des 60 fps ( 60 images pas seconde : soit 1s ->1000ms/60 = 16.6 -> 16
        On doit donc attendre 16 ms entre chaque image (frame) */
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;
 
    }

    
    exit(0);
 
}

int main(int argc, char** argv){
	
	int gflag = 0;
	int aflag = 0;
	char *fileValue = NULL;
	int index;
	int c;
	double* resultat;

	

	opterr = 0;

	while ((c = getopt (argc, argv, "ga:")) != -1)
		switch (c){
		case 'g':
			gflag = 1;
			break;
		case 'a':
			aflag = takeValueForAlgorithm(optarg);
			if (aflag == -1){
				fprintf (stderr, "Option -a has bad argument.\n", optopt);
				return 1;
			}
			break;
		case 'c':
			fileValue = optarg;
			break;
		case '?':
			if (optopt == 'a')
				fprintf (stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
			return 1;
		default:
			fileValue = optarg;
	}

	printf("[TSPSolver] Ouverture du fichier\n");

	fileValue = argv[optind];
	if (fileValue == NULL){
		fprintf (stderr, "Erreur : Pas de fichier spécifié\n");
		return 1;
	}

	Matrix data = ouvrirTSP(fileValue);
	if (data == NULL){
		fprintf (stderr, "Erreur d'ouverture du fichier spécifié\n");
		return 1;
	}

	printf("[TSPSolver] Démarrage de l'algorithme n°%d\n", aflag);

	if (aflag == 0){
		resultat = nearestNeighbour(data);
	}
	else if (aflag == 1){
		resultat = mst(data);
		freeEnsemble();
	}
	else if (aflag == 2){
		resultat = bruteforce(data);
	}
	else if (aflag == 3){
		resultat = branchAndBound(data);
	}

	afficher(resultat,getMatrixLength(data));

	printf("[TSPSolver] Démarrage de l'interface graphique\n");
		
	if (gflag == 1){
		int ** cities = getCitiesFromTSP(fileValue);
		drawTSPPath(resultat, getMatrixLength(data), cities);

		for (int i=0; i<getMatrixLength(data); i++){
			 free(*(cities + i));
		}
		free(cities);
	}

	free(data);

	return EXIT_SUCCESS;
}

