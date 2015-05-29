#include <malloc.h>
#include <stdlib.h>

#include <Graph.h>

#define INITIAL_NUMBERS_OF_CHILDS 10

static int numNextNode = 1;

struct node{
	int numNode;
	int value;
	struct node* firstChild;
	struct node* brother;
	struct node* father;
};

Node createNode(){
	Node n = malloc(sizeof(struct node));
	n->numNode = numNextNode;
	numNextNode++;
	n->value = 0;
	n->firstChild = NULL;
	n->brother = NULL;
	n->father = NULL;

	return n;
}

void setNodeValue(Node n,int v){
	n->value = v;
}

int getNodeValue(Node n){
	return n->value;
}

Node getChild(Node n){
	return n->firstChild;
}

Node getBrother(Node n){
	return n->brother;
}

bool isRoot(Node n){
	return n->father == NULL;
}

bool hasChild(Node n){
	return n->firstChild != NULL;
}

bool hasBrother(Node n){
	return n->brother != NULL;
}

Node createChildToNode(Node n, int v){
	Node c = createNode();
	c->father = n;
	c->value = v;
	if (hasChild(n)){
		Node tmp = n->firstChild;
		while (hasBrother(tmp))
			tmp->brother;
		tmp->brother = c;
	}
	else
		n->firstChild = c;

	return c;
}

Node createBrotherToNode(Node n, int v){
	if(isRoot(n))
		return NULL;

	while(hasBrother(n))
		n = n->brother;

	Node b = createNode();
	n->brother = b;
	b->value = v;
	b->father = n->father;

	return b;
}

static bool isFirstChildOfNode(Node f, Node c){
	if (!hasChild(f))
		return false;

	return f->firstChild->numNode == c->numNode;
}

static bool isNextBrotherOfNode(Node n, Node nextNode){
	if (!hasBrother(n))
		return false;

	return n->brother->numNode == nextNode->numNode;
}

static Node getPreviousNodeOfNode(Node n){
	Node f = n->father;
	if (isFirstChildOfNode(f, n))
		return NULL;

	Node currentNode = f->firstChild;
	while (!isNextBrotherOfNode(currentNode, n) || currentNode == NULL) {
		currentNode = currentNode->brother;
	} 

	return currentNode;
}

void removeNode(Node n){
	if(!isRoot(n)) {
		Node f = n->father;

		if (isFirstChildOfNode(f, n)){
			f->firstChild = n->brother;
		}
		else {
			Node previousNode = getPreviousNodeOfNode(n);
			previousNode->brother = n->brother;
		}
	}

	if (hasChild(n))
		destructNodeAndChilds(n);
	else
		destructNode(n);
}

void destructNode(Node n){
	free(n);
}

Node destructNodeAndChilds(Node n){
	Node nRes = NULL;
	if (hasBrother(n))
		nRes = getBrother(n);
	if (!hasChild(n))
		free(n);
	else {
		Node tmp = n->firstChild;
		do{
			tmp = destructNodeAndChilds(tmp);
		} while (tmp != NULL);
		free(n);
	}

	return nRes;
}