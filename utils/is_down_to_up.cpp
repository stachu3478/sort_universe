#include "is_down_to_up.h"
#include <iostream>

;using namespace std;

int is_down_to_up(int* arr, int length)
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
