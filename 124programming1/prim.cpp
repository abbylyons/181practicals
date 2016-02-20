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
	unsigned int size = g.size();
	Pqueue pqueue(size);
	std::vector<Edge> edges = g.getEdges();

	// initialize finished array
	bool finished[size];
	memset(finished, size * sizeof(bool), 0);
	finished[edges[0].a] = true;

	double cost = 0.0;
	// start iterating
	while (!done(finished, size))
	{
		for (unsigned int i = 0; i < size; ++i)
		{
			if (finished[edges[i].b])  continue;
			if (finished[edges[i].a])  pqueue.insert(edges[i]);
		}
		Edge top = pqueue.removeMin();
		do
		{
			std::cout << pqueue.empty() << std::endl;
			if (!finished[top.b])
			{
				cost += top.w;
				finished[top.b] = true;
				break;
			}

			top = pqueue.removeMin();
		} while (!pqueue.empty());
	}
	return cost;
}
