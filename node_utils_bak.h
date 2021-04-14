#ifndef NODE_UTILS_H_INCLUDED
#define NODE_UTILS_H_INCLUDED

#include "Graph.h"
#include "read_utils.h"
#include <iostream>
#include "measure.h"

using namespace std;

void print_array(int* arr, int length)
{
    for (int i = 0; i < length; i++)
        cout << arr[i] << " ";
    cout << endl;
}

Graph* mg;
void prepare12(int n)
{
    delete mg;
    mg = new Graph(n);
    mg->createAcyclicEdges();
}

void measure1(int n)
{
    mg->matrixBreadthSort();
}

void measure2(int n)
{
    mg->matrixDepthSort();
}

void prepare34(int n)
{
    prepare12(n);
    mg->matrixToListDump();
}

void measure3(int n)
{
    mg->listBreadthSort();
}

void measure4(int n)
{
    mg->listDepthSort();
}

void prepare56(int n)
{
    prepare12(n);
    mg->matrixToTableDump();
}

void measure5(int n)
{
    mg->tableBreadthSort();
}

void measure6(int n)
{
    mg->tableDepthSort();
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
        << "1. Generate graph as matrix of neighbours auto\n"
        << "2. Generate graph as matrix of neighbours typed\n"
        << "3. Generate graph as list of next nodes auto\n"
        << "4. Generate graph as list of next nodes typed\n"
        << "5. Generate graph as table of edges auto\n"
        << "6. Generate graph as table of edges auto\n"
        << "7. Breadth first verbose\n"
        << "8. Depth first verbose\n"
        << "9. Breadth first topological sort\n"
        << "10. Depth first topological sort\n"
        << "11. Breadth first topological sort - matrix measurement\n"
        << "12. Depth first topological sort - matrix measurement\n"
        << "13. Breadth first topological sort - list measurement\n"
        << "14. Depth first topological sort - list measurement\n"
        << "15. Breadth first topological sort - table measurement\n"
        << "16. Depth first topological sort - table measurement\n"
        << "0. Exit\n";
        cin >> alg_type;

        switch (alg_type)
        {
            case 1:
            {
                data_type = alg_type;
                int length = safeReadLength();
                graph = new Graph(length);
                graph->createAcyclicEdges();
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showMatrix();
            }
            break;
            case 2:
            {
                data_type = alg_type;
                int length = safeReadLength();
                graph = new Graph(length);
                graph->setMatrix(typeMatrix(length));
                cout << "[i] Typed" << endl;
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showMatrix();
            }
            break;
            case 3:
            {
                data_type = alg_type;
                int length = safeReadLength();
                graph = new Graph(length);
                graph->createAcyclicEdges();
                graph->matrixToListDump();
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showList();
            }
            break;
            case 4:
            {
                data_type = alg_type;
                int length = safeReadLength();
                graph = new Graph(length);
                graph->setMatrix(typeMatrix(length));
                cout << "[i] Typed" << endl;
                graph->matrixToListDump();
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showList();
            }
            break;
            case 5:
            {
                data_type = alg_type;
                int length = safeReadLength();
                graph = new Graph(length);
                graph->createAcyclicEdges();
                graph->matrixToTableDump();
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showTable();
            }
            break;
            case 6:
            {
                data_type = alg_type;
                int length = safeReadLength();
                graph = new Graph(length);
                graph->setMatrix(typeMatrix(length));
                cout << "[i] Typed" << endl;
                graph->matrixToTableDump();
                cout << "[i] Edge count: " << graph->getEdgeCount() << endl;
                graph->showTable();
            }
            break;
            case 7:
            {
                switch (data_type)
                {
                    case 1: case 2: graph->matrixBreadthVerbose(); break;
                    case 3: case 4: graph->listBreadthVerbose(); break;
                    case 5: case 6: graph->tableBreadthVerbose(); break;
                    default: {
                        cout << "Nieznany typ danych! " << data_type << endl;
                        throw data_type;
                    }
                }
            }
            break;
            case 8:
            {
                switch (data_type)
                {
                    case 1: case 2: graph->matrixDepthVerbose(); break;
                    case 3: case 4: graph->listDepthVerbose(); break;
                    case 5: case 6: graph->tableDepthVerbose(); break;
                    default: {
                        cout << "Nieznany typ danych! " << data_type << endl;
                        throw data_type;
                    }
                }
            }
            break;
            case 9:
            {
                switch (data_type)
                {
                    case 1: case 2: print_array(graph->matrixBreadthSort(), graph->getNodeCount()); break;
                    case 3: case 4: print_array(graph->listBreadthSort(), graph->getNodeCount()); break;
                    case 5: case 6: print_array(graph->tableBreadthSort(), graph->getNodeCount()); break;
                    default: {
                        cout << "Nieznany typ danych! " << data_type << endl;
                        throw data_type;
                    }
                }
            }
            break;
            case 10:
            {
                switch (data_type)
                {
                    case 1: case 2: print_array(graph->matrixDepthSort(), graph->getNodeCount()); break;
                    case 3: case 4: print_array(graph->listDepthSort(), graph->getNodeCount()); break;
                    case 5: case 6: print_array(graph->tableDepthSort(), graph->getNodeCount()); break;
                    default: {
                        cout << "Nieznany typ danych! " << data_type << endl;
                        throw data_type;
                    }
                }
            }
            break;
            case 11: measure(measure1, prepare12); break;
            case 12: measure(measure2, prepare12); break;
            case 13: measure(measure3, prepare34); break;
            case 14: measure(measure4, prepare34); break;
            case 15: measure(measure5, prepare56); break;
            case 16: measure(measure6, prepare56); break;
            case 0: return;
            default: cout << "Work in progress.\n";
        };
    };
}

#endif // NODE_UTILS_H_INCLUDED
