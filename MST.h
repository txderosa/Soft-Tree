#ifndef MST_H
#define MST_H

#include <iostream>
#include <algorithm> // for Kruskal: sort()
#include <limits> //For infinity in Prim

#include "Graph.h"
#include "DisjointComps.h" // for Kruskal
#include "FHeap.h" // for Fib

Graph Prim(Graph g, Graph &mst);

Graph Kruskal(Graph g, Graph &mst);

int Fib(Graph g, Graph &mst);

void extractMST(Graph &mst, int lastID);

#endif
