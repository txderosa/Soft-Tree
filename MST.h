#ifndef MST_H
#define MST_H

#include <iostream>
#include <algorithm> // for Kruskal: sort(), for Prim: find()
#include <limits> //For infinity in Prim
#include <vector> // For min-heap in Prim

#include "Graph.h"
#include "DisjointComps.h" // for Kruskal
#include "FHeap.h" // for Fib

void Prim(Graph g, Graph &mst);

void extractPrimMST(Graph &mst);

void Kruskal(Graph g, Graph &mst);

void Fib(Graph g, Graph &mst);

void extractMST(Graph &mst);

#endif
