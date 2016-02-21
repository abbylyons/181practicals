// graph.h

#include <tuple>
#include <utility>
#include <vector>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>

// 2-dimensional graph, not on the coordinate plane
typedef std::pair<float, float> d2Point;
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
		Graph(const unsigned int size, const unsigned int dimension);
		unsigned int size() const; // number of vertices
		void print() const;
		Edge getEdge(const unsigned int index) const;
		unsigned int numEdges() const;
	private:
		std::vector<Edge> m_edges;
		const unsigned int m_size;
};
