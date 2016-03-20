// scannerTest.cpp

#include "matrix.h"

int main(void)
{
  int * data = (int *) malloc(sizeof(int) * 20);
  if(data == NULL)
  {
    std::cout << "error allocating memory" << std::endl;
    return 1;
  }
  data[0] = 0;
  data[1] = 1;
  data[2] = 2;
  data[3] = 3;
  data[4] = 4;
  data[5] = 5;
  data[6] = 6;
  data[7] = 7;
  data[8] = 8;
  data[9] = 9;
  data[10] = 10;
  data[11] = 11;
  data[12] = 12;
  data[13] = 13;
  data[14] = 14;
  data[15] = 15;
  data[16] = 16;
  data[17] = 17;
  data[18] = 18;
  data[19] = 19;

  Scanner S = Scanner(data, true, 5, 4, 5, 4);

  S.startNextRow();
  S.nextInRow();
  int * temp = S.offset();
  S = Scanner(temp, true, 5, 4, 3, 2);
  std::cout << S.current() << std::endl; // 6
  std::cout << S.nextInRow() << std::endl; // 7
  std::cout << S.nextInColumn() << std::endl; // 12
  S.startNextColumn();
  std::cout << S.current() << std::endl; // 8
  S.startNextRow();
  std::cout << S.nextInRow() << std::endl; // 12
  std::cout << S.nextInRow() << std::endl; // 13


  std::cout << "columns" << std::endl;
  data[0] = 0;
  data[1] = 4;
  data[2] = 8;

  data[3] = 1;
  data[4] = 5;
  data[5] = 9;

  data[6] = 2;
  data[7] = 6;
  data[8] = 10;

  data[9] = 3;
  data[10] = 7;
  data[11] = 11;

  S = Scanner(data, false, 4, 3, 4, 3);
  std::cout << S.current() << std::endl; //0
  std::cout << S.nextInRow() << std::endl; // 1
  S.startNextRow();
  std::cout << S.current() << std::endl; //4
  S.startNextColumn();
  std::cout << S.current() << std::endl; // 1
  std::cout << S.nextInColumn() << std::endl; // 5

  free(data);
  return 0;

}
