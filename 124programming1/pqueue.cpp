// pqueue.cpp

#include "pqueue.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

Pqueue::Pqueue(int size)
{
  // initialize the array of edges
  unsigned long int edges = (size*(size-1))/2;
  m_array = (Edge*)malloc((sizeof(Edge))*(edges+1));
  m_end = 0;
}

void Pqueue::insert(Edge e)
{
  // insert new edge to the end
  m_end ++;
  m_array[m_end] = e;
  unsigned long int pos = m_end;

  // keep swapping up to keep the order property
  while (pos/2 != 0) {
    if (m_array[pos].w < m_array[pos/2].w)
    {
      Edge temp = m_array[pos/2];
      m_array[pos/2] = m_array[pos];
      m_array[pos] = temp;
      pos = pos/2;
    }
    else {
      break;
    }
  }
}

Edge Pqueue::removeMin(void)
{
  Edge min = m_array[1];
  m_array[1] = m_array[m_end];
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
          m_array[pos] = temp;
          pos = 2*pos + 1;
        }
      }
      if (m_array[2*pos].w < m_array[pos].w)
      {
        Edge temp = m_array[2*pos];
        m_array[2*pos] = m_array[pos];
        m_array[pos] = temp;
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
