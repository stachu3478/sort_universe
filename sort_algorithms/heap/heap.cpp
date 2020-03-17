#include <iostream>
#include "heap.h"

using namespace std;

int left_child(int i)
{
    return (i + 1) * 2 - 1;
};

int right_child(int i)
{
    return (i + 1) * 2;
};

int parent(int i)
{
    return (i - 1) / 2;
};

void swapp(int* arr, int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
};

void heapify(int* arr, int start, int length)
{
    int i = start;
    while (1)
    {
        int left = left_child(i);
        int right = left + 1;
        int max_id;
        if (right < length)
        {
            if (arr[left] > arr[right])
                max_id = left;
            else
                max_id = right;
        }
        else if (left < length)
        {
            max_id = left;
        }
        else return;
        if (arr[max_id] > arr[i])
            swapp(arr, max_id, i);
        else return;
        i = max_id;
    };
};

int* heap_sort(int* arr, int length)
{
    int lmin1 = length - 1;
    for (int i = parent(lmin1); i >= 0; i--)
        heapify(arr, i, length);
    for (int i = 0; i < length; i++)
    {
        swapp(arr, 0, lmin1 - i);
        heapify(arr, 0, lmin1 - i);
    };
    return arr;
};
