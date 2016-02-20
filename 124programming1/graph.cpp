// graph.cpp

#include "graph.h"

class Graph
{
	public:
		Graph();
		Graph(unsigned int size);
		unsigned int size(); // number of vertices
		void add(Edge edge);
		void print();
		std::vector<Edge> getEdges();
	private:
		std::vector<Edge> m_edges;
		std::vector<int> m_vertices;
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