#ifndef KNAPSACK_UTILS_H_INCLUDED
#define KNAPSACK_UTILS_H_INCLUDED

#ifndef NODE_UTILS_H_INCLUDED
#define NODE_UTILS_H_INCLUDED

#include "KnapsackSolver.h"
#include "read_utils.h"
#include <iostream>
#include "measure.h"

using namespace std;

KnapsackSolver* measureSolver;
char* to_cstr(string s)
{
    char cstr[s.size() + 1];
    strcpy(cstr, s.c_str());
    return cstr;
}

void prepare1(int n)
{
    cout << "F" << endl;
    string F;
    cin >> F;
    cout << endl;
    measureSolver = new KnapsackSolver();
    measureSolver->loadProblem(F);
}

void measure1(int n)
{
    measureSolver->solveBruteForceFast();
}

void measure2(int n)
{
    measureSolver->solveDP();
}

void knapsack_app()
{
    KnapsackSolver* solver = new KnapsackSolver();
    while (1)
    {
        int alg_type = 0;
        cout<< "Choose an operation or exit:\n"
        << "1. Generate knapsack problem\n"
        << "2. Solve knapsack problem brute-force\n"
        << "3. Solve knapsack problem DP\n"
        << "4. Knapsack problem verbose\n"
        << "5. Knapsack problem save\n"
        << "6. Knapsack problem load\n"
        << "7. Knapsack problem brute-force measurement\n"
        << "8. Knapsack problem DP measurement\n"
        << "9. Cokolwiek robisz, nie odpalaj tego algorytmu\n"
        << "0. Exit\n";
        cin >> alg_type;
        switch (alg_type)
        {
            case 1:
            {
                cout << "Item count? ";
                int itemCount = safeReadInteger();
                cout << endl << "Capacity? ";
                int capacity = safeReadInteger();
                cout << endl << "Total item weight by %capacity ? ";
                int overload = safeReadInteger();
                solver->createProblem(itemCount, capacity, overload / 100.0);
                cout << endl << "Problem generated." << endl;
            }
            break;
            case 2:
            {
                bool* solution = solver->solveBruteForce();
                int itemCount = solver->getItemCount();
                for (int i = 0; i < itemCount; i++)
                    cout << solution[i] << " ";
                cout << endl;
                for (int i = 0; i < itemCount; i++)
                    if (solution[i])
                        cout << i + 1 << " ";
                cout << "Used weight: " << solver->getUsedCapacity(solution) << endl;
                cout << "Value earned: " << solver->getTotalValue(solution) << endl;
                cout << endl;
            }
            break;
            case 3:
            {
                bool* solution = solver->solveDP();
                int itemCount = solver->getItemCount();
                for (int i = 0; i < itemCount; i++)
                    cout << solution[i] << " ";
                cout << endl;
                for (int i = 0; i < itemCount; i++)
                    if (solution[i])
                        cout << i + 1 << " ";
                cout << "Used weight: " << solver->getUsedCapacity(solution) << endl;
                cout << "Value earned: " << solver->getTotalValue(solution) << endl;
                cout << endl;
            }
            break;
            case 4:
            {
                solver->verbose();
            }
            break;
            case 5:
            {
                cout << "F" << endl;
                string F;
                cin >> F;
                cout << endl;
                solver->saveProblem(F);
            }
            break;
            case 6:
            {
                cout << "F" << endl;
                string F;
                cin >> F;
                cout << endl;
                solver->loadProblem(F);
            }
            break;
            case 7:
            {
                basic_measure(measure1, prepare1);
            }
            break;
            case 8:
            {
                basic_measure(measure2, prepare1);
            }
            break;
            case 9:
            {
                bool* solution = solver->solveBruteForceFast();
                int itemCount = solver->getItemCount();
                for (int i = 0; i < itemCount; i++)
                    cout << solution[i] << " ";
                cout << endl;
                for (int i = 0; i < itemCount; i++)
                    if (solution[i])
                        cout << i + 1 << " ";
                cout << "Used weight: " << solver->getUsedCapacity(solution) << endl;
                cout << "Value earned: " << solver->getTotalValue(solution) << endl;
                cout << endl;
            }
            break;
            case 0: return;
            default: cout << "Work in progress.\n";
        };
    };
}

#endif // NODE_UTILS_H_INCLUDED


#endif // KNAPSACK_UTILS_H_INCLUDED
