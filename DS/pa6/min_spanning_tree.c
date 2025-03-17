#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_VERTICES 100000
#define MAX_EDGES 500000

typedef struct _Edge {
	int u, v;
	int weight;
} Edge;

int N, M; // N: # of vertices, M: # of edges
Edge Edges[MAX_EDGES];
void sortEdges(Edge* E, int size);

// Disjoint-Set Structure
typedef struct _DisjointSetNode {
	int parent;
	int size;
} DisjointSetNode;

DisjointSetNode DSNodes[MAX_VERTICES];
int findRoot(int u);
bool mergeSets(int u, int v);

int main() {
	int i, minCost = 0;
	scanf("%d%d", &N, &M);
	for (i = 0; i < M; i++)
		scanf("%d%d%d", &Edges[i].u, &Edges[i].v, &Edges[i].weight);

	sortEdges(Edges, M); // Sort edges in the increasing order of edge weights

	for (i = 0; i < N; i++) { // Initialize DSNodes
		DSNodes[i].parent = i;
		DSNodes[i].size = 1;
	}
	for (i = 0; i < M; i++) {
		if (mergeSets(Edges[i].u, Edges[i].v)) // If the nodes are not connected yet,
			minCost += Edges[i].weight;		// then add the edge into the minimum spanning tree
	}
	printf("%d\n", minCost);
	return 0;
}

void sortEdges(Edge* E, int size) {
	// TODO
	// You must implement this function ...
	// - Sort edges in the increasing order of edge weights
	// - Use M (# of edges) and Edges[] (array of edges) 
	// - Use any sorting algorithm
	int i, j, k;
	if (size <= 1) return;
	int helfSize = size / 2;

	sortEdges(E, helfSize);
	sortEdges(E + helfSize, size - helfSize);

	Edge* mergedEdges = (Edge*)malloc(sizeof(Edge) * size);
	j = 0;
	k = helfSize;
	for (i = 0; i < size; i++)
	{
		if (j >= helfSize) mergedEdges[i] = E[k++];
		else if (k >= size) mergedEdges[i] = E[j++];
		else
		{
			if (E[j].weight < E[k].weight) mergedEdges[i] = E[j++];
			else mergedEdges[i] = E[k++];
		}
	}
	for (i = 0; i < size; i++)
		E[i] = mergedEdges[i];
	free(mergedEdges);
}

int findRoot(int u) {
	if (DSNodes[u].parent == u) return u;
	DSNodes[u].parent = findRoot(DSNodes[u].parent);
	return DSNodes[u].parent;
}

bool mergeSets(int u, int v) {
	u = findRoot(u);
	v = findRoot(v);
	if (u == v) return false;
	if (DSNodes[u].size > DSNodes[v].size) {
		DSNodes[u].size += DSNodes[v].size;
		DSNodes[v].parent = u;
	}
	else {
		DSNodes[v].size += DSNodes[u].size;
		DSNodes[u].parent = v;
	}
	return true;
}
