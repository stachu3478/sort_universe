#ifndef SORT_TEST_H_INCLUDED
#define SORT_TEST_H_INCLUDED

#include <iostream>
#include "../array_generators/random/random.h"
#include "../utils/is_down_to_up.h"
#include "../array_generators/utils/is_acc_number_of_int.h"
#include "../utils/copy_array.h"
#include "../sort_algorithms/selection/selection.h"
#include "../sort_algorithms/insertion/insertion.h"
#include "../sort_algorithms/shell/shell.h"
#include "../sort_algorithms/quick/quick.h"
#include "../sort_algorithms/bubble/bubble.h"
#include "../sort_algorithms/heap/heap.h"

using namespace std;

typedef int* sort_algorithm(int* arr, int length);

int test_algorithm(sort_algorithm alg)
{
    int length = 100;
    int* input_array = random_list(length);
    int* original = copy_array(input_array, length);
    int* output_array = alg(input_array, length);
    cout << "Is the same array" << endl;
    if (input_array != output_array)
        return 1;
    cout << "Is non-negative" << endl;
    if (is_accessible_number_of_integers(output_array, length) == 1)
        return 1;
    cout << "Is sorted" << endl;
    if (!is_down_to_up(output_array, length))
        return 1;
    cout << "Has the same elements" << endl;
    for (int i = 0; i < length; i++)
    {
        int current = original[i];
        int found = 0;
        for (int j = 0; j < length; j++)
        {
            if (current == output_array[j])
            {
                // already found, we wont count that more
                output_array[j] = -1;
                found = 1;
                break;
            };
        };
        if (!found)
            return 1;
    };
    return 0;
};

// Here are tested all sort algorithms
// Elements should be sorted from down to up (e.g. 1, 2, 3)
int sort_test()
{
    cout << ">> Hello algs!" << endl;
    cout << "> Selection sort" << endl;
    if (test_algorithm(selection_sort))
        return 1;
    cout << "> Insertion sort" << endl;
    if (test_algorithm(insertion_sort))
        return 1;
    cout << "> Shell sort | Knuth" << endl;
    if (test_algorithm(shell_sort))
        return 1;
    cout << "> Quick sort | Right pivot" << endl;
    if (test_algorithm(quick_sort_right))
        return 1;
    cout << "> Quick sort | Random pivot" << endl;
    if (test_algorithm(quick_sort_rand))
        return 1;
    cout << "> Bubble sort" << endl;
    if (test_algorithm(bubble_sort))
        return 1;
    // cout << "> Heap sort" << endl;
    // int* heap_in = random_list(100);
    // int* heap_orig = copy_array(heap_in, 100);
    // if (test_algorithm(heap_in, heap_orig, heap_sort(heap_in, 100), 100))
        // return 1;

    return 0;
};

#endif // SORT_TEST_H_INCLUDED
