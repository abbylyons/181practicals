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
          case 0: ifstream infile;
                  infile.open (inputfile);
                  len = dimension*dimension;
                  if (infile.is_open())
                  {
                    int * dataA = (int*) = malloc(sizeof(int)*len);
                    int * dataB = (int*) = malloc(sizeof(int)*len);
                    if(dataA == NULL || dataB == NULL)
                    {
                      std::cout << "error allocating memory" << std::endl;
                      return 1;
                    }
                    for (unsigned int i = 0; i < len; i++)
                    {
                      getline (infile,line);
                      dataA[i] = atoi(line);
                    }
                    for (unsigned int i = 0; i < len; i++)
                    {
                      getline (infile,line);
                      dataB[i] = atoi(line);
                    }
                    // input matrices to work with
                    Scanner matrixA = Scanner(dataA, true, dimension, dimension, dimension, dimension);
                    Scanner matrixB = Scanner(dataB, true, dimension, dimension, dimension, dimension);
                    Scanner matrixC = strassens(matrixA, matrixB);
                    std::cout << matrixC.current() << std::endl;
                    matrixC.nextInRow();
                    for (int i = 1; i < dimension; i++)
                    {
                      std::cout << matrixC.nextInColumn() << std::endl;
                      matrixC.nextInRow();
                    }
                    std::cout << std::endl;
                  }
                  infile.close();
                  break;

          // used for testing addMatrices and conventionalMatrixMult
          case 1: int* data =(int *) malloc(sizeof(int) * 4);
                  if(data == NULL)
                  {
                    std::cout << "error allocating memory" << std::endl;
                    return 1;
                  }
                  data[0] = 1;
                  data[1] = 2;
                  data[2] = 3;
                  data[3] = 4;
                  Scanner A = Scanner(data, true, 2, 2, 2, 2);
                  Scanner B = Scanner(data, false, 2, 2, 2, 2);
                  std::cout << "A:" << std::endl;
                  std::cout << A.current();
                  std::cout << " " << A.nextInRow() << std::endl;
                  A.startNextRow();
                  std::cout << A.current();
                  std::cout << " " << A.nextInRow() << std::endl;
                  std::cout << std::endl;
                  std::cout << "B:" << std::endl;
                  std::cout << B.current();
                  std::cout << " " << B.nextInRow() << std::endl;
                  B.startNextRow();
                  std::cout << B.current();
                  std::cout << " " << B.nextInRow() << std::endl;
                  std::cout << std::endl;
                  Scanner C = addMatrices(A, B, true);
                  Scanner D = addMatrices(A, B, false);
                  std::cout << "C:" << std::endl;
                  std::cout << C.current();
                  std::cout << " " << C.nextInRow() << std::endl;
                  C.startNextRow();
                  std::cout << C.current();
                  std::cout << " " << C.nextInRow() << std::endl;
                  std::cout << std::endl;
                  std::cout << "D:" << std::endl;
                  std::cout << D.current();
                  std::cout << " " << D.nextInRow() << std::endl;
                  D.startNextRow();
                  std::cout << D.current();
                  std::cout << " " << D.nextInRow() << std::endl;
                  Scanner E = conventionalMatrixMult(A, B, true);
                  Scanner F = conventionalMatrixMult(A, B, false);
                  std::cout << std::endl;
                  std::cout << "E:" << std::endl;
                  std::cout << E.current();
                  std::cout << " " << E.nextInRow() << std::endl;
                  E.startNextRow();
                  std::cout << E.current();
                  std::cout << " " << E.nextInRow() << std::endl;
                  std::cout << std::endl;
                  std::cout << "F:" << std::endl;
                  std::cout << F.current();
                  std::cout << " " << F.nextInRow() << std::endl;
                  F.startNextRow();
                  std::cout << F.current();
                  std::cout << " " << F.nextInRow() << std::endl;
                  free(data);
                  C.freeData();
                  D.freeData();
                  E.freeData();
                  F.freeData();
                  break;
        }
    }
}