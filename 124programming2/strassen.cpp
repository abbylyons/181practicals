// strassen.cpp

#include "matrixops.h"


int main (int argc, char *argv[])
{
    // argc should be 4 for correct execution
    if (argc != 4)
    {
        std::cout << "Wrong input. Usage: strassen mode dimension inputfile" << std::endl;
        return 1;
    }

    // get parameters
    else
    {
        const unsigned short int mode = atoi(argv[1]);
        std::cout << mode << std::endl;
        const unsigned int dimension = atoi(argv[2]);
        char * inputfile = argv[3];

        switch(mode)
        {
          // Read inout from the file
          case 0:
          {
            std::ifstream infile;
            infile.open (inputfile);
            unsigned int len = dimension*dimension;
            char* line = (char*) malloc(sizeof(char)*10);
            if (infile.is_open())
            {
              int * dataA = (int*) malloc(sizeof(int)*len);
              int * dataB = (int*) malloc(sizeof(int)*len);
              if(dataA == NULL || dataB == NULL)
              {
                std::cout << "error allocating memory" << std::endl;
                return 1;
              }
              for (unsigned int i = 0; i < len; i++)
              {
                infile >> line;
                dataA[i] = atoi(line);
              }
              for (unsigned int i = 0; i < len; i++)
              {
                infile >> line;
                dataB[i] = atoi(line);
              }
              free(line);

              // input matrices to work with
              Scanner matrixA = Scanner(dataA, true, dimension, dimension, dimension, dimension);
              Scanner matrixB = Scanner(dataB, true, dimension, dimension, dimension, dimension);
              MatrixOps matmath = MatrixOps();
              Scanner matrixC = matmath.strassens(matrixA, matrixB);
              std::cout << matrixC.current() << std::endl;
              matrixC.nextInRow();
              for (unsigned int i = 1; i < dimension; i++)
              {
                std::cout << matrixC.nextInColumn() << std::endl;
                matrixC.nextInRow();
              }
              std::cout << std::endl;
              free(dataA);
              free(dataB);
            }
            infile.close();
            break;
          }
        }
    }
}
