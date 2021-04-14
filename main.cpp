#include <iostream>
#include "test_suite.h"
#include "utils/measure.h"

#include "knapsack_utils.h"

#include "sort_algorithms/selection/selection.h"
#include "sort_algorithms/insertion/insertion.h"
#include "sort_algorithms/shell/shell.h"
#include "sort_algorithms/quick/quick.h"
#include "sort_algorithms/heap/heap.h"
#include "sort_algorithms/bubble/bubble.h"
#include "tree_utils/NodeApp.h"

using namespace std;

int main()
{
    // TODO exclude tests on production build
    int test;
    if ((test = test_suite()))
        return test;

    // NodeApp();
    // node_app2();
    knapsack_app();

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
        << "8. Quick | Right pivot corrected\n"
        << "9. Quick | Random pivot corrected\n"
        << "10. Insertion sort corrected\n"
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
            case 8: measure(quick_sort_right_c); break;
            case 9: measure(quick_sort_rand_c); break;
            case 10: measure(insertion_sort_s); break;
            default: return alg_type;
        };
    };

    return 0;
};
