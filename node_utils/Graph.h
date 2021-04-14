#ifndef GRAPH_H
#define GRAPH_H

class Graph
{
    public:
        /** Default constructor */
        Graph(int nodes);
        /** Default destructor */
        virtual ~Graph();

        int getEdgeCount() { return this->edgeCount; };
        int getNodeCount() { return this->nodeCount; };
        void setMatrix(bool* mat) { this->matrix = mat; this->countEdges(); };

        bool createEdge(int fromNode, int toNode);
        void createHamiltonianCycle();
        void createCycle(int v1, int v2, int v3);
        void createCycles(double level);
        void isolate(int vertex);

        void listDepthVerbose();
        void showList();
        void matrixToListDump();

        void dfs_euler(int v);
        void findEulerCycle(bool verbose);
        void findEulerCycle2(bool verbose);
        void findHamiltonianCycle(bool verbose);
        void findHamiltonianCycle2(bool verbose);

    protected:

    private:
        void countEdges();
        int nodeCount;
        int edgeCount;
        bool has_list;
        bool* matrix;
        int** _list;
};

#endif // GRAPH_H
