#include "TrueBoolArray.h"
#include <cstddef>

bool* BOOLEAN;

TrueBoolArray::TrueBoolArray(int length)
{
    this->arr = new unsigned char[(length + 7) >> 3];
    if (BOOLEAN == NULL)
    {
        BOOLEAN = new bool[2];
        BOOLEAN[0] = 0;
        BOOLEAN[1] = 1;
    }
}

TrueBoolArray::~TrueBoolArray()
{
    //dtor
}
