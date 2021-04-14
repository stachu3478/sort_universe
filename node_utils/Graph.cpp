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
    this->has_list = 0;
}

bool Graph::createEdge(int fromNode, int toNode)
{
    int pos = toNode * this->nodeCount + fromNode;
    bool notFilled = this->matrix[pos] == 0;
    if (notFilled)
    {
        this->matrix[pos] = 1;
        this->edgeCount++;
    }
    return notFilled;
}

void Graph::isolate(int vertex)
{
    bool* mat = this->matrix;
    int edgeCount = this->edgeCount;
    int vertexCount = this->nodeCount;
    int rowStart = vertex * nodeCount;
    int rowEnd = vertex * nodeCount + nodeCount;
    int colStart = vertex;
    int colEnd = nodeCount * nodeCount;
    for (int i = rowStart; i < rowEnd; i++)
    {
        if (mat[i] == 1)
        {
            mat[i] = 0;
            edgeCount--;
        }
    }
    for (int i = colStart; i < colEnd; i += nodeCount)
    {
        if (mat[i] == 1)
        {
            mat[i] = 0;
            edgeCount--;
        }
    }
}

void Graph::createHamiltonianCycle()
{
    int vertexCount = this->nodeCount;
    int* vertexMix = new int[vertexCount];
    for (int i = 0; i < vertexCount; i++)
    {
        vertexMix[i] = i;
    }
    for (int i = 0; i < vertexCount; i++)
    {
        int randIndex = rand() % vertexCount;
        int tmp = vertexMix[randIndex];
        vertexMix[randIndex] = vertexMix[i];
        vertexMix[i] = tmp;
    }
    vertexCount--;
    for (int i = 0; i < vertexCount; i++)
    {
        this->createEdge(vertexMix[i], vertexMix[i + 1]);
        this->createEdge(vertexMix[i + 1], vertexMix[i]);
    }
    this->createEdge(vertexMix[0], vertexMix[vertexCount]);
    this->createEdge(vertexMix[vertexCount], vertexMix[0]);
}

void Graph::createCycles(double level)
{
    this->createHamiltonianCycle();
    int vertexCount = this->nodeCount;
    int toMake = (int)(vertexCount * vertexCount * level);
    int maxIterations = vertexCount * vertexCount;
    int elapsed = 0;
    while (this->edgeCount < toMake)
    {
        int v1 = rand() % vertexCount;
        int v2 = rand() % vertexCount;
        int v3 = rand() % vertexCount;
        if (v1 == v2) continue;
        if (v1 == v3) continue;
        if (v2 == v3) continue;
        this->createEdge(v1, v2);
        this->createEdge(v2, v1);
        this->createEdge(v1, v3);
        this->createEdge(v3, v1);
        this->createEdge(v3, v2);
        this->createEdge(v2, v3);
        if (elapsed++ > maxIterations) return;
    }
}

void Graph::findHamiltonianCycle(bool verbose)
{
    bool* unvisited = new bool[nodeCount];
    int** _list = this->_list;
    unvisited[0] = 0;
    for (int i = 1; i < nodeCount; i++)
        unvisited[i] = 1;
    int* toVisit = new int[nodeCount];
    int* toSearch = new int[nodeCount];
    int stackPtr = 0;
    int current = 0;
    int i = 0;
    int* row = _list[current];
    int vertex = row[0];
    int sizeNeeded = nodeCount - 1;
    while (1)
    {
        while (vertex != -1)
        {
            if (unvisited[vertex])
            {
                unvisited[vertex] = 0;
                toVisit[stackPtr] = current; // NURKOWANIE
                toSearch[stackPtr++] = i + 1;
                row = _list[current = vertex];
                vertex = row[i = 0];
            }
            else if (vertex == 0 && stackPtr == sizeNeeded)
            {
                if (!verbose)
                    return;
                for (int j = 0; j < sizeNeeded; j++)
                    cout << toVisit[j] << " ";
                cout << vertex << " ";
                return; // CYKL ZNALEZIONY
            }
            else vertex = row[++i];
        }
        // if (rand() < 1) cout << ".";
        do
        {
            if (stackPtr == 0)
            {
                return;
            }
            unvisited[current] = 1;
            // NAWROT
            row = _list[current = toVisit[--stackPtr]];
            vertex = row[i = toSearch[stackPtr]];
        } while (vertex == -1);
    }
}

int** next_edge_list;
bool* visited;
int visitedCount;
int _count;
int* path;
int k;
bool fhc(int current)
{
    // if (rand() < 1) cout << ".";
    visited[current] = 1;
    visitedCount++;
    int* row = next_edge_list[current];
    int i = -1;
    while (row[++i] != -1)
    {
        if (row[i] == 0 && visitedCount == _count) return true;
        if (visited[row[i]]) continue;
        if (fhc(row[i]))
        {
            path[k++] = row[i];
            return true;
        }
    }
    visited[current] = 0;
    visitedCount--;
    return false;
}

void Graph::findHamiltonianCycle2(bool verbose)
{
    _count = this->nodeCount;
    next_edge_list = this->_list;
    visited = new bool[_count];
    visitedCount = 0;
    for (int i = 1; i < _count; i++)
        visited[i] = 0;
    path = new int[_count];
    path[0] = 0;
    k = 1;
    if (fhc(0))
    {
        if (!verbose)
            return;
        for (int j = 0; j < _count; j++)
            cout << path[j] << " "; // CYKL ZNALEZIONY
        cout << endl;
    }
    else if (verbose)
        cout << "Brak cyklu " << endl; // BRAK CYKLU
}

bool* euler_matrix;
int* euler_path;
int euler_k;
void Graph::dfs_euler(int v)
{
    int row = v * this->nodeCount;
    for (int i = 0; i < nodeCount; i++)
    {
        if (!euler_matrix[row + i]) continue;
        euler_matrix[row + i] = 0;
        euler_matrix[i * this->nodeCount + v] = 0;
        this->dfs_euler(i);
    }
    euler_path[euler_k++] = v;
}

void Graph::findEulerCycle(bool verbose)
{
    int matSize = this->nodeCount * this->nodeCount;
    euler_path = new int[1 + edgeCount / 2];
    euler_k = 0;
    euler_matrix = new bool[matSize];
    for (int i = 0; i < matSize; i++)
        euler_matrix[i] = this->matrix[i];
    this->dfs_euler(0);
    if (euler_k == 1 + edgeCount / 2)
    {
        if (verbose)
        {
            for (int i = 0; i < 1 + edgeCount / 2; i++)
                cout << euler_path[i] << " ";
            cout << endl;
        }
    } else
    {
        cout << "Brak cyklu Eulera" << euler_k << endl;
        if (!verbose)
        {
            this->matrixToListDump();
            this->showList();
            throw this;
        }
    }
}

void Graph::findEulerCycle2(bool verbose)
{
    int matSize = this->nodeCount * this->nodeCount;
    bool* mat = new bool[matSize];
    for (int i = 0; i < matSize; i++)
        mat[i] = this->matrix[i];
    int* toVisit = new int[edgeCount];
    int* toSearch = new int[edgeCount];
    int stackPtr = 0;
    int* path = new int[edgeCount];
    int pathPtr = 0;
    int i = -1;
    int row = 0;
    while (1)
    {
        while (++i < nodeCount)
        {
            if (!mat[row + i]) continue;
            mat[row + i] = 0;
            mat[i * nodeCount + row / nodeCount] = 0;
            toVisit[stackPtr] = row / nodeCount; // NURKOWANIE
            toSearch[stackPtr++] = i;
            row = i * nodeCount;
            i = -1;
        }
        path[pathPtr++] = row / nodeCount;
        if (stackPtr == 0)
        {
            if (pathPtr != 1 + edgeCount / 2)
                cout << "Brak cyklu Eulera" << pathPtr << endl;
            if (!verbose) return;
            for (int i = 0; i < 1 + edgeCount / 2; i++)
                cout << path[i] << " ";
            cout << endl;
            return;
        }
        // NAWROT
        row = toVisit[--stackPtr] * nodeCount;
        i = toSearch[stackPtr];
    }
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
    this->has_list = 1;
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

Graph::~Graph()
{
    if (this->has_list)
        for (int i = 0; i < nodeCount; i++)
            delete[] this->_list[i];
    delete[] this->matrix;
}
