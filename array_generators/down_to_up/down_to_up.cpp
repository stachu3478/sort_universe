#include<bits/stdc++.h>

int* down_to_up(int length, int faces)
{
    int elements_per_face = length / faces;
    int elements_per_last = length % faces;
    int rand_step = (INT_MAX / elements_per_face) - 1;

    int* arr = new int[length];
    int current_min = 0;

    for (int i = 0; i < length; i++)
    {
        current_min += rand() % rand_step;
        arr[i] += current_min;
    }

    return arr;

}