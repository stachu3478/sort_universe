int* selection_sort(int* arr, int length)
{
    for (int i = 0; i < length; i++)
    {
        int min_found = arr[i];
        int min_index = i;
        for (int j = i + 1; j < length; j++)
        {
            if (arr[j] < min_found)
            {
                min_found = arr[j];
                min_index = j;
            };
        };
        int tmp = min_found;
        arr[min_index] = arr[i];
        arr[i] = tmp;
    };
    return arr;
};
