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

        void setValue(int val) { this->value = val; };
        int getValue() { this->value; };
        void setLeftChild(BSTNode* val) { this->leftChild = val; };
        void setRightChild(BSTNode* val) { this->rightChild = val; };
        BSTNode* getLeftChild() { return this->leftChild; };
        BSTNode* getRightChild() { return this->rightChild; };
        int getHeight();

        bool opeator==(BSTNode* val) { return this->value == val->value; };
        bool opeator>(BSTNode* val) { return this->value > val->value; };
        bool opeator<(BSTNode* val) { return this->value < val->value; };
        bool opeator>=(BSTNode* val) { return this->value >= val->value; };
        bool opeator<=(BSTNode* val) { return this->value <= val->value; };

        void preOrderVerbose();
        void inOrderVerbose();
        void postOrderVerbose();
        // TODO wypisanie sciezki poszukiwania
        BSTNode* getLeast(bool verbose);
        BSTNode* getLeast() { return this->getLeast(false); };
        BSTNode* getHighest(bool verbose);
        BSTNode* getHighest() { return this->getHighest(false); };

        BSTNode* findChild(int targetValue);
        BSTNode* removeChild(int targetValue);

        BSTNode* nearestLower() { return this->leftChild->getHighest(); };
        BSTNode* nearestHigher() { return this->rightChild->getLeast(); };
        void rotateLeft();
        void rotateRight();

        void flatten();

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
