#include <cstddef>
#include "Stack.h"
#include "Pair.h"

Stack::Stack()
{
    this->hay = NULL;
    this->_size = 0;
}

void Stack::put(int val)
{
    if (this->hay == NULL)
        this->hay = new Pair(val);
    else
        this->hay = new Pair(val, this->hay);
    this->_size++;
}

int Stack::prev()
{
    if (this->hay == NULL) return -1;
    Pair* pre = this->hay->getKey();
    if (pre == NULL) return -1;
    return pre->getVal();
}

int Stack::pull()
{
    if (this->hay == NULL) return -1;
    int val = this->hay->getVal();
    this->hay = this->hay->getKey();
    this->_size--;
    return val;
}

Stack::~Stack()
{
    //dtor
}
