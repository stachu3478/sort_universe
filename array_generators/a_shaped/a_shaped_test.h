#ifndef A_SHAPED_TEST_H_INCLUDED
#define A_SHAPED_TEST_H_INCLUDED

#include <iostream>
#include "a_shaped.h"
#include "../utils/is_acc_number_of_int.h"
#include "../../utils/is_down_to_up.h"

int a_shaped_test()
{
    int* arr;
    cout << "> A-shaped array with length of 100" << endl;
    cout << "Is accessible number of integers" << endl;
    if(is_accessible_number_of_integers(a_shaped(100), 100))
        return 1;
    cout << "> A-shaped array with 1 repeat" << endl;
    arr = a_shaped(100);
    if (!is_down_to_up(arr, 50))
        return 1;
    int curr = arr[50];
    for (int i = 50; i < 100; i++)
    {
        cout << arr[i] << endl;
        if (curr < arr[i])
            return 1;
        else
            curr = arr[i];
    }
    return 0;
}

#endif // A_SHAPED_TEST_H_INCLUDED
