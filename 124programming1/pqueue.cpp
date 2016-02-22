// pqueue.cpp

#include "pqueue.h"


Pqueue::Pqueue(int size)
  : m_end(0)
{
    // initialize the array of edges
    m_array = (Edge *)malloc((sizeof(Edge)) * (size + 2));
    memset(m_array, 0, sizeof(Edge) * (size + 2));
    // array for holding positions
    m_positions = (unsigned int *)malloc((sizeof(unsigned int)) * (size + 2));
    memset(m_positions, 0, sizeof(unsigned int) * (size + 2));
}

void Pqueue::insert(Edge e, unsigned short int target)
{
    unsigned int pos;
    if (target == 0)
    {
        unsigned int temp = e.b;
        e.b = e.a;
        e.a = temp;
    }

    // check whether there is a corresponding edge in the graph already.
    if (m_positions[e.b] > 0)
    {
        // check if new edge is "cheaper"
        if (m_array[m_positions[e.b]].w > e.w)
        {
            // swap the elements
            m_array[m_positions[e.b]] = e;
            pos = m_positions[e.b];
        }
        else return; // don't insert the edge
    }
    else
    {
        // insert new edge to the end
        ++m_end;
        m_array[m_end] = e;
        m_positions[e.b] = m_end;
        pos = m_end;
    }

    // keep swapping up to keep the order property
    while (pos/2 != 0)
    {
        if (m_array[pos].w < m_array[pos / 2].w)
        {
            Edge temp = m_array[pos / 2];
            m_array[pos / 2] = m_array[pos];
            m_positions[m_array[pos / 2].b] = pos / 2;
            m_array[pos] = temp;
            m_positions[temp.b] = pos;
            pos = pos / 2;
        }
        else return;
    }
}

Edge Pqueue::removeMin(void)
{
    Edge min = m_array[1];
    m_positions[min.b] = 0;
    unsigned long int pos = 1;
    if (m_end != 1)
    {
        m_array[1] = m_array[m_end];
        m_positions[m_array[1].b] = 1;
    }
    --m_end;
    while (pos < m_end)
    {
        // check if vertex has left child
        if(2 * pos <= m_end)
        {
            // check if vertex has right child
            if(2 * pos +1 <= m_end)
            {
                //check if right child is smaller than left and parent
                if(m_array[2 * pos + 1].w < m_array[2 * pos].w 
                    && m_array[pos].w > m_array[2 * pos + 1].w)
                {
                    Edge temp = m_array[2 * pos + 1];
                    m_array[2 * pos + 1] = m_array[pos];
                    m_positions[m_array[2 * pos + 1].b] = 2 * pos + 1;
                    m_array[pos] = temp;
                    m_positions[m_array[pos].b] = pos;
                    pos = 2 * pos + 1;
                }
                else if (m_array[2 * pos].w < m_array[pos].w)
                {
                    Edge temp = m_array[2 * pos];
                    m_array[2 * pos] = m_array[pos];
                    m_positions[m_array[2 * pos].b] = 2 * pos;
                    m_array[pos] = temp;
                    m_positions[m_array[pos].b] = pos;
                    pos = 2 * pos;
                }
                else
                {
                    return min;
                }
            }
            else if (m_array[2 * pos].w < m_array[pos].w)
            {
                Edge temp = m_array[2 * pos];
                m_array[2 * pos] = m_array[pos];
                m_positions[m_array[2 * pos].b] = 2 * pos;
                m_array[pos] = temp;
                m_positions[m_array[pos].b] = pos;
                pos = 2 * pos;
            }
            else
            {
                return min;
            }
        }
        else
        {
            return min;
        }
    }
    return min;
}

void Pqueue::print(void) const
{
    for(unsigned int i = 1; i <= m_end; ++i)
    {
        std::cout << m_array[i].a << " " << m_array[i].b << " " << m_array[i].w << std::endl;
    }
    for (int i = 0; i < 11; ++i)
    {
        std::cout << m_positions[i] << ", ";
    }
}

Pqueue::~Pqueue(void)
{
    free(m_array);
    free(m_positions);
}
