#ifndef DOWN_TO_UP_TEST_H_INCLUDED
#define DOWN_TO_UP_TEST_H_INCLUDED

#include <iostream>
#include "down_to_up.h"
#include "../utils/is_acc_number_of_int.h"
#include "../../utils/is_down_to_up.h"

;using namespace std;

int down_to_up_test()
{
    cout << "> Down to up array with length of 100" << endl;
    cout << "Is accessible number of integers" << endl;
    if(is_accessible_number_of_integers(down_to_up(100, 1), 100))
        return 1;
    cout << "Has increasing elements at one face" << endl;
    if (!is_down_to_up(down_to_up(100, 1), 100))
        return 1;
    // TODO
    /* cout << "Gets increasing elements at multiple faces (5) with no modulo" << endl;
    arr = down_to_up(100, 5);
    for (int pos = 0; pos < 100; pos += 20)
    {
        int current = arr[pos];
        for (int i = pos; i < pos + 20; i++)
            if (current > arr[i])
                return 1;
            else
                current = arr[i];
    }
    cout << "... and check face existence" << endl;
    for (int pos = 20; pos < 80; pos += 20)
    {
        if (arr[pos - 1] < arr[pos])
            return 1;
    }
    cout << "Gets increasing elements at multiple faces (6) with modulo" << endl;
    arr = down_to_up(100, 6);
    for (int pos = 0; pos < 100; pos += 16)
    {
        int current = arr[pos];
        for (int i = pos; i < pos + 16; i++)
            if (current > arr[i])
                return 1;
            else
                current = arr[i];
    }
    int current = arr[96];
        for (int i = 96; i < 100; i++)
            if (current > arr[i])
                return 1;
    cout << "... and check face existence" << endl;
    for (int pos = 16; pos < 96; pos += 16)
    {
        if (arr[pos - 1] < arr[pos])
            return 1;
    } */
    return 0;
};

#endif // DOWN_TO_UP_TEST_H_INCLUDED
