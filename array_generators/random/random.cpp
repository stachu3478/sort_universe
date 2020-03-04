#include <stdlib.h>
#include <cstdio>

int* random_list(int length)
{
    int* arr = new int[length];
    for (int i = 0; i < length; i++)
        arr[i] = rand();
    return arr;
}
