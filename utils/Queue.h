#ifndef QUEUE_H
#define QUEUE_H

#include "Pair.h"

class Queue
{
    public:
        /** Default constructor */
        Queue();
        /** Default destructor */
        virtual ~Queue();

        void put(int val);
        int pull();
        int getSize() { return _size; };

    protected:

    private:
        Pair* first;
        Pair* last;
        int _size;
};

#endif // QUEUE_H
