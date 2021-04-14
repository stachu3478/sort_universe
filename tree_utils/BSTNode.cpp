#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "BSTNode.h"

using namespace std;

void skip(auto a){};

BSTNode::BSTNode()
{
    this->leftChild = NULL;
    this->rightChild = NULL;
}

BSTNode::BSTNode(int val)
{
    this->value = val;
    this->leftChild = NULL;
    this->rightChild = NULL;
    this->height = 1;
    this->height_present = 1;
}

void BSTNode::_insert(int val) // not tested
{
    BSTNode* target;
    bool larger = val > this->value;
    if (larger)
        target = this->rightChild;
    else
        target = this->leftChild;
    if (target == NULL)
    {
        target = new BSTNode(val);
        if (larger)
            this->rightChild = target;
        else
            this->leftChild = target;
    }
    else
        target->_insert(val);
    if (this->height <= target->getHeight())
        this->height = target->getHeight() + 1;
    this->height_present = 1;
}

BSTNode::BSTNode(int* arr, int length)
{
    this->leftChild = NULL;
    this->rightChild = NULL;
    if (length > 0)
    {
        this->value = arr[0];
        this->height = 0;
        this->height_present = 1;
    }
    for (int i = 1; i < length; i++)
        this->_insert(arr[i]);
}

BSTNode* BSTNode::avlFromSorted(int* arr, int length)
{
    int mid = length / 2;
    int height, leftHeight = 0, rightHeight = 0;
    BSTNode* root = new BSTNode(arr[mid]);
    if (mid > 0)
    {
        root->leftChild = BSTNode::avlFromSorted(arr, mid);
        leftHeight += root->leftChild->getHeight();
    } else root->leftChild = NULL;
    if (length - mid - 1 > 0)
    {
        root->rightChild = BSTNode::avlFromSorted(arr + mid + 1, length - mid - 1);
        rightHeight += root->rightChild->getHeight();
    } else root->rightChild = NULL;
    if (leftHeight > rightHeight)
        height = leftHeight;
    else height = rightHeight;
    root->height = height;
    root->height_present = 1;
    return root;
}

int BSTNode::getHeight()
{
    if (this->height_present)
        return this->height;
    return 0;
}

void BSTNode::preOrderVerbose()
{
    cout << this->value << endl;
    if (this->leftChild != NULL) this->leftChild->preOrderVerbose();
    if (this->rightChild != NULL) this->rightChild->preOrderVerbose();
}

void BSTNode::inOrderVerbose()
{
    if (this->leftChild != NULL) this->leftChild->inOrderVerbose();
    cout << this->value << endl;
    if (this->rightChild != NULL) this->rightChild->inOrderVerbose();
}

void BSTNode::postOrderVerbose()
{
    if (this->leftChild != NULL) this->leftChild->postOrderVerbose();
    if (this->rightChild != NULL) this->rightChild->postOrderVerbose();
    cout << this->value << endl;
}

void BSTNode::preOrderCycle()
{
    skip(this->value);
    if (this->leftChild != NULL) this->leftChild->preOrderCycle();
    if (this->rightChild != NULL) this->rightChild->preOrderCycle();
}

void BSTNode::inOrderCycle()
{
    if (this->leftChild != NULL) this->leftChild->inOrderCycle();
    skip(this->value);
    if (this->rightChild != NULL) this->rightChild->inOrderCycle();
}

void BSTNode::postOrderCycle()
{
    if (this->leftChild != NULL) this->leftChild->postOrderCycle();
    if (this->rightChild != NULL) this->rightChild->postOrderCycle();
    this->value;
}



BSTNode* BSTNode::getLeast(bool verbose)
{
    if (verbose)
        cout << this->value << endl;
    if (this->leftChild != NULL)
        return this->leftChild->getLeast(verbose);
    return this;
}

BSTNode* BSTNode::getHighest(bool verbose)
{
    if (verbose)
        cout << this->value << endl;
    if (this->rightChild != NULL)
        return this->rightChild->getHighest(verbose);
    return this;
}

BSTNode* BSTNode::findChild(int targetValue, bool parent)
{
    if (parent)
        return this->findParent(targetValue);
    return this->findChild(targetValue);
}

BSTNode* BSTNode::findChild(int targetValue)
{
    if (targetValue < this->value)
    {
        if (this->leftChild != NULL)
            return this->leftChild->findChild(targetValue);
        return NULL;
    } else if (targetValue > this->value)
    {
        if (this->rightChild != NULL)
            return this->rightChild->findChild(targetValue);
        return NULL;
    }
    return this;
}

BSTNode* BSTNode::findParent(int targetValue)
{
    if (
        (this->rightChild != NULL && this->rightChild->getValue() == targetValue)
        || (this->leftChild != NULL && this->leftChild->getValue() == targetValue)
    ) return this;
    if (targetValue < this->value)
    {
        if (this->leftChild != NULL)
            return this->leftChild->findChild(targetValue);
        return NULL;
    } else if (targetValue > this->value)
    {
        if (this->rightChild != NULL)
            return this->rightChild->findChild(targetValue);
        return NULL;
    }
    return NULL;
}

BSTNode* BSTNode::removeChild(int targetValue)
{
    BSTNode* parent = this->findChild(targetValue, 1);
    BSTNode* removed;
    if (parent == NULL) return NULL;
    if (parent->leftChild != NULL && parent->leftChild->value == targetValue) {
        removed = parent->leftChild;
        BSTNode* neigh = removed->getHighest();
        if (neigh == removed)
            parent->leftChild = NULL;
        else
            parent->leftChild = neigh;
    } else
    {
        removed = parent->rightChild;
        BSTNode* neigh = removed->getLeast();
        if (neigh == removed)
            parent->rightChild = NULL;
        else
            parent->rightChild = neigh;
    }
    /*while (removed->rightChild)
        parent = removed->rotateLeft();
    while (removed->leftChild)
        parent = removed->rotateRight();*/
    //if (removed->rightChild || removed->leftChild)
    //    cout << "Still sucks" << endl;
    //if (parent->rightChild != removed)
    //    cout << "Sucks even more" << endl;
    if (removed->value != targetValue)
        cout << "If i suck, everybody sucks" << endl;
    //parent->rightChild = NULL;
    return removed;
}

BSTNode* BSTNode::rotateLeft()
{
    if (this->rightChild == NULL) return this;
    BSTNode* right = this->rightChild;
    BSTNode* a = right->leftChild;
    this->rightChild = a;
    right->leftChild = this;
    return right;
}

BSTNode* BSTNode::rotateRight()
{
    if (this->leftChild == NULL) return this;
    BSTNode* left = this->leftChild;
    BSTNode* a = left->rightChild;
    this->leftChild = a;
    left->rightChild = this;
    return left;
}

BSTNode* BSTNode::linify()
{
    BSTNode* newRoot = this->rotateRight();
    while (newRoot->getLeftChild() != NULL)
        newRoot = newRoot->rotateRight();
    BSTNode* parRoot = newRoot;
    BSTNode* childRoot = newRoot->rightChild;
    int height = 0;
    while (childRoot != NULL)
    {
        while (childRoot->leftChild != NULL)
            childRoot = childRoot->rotateRight();
        parRoot->rightChild = childRoot;
        parRoot = childRoot;
        childRoot = childRoot->rightChild;
        height++;
    }
    newRoot->height = height;
    return newRoot;
}

BSTNode* BSTNode::compressionCycle(int skips)
{
    BSTNode* topRoot = this;
    if (skips > 0)
        topRoot = topRoot->rotateLeft();
    BSTNode* currentRoot = topRoot;
    BSTNode* prevRoot = topRoot;
    for (int i = 1; i < skips; i++)
    {
        currentRoot = currentRoot->rightChild->rotateLeft();
        prevRoot->rightChild = currentRoot;
        prevRoot = currentRoot;
    }
    return topRoot;
}

BSTNode* BSTNode::flatten()
{
    BSTNode* topRoot = this->linify();
    int length = topRoot->height;
    int a1 = (length >> 1) + 1;
    while (a1 != (a1 | (a1 >> 1)))
        a1 |= a1 >> 1;
    topRoot = topRoot->compressionCycle(length - a1);
    while (a1 > 1)
    {
        a1 >>= 1;
        topRoot = topRoot->compressionCycle(a1);
    }
    return topRoot;
}

BSTNode::~BSTNode()
{
    if (this->leftChild != NULL)
        delete this->leftChild;
    if (this->rightChild != NULL)
        delete this->rightChild;
}
