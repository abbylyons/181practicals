#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

struct Edge
{
  float w;
  unsigned short int a;
  unsigned short int b;
};

// priority queue
class Pqueue
{
  private:
    Edge* array;
    unsigned long int end;
  public:
    bool empty(void);
    void insert(Edge e);
    Edge removeMin(void);
    Pqueue(int size);
    void print(void);
 };

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


// function declarations


// main funtion
int main (int argc, char *argv[])
{

  unsigned short int mode = 0;
  unsigned short int numpoints = 0;
  unsigned short int numtrials = 0;
  unsigned short int dimension = 0;

  // argc should be 2 for correct execution
  if (argc != 5)
  {
    cout << "Wrong input. Usage: randmst mode numpoints numtrials dimension" << endl;
    return 1;
  }

  // get parameters
  else
  {
    mode = atoi(argv[1]);
    numpoints = atoi(argv[2]);
    numtrials = atoi(argv[3]);
    dimension = atoi(argv[4]);
    if (dimension > 4 || dimension == 1)
    {
      cout << "Wrong dimension" << endl;
      return 1;
    }
  }

  // intialize graph
  Pqueue edges(numpoints);

  // seed the random generator
  srand(time(NULL));

  // initialize edges
  for(int i = 0; i < numpoints; i++)
  {
    for(int j = i+1; j < numpoints; j++)
    {
      Edge e;
      float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
      if (dimension > 0)
      {
         float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
         if (dimension > 2)
         {
           float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
           if (dimension > 3)
           {
             float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
             e.w = sqrt(x*x + y*y + z*z + g*g);
           }
           else
           {
             e.w = sqrt(x*x + y*y + z*z);
           }
         }
         else
         {
           e.w = sqrt(x*x + y*y);
         }
      }
      else
      {
        e.w = x;
      }
      e.a = i;
      e.b = j;
      edges.insert(e);
    }
  }

  // all done folks!
  return 0;
}
