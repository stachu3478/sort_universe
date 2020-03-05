#include <iostream>
#include "test_suite.h"

using namespace std;

int main()
{
    // TODO exclude tests on production build
    int test;
    if (test = test_suite())
        return test;
    cout << "Hello world!" << endl;
    return 0;
}
