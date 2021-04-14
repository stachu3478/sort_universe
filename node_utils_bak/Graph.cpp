#include "Graph.h"
#include <iostream>
#include <iomanip>

#include <stdlib.h>
#include <cstdio>

#include "Stack.h"
#include "Queue.h"

using namespace std;

Graph::Graph(int nodes)
{
    this->matrix = new bool[nodes * nodes];
    this->nodeCount = nodes;
    this->edgeCount = 0;
    int pairs = nodes * nodes;
    for (int i = 0; i < pairs; i++)
        this->matrix[i] = 0;
    this->hasTable = 0;
    this->hasList = 0;
    this->hasMatrix = 1;
}

void Graph::createEdge(int fromNode, int toNode)
{
    this->matrix[toNode * this->nodeCount + fromNode] = 1;
    this->edgeCount++;
}

void Graph::countEdges()
{
    int matSize = this->nodeCount * this->nodeCount;
    bool* mat = this->matrix;
    int edgeCount = 0;
    for (int i = 0; i < matSize; i++)
        if (mat[i] != 0) edgeCount++;
    this->edgeCount = edgeCount;
}

void Graph::createAcyclicEdges()
{
    int nodeCount = this->nodeCount;
    for (int col = 0; col < nodeCount; col++)
        for (int row = 0; row < col; row++)
            if (rand() % 2 == 1)
                createEdge(col, row);
}

void Graph::showMatrix()
{
    int nodeCount = this->nodeCount;
    bool* mat = this->matrix;
    cout << "\\  |";
    for (int i = 0; i < nodeCount; i++)
        cout << setw(3) << i << "|";
    cout << endl;
    for (int i = 0; i < nodeCount; i++)
    {
        cout << setw(3) << i << "|";
        for (int j = 0; j < nodeCount; j++)
        {
            cout << setw(3) << mat[i * nodeCount + j] << "|";
        }
        cout << endl;
    }
}

typedef int* intList;

void Graph::matrixToListDump()
{
    int nodeCount = this->nodeCount;
    bool* mat = this->matrix;
    intList* totalList = new intList[nodeCount];
    for (int row = 0; row < nodeCount; row++)
    {
        Stack* connected = new Stack();
        for (int col = 0; col < nodeCount; col++)
            if (mat[row * nodeCount + col] != 0)
                connected->put(col);
        int rowEdgeCount = connected->getSize();
        int* connectedList = new int[rowEdgeCount + 1];
        connectedList[rowEdgeCount] = -1;
        for (int i = rowEdgeCount - 1; i >= 0; i--)
            connectedList[i] = connected->pull();
        totalList[row] = connectedList;
    }
    this->_list = totalList;
    delete[] this->matrix;
    this->hasList = 1;
    this->hasMatrix = 0;
}

void Graph::showList()
{
    int nodeCount = this->nodeCount;
    cout << "----------" << endl;
    for (int i = 0; i < nodeCount; i++)
    {
        int* localNodes = this->_list[i];
        cout << setw(3) << "E" << setw(3) << i << "|";
        int j = 0;
        int node;
        while ((node = localNodes[j]) != -1)
        {
            j++;
            cout << setw(3) << node << " ->";
        }
        cout << " ." << endl;
    }
}

void Graph::matrixToTableDump()
{
    int nodeCount = this->nodeCount;
    bool* mat = this->matrix;
    intList* totalList = new intList[edgeCount];
    int edgeIndex = 0;
    for (int row = 0; row < nodeCount; row++)
        for (int col = 0; col < nodeCount; col++)
            if (mat[row * nodeCount + col] != 0)
            {
                int* edge = totalList[edgeIndex++] = new int[2];
                edge[0] = row;
                edge[1] = col;
            }
    this->table = totalList;
    delete[] this->matrix;
    this->hasTable = 1;
    this->hasMatrix = 0;
}

void Graph::showTable()
{
    int edgeCount = this->edgeCount;
    cout << "----------" << endl;
    for (int i = 0; i < edgeCount; i++)
    {
        int* edge = this->table[i];
        cout << setw(7) << edge[0] << "->" << edge[1];
    }
    cout << endl;
}

void Graph::matrixBreadthVerbose()
{
    int nodeCount = this->nodeCount;
    bool* visited = new bool[nodeCount];
    bool* mat = this->matrix;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    Queue* toVisit = new Queue();
    int current = 0;
    cout << current << " ";
    visited[current] = 1;
    toVisit->put(current);
    while (toVisit->getSize() > 0)
    {
        current = toVisit->pull();
        int row = current * nodeCount;
        for (int i = 0; i < nodeCount; i++)
            if (mat[row + i] != 0 && !visited[i])
            {
                cout << i << " ";
                visited[i] = 1;
                toVisit->put(i);
            }
    }
    cout << endl;
}

void Graph::matrixDepthVerbose()
{
    int nodeCount = this->nodeCount;
    bool* visited = new bool[nodeCount];
    bool* mat = this->matrix;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    Stack* toVisit = new Stack();
    int current;
    toVisit->put(0);
    while (toVisit->getSize() > 0)
    {
        current = toVisit->pull();
        if (!visited[current])
        {
            cout << current << " ";
            visited[current] = 1;
        }
        int row = current * nodeCount;
        for (int i = nodeCount - 1; i >= 0; i--)
            if (mat[row + i] != 0 && !visited[i])
                toVisit->put(i);
    }
    cout << endl;
}

void Graph::listBreadthVerbose()
{
    int nodeCount = this->nodeCount;
    bool* visited = new bool[nodeCount];
    int** _list = this->_list;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    Queue* toVisit = new Queue();
    int current = 0;
    cout << current << " ";
    visited[current] = 1;
    toVisit->put(current);
    while (toVisit->getSize() > 0)
    {
        current = toVisit->pull();
        int* row = _list[current];
        int i = -1;
        while (row[++i] != -1)
            if (!visited[row[i]])
            {
                cout << row[i] << " ";
                visited[row[i]] = 1;
                toVisit->put(row[i]);
            }
    }
    cout << endl;
}

void Graph::listDepthVerbose()
{
    int nodeCount = this->nodeCount;
    bool* visited = new bool[nodeCount];
    int** _list = this->_list;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    Stack* toVisit = new Stack();
    int current;
    toVisit->put(0);
    while (toVisit->getSize() > 0)
    {
        current = toVisit->pull();
        if (!visited[current])
        {
            cout << current << " ";
            visited[current] = 1;
        }
        int* row = _list[current];
        int i = -1;
        while (row[++i] != -1);
        while (row[--i] >= 0)
            if (!visited[row[i]])
                toVisit->put(row[i]);
    }
    cout << endl;
}

void Graph::tableBreadthVerbose()
{
    int nodeCount = this->nodeCount;
    int edgeCount = this->edgeCount;
    bool* visited = new bool[nodeCount];
    int** table = this->table;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    Queue* toVisit = new Queue();
    int current = 0;
    cout << current << " ";
    visited[current] = 1;
    toVisit->put(current);
    while (toVisit->getSize() > 0)
    {
        current = toVisit->pull();
        for (int i = 0; i < edgeCount; i++)
        {
            int* edge = table[i];
            if (edge[0] == current && !visited[edge[1]])
            {
                cout << edge[1] << " ";
                visited[edge[1]] = 1;
                toVisit->put(edge[1]);
            }
        }
    }
    cout << endl;
}

void Graph::tableDepthVerbose()
{
    int nodeCount = this->nodeCount;
    int edgeCount = this->edgeCount;
    bool* visited = new bool[nodeCount];
    int** table = this->table;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    Stack* toVisit = new Stack();
    int current;
    toVisit->put(0);
    while (toVisit->getSize() > 0)
    {
        current = toVisit->pull();
        if (!visited[current])
        {
            cout << current << " ";
            visited[current] = 1;
        }
        for (int i = edgeCount - 1; i >= 0; i--)
        {
            int* edge = table[i];
            if (edge[0] == current && !visited[edge[1]])
                toVisit->put(edge[1]);
        }
    }
    cout << endl;
}

int* Graph::matrixBreadthSort()
{
    int nodeCount = this->nodeCount;
    int* inDegree = new int[nodeCount];
    int* solution = new int[nodeCount];
    int solutionPtr = 0;
    bool* mat = this->matrix;
    for (int i = 0; i < nodeCount; i++)
        inDegree[i] = 0;
    int current = 0;
    int matSize = nodeCount * nodeCount;
    for (int i = 0; i < matSize; i++)
        if (mat[i] == 1)
            inDegree[i % nodeCount]++;
    for (int i = 0; i < nodeCount; i++)
    {
        bool done = true;
        for (int j = 0; j < nodeCount; j++)
            if (inDegree[j] == 0)
            {
                done = false;
                solution[solutionPtr++] = j;
                inDegree[j] = -1;
                for (int k = 0; k < nodeCount; k++)
                    if (mat[j * nodeCount + k] == 1)
                        inDegree[k]--;
            }
        if (done) break;
    }
    if (solutionPtr < nodeCount)
        cout << "Istnieje cykl";
    return solution;
}

void mdsr(int current, char* visited, int* solution, int& solutionPtr, int nodeCount, bool* mat)
{
    int row = current * nodeCount;
    visited[current] = 1;
    for (int i = 0; i < nodeCount; i++)
        if (mat[row + i] != 0)
        {
            if (visited[i] == 1)
                cout << "Istnieje cykl" << endl;
            if (visited[i] == 0)
                mdsr(i, visited, solution, solutionPtr, nodeCount, mat);
        }
    visited[current] = 2;
    solution[--solutionPtr] = current;
}

int* Graph::matrixDepthSort()
{
    int nodeCount = this->nodeCount;
    char* visited = new char[nodeCount];
    int* solution = new int[nodeCount];
    bool* mat = this->matrix;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    int solutionPtr = nodeCount;
    for (int i = 0; i < nodeCount; i++)
        if (visited[i] == 0)
            mdsr(i, visited, solution, solutionPtr, nodeCount, mat);
    return solution;
}

int* Graph::listBreadthSort()
{
    int nodeCount = this->nodeCount;
    int* inDegree = new int[nodeCount];
    int* solution = new int[nodeCount];
    int solutionPtr = 0;
    int** _list = this->_list;
    for (int i = 0; i < nodeCount; i++)
        inDegree[i] = 0;
    int current = 0;
    for (int i = 0; i < nodeCount; i++)
    {
        int j = -1;
        int* ins = _list[i];
        while (ins[++j] != -1)
            inDegree[ins[j]]++;
    }
    for (int i = 0; i < nodeCount; i++)
    {
        bool done = true;
        for (int j = 0; j < nodeCount; j++)
            if (inDegree[j] == 0)
            {
                done = false;
                solution[solutionPtr++] = j;
                inDegree[j] = -1;
                int l = -1;
                int* ins = _list[j];
                while (ins[++l] != -1)
                    inDegree[ins[l]]--;
            }
        if (done) break;
    }
    if (solutionPtr < nodeCount)
        cout << "Istnieje cykl" << endl;
    return solution;
}

void ldsr(int current, char* visited, int* solution, int& solutionPtr, int nodeCount, int** _list)
{
    visited[current] = 1;
    int i = -1;
    int* ins = _list[current];
    while (ins[++i] != -1)
    {
        if (visited[ins[i]] == 1)
            cout << "Istnieje cykl" << endl;
        if (visited[ins[i]] == 0)
            ldsr(ins[i], visited, solution, solutionPtr, nodeCount, _list);
    }
    visited[current] = 2;
    solution[--solutionPtr] = current;
}

int* Graph::listDepthSort()
{
    int nodeCount = this->nodeCount;
    char* visited = new char[nodeCount];
    int* solution = new int[nodeCount];
    int** _list = this->_list;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    int solutionPtr = nodeCount;
    for (int i = 0; i < nodeCount; i++)
        if (visited[i] == 0)
            ldsr(i, visited, solution, solutionPtr, nodeCount, _list);
    return solution;
}

int* Graph::tableBreadthSort()
{
    int nodeCount = this->nodeCount;
    int* inDegree = new int[nodeCount];
    int* solution = new int[nodeCount];
    int solutionPtr = 0;
    int** table = this->table;
    int edgeCount = this->edgeCount;
    for (int i = 0; i < nodeCount; i++)
        inDegree[i] = 0;
    int current = 0;
    for (int i = 0; i < edgeCount; i++)
        inDegree[table[i][1]]++;
    for (int i = 0; i < nodeCount; i++)
    {
        bool done = true;
        for (int j = 0; j < nodeCount; j++)
            if (inDegree[j] == 0)
            {
                done = false;
                solution[solutionPtr++] = j;
                inDegree[j] = -1;
                for (int k = 0; k < edgeCount; k++)
                    if (table[k][0] == j)
                        inDegree[table[k][1]]--;
            }
        if (done) break;
    }
    if (solutionPtr < nodeCount)
        cout << "Istnieje cykl" << endl;
    return solution;
}

void tdsr(int current, char* visited, int* solution, int& solutionPtr, int edgeCount, int** table)
{
    visited[current] = 1;
    for (int i = 0; i < edgeCount; i++)
        if (table[i][0] == current)
        {
            if (visited[table[i][1]] == 1)
                cout << "Istnieje cykl" << endl;
            if (visited[table[i][1]] == 0)
                tdsr(table[i][1], visited, solution, solutionPtr, edgeCount, table);
        }
    visited[current] = 2;
    solution[--solutionPtr] = current;
}

int* Graph::tableDepthSort()
{
    int nodeCount = this->nodeCount;
    int edgeCount = this->edgeCount;
    char* visited = new char[nodeCount];
    int* solution = new int[nodeCount];
    int** table = this->table;
    for (int i = 0; i < nodeCount; i++)
        visited[i] = 0;
    int solutionPtr = nodeCount;
    for (int i = 0; i < nodeCount; i++)
        if (visited[i] == 0)
            tdsr(i, visited, solution, solutionPtr, edgeCount, table);
    return solution;
}


Graph::~Graph()
{
    if (this->hasList)
        for (int i = 0; i < nodeCount; i++)
            delete[] this->_list[i];
    if (this->hasMatrix)
        delete[] this->matrix;
    if (this->hasTable)
        for (int i = 0; i < edgeCount; i++)
            delete[] this->table[i];
}
