#include <bits/stdc++.h>
#include "up_to_down.h"

int* up_to_down(int length, int faces)
{
    int elements_per_face = length / faces;
    // int elements_per_last = length % faces;
    int rand_step = (INT_MAX / elements_per_face);

    int* arr = new int[length];
    int current_max = INT_MAX;

    for (int i = 0; i < length; i++)
    {
        current_max -= rand() % rand_step;
        arr[i] = current_max;
    }

    return arr;
}
