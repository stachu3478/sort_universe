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
        int max_val, max_id;
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
        max_val = arr[max_id];
        if (max_val > arr[i])
            swapp(arr, max_id, i);
        else return;
        i = max_id;
    };
};

int* heap_sort(int* arr, int length)
{
    for (int i = length; i >= 0; i--)
        heapify(arr, i, length);
    int co = 1;
    int cur = 0;
    for (int i = 0; i < length; i++)
    {
        cout << arr[i] << " ";
        if (++cur == co)
        {
            cout << endl;
            co <<= 1;
            cur = 0;
        };
    };
    for (int i = 0; i < length; i++)
    {
        swapp(arr, 0, length - i - 1);
        heapify(arr, 0, length - i - 2);
    };
    return arr;
};
