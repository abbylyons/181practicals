// prim.cpp

#include "pqueue.h"

#include <iostream>

Graph prim(Graph g);
D2Graph prim(D2Graph g);
D3Graph prim(D3Graph g);
D4Graph prim(D4Graph g);

int main(void)
{
	return 0;
}

Graph prim(Graph g)
{
	// initialize priority queue, finished array, and cost
	unsigned int size = g.size();
	Pqueue pqueue(size);
	std::vector<Edge> edges = g.getEdges();
	pqueue.insert(edges[0]);
	bool finished[size];
	memset(finished, size * sizeof(bool), 0);

	float cost = 0.0;

	// start iterating
	while (!pqueue.empty()) {
		Edge top = pqueue.removeMin();
		if (!finished[top.b])
		{
			cost += top.w;
			finished[top.b] = true;
		}
		for (unsigned int i = 0; i < size; ++i)
		{
			if (finished[edges[i].b])  continue;
			pqueue.insert(edges[i]);
		}
	}
	std::cout << "Cost is " << cost << std::endl;

	// do I have to make a new graph? Help
	return g;
}
