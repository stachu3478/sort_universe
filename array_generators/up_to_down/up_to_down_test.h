#ifndef UP_TO_DOWN_TEST_H_INCLUDED
#define UP_TO_DOWN_TEST_H_INCLUDED

#include <iostream>
#include "up_to_down.h"
#include "../utils/is_acc_number_of_int.h"

;using namespace std;

int up_to_down_test()
{
    int* arr;
    cout << "> Up to down array with length of 100" << endl;
    cout << "Is accessible number of integers" << endl;
    if(is_accessible_number_of_integers(up_to_down(100), 100))
        return 1;
    cout << "Has decreasing elements at one face" << endl; // FIXME
    arr = up_to_down(100);
    int curr = arr[0];
    for (int i = 0; i < 100; i++)
    {
        cout << arr[i] << endl;
        if (curr < arr[i])
            return 1;
        else
            curr = arr[i];
    }
    // TODO
    /* cout << "Gets decreasing elements at multiple faces (5) with no modulo" << endl;
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
    cout << "Gets decreasing elements at multiple faces (6) with modulo" << endl;
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
}

#endif // UP_TO_DOWN_TEST_H_INCLUDED
