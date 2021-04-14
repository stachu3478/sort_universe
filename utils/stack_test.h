#ifndef STACK_TEST_H_INCLUDED
#define STACK_TEST_H_INCLUDED

#include <iostream>
#include "Stack.h"
#include "../array_generators/random/random.h"

using namespace std;

int stack_test()
{
    cout << ">>> Stack" << endl;
    int* arr = random_list(100);
    Stack* _stack = new Stack();
    cout << "> Putting data" << endl;
    for (int i = 0; i < 100; i++)
    {
        _stack->put(arr[i]);
        cout << arr[i] << " ";
    }
    cout << "> Proper size" << endl;
    if (_stack->getSize() != 100) return 1;
    cout << "> Proper feedback data" << endl;
    for (int i = 99; i >= 0; i--)
    {
        int val = _stack->pull();
        cout << val << " ";
        if (val != arr[i]) return 1;
    }
    return 0;
}

#endif // STACK_TEST_H_INCLUDED
