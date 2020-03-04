#ifndef TEST_SUITE_H_INCLUDED
#define TEST_SUITE_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include "array_generators/random/random_test.h"
#include "array_generators/down_to_up/down_to_up_test.h"

using namespace std;

int test_suite()
{
    int result = 0;
    cout << "Hello test!" << endl;
    try {
        result += random_list_test();
        result += down_to_up_test();
    }
    catch (...) {
        cout << "FAIL" << endl;
        return -1;
    }

    if (!result)
    {
        cout << flush;
        system("CLS");
    }
    else
    {
        cout << "FAIL" << endl;
    };
    return result;
}

#endif // TEST_SUITE_H_INCLUDED
