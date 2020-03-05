#ifndef SINGLE_VALUE_TEST_H_INCLUDED
#define SINGLE_VALUE_TEST_H_INCLUDED

#include <iostream>
#include "single_value.h"
#include "../utils/is_acc_number_of_int.h"

int single_value_test()
{
    int* arr;
    cout << "> Single value array with length of 100" << endl;
    cout << "Is accessible number of integers" << endl;
    if(is_accessible_number_of_integers(single_value(100), 100))
        return 1;
    cout << "All elements have the same value" << endl;
    arr = single_value(100);
    int curr = arr[0];
    for (int i = 0; i < 100; i++)
    {
        cout << arr[i] << endl;
        if (curr != arr[i])
            return 1;
    }
    return 0;
}

#endif // SINGLE_VALUE_TEST_H_INCLUDED
