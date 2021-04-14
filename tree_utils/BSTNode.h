#ifndef BSTNODE_H
#define BSTNODE_H

class BSTNode
{
    public:
        /** Default constructor */
        BSTNode();
        BSTNode(int val);
        BSTNode(int* arr, int length);
        static BSTNode* avlFromSorted(int* arr, int length);
        /** Default destructor */
        virtual ~BSTNode();

        void _insert(int val);
        void setValue(int val) { this->value = val; };
        int getValue() { return this->value; };
        void setLeftChild(BSTNode* val) { this->leftChild = val; };
        void setRightChild(BSTNode* val) { this->rightChild = val; };
        BSTNode* getLeftChild() { return this->leftChild; };
        BSTNode* getRightChild() { return this->rightChild; };
        int getHeight();

        void preOrderVerbose();
        void inOrderVerbose();
        void postOrderVerbose();
        void preOrderCycle();
        void inOrderCycle();
        void postOrderCycle();
        // TODO wypisanie sciezki poszukiwania
        BSTNode* getLeast(bool verbose);
        BSTNode* getLeast() { return this->getLeast(false); };
        BSTNode* getHighest(bool verbose);
        BSTNode* getHighest() { return this->getHighest(false); };

        BSTNode* findParent(int targetValue);
        BSTNode* findChild(int targetValue);
        BSTNode* findChild(int targetValue, bool parent);
        BSTNode* removeChild(int targetValue);

        BSTNode* rotateLeft();
        BSTNode* rotateRight();

        BSTNode* linify();
        BSTNode* compressionCycle(int skips);
        BSTNode* flatten();

    protected:

    private:
        // TODO Zmierz wysokosc drzewa podczas tworzenia BST
        int value;

        int height;
        bool height_present;

        BSTNode* leftChild;
        BSTNode* rightChild;
};

#endif // BSTNODE_H
