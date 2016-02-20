// pqueue.h

struct Edge
{
  float w;
  unsigned short int a;
  unsigned short int b;
};

class Pqueue
{
  public:
    inline bool empty(void);
    void insert(Edge e);
    Edge removeMin(void);
    Pqueue(int size);
    void print(void);
  private:
    Edge* m_array;
    unsigned long int m_end;
};

inline bool Pqueue::empty(void)
{
  return (m_end == 0);
}