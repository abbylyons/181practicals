// scanner.cpp

#include "scanner.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <utility>

Scanner::Scanner(int* matrix, bool isRowMajor, unsigned int originalWidth,
unsigned int originalHeight, unsigned int width, unsigned int height)
  :m_isRowMajor(isRowMajor),
  m_matrix(matrix),
  m_originalWidth(originalWidth),
  m_originalHeight(originalHeight),
  m_col(0),
  m_row(0),
  m_width(width),
  m_height(height)
{

}

void Scanner::goHome()
{
  this->startCurrentRow();
  this->startCurrentColumn();
}

void Scanner::freeData()
{
  this->goHome();
  free(this->offset());
}


int Scanner::nextInRow()
{
  if  (m_col < m_width)
  {
    m_col++;
    if (m_isRowMajor)
    {
      m_matrix++;
    }
    else
    {
      m_matrix += m_originalHeight;
    }
    return *m_matrix;
  }
  else
  {
    // TODO: Throw error because out of bounds
    return -99999999;
  }
}

int Scanner::nextInColumn()
{
  if  (m_row < m_height)
  {
    m_row++;
    if (m_isRowMajor)
    {
      m_matrix += m_originalWidth;
    }
    else
    {
      m_matrix ++;
    }
    return *m_matrix;
  }
  else
  {
    // TODO: Throw error because out of bounds
    return -99999999;
  }
}


void Scanner::startNextColumn()
{
  if (m_col < m_width)
  {
    if (m_isRowMajor)
    {
      m_matrix -= m_row * m_originalWidth - 1;
    }
    else
    {
      m_matrix += (m_originalHeight - m_row);
    }
    m_col += 1;
    m_row = 0;
  }
}

void Scanner::startNextRow()
{
  if (m_row < m_height)
  {
    if (m_isRowMajor)
    {
      m_matrix += (m_originalWidth - m_col);
    }
    else
    {
      m_matrix -= (m_col * m_originalHeight) - 1;
    }
    m_row += 1;
    m_col = 0;
  }
}

void Scanner::startCurrentColumn()
{
  if (m_isRowMajor)
  {
    m_matrix -= m_row * m_originalWidth;
  }
  else
  {
    m_matrix -= m_row;
  }
  m_row = 0;
}

void Scanner::startCurrentRow()
{
  if (m_isRowMajor)
  {
    m_matrix -= m_col;
  }
  else
  {
    m_matrix -= m_col * m_originalHeight;
  }
  m_col = 0;
}
