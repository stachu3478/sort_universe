#include "KnapsackSolver.h"

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <ctime>

using namespace std;

KnapsackSolver::KnapsackSolver()
{
    _has_problem = false;
}

void KnapsackSolver::createProblem(int itemCount, int capacity, double overload)
{
    _items = new int[itemCount];
    _values = new int[itemCount];
    _capacity = capacity;
    _item_count = itemCount;
    int totalItemCapacity = (int)(overload * capacity);
    int derivedItemCapacity = totalItemCapacity / itemCount;
    int randomRange = derivedItemCapacity * 2 - 2;
    srand(time(NULL));
    for (int i = 0; i < itemCount; i++)
    {
        _items[i] = (rand() % randomRange) + 1;
        _values[i] = (rand() & randomRange) + 1;
    }
    _has_problem = true;
}

void KnapsackSolver::verbose()
{
    cout << _capacity << endl;
    cout << _item_count << endl;
    for (int i = 0; i < _item_count; i++)
        cout << _values[i] << " " << _items[i] << endl;
}

bool* KnapsackSolver::solveBruteForce()
{
    if (!_has_problem) throw NoProblemFoundException();
    bool* solution = new bool[_item_count];
    bool* check = new bool[_item_count];
    for (int i = 0; i < _item_count; i++)
    {
        solution[i] = false;
        check[i] = false;
    }
    int bestValue = 0;
    int last_item = _item_count - 1;
    int power_point = last_item;
    int currentWeight = 0;
    int currentValue = 0;
    while (1)
    {
        if (currentValue > bestValue && currentWeight <= _capacity)
        {
            for (int i = 0; i < _item_count; i++)
                solution[i] = check[i];
            bestValue = currentValue;
        }
        if (check[power_point])
        {
            do
            {
                check[power_point] = false;
                currentWeight -= _items[power_point];
                currentValue -= _values[power_point];
                power_point--;
                if (power_point < 0) break;
            } while (check[power_point]);
            if (power_point < 0) break;
            check[power_point] = true;
            currentWeight += _items[power_point];
            currentValue += _values[power_point];
            power_point = last_item;
        } else {
            check[power_point] = true;
            currentWeight += _items[power_point];
            currentValue += _values[power_point];
        }
    }
    return solution;
}

int trail_zeros(bool* arr, int _max)
{
    int val = 0;
    while (val < _max && !arr[val])
        val++;
    return val;
}

bool* KnapsackSolver::solveBruteForceFast()
{
    if (!_has_problem) throw NoProblemFoundException();
    bool* solution = new bool[_item_count];
    bool* check = new bool[_item_count + 1];
    check[_item_count + 1] = 1;
    for (int i = 0; i < _item_count; i++)
    {
        solution[i] = false;
        check[i] = false;
    }
    int bestValue = 0;
    int power_point;
    int currentWeight = 0;
    int currentValue = 0;
    int gray1 = 0;
    int gray0 = 0;
    int msb = -1;
    while (1)
    {
        if (currentValue > bestValue && currentWeight <= _capacity)
        {
            for (int i = 0; i < _item_count; i++)
                solution[i] = check[i];
            bestValue = currentValue;
        }
        if ((gray1 & 1) == 0)
            power_point = 0;
        else
        {
            power_point = gray0 + 1;
            if (power_point == _item_count)
                break;
        }
        if (check[power_point])
        {
            check[power_point] = false;
            currentWeight -= _items[power_point];
            currentValue -= _values[power_point];
            gray1--;
            if (gray0 == power_point)
                do
                    gray0++;
                while (!check[gray0]);
        } else {
            check[power_point] = true;
            currentWeight += _items[power_point];
            currentValue += _values[power_point];
            gray1++;
            if (gray0 > power_point)
                gray0 = power_point;
        }
    }
    return solution;
}

bool* KnapsackSolver::solveDP()
{
    int** check = new int*[_item_count + 1];
    check[0] = new int[_capacity + 1];
    for (int i = 0; i <= _capacity; i++)
        check[0][i] = 0;
    int* prevRow = check[0];
    for (int y = 1; y <= _item_count; y++)
    {
        int weight = _items[y - 1];
        int value = _values[y - 1];
        int* row = new int[_capacity + 1];
        row[0] = 0;
        for (int x = 1; x <= _capacity; x++)
        {
            if (weight > x)
            {
                row[x] = prevRow[x];
            } else
            {
                int l = prevRow[x];
                int r;
                if (x - weight >= 0)
                    r = prevRow[x - weight] + value;
                else
                    r = 0;
                if (l > r)
                    row[x] = l;
                else
                    row[x] = r;
            }
        }
        prevRow = check[y] = row;
    }
    bool* solution = new bool[_item_count];
    int itemPointer = _item_count;
    int weightPointer = _capacity;
    while (itemPointer > 1)
    {
        if (check[itemPointer][weightPointer] > check[itemPointer - 1][weightPointer])
        {
            solution[itemPointer - 1] = true;
            weightPointer -= _items[itemPointer - 1];
        } else
        {
            solution[itemPointer - 1] = false;
        }
        itemPointer--;
    }
    if (weightPointer == 0)
        solution[0] = false;
    else
        solution[0] = true;
    return solution;
}

int KnapsackSolver::getUsedCapacity(bool* items)
{
    int used = 0;
    for (int i = 0; i < _item_count; i++)
        if (items[i])
            used += _items[i];
    return used;
}

int KnapsackSolver::getTotalValue(bool* items)
{
    int total = 0;
    for (int i = 0; i < _item_count; i++)
        if (items[i])
            total += _values[i];
    return total;
}

void KnapsackSolver::saveProblem(string filename)
{
    ofstream file;
    file.open(filename);
    file << _capacity << endl;
    file << _item_count << endl;
    for (int i = 0; i < _item_count; i++)
        file << _values[i] << " " << _items[i] << endl;
    file.close();
}

void KnapsackSolver::loadProblem(string filename)
{
    ifstream file;
    file.open(filename);
    file >> _capacity;
    file >> _item_count;
    _values = new int[_item_count];
    _items = new int[_item_count];
    for (int i = 0; i < _item_count; i++)
    {
        file >> _values[i];
        file >> _items[i];
    }
    _has_problem = true;
    file.close();
}

KnapsackSolver::~KnapsackSolver()
{
    //dtor
}
