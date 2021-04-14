#ifndef QUEUE_TEST_H_INCLUDED
#define QUEUE_TEST_H_INCLUDED

#include <iostream>
#include "Queue.h"
#include "../array_generators/random/random.h"

using namespace std;

int queue_test()
{
    cout << ">>> Queue" << endl;
    int* arr = random_list(100);
    Queue* q = new Queue();
    cout << "> Putting data" << endl;
    for (int i = 0; i < 100; i++)
    {
        q->put(arr[i]);
        cout << arr[i] << " ";
    }
    cout << "> Proper size" << endl;
    if (q->getSize() != 100) return 1;
    cout << "> Proper feedback data" << endl;
    for (int i = 0; i < 100; i++)
    {
        int val = q->pull();
        cout << val << " ";
        if (val != arr[i]) return 1;
    }
    return 0;
}

#endif // QUEUE_TEST_H_INCLUDED
