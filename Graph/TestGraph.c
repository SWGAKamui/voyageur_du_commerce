#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <Graph.h>

int main(){
	bool success = true;

	Node root = createNode();
	setNodeValue(root, 1);
	Node c1 = createChildToNode(root, 4);

	if (getNodeValue(c1) == 4)
		printf("-> Création d'un fils - Utilisation du fils : OK\n");
	else {
		printf("-> Création d'un fils - Utilisation du fils : ERROR\n");
		success = false;
	}

	Node c2 = createBrotherToNode(c1, 8);

	if (getNodeValue(c2) == 8)
		printf("-> Création d'un frère - Utilisation du frère : OK\n");
	else {
		printf("-> Création d'un frère - Utilisation du frère : ERROR\n");
		success = false;
	}

	removeNode(c1);

	if (getNodeValue(getChild(root)) == 8)
		printf("-> Suppression d'un noeud : OK\n");
	else {
		printf("-> Suppression d'un noeud : ERROR\n");
		success = false;
	}
	printf("\n");
	removeNode(root);

	if(success)
		return EXIT_SUCCESS;
	return EXIT_FAILURE;
}
