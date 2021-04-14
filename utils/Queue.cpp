#include <cstddef>
#include "Queue.h"
#include "Pair.h"

Queue::Queue()
{
    this->first = NULL;
    this->last = NULL;
    this->_size = 0;
}

void Queue::put(int val)
{
    if (this->first == NULL)
    {
        this->last = this->first = new Pair(val);
    }
    else {
        Pair* p = new Pair(val);
        this->last->setKey(p);
        this->last = p;
    }
    this->_size++;
}

int Queue::pull()
{
    if (this->first == NULL) return 0;
    int val = this->first->getVal();
    this->first = this->first->getKey();
    this->_size--;
    return val;
}

Queue::~Queue()
{
    //dtor
}
