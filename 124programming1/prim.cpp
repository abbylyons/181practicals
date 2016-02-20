// prim.cpp

#include "graph.h"
#include "pqueue.h"

Graph prim(Graph g);
2dGraph prim(2dGraph g);
3dGraph prim(3dGraph g);
4dGraph prim(4dGraph g);

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
	bool finished[size] = {false};
	float cost = 0.0;

	// start iterating
	while (!pqueue.empty()) {
		Edge top = queue.removeMin();
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
}

2dGraph prim(2dGraph g)
{

}

3dGraph prim(3dGraph g)
{

}

4dGraph prim(4dGraph g)
{

}


void func() {
	
	priority_queue< pii, vector< pii >, greater< pii > > Q;
	Q.push(make_pair(0, 1));	// insert vertex 1 with cost 0
	cost = 0;
	
	printf("%lld\n", cost);
}
