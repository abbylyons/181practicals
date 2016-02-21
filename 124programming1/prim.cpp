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

double prim(Graph &g)
{
	// initialize priority queue
	unsigned int vertices = g.size();
	unsigned int edgeCount = g.numEdges();
	Pqueue pqueue(edgeCount);

	// initialize finished array
	bool * finished = new bool[vertices];
	memset(finished, vertices * sizeof(bool), false);

	// let's get started!
	short int newVertex = g.getEdge(0).a;
	std::cout << "First new vertex is " << newVertex << std::endl;
	finished[newVertex] = true;

	double cost = 0.0;

	// start iterating
	while (!done(finished, vertices))
	{
		for (unsigned int i = 0; i < edgeCount; ++i)
		{
			Edge edge = g.getEdge(i);
			if (edge.a == newVertex)  
			{
				if (finished[edge.b])  continue;
				pqueue.insert(edge);
				std::cout << edge.a << " " << edge.b << " " << edge.w << std::endl;
			}
			if (edge.b == newVertex)
			{
				if (finished[edge.a])  continue;
				pqueue.insert(edge);
				std::cout << edge.a << " " << edge.b << " " << edge.w << std::endl;
			}
		}

		while (!pqueue.empty())
		{
			Edge top = pqueue.removeMin();
			std::cout << "Remove min: " << top.w << std::endl;
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
