#include <bits/stdc++.h>
#include "single_value.h"

int* single_value(int length)
{
    int* arr = new int[length];
    arr[0] = rand();

    for (int i = 1; i < length; i++)
    {
        arr[i] = arr[0];
    }

    return arr;
}
