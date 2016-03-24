// matrixops.cpp

#include "matrixops.h"

#define CROSSOVER 2

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
  int * newdata = (int *) malloc(sizeof(int) * dim * dim);
  if(newdata == NULL)
  {
    std::cout << "error allocating memory" << std::endl;
    throw "malloc error";
  }
  if (outColMajor)
  {
    for (unsigned int i = 0; i < dim; i++)
    {
      for (unsigned int j = 0; j < dim; j++)
      {
        newdata[i * dim + j] = A.current() + B.current();
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
    for (unsigned int i = 0; i < dim; i++)
    {
      for (unsigned int j = 0; j < dim; j++)
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
  A.goHome();
  B.goHome();
  std::cout << "New strassens" << std::endl;
  A.print();
  std::cout << (A.isRowMajor() ? "row major" : "col major") << std::endl;
  B.print();
  std::cout << (B.isRowMajor() ? "row major" : "col major") << std::endl;
  unsigned int A_height = A.getHeight();
  unsigned int A_width = A.getWidth();
  unsigned int B_height = B.getHeight();
  unsigned int B_width = B.getWidth();
  unsigned int A_originalHeight = A.getOriginalHeight();
  unsigned int A_originalWidth = A.getOriginalWidth();
  unsigned int B_originalHeight = B.getOriginalHeight();
  unsigned int B_originalWidth = B.getOriginalWidth();
  bool A_type = A.isRowMajor();
  bool B_type = B.isRowMajor();
  int* A_offset = A.offset();
  int* B_offset = B.offset();
  Scanner A11 = Scanner();
  Scanner A12 = Scanner();
  Scanner A21 = Scanner();
  Scanner A22 = Scanner();
  Scanner B11 = Scanner();
  Scanner B12 = Scanner();
  Scanner B21 = Scanner();
  Scanner B22 = Scanner();
  if (A_type)
  {
<<<<<<< HEAD
    A11 = Scanner(A_offset, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A21 = Scanner(A_offset + A_originalWidth*A_originalHeight/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A12 = Scanner(A_offset + A_originalWidth/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A22 = Scanner(A_offset + A_originalWidth*(A_originalHeight/2) + A_originalWidth/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
  }
  else
  {
    A11 = Scanner(A_offset, !A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A21 = Scanner(A_offset + A_originalHeight/2, !A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A12 = Scanner(A_offset + A_originalHeight*A_originalWidth/2, !A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A22 = Scanner(A_offset + A_originalHeight*(A_originalWidth/2) + A_originalWidth/2, !A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
  }
  if (B_type)
  {
    B11 = Scanner(B_offset, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B21 = Scanner(B_offset + B_originalWidth*B_originalHeight/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B12 = Scanner(B_offset + B_originalWidth/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B22 = Scanner(B_offset + B_originalWidth*(B_originalHeight/2) + B_width/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
  }
  else
  {
    B11 = Scanner(B_offset, !B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B21 = Scanner(B_offset + B_originalHeight/2, !B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B12 = Scanner(B_offset + B_originalHeight*B_originalWidth/2, !B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B22 = Scanner(B_offset + B_originalHeight*(B_originalWidth/2) + B_originalWidth/2, !B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
  }

  Scanner M1 = Scanner();
  Scanner M2 = Scanner();
  Scanner M3 = Scanner();
  Scanner M4 = Scanner();
  Scanner M5 = Scanner();
  Scanner M6 = Scanner();
  Scanner M7 = Scanner();
  if (A_height <= CROSSOVER)
  {
    A11.print();
    A12.print();
    A21.print(); // fix
    A22.print(); // fix
    B11.print();
    B12.print(); // fix
    B21.print();
    B22.print(); // fix
    M1 = conventionalMatrixMult(addMatrices(A11, A22, false), addMatrices(B11, B22, true), false);
    M2 = conventionalMatrixMult(addMatrices(A21, A22, false), B11, false);
    M3 = conventionalMatrixMult(A11, subtractMatrices(B12, B22, true), false);
    M4 = conventionalMatrixMult(A22, subtractMatrices(B21, B11, true), false);
    M5 = conventionalMatrixMult(addMatrices(A11, A12, false), B22, false);
    M6 = conventionalMatrixMult(subtractMatrices(A21, A11, false), addMatrices(B11, B12, true), false);
    M7 = conventionalMatrixMult(subtractMatrices(A12, A22, false), addMatrices(B21, B22, true), false);
  }
  else
  {
    M1 = strassens(addMatrices(A11, A22, false), addMatrices(B11, B22, true));
    M2 = strassens(addMatrices(A21, A22, false), B11);
    M3 = strassens(A11, subtractMatrices(B12, B22, true));
    M4 = strassens(A22, subtractMatrices(B21, B11, true));
    M5 = strassens(addMatrices(A11, A12, false), B22);
    M6 = strassens(subtractMatrices(A21, A11, false), addMatrices(B11, B12, true));
    M7 = strassens(subtractMatrices(A12, A22, false), addMatrices(B21, B22, true));
  }
  Scanner C11 = addMatrices(subtractMatrices(addMatrices(M1, M4, false), M5, false), M7, false);
  Scanner C12 = addMatrices(M3, M5, false);
  Scanner C21 = addMatrices(M2, M4, false);
  Scanner C22 = addMatrices(addMatrices(subtractMatrices(M1, M2, false), M3, false), M6, false);

  M1.print();
  M2.print();
  M3.print();
  M4.print();
  M5.print();
  M6.print();
  M7.print();
  C11.print();
  C12.print();
  C21.print();
  C22.print();

  int d = C11.getHeight();
  int * newMatrix = (int *) malloc(d * d * 4 * sizeof(int));
  int * offset1 = C11.offset();
  int * offset2 = C12.offset();
  for (int i = 0; i < d; ++i)
  {
    memcpy(newMatrix, offset1, d * sizeof(int));
    memcpy(newMatrix + d, offset2, d * sizeof(int));
    newMatrix += 2 * d;
    offset1 += d;
    offset2 += d;
  }
  offset1 = C21.offset();
  offset2 = C22.offset();
  for (int i = 0; i < d; ++i)
  {
    memcpy(newMatrix, offset1, d * sizeof(int));
    memcpy(newMatrix + d, offset2, d * sizeof(int));
    newMatrix += 2 * d;
    offset1 += d;
    offset2 += d;
  }
  newMatrix -= d * d * 4;
  d *= 2;
  Scanner X = Scanner(newMatrix, true, d, d, d, d);
  X.print();
  return X;
  //TODO: free pooling
  //TODO: add padding
  //TODO: add base case
}
