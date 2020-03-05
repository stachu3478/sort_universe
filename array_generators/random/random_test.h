#ifndef RANDOM_TEST_H_INCLUDED
#define RANDOM_TEST_H_INCLUDED

#include <iostream>
#include "random.h"
#include "../utils/is_acc_number_of_int.h"

using namespace std;

int random_list_test()
{
    cout << "> Random array with length of 100" << endl;
    cout << "Is accessible number of integers" << endl;
    return is_accessible_number_of_integers(random_list(100), 100);
};

#endif // RANDOM_TEST_H_INCLUDED
