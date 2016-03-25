// matrixops.cpp

#include "matrixops.h"
#include <cmath>

MatrixOps::MatrixOps()
  : m_data(NULL)
{

}

MatrixOps::~MatrixOps()
{
  unload();
}

void MatrixOps::unload()
{
  while (m_data != NULL)
  {
    node * temp = m_data;
    m_data = m_data->next;
    free(temp->matrix);
    free(temp);
  }
  m_data = NULL;
}

// multiply 2 square matrices using traditional method
Scanner MatrixOps::conventionalMatrixMult(Scanner A, Scanner B, bool outColMajor)
{
  A.goHome();
  B.goHome();
  unsigned int dim = A.getHeight();
  unsigned int len = dim*dim;
  int * newdata = (int *) malloc(sizeof(int) * len);
  node * newNode = (node *) malloc(sizeof(node));
  newNode->matrix = newdata;
  newNode->next = m_data;
  m_data = newNode;
  if(newdata == NULL)
  {
    std::cout << "error allocating memory" << std::endl;
    throw "malloc error";
  }
  memset(newdata, 0, sizeof(int) * len);

  for (unsigned int col = 0; col < dim; col++)
  {
    for (unsigned int row = 0; row < dim; row++)
    {
      int * Bcur = B.offset();
      int * Acur = A.offset();
      for (unsigned int i = 0; i < dim; i++)
      {
        if (outColMajor)
        {
          newdata[col*dim + row] += Bcur[i] * Acur[i];
        }
        else
        {
          newdata[row*dim + col] += Bcur[i] * Acur[i];
        }
      }
      A.startNextRow();
    }
    B.startNextColumn();
    A.startCurrentColumn();
  }
  if (outColMajor)
  {
    return Scanner(newdata, false, dim, dim, dim, dim);
  }
  else
  {
    return Scanner(newdata, true, dim, dim, dim, dim);
  }
}


// add 2 square matrices
Scanner MatrixOps::addMatrices(Scanner A, Scanner B, bool outColMajor)
{
  // send the scanner in input matrices home
  A.goHome();
  B.goHome();
  unsigned int dim = A.getHeight();

  // allocate memory for output matix
  int * newdata = (int *) malloc(sizeof(int) * dim * dim);
  node * newNode = (node *) malloc(sizeof(node));
  newNode->matrix = newdata;
  newNode->next = m_data;
  m_data = newNode;
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
        if (j < dim-1)
        {
          A.nextInColumn();
          B.nextInColumn();
        }
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
        if (j < dim-1)
        {
          A.nextInRow();
          B.nextInRow();
        }
      }
      A.startNextRow();
      B.startNextRow();
    }
  }
  return Scanner(newdata, true, dim, dim, dim, dim);
}

// subtract 2 square matrices
Scanner MatrixOps::subtractMatrices(Scanner A, Scanner B, bool outColMajor)
{
  // send the scanner in input matrices home
  A.goHome();
  B.goHome();
  unsigned int dim = A.getHeight();

  // allocate memory for output matix
  int * newdata = (int *) malloc(sizeof(int) * dim*dim);
  node * newNode = (node *) malloc(sizeof(node));
  newNode->matrix = newdata;
  newNode->next = m_data;
  m_data = newNode;
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
        if (j < dim-1)
        {
          A.nextInColumn();
          B.nextInColumn();
        }
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
        if (j < dim-1)
        {
          A.nextInRow();
          B.nextInRow();
        }
      }
      A.startNextRow();
      B.startNextRow();
    }
  }
  return Scanner(newdata, true, dim, dim, dim, dim);
}

Scanner MatrixOps::strassensWrapper(Scanner A, Scanner B, unsigned int crossover)
{
  A.goHome();
  B.goHome();
  unsigned int dim = A.getHeight();
  // calculate padding
  if (dim > crossover)
  {
    unsigned int numDivs = pow(2, ceil((log(dim) - log(crossover)) / log(2)));
    if (dim % numDivs != 0) 
    { 
      unsigned int padding = numDivs - dim % numDivs;
      int * newA = (int *) malloc(sizeof(int) * (dim + padding) * (dim + padding));
      node * newNode = (node *) malloc(sizeof(node));
      newNode->matrix = newA;
      newNode->next = m_data;
      m_data = newNode;
      int * newB = (int *) malloc(sizeof(int) * (dim + padding) * (dim + padding));
      newNode = (node *) malloc(sizeof(node));
      newNode->matrix = newB;
      newNode->next = m_data;
      m_data = newNode;
      int * offsetA = A.offset();
      int * offsetB = B.offset();
      for (unsigned int i = 0; i < dim; ++i)
      {
        memcpy(newA + i * (dim + padding), offsetA + i * dim, dim * sizeof(int));
        memset(newA + i * (dim + padding) + dim, 0, padding);
        memcpy(newB + i * (dim + padding), offsetB + i * dim, dim * sizeof(int));
        memset(newB + i * (dim + padding) + dim, 0, padding);
      }
      for (unsigned int i = 0; i < padding; ++i)
      {
        memset(newA + dim * (dim + padding), 0, dim + padding);
        memset(newB + dim * (dim + padding), 0, dim + padding);
      }
      Scanner paddedA = Scanner(newA, A.isRowMajor(), dim + padding, dim + padding, dim + padding, dim + padding);
      Scanner paddedB = Scanner(newB, B.isRowMajor(), dim + padding, dim + padding, dim + padding, dim + padding);
      Scanner result = strassens(paddedA, paddedB, crossover);
      result.goHome();
      int * newC = (int *) malloc(sizeof(int) * dim * dim);
      newNode = (node *) malloc(sizeof(node));
      newNode->matrix = newC;
      newNode->next = m_data;
      m_data = newNode;
      int * offsetC = result.offset();
      for (unsigned int i = 0; i < dim; ++i)
      {
        memcpy(newC + i * dim, offsetC + i * (dim+padding), dim * sizeof(int));
      }
      return Scanner(newC, result.isRowMajor(), dim, dim, dim, dim);
    }
    else
    {
      return strassens(A, B, crossover);
    }
  }
  else
  {
    return conventionalMatrixMult(A, B, false);
  }
}

Scanner MatrixOps::strassens(Scanner A, Scanner B, unsigned int crossover)
{
  A.goHome();
  B.goHome();
  unsigned int A_height = A.getHeight();
  if (A_height <= crossover)
  {
    return conventionalMatrixMult(A, B, false);
  }
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
    A11 = Scanner(A_offset, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A21 = Scanner(A_offset + A_originalWidth*A_height/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A12 = Scanner(A_offset + A_width/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A22 = Scanner(A_offset + A_originalWidth*(A_height/2) + A_width/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
  }
  else
  {
    A11 = Scanner(A_offset, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A21 = Scanner(A_offset + A_height/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A12 = Scanner(A_offset + A_originalHeight*A_width/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
    A22 = Scanner(A_offset + A_originalHeight*(A_width/2) + A_height/2, A_type, A_originalWidth, A_originalHeight, A_width/2, A_height/2);
  }
  if (B_type)
  {
    B11 = Scanner(B_offset, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B21 = Scanner(B_offset + B_originalWidth*B_height/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B12 = Scanner(B_offset + B_width/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B22 = Scanner(B_offset + B_originalWidth*(B_height/2) + B_width/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
  }
  else
  {
    B11 = Scanner(B_offset, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B21 = Scanner(B_offset + B_height/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B12 = Scanner(B_offset + B_originalHeight*B_width/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
    B22 = Scanner(B_offset + B_originalHeight*(B_width/2) + B_height/2, B_type, B_originalWidth, B_originalHeight, B_width/2, B_height/2);
  }
  MatrixOps m1 = MatrixOps();
  MatrixOps m2 = MatrixOps();
  MatrixOps m3 = MatrixOps();
  MatrixOps m4 = MatrixOps();
  MatrixOps m5 = MatrixOps();
  MatrixOps m6 = MatrixOps();
  MatrixOps m7 = MatrixOps();
  Scanner M1 = m1.strassens(addMatrices(A11, A22, false), addMatrices(B11, B22, true), crossover);
  Scanner M2 = m2.strassens(addMatrices(A21, A22, false), B11, crossover);
  Scanner M3 = m3.strassens(A11, subtractMatrices(B12, B22, true), crossover);
  Scanner M4 = m4.strassens(A22, subtractMatrices(B21, B11, true), crossover);
  Scanner M5 = m5.strassens(addMatrices(A11, A12, false), B22, crossover);
  Scanner M6 = m6.strassens(subtractMatrices(A21, A11, false), addMatrices(B11, B12, true), crossover);
  Scanner M7 = m7.strassens(subtractMatrices(A12, A22, false), addMatrices(B21, B22, true), crossover);
  Scanner C11 = addMatrices(subtractMatrices(addMatrices(M1, M4, false), M5, false), M7, false);
  Scanner C12 = addMatrices(M3, M5, false);
  Scanner C21 = addMatrices(M2, M4, false);
  Scanner C22 = addMatrices(addMatrices(subtractMatrices(M1, M2, false), M3, false), M6, false);
  m1.unload();
  m2.unload();
  m3.unload();
  m4.unload();
  m5.unload();
  m6.unload();
  m7.unload();

  int d = C11.getHeight();
  int * newMatrix = (int *) malloc(d * d * 4 * sizeof(int));
  node * newNode = (node *) malloc(sizeof(node));
  newNode->matrix = newMatrix;
  newNode->next = m_data;
  m_data = newNode;
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
  return X;
}