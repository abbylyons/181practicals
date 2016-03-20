// matrixops.cpp

#include "matrixops.h"

// multiply 2 square matrices using traditional method
Scanner conventionalMatrixMult(Scanner A, Scanner B, bool outColMajor)
{
  A.goHome();
  B.goHome();
  unsigned int dim = A.getHeight();
  unsigned int len = dim*dim;
  int * newdata = (int *) malloc(sizeof(int) * len);
  if(newdata == NULL)
  {
    std::cout << "error allocating memory" << std::endl;
    return 1;
  }
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
  // send the scanner in input matrices home
  A.goHome();
  B.goHome();
  unsigned int dim = A.getHeight();

  // allocate memory for output matix
  int * newdata = (int *) malloc(sizeof(int) * dim*dim);
  if(newdata == NULL)
  {
    std::cout << "error allocating memory" << std::endl;
    return 1;
  }
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

Scanner strassens(Scanner A, Scanner B)
{
  //TODO: Make the stassens algorithm.
}
