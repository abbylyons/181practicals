// randmst.cpp

#include "prim.h"

#include <time.h>

int main (int argc, char *argv[])
{
    // argc should be 5 for correct execution
    if (argc != 5)
    {
        std::cout << "Wrong input. Usage: randmst mode numpoints numtrials dimension" << std::endl;
        return 1;
    }

    // get parameters
    else
    {
        // const unsigned short int mode = atoi(argv[1]);
        const unsigned int numpoints = atoi(argv[2]);
        const unsigned short int numtrials = atoi(argv[3]);
        const unsigned short int dimension = atoi(argv[4]);
        if (dimension > 4 || dimension == 1)
        {
            std::cout << "Wrong dimension" << std::endl;
            return 1;
        }

        double total_cost = 0.0;
        double runtime = 0;
        for (int i = 0; i < numtrials; i++)
        {
            clock_t t = clock();
            Graph g = Graph(numpoints, dimension);
            total_cost += prim(g);
            t = clock() - t;
            runtime += (double) t;
        }

        std::cout << total_cost/numtrials << " " << numpoints << " " << numtrials << " " << dimension  << std::endl;
        std::cout << "Runtime: " << runtime/(numtrials * CLOCKS_PER_SEC) << std::endl;
        std::cout << "------------" << std::endl;
    }
    return 0;
}
