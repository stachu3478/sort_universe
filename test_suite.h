#ifndef TEST_SUITE_H_INCLUDED
#define TEST_SUITE_H_INCLUDED

#include <iostream>
#include <stdlib.h>
#include "array_generators/random/random_test.h"
#include "array_generators/down_to_up/down_to_up_test.h"
#include "array_generators/up_to_down/up_to_down_test.h"
#include "array_generators/single_value/single_value_test.h"
#include "array_generators/a_shaped/a_shaped_test.h"
#include "array_generators/v_shaped/v_shaped_test.h"

using namespace std;

int checkFail(int state, int newState)
{
    if (!state)
    {
        if (newState)
        {
            cout << "FAIL" << endl;
        }
    }
}

int test_suite()
{
    int result = 0;
    cout << "Hello test!" << endl;
    try {
        checkFail(result, result += random_list_test());
        checkFail(result, result += down_to_up_test());
        checkFail(result, result += up_to_down_test());
        checkFail(result, result += single_value_test());
        checkFail(result, result += a_shaped_test());
        checkFail(result, result += v_shaped_test());
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
