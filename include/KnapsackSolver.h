#ifndef KNAPSACKSOLVER_H
#define KNAPSACKSOLVER_H

#include <iostream>

;using namespace std;

class NoProblemFoundException {};
class KnapsackSolver
{
    public:
        /** Default constructor */
        KnapsackSolver();
        /** Default destructor */
        virtual ~KnapsackSolver();

        void createProblem(int items, int capacity, double overload);
        void verbose();
        void saveProblem(string f);
        void loadProblem(string f);
        int getItemCount() { return _item_count; };

        bool* solveBruteForce();
        bool* solveBruteForceFast();
        bool* solveDP();

        int getUsedCapacity(bool* items);
        int getTotalValue(bool* items);

    protected:

    private:
        void knap_rec(bool* solution, bool* check, int bit, int& bestValue, int currentWeight, int currentValue);

        int* _items; // right item weights
        int* _values;
        int _capacity;
        int _item_count;

        bool _has_problem;
};

#endif // KNAPSACKSOLVER_H
