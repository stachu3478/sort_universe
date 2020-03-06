// Quick sort - recurences - pivot as first element
int* quick_sort(int* arr, int length)
{
    int i = 1, j = length - 1;
    int p = arr[0];
    while (i < j)
        if (arr[i] > p)
        {
            int tmp = arr[i];
            arr[i] = arr[j];
            arr[j--] = tmp;
        } else
            i++;
    if (arr[j] > p)
        j--;
    arr[0] = arr[j];
    arr[j] = p;
    if (j > 1)
        quick_sort(arr, j);
    if (j < length - 2)
        quick_sort(arr + j + 1, length - j - 1);
    return arr;
};
