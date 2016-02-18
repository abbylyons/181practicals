// pqueue.cpp

#include "pqueue.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

Pqueue::Pqueue( int size)
{

  // initialize the array of edges
  unsigned long int edges = (size*(size-1))/2;
  array = (Edge*)malloc((sizeof(Edge))*(edges+1));
  end = 0;
}

void Pqueue::insert(Edge e)
{
  // insert new edge to the end
  end ++;
  array[end] = e;
  unsigned long int pos = end;

  // keep swapping up to keep the order property
  while (pos/2 != 0) {
    if (array[pos].w < array[pos/2].w)
    {
      Edge temp = array[pos/2];
      array[pos/2] = array[pos];
      array[pos] = temp;
      pos = pos/2;
    }
    else {
      break;
    }
  }
}

bool Pqueue::empty(void)
{
  return (end == 0);
}

Edge Pqueue::removeMin(void)
{
  //TODO: Check if empty
  Edge min = array[1];
  array[1] = array[end];
  end --;
  unsigned long int pos = 1;
  while (pos < end)
  {
    // check if vertex has left child
    if(2*pos <= end)
    {
      // check if vertex has right child
      if(2*pos +1 <= end)
      {
        //check if right child is smaller than left and parent
        if(array[2*pos + 1].w < array[2*pos].w && array[pos].w > array[2*pos + 1].w)
        {
          Edge temp = array[2*pos + 1];
          array[2*pos + 1] = array[pos];
          array[pos] = temp;
          pos = 2*pos + 1;
        }
      }
      else if (array[2*pos].w < array[pos].w)
      {
        Edge temp = array[2*pos];
        array[2*pos] = array[pos];
        array[pos] = temp;
        pos = 2*pos;
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
  for(int i = 1; i <= end; i++)
  {
    cout << array[i].w << endl;
  }
}
