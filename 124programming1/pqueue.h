// pqueue.h

using namespace std;

struct Edge
{
  float w;
  unsigned short int a;
  unsigned short int b;
};

class Pqueue
{
  private:
    Edge* array;
    unsigned long int end;
  public:
    bool empty(void);
    void insert(Edge e);
    Edge removeMin(void);
    Pqueue(int size);
    void print(void);
};