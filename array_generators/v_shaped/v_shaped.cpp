#include "v_shaped.h"
#include "../down_to_up/down_to_up.h"
#include "../up_to_down/up_to_down.h"

int* v_shaped(int length)
{
    int length_part_1 = length / 2;
    int* part1 = up_to_down(length_part_1, 1);
    int* part2 = down_to_up(length - length_part_1, 1);

    int* arr = new int[length];
    for (int i = 0; i < length_part_1; i++)
    {
        arr[i] = part1[i];
    }
    for (int i = 0; i < length - length_part_1; i++)
    {
        arr[i + length_part_1] = part2[i];
    }

    return arr;
};
