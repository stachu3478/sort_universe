#include "../insertion/insertion.h"

// With Knuth skips
int* shell_sort(int* arr, int length)
{
    int delta_skip = 1;
    int max_skip = length / 3;
    while (delta_skip <= max_skip)
        delta_skip = 3 * delta_skip + 1;
    do {
        --delta_skip /= 3;
        for (int i = 0; i < delta_skip; i++)
            insertion_sort(arr + i, length - i, delta_skip);
    } while (delta_skip > 1);
    return arr;
};
