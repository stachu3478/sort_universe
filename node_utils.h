#ifndef NODE_UTILS_H_INCLUDED
#define NODE_UTILS_H_INCLUDED

#include "Graph.h"
#include "read_utils.h"
#include <iostream>
#include "measure.h"

using namespace std;

Graph* mg;
void prepare1(int n)
{
    cout << "(";
    delete mg;
    cout << ")";
    mg = new Graph(n);
    cout << ":";
    mg->createCycles(0.3);
    cout << "[";
    mg->matrixToListDump();
    cout << "]";
}

void prepare11(int n)
{
    cout << "(";
    delete mg;
    cout << ")";
    mg = new Graph(n);
    cout << ":";
    mg->createCycles(0.7);
    cout << "[";
    mg->matrixToListDump();
    cout << "]";
}

void prepare2(int n)
{
    delete mg;
    mg = new Graph(n);
    mg->createCycles(0.3);
}

void prepare22(int n)
{
    delete mg;
    mg = new Graph(n);
    mg->createCycles(0.7);
}

void prepare3(int n)
{
    delete mg;
    mg = new Graph(n);
    mg->createCycles(0.5);
    int nonZero = 0;
    while (nonZero == 0)
    {
        nonZero = rand() % n;
        cout << ":";
    }
    mg->isolate(nonZero);
    mg->matrixToListDump();
}

void measure1(int n)
{
    mg->findHamiltonianCycle2(0);
}

void measure2(int n)
{
    mg->findEulerCycle2(0);
}

void measure3(int n)
{
    mg->findHamiltonianCycle(0);
}

void node_app2()
{
    Graph* graph;
    int data_type = -1;
    while (1)
    {
        int alg_type = 0;
        // Always typing matrix
        // and conveting to target type
        cout<< "Choose an operation on graph or exit:\n"
        << "1. Generate hamiltionian graph auto\n"
        << "2. Generate hamiltionian graph typed\n"
        << "3. Isolate typed vertex\n"
        << "4. Graph verbose\n"
        << "5. Find Euler cycle\n"
        << "6. Find hamiltionian cycle\n"
        << "7. Find Euler cycle measurement 30%\n"
        << "8. Find hamiltionian cycle measurement 30%\n"
        << "9. Find Euler cycle measurement 70%\n"
        << "10. Find hamiltionian cycle measurement 70%\n"
        << "11. Find hamiltionian cycle in non-hamiltonian measurement 50%\n"
        << "0. Exit\n";
        cin >> alg_type;
        switch (alg_type)
        {
            case 1:
            {
                data_type = alg_type;
                int length = safeReadLength();
                graph = new Graph(length);
                cout << "Podaj nasycenie grafu krawedziami w %" << endl;
                graph->createCycles(safeReadInteger() / 100.0);
                graph->matrixToListDump();
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showList();
            }
            break;
            case 2:
            {
                data_type = alg_type;
                int length = safeReadLength();
                graph = new Graph(length);
                graph->setMatrix(typeMatrix(length));
                graph->matrixToListDump();
                cout << "[i] Typed" << endl;
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showList();
            }
            break;
            case 3:
            {
                cout << "Podaj wierzcholek ktory ma byc izolowany" << endl;
                graph->isolate(safeReadInteger());
                graph->matrixToListDump();
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showList();
            }
            break;
            case 4:
            {
                graph->listDepthVerbose();
            }
            break;
            case 5:
            {
                graph->findEulerCycle2(1);
            }
            break;
            case 6:
            {
                graph->findHamiltonianCycle2(1);
            }
            break;
            case 7:
            {
                measure(measure2, prepare2);
            }
            break;
            case 8:
            {
                measure(measure1, prepare1);
            }
            break;
            case 9:
            {
                measure(measure2, prepare22);
            }
            break;
            case 10:
            {
                measure(measure3, prepare11);
            }
            break;
            case 11:
            {
                measure(measure1, prepare3);
            }
            break;
            case 0: return;
            default: cout << "Work in progress.\n";
        };
    };
}

#endif // NODE_UTILS_H_INCLUDED
