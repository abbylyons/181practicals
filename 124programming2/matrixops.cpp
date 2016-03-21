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
    throw "malloc error";
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
    throw "malloc error";
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

// subtract 2 square matrices
Scanner subtractMatrices(Scanner A, Scanner B, bool outColMajor)
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
    throw "malloc error";
  }
  if (outColMajor)
  {
    for (unsigned int i = 0; i < dim; i ++)
    {
      for (unsigned int j = 0; j < dim; j ++)
      {
        newdata[i*dim+j] = A.current() - B.current();
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
        newdata[i*dim+j] = A.current() - B.current();
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
  unsigned int A_height = A.getHeight();
  unsigned int A_width = A.getWidth();
  unsigned int B_height = B.getHeight();
  unsigned int B_width = B.getWidth();
  bool A_type = A.isRowMajor();
  bool B_type = B.isRowMajor();
  int* A_offset = A.offset();
  int* B_offset = B.offset();
  Scanner A11 = Scanner(A_offset, A_type, A_width, A_height, A_width/2, A_height/2);
  Scanner A12;
  Scanner A21;
  Scanner A22;
  Scanner B11 = Scanner(B_offset, B_type, B_width, B_height, B_width/2, B_height/2);
  Scanner B12;
  Scanner B21;
  Scanner B22;
  if (A_type)
  {
    A12 = Scanner(A_offset + A_width*A_height/2, A_type, A_width, A_height, A_width/2, A_height/2);
    A21 = Scanner(A_offset + A_width/2, A_type, A_width, A_height, A_width/2, A_height/2);
    A22 = Scanner(A_offset + A_width*(A_height/2) + A_width/2, A_type, A_width, A_height, A_width/2, A_height/2);
  }
  else
  {
    A12 = Scanner(A_offset + A_height/2, A_type, A_width, A_height, A_width/2, A_height/2);
    A21 = Scanner(A_offset + A_height*A_width/2, A_type, A_width, A_height, A_width/2, A_height/2);
    A22 = Scanner(A_offset + A_height*(A_width/2) + A_width/2, A_type, A_width, A_height, A_width/2, A_height/2);
  }
  if (B_type)
  {
    B12 = Scanner(B_offset + B_width*B_height/2, B_type, B_width, B_height, B_width/2, B_height/2);
    B21 = Scanner(B_offset + B_width/2, B_type, B_width, B_height, B_width/2, B_height/2);
    B22 = Scanner(B_offset + B_width*(B_height/2) + B_width/2, B_type, B_width, B_height, B_width/2, B_height/2);
  }
  else
  {
    B12 = Scanner(B_offset + B_height/2, B_type, B_width, B_height, B_width/2, B_height/2);
    B21 = Scanner(B_offset + B_height*B_width/2, B_type, B_width, B_height, B_width/2, B_height/2);
    B22 = Scanner(B_offset + B_height*(B_width/2) + B_width/2, B_type, B_width, B_height, B_width/2, B_height/2);
  }
  Scanner M1 = strassens(addMatrices(A11, A22, true), addMatrices(B11, B22, false));
  Scanner M2 = strassens(addMatrices(A21, A22, true), B11);
  Scanner M3 = strassens(A11, subtractMatrices(B12, B22, false));
  Scanner M4 = strassens(A22, subtractMatrices(B21, B11, false));
  Scanner M5 = strassens(addMatrices(A11, A12, true), B22);
  Scanner M6 = strassens(subtractMatrices(A21, A11, true), addMatrices(B11, B12, false));
  Scanner M7 = strassens(subtractMatrices(A12, A22), addMatrices(B21, B22, false));
  Scanner C11 = addMatrices(subtractMatrices(addMatrices(M1, M4, false), M5, false), M7, false);
  Scanner C12 = addMatrices(M3, M5, false);
  Scanner C21 = addMatrices(M2, M4, false);
  Scanner C22 = addMatrices(addMatrices(subtractMatrices(M1, M2, false), M3, false), M6, false);

  //TODO: implement a way how to stich C11, C12, C21, C22 together into one matrix.
  //TODO: add in the cutoff point and switch to conventionalMatrixMult
  //TODO: free pooling
  //TODO: destoryers
  //TODO: Grab your Nutz and scream Fuck the Police

}
