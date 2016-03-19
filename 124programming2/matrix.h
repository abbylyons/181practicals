// matrix.h

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <utility>


class Scanner
{
  public:
    Scanner(int* matrix, bool isRowMajor, unsigned int originalWidth,
      unsigned int originalHeight, unsigned int width, unsigned int height);
    int nextInRow();
    int nextInColumn();
    void startNextColumn();
    void startNextRow();
    int current();
    int* offset();

  private:
    bool m_isRowMajor;
    int * m_matrix;
    unsigned int m_originalWidth;
    unsigned int m_originalHeight;
    unsigned int m_col;
    unsigned int m_row;
    unsigned int m_width;
    unsigned int m_height;
};
