// strassen.cpp

#include "matrixops.h"
#include <float.h>

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
              for (unsigned int i = 0; i < len; ++i)
              {
                infile >> line;
                dataA[i] = atoi(line);
              }
              for (unsigned int j = 0; j < dimension; ++j)
              {
                for (unsigned int i = 0; i < dimension; ++i)
                {
                  infile >> line;
                  dataB[i*dimension+j] = atoi(line);
                }
              }
              free(line);

              // input matrices to work with
              Scanner matrixA = Scanner(dataA, true, dimension, dimension, dimension, dimension);
              matrixA.print();
              Scanner matrixB = Scanner(dataB, false, dimension, dimension, dimension, dimension);
              matrixB.print();
              MatrixOps matmath = MatrixOps();
              Scanner matrixC = matmath.strassensWrapper(matrixA, matrixB);
              matrixC.print();
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
          // used for determining crossover
          case 1:
          {
            MatrixOps matmath = MatrixOps();
            int * dataA = new int[dimension*dimension+1];
            for (unsigned int i = 0; i < dimension; ++i)
            {
              for (unsigned int j = 0; j < dimension; ++j)
              {
                dataA[i * dimension + j] = rand() % 3 - 1;
              }
            }
            int * dataB = new int[dimension*dimension+1];
            for (unsigned int i = 0; i < dimension; ++i)
            {
              for (unsigned int j = 0; j < dimension; ++j)
              {
                dataB[i * dimension + j] = rand() % 3 - 1;
              }
            }

            Scanner A = Scanner(dataA, true, dimension, dimension, dimension, dimension);
            Scanner B = Scanner(dataB, false, dimension, dimension, dimension, dimension);
            double prevTime = DBL_MAX;
            unsigned int bestPoint = -1;
            unsigned int crossPoint = 8;
            while (crossPoint < dimension)
            {
              double runtime = 0;
              clock_t t = clock();
              matmath.strassensWrapper(A, B, crossPoint);
              matmath.unload();
              runtime = (double) (clock() - t) / CLOCKS_PER_SEC * 1000;
              std::cout << "Crosspoint: " << crossPoint << std::endl;
              std::cout << "Runtime: " << runtime << std::endl;
              if (prevTime > runtime)
              {
                bestPoint = crossPoint;
                prevTime = runtime;
              }
              crossPoint *= 2;
            }
            std::cout << "Best crossover point: " << bestPoint << std::endl;
            free(dataA);
            free(dataB);
            return 0;
          }
          // used for determining average runtime for 3 trials
          case 2:
          {
            MatrixOps matmath = MatrixOps();
            for (unsigned int i = 2; i <= 4096; i *= 2)
            {
              int * dataA = new int[i * i + 1];
              for (unsigned int j = 0; j < i; ++j)
              {
                for (unsigned int k = 0; k < i; ++k)
                {
                  dataA[j * i + k] = rand() % 3 - 1;
                }
              }
              int * dataB = new int[i*i+1];
              for (unsigned int j = 0; j < i; ++j)
              {
                for (unsigned int k = 0; k < i; ++k)
                {
                  dataB[j * i + k] = rand() % 3 - 1;
                }
              }
              Scanner A = Scanner(dataA, true, i, i, i, i);
              Scanner B = Scanner(dataB, false, i, i, i, i);
              double averageTime = 0;
              for (unsigned int j = 0; j < 3; ++j)
              {
                double runtime = 0;
                clock_t t = clock();
                matmath.strassensWrapper(A, B);
                matmath.unload();
                runtime = (double) (clock() - t) / CLOCKS_PER_SEC * 1000 / 3;
                averageTime += runtime;
              }
              std::cout << "Dimension: " << i << std::endl;
              std::cout << "Average runtime: " << averageTime << std::endl;
              free(dataA);
              free(dataB);
            }
            return 0;
          }
          case 3:
          {
            MatrixOps matmath = MatrixOps();
            int * dataA = new int[dimension*dimension+1];
            for (unsigned int i = 0; i < dimension; ++i)
            {
              for (unsigned int j = 0; j < dimension; ++j)
              {
                dataA[i * dimension + j] = j;
              }
            }
            int * dataB = new int[dimension*dimension+1];
            for (unsigned int i = 0; i < dimension; ++i)
            {
              for (unsigned int j = 0; j < dimension; ++j)
              {
                dataB[i * dimension + j] = j;
              }
            }

            Scanner A = Scanner(dataA, true, dimension, dimension, dimension, dimension);
            Scanner B = Scanner(dataB, false, dimension, dimension, dimension, dimension);
            Scanner C = matmath.strassensWrapper(A, B, 4);
            C.print();
            free(dataA);
            free(dataB);
            return 0;
          }
      }
    }
}