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

int test_algorithm(int* input_array, int* original, int* output_array, int length)
{
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
    int* selection_in = random_list(100);
    int* selection_orig = copy_array(selection_in, 100);
    if (test_algorithm(selection_in, selection_orig, selection_sort(selection_in, 100), 100))
        return 1;
    cout << "> Insertion sort" << endl;
    int* insertion_in = random_list(100);
    int* insertion_orig = copy_array(insertion_in, 100);
    if (test_algorithm(insertion_in, insertion_orig, insertion_sort(insertion_in, 100), 100))
        return 1;
    cout << "> Shell sort | Knuth" << endl;
    int* shell_in = random_list(100);
    int* shell_orig = copy_array(shell_in, 100);
    if (test_algorithm(shell_in, shell_orig, shell_sort(shell_in, 100), 100))
        return 1;
    cout << "> Quick sort | Recurences" << endl;
    int* quick_in = random_list(100);
    int* quick_orig = copy_array(quick_in, 100);
    if (test_algorithm(quick_in, quick_orig, quick_sort(quick_in, 100), 100))
        return 1;
    cout << "> Bubble sort" << endl;
    int* bubble_in = random_list(100);
    int* bubble_orig = copy_array(bubble_in, 100);
    if (test_algorithm(bubble_in, bubble_orig, bubble_sort(bubble_in, 100), 100))
        return 1;
    // cout << "> Heap sort" << endl;
    // int* heap_in = random_list(100);
    // int* heap_orig = copy_array(heap_in, 100);
    // if (test_algorithm(heap_in, heap_orig, heap_sort(heap_in, 100), 100))
        // return 1;

    return 0;
};

#endif // SORT_TEST_H_INCLUDED
