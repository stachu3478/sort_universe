#ifndef STACK_H
#define STACK_H

#include "Pair.h"

class Stack
{
    public:
        /** Default constructor */
        Stack();
        /** Default destructor */
        virtual ~Stack();

        void put(int val);
        int pull();
        int get() { return this->hay->getVal(); };
        int prev();
        int set(int val) { return this->hay->setVal(val); };
        int getSize() { return _size; };

    protected:

    private:
        Pair* hay;
        int _size;
};

#endif // STACK_H
