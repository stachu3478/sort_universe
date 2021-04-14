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

        void createEdge(int fromNode, int toNode);
        void createAcyclicEdges();

        void matrixBreadthVerbose();
        void matrixDepthVerbose();
        void listBreadthVerbose();
        void listDepthVerbose();
        void tableBreadthVerbose();
        void tableDepthVerbose();

        void showMatrix();
        void showList();
        void showTable();

        int* matrixBreadthSort();
        int* matrixDepthSort();
        int* listBreadthSort();
        int* listDepthSort();
        int* tableBreadthSort();
        int* tableDepthSort();

        void matrixToListDump();
        void matrixToTableDump();

    protected:

    private:
        void countEdges();
        int nodeCount;
        int edgeCount;
        bool* matrix;
        int** _list;
        int** table;
        bool hasTable;
        bool hasList;
        bool hasMatrix;
};

#endif // GRAPH_H
