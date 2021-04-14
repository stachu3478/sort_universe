#include "read_utils.h"
#include "utils/is_down_to_up.h"

#include <iostream>
#include <iomanip>

using namespace std;

int safeReadInteger()
{
    int value;
    while (!(cin >> value))
    {
        cout << "Failed to read a number, try again.\n";
        cin.clear();
        cin.ignore();
    }
    return value;
}

int safeReadLength()
{
    cout << "Type length of the array\n";
    int length = safeReadInteger();
    while (length < 1)
    {
        cout << "Length should be positive, try again.\n";
        length = safeReadInteger();
    };
    return length;
}

int* type_array(int length)
{
	int* arr = new int[length];
	for (int i = 0; i < length; i++)
	{
		cout << "Give " << i << ". element" << endl;
		arr[i] = safeReadInteger();
	};
	return arr;
}

int* typeSafeDownToUpArray(int length)
{
    int* arr = type_array(length);
    while (!is_down_to_up(arr, length))
    {
        cout << "The array is not sorted properly. Try again." << endl;
        arr = type_array(length);
    };
    return arr;
}

bool* typeMatrix(int length)
{
    bool* mat = new bool[length * length];
    cout << "\\  |";
    for (int i = 0; i < length; i++)
        cout << setw(3) << i << "|";
    cout << endl;
    for (int i = 0; i < length; i++)
    {
        cout << setw(3) << i << "|";
        for (int j = 0; j < length; j++)
        {
            char c;
            cin >> c;
            if (c == '0')
                mat[i * length + j] = 0;
            else
                mat[i * length + j] = 1;
            cout << setw(3) << mat[i * length + j] << "|";
        }
        cout << endl;
    }
    return mat;
};
