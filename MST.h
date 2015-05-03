#ifndef MST_H
#define MST_H

#include <iostream>

#include "Graph.h"

Graph Prim(Graph g, Graph &mst);

Graph Kruskal(Graph g, Graph &mst);

int Fib(Graph g, Graph &mst);

void extractMST(Graph &mst, int lastID);

#endif
