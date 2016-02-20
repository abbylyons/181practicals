// prim.cpp

#include "pqueue.h"

#include <iostream>

void prim(Graph g);
D2Graph prim(D2Graph g);
D3Graph prim(D3Graph g);
D4Graph prim(D4Graph g);

int main(void)
{
	return 0;
}

bool done(bool * array, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		if (!array[i])  return false;
	}
	return true;
}

void prim(Graph g)
{
	// initialize priority queue
	unsigned int size = g.size();
	Pqueue pqueue(size);
	std::vector<Edge> edges = g.getEdges();

	// initialize finished array
	bool finished[size];
	memset(finished, size * sizeof(bool), 0);
	finished[edges[0].a] = true;

	float cost = 0.0;

	// start iterating
	while (!done(finished, size)) {
		for (unsigned int i = 0; i < size; ++i)
		{
			if (finished[edges[i].b])  continue;
			if (finished[edges[i].a])  pqueue.insert(edges[i]);
		}
		Edge top = pqueue.removeMin();
		while (!pqueue.empty())
		{
			if (!finished[top.b])
			{
				cost += top.w;
				finished[top.b] = true;
				break;
			}
		}
	}
	std::cout << "Cost is " << cost << std::endl;
}
