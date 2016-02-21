// prim.cpp

#include "prim.h"

bool done(bool * array, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		if (!array[i])  return false;
	}
	return true;
}

double prim(Graph g)
{
	// initialize priority queue
	unsigned int vertices = g.size();
	std::vector<Edge> edges = g.getEdges();
	unsigned int edgeCount = edges.size();
	Pqueue pqueue(edgeCount);

	// initialize finished array
	bool finished[vertices];
	memset(finished, vertices * sizeof(bool), 0);
	finished[edges[0].a] = true;

	double cost = 0.0;

	// start iterating
	while (!done(finished, vertices))
	{
		for (unsigned int i = 0; i < edgeCount; ++i)
		{
			if (finished[edges[i].b])  continue;
			if (finished[edges[i].a])  pqueue.insert(edges[i]);
		}
		std::cout << "Edges added to queue" << std::endl;

		while (!pqueue.empty())
		{
			Edge top = pqueue.removeMin();
			std::cout << top.w << std::endl;
			if (!finished[top.b])
			{
				cost += top.w;
				std::cout << "Cost so far: " << cost << std::endl;
				finished[top.b] = true;
				break;
			}
		}
	}
	return cost;
}
