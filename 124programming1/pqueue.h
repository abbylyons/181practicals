// pqueue.h

#include "graph.h"


class Pqueue
{
  public:
    Pqueue(int size);
    inline bool empty(void);
    void insert(Edge e);
    Edge removeMin(void);
    void print(void);
  private:
    Edge* m_array;
    unsigned long int m_end;
};

inline bool Pqueue::empty(void)
{
  return (m_end < 1);
}
