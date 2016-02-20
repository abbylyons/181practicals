// pqueueTest.cpp

#include "pqueue.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

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