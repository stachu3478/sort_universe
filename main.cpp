#include <iostream>
#include "test_suite.h"
#include "utils/measure.h"

#include "sort_algorithms/selection/selection.h"
#include "sort_algorithms/insertion/insertion.h"
#include "sort_algorithms/shell/shell.h"
#include "sort_algorithms/quick/quick.h"
#include "sort_algorithms/heap/heap.h"
#include "sort_algorithms/bubble/bubble.h"

using namespace std;

int main()
{
    // TODO exclude tests on production build
    int test;
    if ((test = test_suite()))
        return test;

    while (1)
    {
        int alg_type = 0;
        cout<< "Choose algorithm for measurement or exit\n"
        << "1. Selection\n"
        << "2. Insertion\n"
        << "3. Shell | Knuth\n"
        << "4. Quick | Right pivot\n"
        << "5. Quick | Random pivot\n"
        << "6. Heap\n"
        << "7. Bubble\n"
        << "0. Exit\n";
        cin >> alg_type;

        switch (alg_type)
        {
            case 1: measure(selection_sort); break;
            case 2: measure(insertion_sort); break;
            case 3: measure(shell_sort); break;
            case 4: measure(quick_sort_right); break;
            case 5: measure(quick_sort_rand); break;
            case 6: measure(heap_sort); break;
            case 7: measure(bubble_sort); break;
            default: return 0;
        };
    };

    return 0;
};
