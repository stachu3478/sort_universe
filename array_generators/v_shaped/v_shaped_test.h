#ifndef V_SHAPED_TEST_H_INCLUDED
#define V_SHAPED_TEST_H_INCLUDED


#include <iostream>
#include "v_shaped.h"
#include "../utils/is_acc_number_of_int.h"
#include "../../utils/is_down_to_up.h"

int v_shaped_test()
{
    int* arr;
    cout << "> V-shaped array with length of 100" << endl;
    cout << "Is accessible number of integers" << endl;
    if(is_accessible_number_of_integers(v_shaped(100), 100))
        return 1;
    cout << "> V-shaped array with 1 repeat" << endl;
    arr = v_shaped(100);
    int curr = arr[0];
    for (int i = 0; i < 50; i++)
    {
        cout << arr[i] << endl;
        if (curr < arr[i])
            return 1;
        else
            curr = arr[i];
    }
    if (!is_down_to_up(arr + 50, 50))
        return 1;
    return 0;
}

#endif // V_SHAPED_TEST_H_INCLUDED
