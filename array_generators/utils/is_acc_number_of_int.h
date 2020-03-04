#ifndef IS_ACC_NUMBER_OF_INT_H_INCLUDED
#define IS_ACC_NUMBER_OF_INT_H_INCLUDED

int is_accessible_number_of_integers(int* arr, int length)
{
    for (int i = 0; i < 100; i++)
        if (arr[i] + 0 < 0)
            return 1;
    return 0;
}

#endif // IS_ACC_NUMBER_OF_INT_H_INCLUDED
