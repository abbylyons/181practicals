// pqueue.cpp

#include "pqueue.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

Pqueue::Pqueue(int size)
  : m_end(0)
{
  // initialize the array of edges
  unsigned long int edges = (size);
  std::cout << "Making priority queue array..." << std::endl;
  m_array = (Edge*)malloc((sizeof(Edge))*(edges+1));
  std::cout << "Array made successfully" << std::endl;
  memset(m_array, 0, sizeof(Edge)*(edges+1));
  // array for holding positions
  m_positions = (unsigned short int *)malloc((sizeof(unsigned short int))*(edges+1));
  std::cout << "Positions array made successfully" << std::endl;
  memset(m_positions, 0, sizeof(Edge)*(edges+1));
  std::cout << "Positions array set successfully" << std::endl;
}

void Pqueue::insert(Edge e, unsigned short int target)
{
  std::cout << "Inserting edge" << std::endl;
  unsigned short int pos;
  // check whether there is a corresponding edge in the graph already.
  if (m_positions[e.b] != 0)
  {
    // check if new edge is "cheaper"
    if (m_array[m_positions[e.b]].w > e.w)
    {
      // swap the elements
      m_array[m_positions[e.b]] = e;
      pos = m_positions[e.b];
    }
    else
    {
      //don't insert the edge
      return;
    }
  }
  else
  {
    // insert new edge to the end
    m_end ++;
    m_array[m_end] = e;
    m_positions[e.b] = m_end;
    pos = m_end;
  }

  // keep swapping up to keep the order property
  while (pos/2 != 0) {
    if (m_array[pos].w < m_array[pos/2].w)
    {
      Edge temp = m_array[pos/2];
      m_array[pos/2] = m_array[pos];
      m_positions[m_array[pos/2].b] = pos/2;
      m_array[pos] = temp;
      m_positions[temp.b] = pos;
      pos = pos/2;
    }
    else {
      return;
    }
  }
}

Edge Pqueue::removeMin(void)
{
  Edge min = m_array[1];
  m_positions[min.b] = 0;
  m_array[1] = m_array[m_end];
  m_positions[m_array[1].b] = 1;
  m_end--;
  unsigned long int pos = 1;
  while (pos < m_end)
  {

    // check if vertex has left child
    if(2*pos <= m_end)
    {
      // check if vertex has right child
      if(2*pos +1 <= m_end)
      {
        //check if right child is smaller than left and parent
        if(m_array[2*pos + 1].w < m_array[2*pos].w && m_array[pos].w > m_array[2*pos + 1].w)
        {
          Edge temp = m_array[2*pos + 1];
          m_array[2*pos + 1] = m_array[pos];
          m_positions[m_array[2*pos + 1].b] = 2*pos + 1;
          m_array[pos] = temp;
          m_positions[m_array[pos].b] = pos;
          pos = 2*pos + 1;
        }
      }
      if (m_array[2*pos].w < m_array[pos].w)
      {
        Edge temp = m_array[2*pos];
        m_array[2*pos] = m_array[pos];
        m_positions[m_array[2*pos].b] = 2*pos;
        m_array[pos] = temp;
        m_positions[m_array[pos].b] = pos;
        pos = 2*pos;
      }
      else
      {
        return min;
      }
    }
    else
    {
      return min;
    }
  }
  return min;
}

void Pqueue::print(void)
{
  for(unsigned int i = 1; i <= m_end; i++)
  {
    std::cout << m_array[i].w << std::endl;
  }
}

Pqueue::~Pqueue(void)
{
  free(m_array);
  free(m_positions);
}
