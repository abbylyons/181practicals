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

Graph::Graph(unsigned int size, unsigned int dimension)
{

  // seed the random generator
  srand(time(NULL));

  m_size = size;
  if (dimension == 0)
  {
    for (unsigned int i = 0; i < m_size; i++)
    {
      for (unsigned int j = i; j < m_size; j++)
      {
        Edge e;
        e.a = i;
        e.b = j;
        e.w = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        m_edges.push_back(e);
      }
    }
  }
  else if (dimension == 2)
  {

    d2Point* points = (d2Point*) malloc(sizeof(d2Point)*m_size);

    // generate points
    for (unsigned int i = 0; i < m_size; i++)
    {
      float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      points[i] = std::make_pair(x, y);
    }

    for (unsigned int i = 0; i < m_size; i++)
    {
      for (unsigned int j = i; j < m_size; j++)
      {
        Edge e;
        e.a = i;
        e.b = j;
        e.w = sqrt(pow(points[i].first-points[j].first, 2) + pow(points[i].second-points[j].second, 2));
        m_edges.push_back(e);
      }
    }
    free(points);
  }
  else if (dimension == 3)
  {
    d3Point* points = (d3Point*) malloc(sizeof(d3Point)*m_size);

    // generate points
    for (unsigned int i = 0; i < m_size; i++)
    {
      float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      points[i] = d3Point (x, y, z);
    }
    for (unsigned int i = 0; i < m_size; i++)
    {
      for (unsigned int j = i; j < m_size; j++)
      {
        Edge e;
        e.a = i;
        e.b = j;
        e.w = sqrt(pow(std::get<0>(points[i])-std::get<0>(points[j]), 2) +
      pow(std::get<1>(points[i])-std::get<1>(points[j]), 2) + pow(std::get<2>(points[i])-std::get<2>(points[j]), 2));
        m_edges.push_back(e);
      }
    }
    free(points);
  }
  else if (dimension == 4)
  {
    d4Point* points = (d4Point*) malloc(sizeof(d4Point)*m_size);

    // generate points
    for (unsigned int i = 0; i < m_size; i++)
    {
      float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      float w = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      points[i] = d4Point (x, y, z, w);
    }
    for (unsigned int i = 0; i < m_size; i++)
    {
      for (unsigned int j = i; j < m_size; j++)
      {
        Edge e;
        e.a = i;
        e.b = j;
        e.w = sqrt(pow(std::get<0>(points[i])-std::get<0>(points[j]), 2) +
        pow(std::get<1>(points[i])-std::get<1>(points[j]), 2) + pow(std::get<2>(points[i])-std::get<2>(points[j]), 2) +
        pow(std::get<3>(points[i])-std::get<3>(points[j]), 2));
        m_edges.push_back(e);
      }
    }
    free(points);
  }
}

unsigned int Graph::size()
{
  return m_size;
}

void Graph::print()
{
  std::cout << "Edges:" << std::endl;
  std::cout << "u, v, weight" << std::endl;
  int len = m_edges.size();
  for(int i = 0; i < len; i++)
  {
    std::cout << m_edges[i].a << m_edges[i].b << m_edges[i].w << std::endl;
  }
  return;
}

std::vector<Edge> Graph::getEdges()
{
  return m_edges;
}
