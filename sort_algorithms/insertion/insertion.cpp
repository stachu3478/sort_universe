#include "insertion.h"
#include "../../utils/is_down_to_up.h"
#include <iostream>

using namespace std;
// Created for shell sort purposes
// TODO make decrementing check for shell sort
int* insertion_sort(int* arr, int length, int skips)
{
    for (int i = skips; i < length; i += skips)
    {
        int tmp = arr[i];
        int next_pos = 0;
        int to_replace = 0;
        for (int j = i - skips; j >= 0; j -= skips)
        {
            if (tmp >= arr[j])
            {
                next_pos = j + skips;
                break;
            };
            to_replace = 1;
        };
        if (to_replace)
        {
            for (int j = i; j > next_pos; j -= skips)
                arr[j] = arr[j - skips]; // TODO optimize
            arr[next_pos] = tmp;
        };
    };
    return arr;
};

int* insertion_sort_s(int* arr, int length, int skips)
{
    for (int i = skips; i < length; i += skips)
    {
        int j = i;
        int tmp = arr[j];
        for (int j = i - skips; j >= 0; j -= skips)
        {
            if (arr[j] < arr[j + 1]) break;
            tmp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = tmp;
        };
    };
    return arr;
};

// This insertion sort has no binary searching implemented
int* insertion_sort(int* arr, int length)
{
    return insertion_sort(arr, length, 1);
};

int* insertion_sort_s(int* arr, int length)
{
    return insertion_sort_s(arr, length, 1);
};
