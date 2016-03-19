// strassen.cpp

#include "strassen.h"


// multiply 2 square matrices using traditional method
Scanner conventionalMatrixMult(Scanner A, Scanner B, bool outColMajor)
{
  A.goHome();
  B.goHome();
  unsigned int dim = A.getHeight();
  unsigned int len = dim*dim;
  int * newdata = (int *) malloc(sizeof(int) * len);
  memset(newdata, 0, sizeof(int) * len);
  if (outColMajor)
  {
    for (unsigned int col = 0; col < dim; col++)
    {
      for (unsigned int row = 0; row < dim; row++)
      {
        for (unsigned int i = 0; i < dim; i++)
        {
          newdata[col*dim + row] += A.current() * B.current();
          A.nextInRow();
          B.nextInColumn();
        }
        A.startNextRow();
        B.startCurrentColumn();
      }
      B.startNextColumn();
      A.startCurrentColumn();
    }
    return Scanner(newdata, false, dim, dim, dim, dim);
  }
  else
  {
    for (unsigned int col = 0; col < dim; col++)
    {
      for (unsigned int row = 0; row < dim; row++)
      {
        for (unsigned int i = 0; i < dim; i++)
        {
          newdata[row*dim + col] += A.current() * B.current();
          A.nextInRow();
          B.nextInColumn();
        }
        A.startNextRow();
        B.startCurrentColumn();
      }
      B.startNextColumn();
      A.startCurrentColumn();
    }
    return Scanner(newdata, true, dim, dim, dim, dim);
  }
}


// add 2 square matrices
Scanner addMatrices(Scanner A, Scanner B, bool outColMajor)
{
  A.goHome();
  B.goHome();
  unsigned int dim = A.getHeight();
  int * newdata = (int *) malloc(sizeof(int) * dim*dim);
  if (outColMajor)
  {
    for (unsigned int i = 0; i < dim; i ++)
    {
      for (unsigned int j = 0; j < dim; j ++)
      {
        newdata[i*dim+j] = A.current() + B.current();
        A.nextInColumn();
        B.nextInColumn();
      }
      A.startNextColumn();
      B.startNextColumn();
    }
    return Scanner(newdata, false, dim, dim, dim, dim);
  }
  else
  {
    for (unsigned int i = 0; i < dim; i ++)
    {
      for (unsigned int j = 0; j < dim; j ++)
      {
        newdata[i*dim+j] = A.current() + B.current();
        A.nextInRow();
        B.nextInRow();
      }
      A.startNextRow();
      B.startNextRow();
    }
  }
  return Scanner(newdata, true, dim, dim, dim, dim);
}


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

        // used for testing addMatrices and conventionalMatrixMult
        if (mode == 1)
        {
          int* data =(int *) malloc(sizeof(int) * 4);
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
        }
        else
        {
          std::cout << dimension << std::endl;
          std::cout << inputfile << std::endl;
        }
    }
}
