#include <bits/stdc++.h>
#include "down_to_up.h"

;int* down_to_up(int length, int faces, int delta)
{
    int elements_per_face = length / faces;
    int elements_per_last = length % faces;
    int rand_step = (INT_MAX / elements_per_face);

    int* arr = new int[length];
    int current_min = 0;

    for (int i = 0; i < length; i++)
    {
        current_min += (rand() % rand_step) + delta;
        arr[i] = current_min;
    }

    return arr;
};

int* down_to_up(int length, int faces) { return down_to_up(length, faces, 0); };
int* down_to_up(int length) { return down_to_up(length, 1); };
