// pqueue.h

#include "graph.h"

class Pqueue
{
    public:
        Pqueue(int size);
        inline bool empty(void) const;
        void insert(Edge e, unsigned short int target);
        Edge removeMin(void);
        void print(void) const;
        ~Pqueue(void);
    private:
        Edge * m_array;
        unsigned int * m_positions;
        unsigned int m_end;
};

inline bool Pqueue::empty(void) const
{
    return (m_end < 1);
}
