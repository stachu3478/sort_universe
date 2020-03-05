#ifndef IS_DOWN_TO_UP_H_INCLUDED
#define IS_DOWN_TO_UP_H_INCLUDED

#include <iostream>

;int is_down_to_up(int* arr, int length)
{
    int curr = arr[0];
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << endl;
        if (curr > arr[i])
            return 0;
        else
            curr = arr[i];
    };
    return 1;
};

#endif // IS_DOWN_TO_UP_H_INCLUDED
