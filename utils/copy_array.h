#ifndef COPY_ARRAY_H_INCLUDED
#define COPY_ARRAY_H_INCLUDED

// TODO test
int* copy_array(int* arr, int length)
{
    int* arr2 = new int[length];
    for (int i = 0; i < length; i++)
    {
        arr2[i] = arr[i];
    };
    return arr2;
}

#endif // COPY_ARRAY_H_INCLUDED
