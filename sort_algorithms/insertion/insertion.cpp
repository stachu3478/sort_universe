// This insertion sort has no binary searching implemented
int* insertion_sort(int* arr, int length)
{
    for (int i = 1; i < length; i++)
    {
        int tmp = arr[i];
        int next_pos;
        int to_replace = 0;
        for (int j = 0; j < i; j++)
        {
            if (tmp >= arr[j])
            {
                next_pos = j;
                to_replace = 1;
                break;
            };
        };
        if (to_replace)
        {
            for (int j = i; j > next_pos;)
            {
                arr[j--] = arr[j];
            };
            arr[next_pos] = tmp;
        }
    };
    return arr;
};
