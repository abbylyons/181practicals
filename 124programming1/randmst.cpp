#include "prim.h"

int main (int argc, char *argv[])
{
  unsigned short int mode = 0;
  unsigned short int numpoints = 0;
  unsigned short int numtrials = 0;
  unsigned short int dimension = 0;

  // argc should be 2 for correct execution
  if (argc != 5)
  {
    std::cout << "Wrong input. Usage: randmst mode numpoints numtrials dimension" << std::endl;
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
      std::cout << "Wrong dimension" << std::endl;
      return 1;
    }

    double total_cost = 0.0;
    for (int i = 0; i < numtrials; i++)
    {
      Graph g = Graph(numpoints, dimension);
      total_cost += prim(g);
    }

    std::cout << total_cost/numtrials << " " << numpoints << " " << numtrials << " " << dimension  << std::endl;
  }
}
