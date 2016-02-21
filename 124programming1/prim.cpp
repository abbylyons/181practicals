// prim.cpp

#include "prim.h"

double prim(Graph &g)
{
	// initialize priority queue
	const unsigned int vertices = g.size();
	const unsigned int edgeCount = g.numEdges();
	Pqueue pqueue(edgeCount);

	// initialize finished array
	// This is causing valgrind issues even though I clearly initialized it...
	char * finished = new char[vertices];
	/*for (int i = 0; i < vertices; ++i)
	{
		finished[i] = false;
	}*/
	memset(finished, 0, vertices * sizeof(char));
	std::cout << "number of vertices: " << vertices << std::endl;
	std::cout << "bool size " << sizeof(bool) << std::endl;
	std::cout << "finished size " << sizeof(*finished) << std::endl;

	// pick first node for tree
	short int newVertex = g.getEdge(0).a;
	finished[newVertex] = true;
	double cost = 0.0;

	// start iterating
	while (!(done(finished, vertices)))
	{
		// add things to the queue
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

		// get the shortest edge from the queue
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

bool done(char * array, unsigned int size)
{
	for (unsigned int i = 0; i < size; ++i)
	{
		if (!array[i])  return false;
	}
	return true;
}
