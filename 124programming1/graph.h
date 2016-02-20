// graph.h

#include <tuple>
#include <utility>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <math.h>

// 2-dimensional graph, not on the coordinate plane
typedef std:pair<float, float> d2Point;
typedef std::tuple<float, float, float> d3Point;
typedef std::tuple<float, float, float, float> d4Point;

struct Edge
{
  	unsigned short int a;
  	unsigned short int b;
  	float w;
};

class Graph
{
	public:
		Graph(unsigned int size, unsigned int dimension);
		unsigned int size(); // number of vertices
		void add(Edge edge);
		void print();
		std::vector<Edge> getEdges();
	private:
		std::vector<Edge> m_edges;
		unsigned int m_size;
};
