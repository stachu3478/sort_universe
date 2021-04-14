#include <iostream>
#include <iomanip>
#include <time.h>

#include "../array_generators/random/random.h"
#include "../array_generators/down_to_up/down_to_up.h"
#include "../array_generators/up_to_down/up_to_down.h"
#include "../array_generators/single_value/single_value.h"
#include "../array_generators/v_shaped/v_shaped.h"
#include "../array_generators/a_shaped/a_shaped.h"
#include "measure.h"

;using namespace std;

typedef int* generator(int length);
generator* pickGenerator(int id)
{
    switch (id)
    {
        case 0: return random_list;
        case 1: return down_to_up;
        case 2: return up_to_down;
        case 3: return single_value;
        case 4: return v_shaped;
        case 5: return a_shaped;
    };
};

void measure(sort_algorithm alg)
{
    int instanceType = 0,
        baseSize = 1000,
        threshold = 100,
        delta = 100,
        measurements = 10;
    cout<< "Which instance type do you want to use? (0)\n"
        << "0. Random\n"
        << "1. Going up\n"
        << "2. Going down\n"
        << "3. Single value\n"
        << "4. V-shaped\n"
        << "5. A-shaped\n";
    cin >> instanceType;
    cout<< "Please type number of items per instance. (1000)\n";
    cin >> baseSize;
    cout<< "How many items should be added to instance after succesful measurement? (1000)\n";
    cin >> delta;
    cout<< "What should be timeout for sorting in miliseconds? (100)\n";
    cin >> threshold;
    cout<< "Please type number of measurements per instance size. (10)\n";
    cin >> measurements;

    cout << setw(10) << "Size" << setw(2) << "|" << setw(15) << "Average time (ms)\n";
    cout << string(35, '-') << endl;

    cout << fixed << setprecision(1);
    double output_time = 0;
    generator* gen = pickGenerator(instanceType);
    while (output_time < threshold)
    {
        int sort_time = 0;
        for (int n = 0; n < measurements; n++)
        {
            int* arr = gen(baseSize);
            clock_t start = clock();
            alg(arr, baseSize);
            sort_time += clock() - start;
            delete arr;
        };
        output_time = (double)sort_time / measurements;
        cout << setw(10) << baseSize << setw(2) << "|" << setw(10) << output_time << endl;
        baseSize += delta;
    };
};

void basic_measure(algorithm alg, algorithm prepare)
{
    prepare(0);
    int time = 0;
    int ops = 0;
    while (time == 0)
    {
        clock_t start = clock();
        alg(0);
        time = clock() - start;
        ops++;
    }
    cout << setw(10) << 0 << setw(2) << "|" << setw(10) << time << " Elapsed: " << ops << endl;
}

void measure(algorithm alg, algorithm prepare)
{
    int baseSize = 1000,
        threshold = 100,
        delta = 100,
        measurements = 10;
    cout<< "Please type number of items per instance. (1000)\n";
    cin >> baseSize;
    cout<< "How many items should be added to instance after succesful measurement? (1000)\n";
    cin >> delta;
    cout<< "What should be timeout for sorting in miliseconds? (100)\n";
    cin >> threshold;
    cout<< "Please type number of measurements per instance size. (10)\n";
    cin >> measurements;

    cout << setw(10) << "Size" << setw(2) << "|" << setw(15) << "Average time (ms)\n";
    cout << string(35, '-') << endl;

    cout << fixed << setprecision(1);
    double output_time = 0;
    while (output_time < threshold)
    {
        int time = 0;
        for (int n = 0; n < measurements; n++)
        {
            prepare(baseSize);
            clock_t start = clock();
            alg(baseSize);
            time += clock() - start;
        };
        output_time = (double)time / measurements;
        cout << setw(10) << baseSize << setw(2) << "|" << setw(10) << output_time << endl;
        baseSize += delta;
    };
};
