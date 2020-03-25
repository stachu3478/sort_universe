#include <stdlib.h>
#include <cstdio>
#include <iostream>
using namespace std;

typedef int pivot_getter(int maxx);
int random_pivot(int maxx) { return rand() % (maxx + 1); };
int right_pivot(int maxx) { return maxx; };

// Quick sort - recurences - pivot as first element
int* quick_sort(int* arr, int length, pivot_getter get_p)
{
    int i = 1, j = length - 1;
    int p_index = get_p(j);
    int p = arr[p_index];
    arr[p_index] = arr[0];
    arr[0] = p;
    while (i < j)
        if (arr[i] > p)
        {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j--] = tmp;
        } else
            i++;
    if (arr[j] > p)
        j--;
    arr[0] = arr[j];
    arr[j] = p;
    if (j > 1)
        quick_sort(arr, j, get_p);
    if (j < length - 2)
        quick_sort(arr + j + 1, length - j - 1, get_p);
    return arr;
};

// Quick sort - corrected - pivot as first element
int* quick_sort_c(int* arr, int length, pivot_getter get_p)
{
    if (length <= 1) return arr;
    int i = 0, j = length - 1;
    int p = arr[get_p(j)];
    while (1)
    {
        while (arr[i] < p) i++;
        while (arr[j] > p) j--;
        if (i < j)
        {
            int tmp = arr[i];
            arr[i++] = arr[j];
            arr[j--] = tmp;
        }
        else if (i > j)
        {
            quick_sort_c(arr, j + 1, get_p);
            quick_sort_c(arr + i, length - i, get_p);
            return arr;
        } else
        {
            quick_sort_c(arr, i, get_p);
            quick_sort_c(arr + i + 1, length - i - 1, get_p);
            return arr;
        };
    };

    return arr;
};

int* quick_sort_right(int* arr, int length) { return quick_sort(arr, length, right_pivot); };
int* quick_sort_rand(int* arr, int length) { return quick_sort(arr, length, random_pivot); };
int* quick_sort_right_c(int* arr, int length) { return quick_sort_c(arr, length, right_pivot); };
int* quick_sort_rand_c(int* arr, int length) { return quick_sort_c(arr, length, random_pivot); };
