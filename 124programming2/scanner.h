// matrix.h

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <utility>
#include <fstream>


class Scanner
{
  public:
    Scanner(int* matrix, bool isRowMajor, unsigned int originalWidth,
      unsigned int originalHeight, unsigned int width, unsigned int height);
    int nextInRow();
    int nextInColumn();
    void startNextColumn();
    void startNextRow();
    void startCurrentColumn();
    void startCurrentRow();
    void goHome();
    inline bool isRowMajor() const;
    inline int current() const;
    inline int* offset() const;
    inline unsigned int getWidth() const;
    inline unsigned int getHeight() const;
    void freeData();

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

inline bool Scanner::isRowMajor() const
{
  return m_isRowMajor;
};

inline unsigned int Scanner::getHeight() const
{
    return m_height;
};

inline unsigned int Scanner::getWidth() const
{
    return m_width;
};

inline int Scanner::current() const
{
  return *m_matrix;
};

inline int* Scanner::offset() const
{
  return m_matrix;
};
