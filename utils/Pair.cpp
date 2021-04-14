#include <cstddef>
#include "Pair.h"

Pair::Pair(int val)
{
    this->val = val;
    this->key = NULL;
}

Pair::Pair(int val, Pair* key)
{
    this->val = val;
    this->key = key;
}

Pair::~Pair()
{
    //dtor
}
