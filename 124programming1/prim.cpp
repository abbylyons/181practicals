// prim.cpp

#include "prim.h"

double prim(const Graph & g)
{
	// initialize priority queue
	const unsigned int vertices = g.size();
	const unsigned int edgeCount = g.numEdges();
	Pqueue pqueue(vertices);

	// initialize finished array
	bool * const finished = new bool[vertices];
	memset(finished, 0, vertices * sizeof(bool));

	// pick first node for tree
	unsigned int newVertex = g.getEdge(0).a;
	finished[newVertex] = true;
	double cost = 0.0;
	// start iterating
	while (!(done(finished, vertices)))
	{
		// add things to the queue
		for (unsigned int i = 0; i < edgeCount-1; ++i)
		{
			const Edge edge = g.getEdge(i);
			if (edge.a == newVertex)
			{
				if (finished[edge.b])  continue;
				pqueue.insert(edge, 1);
			}
			if (edge.b == newVertex)
			{
				if (finished[edge.a])  continue;
				pqueue.insert(edge, 0);
			}
		}

		// get the shortest edge from the queue
		while (!pqueue.empty())
		{
			const Edge top = pqueue.removeMin();
			if (!finished[top.b])
			{
				cost += top.w;
				newVertex = top.b;
				finished[newVertex] = true;
				break;
			}
			if (!finished[top.a])
			{
				cost += top.w;
				newVertex = top.a;
				finished[newVertex] = true;
				break;
			}
		}
	}
	delete finished;
	return cost;
}

bool done(bool * const array, const unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		if (!array[i])  return false;
	}
	return true;
}