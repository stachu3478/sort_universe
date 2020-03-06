int* bubble_sort(int* arr, int length)
{
    for (int i = length - 1; i > 1; i--)
    {
        int tmp = -1;
        for (int j = 0; j < i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            };
        };
        if (tmp == -1)
            break;
    };
    return arr;
};
