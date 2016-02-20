// graph.h

#include <tuple>
#include <utility>
#include <vector>

typedef std::pair<float, float> d2Point;
typedef std::tuple<float, float, float> d3Point;
typedef std::tuple<float, float, float, float> d4Point;

// 2-dimensional graph, not on the coordinate plane

struct Edge
{
  	unsigned short int a;
  	unsigned short int b;
  	float w;
};

class Graph
{
	public:
		Graph();
		Graph(int size);
		unsigned int size();
		void add(Edge edge);
		void print();
		std::vector<Edge> getEdges();
	private:
		std::vector<Edge> m_edges;
		std::vector<int> m_vertices;
};

// 2-dimensional graph in the unit square

struct D2Edge
{
	d2Point a;
	d2Point b;
	float w;
};

class D2Graph
{
	public:
		D2Graph();
		D2Graph(int size);
		unsigned int size();
		void add(D2Edge edge);
		void print();
	private:
		std::vector<D2Edge> m_edges;
};

// 3-dimensional graph in the unit cube

struct D3Edge
{
	d3Point a;
	d3Point b;
	float w;
};

class D3Graph
{
	public:
		D3Graph();
		D3Graph(int size);
		unsigned int size();
		void add(D3Edge edge);
		void print();
	private:
		std::vector<D3Edge> m_edges;
};

// 4-dimensional graph in the unit hypercube

struct D4Edge
{
	d4Point a;
	d4Point b;
	float w;
};

class D4Graph
{
	public:
		D4Graph();
		D4Graph(int size);
		unsigned int size();
		void add(D4Edge edge);
		void print();
	private:
		std::vector<D4Edge> m_edges;
};