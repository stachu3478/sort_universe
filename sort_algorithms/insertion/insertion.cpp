// Created for shell sort purposes
// TODO make decrementing check for shell sort
int* insertion_sort(int* arr, int length, int skips)
{
    for (int i = skips; i < length; i += skips)
    {
        int tmp = arr[i];
        int next_pos = 0;
        int to_replace = 0;
        for (int j = i - skips; j >= 0; j -= skips)
        {
            if (tmp >= arr[j])
            {
                next_pos = j + skips;
                break;
            } else
            {
                to_replace = 1;
            }
        };
        if (to_replace)
        {
            for (int j = i; j > next_pos;)
            {
                arr[j] = arr[j -= skips];
            };
            arr[next_pos] = tmp;
        };
    };
    return arr;
}

// This insertion sort has no binary searching implemented
int* insertion_sort(int* arr, int length)
{
    return insertion_sort(arr, length, 1);
};
