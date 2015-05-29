#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>

typedef struct node* Node;

Node createNode();
void destructNode(Node n);
Node destructNodeAndChilds(Node n);

void setNodeValue(Node n,int v);
int getNodeValue(Node n);
Node getChild(Node n);
Node getBrother(Node n);

bool isRoot(Node n);
bool hasChild(Node n);
bool hasBrother(Node n);

Node createChildToNode(Node n, int v);
Node createBrotherToNode(Node n, int v);
void removeNode(Node n);

#endif

