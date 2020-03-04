#include <iostream>
#include "test_suite.h"

using namespace std;

int main()
{
    int test;
    if (test = test_suite())
        return test;
    cout << "Hello world!" << endl;
    return 0;
}
