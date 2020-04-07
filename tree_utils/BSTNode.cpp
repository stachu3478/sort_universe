#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "BSTNode.h"

using namespace std;

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
        this->height = 1;
        this->height_present = 1;
    }
    for (int i = 1; i < length; i++)
        this->_insert(arr[i]);
}

BSTNode* BSTNode::avlFromSorted(int* arr, int length)
{
    int mid = length / 2;
    int height, leftHeight = 1, rightHeight = 1;
    BSTNode* root = new BSTNode(arr[mid]);
    if (mid > 0)
    {
        root->leftChild = BSTNode::avlFromSorted(arr, mid);
        leftHeight += root->leftChild->getHeight();
    }
    if (length - mid - 1 > 0)
    {
        root->rightChild = BSTNode::avlFromSorted(arr + mid + 1, length - mid - 1);
        rightHeight += root->rightChild->getHeight();
    }
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
    {
        if (
            (this->rightChild != NULL && this->rightChild->getValue() == targetValue)
            || (this->leftChild != NULL && this->leftChild->getValue() == targetValue)
        ) return this;
    }
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
    if (!parent)
        return this;
    return NULL;
}

BSTNode* BSTNode::findChild(int targetValue)
{
    return findChild(targetValue, 0);
}

BSTNode* BSTNode::removeChild(int targetValue)
{
    BSTNode* parent = NULL;
    BSTNode* child = this;
    BSTNode* removedChild = this;
    int choiceState = 0;
    while (1)
    {
        if (targetValue < child->value)
        {
            if (child->leftChild != NULL)
            {
                parent = child;
                child = child->leftChild;
                choiceState = -1;
            }
            else return NULL;
        } else if (targetValue > child->value)
        {
            if (child->rightChild != NULL)
            {
                parent = child;
                child = child->rightChild;
                choiceState = 1;
            }
            else return NULL;
        } else break;
    }
    bool leftOrRight = rand() % 2;
    BSTNode* first;
    BSTNode* second;
    removedChild = child;
    if (leftOrRight)
    {
        first = child->leftChild;
        second = child->rightChild;
    } else
    {
        first = child->rightChild;
        second = child->leftChild;
    }
    if (first != NULL)
    {
        child = first;
    } else if (second != NULL)
    {
        child = second;
    } else child = NULL;
    if (choiceState == 1)
    {
        parent->rightChild = child;
    } else if (choiceState == -1)
    {
        parent->leftChild = child;
    }
    return removedChild;
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
    if (newRoot->rightChild != NULL)
    {
        newRoot->rightChild = newRoot->rightChild->linify();
        newRoot->height = newRoot->rightChild->height + 1;
    }
    else
        newRoot->height = 1;
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
    int sizeNeeded = 2;
    int a1 = length / 2 + 1;
    while (a1 != (a1 = (a1 | (a1 >> 1))));
    topRoot = topRoot->compressionCycle(length - a1);
    while (a1 > 1)
    {
        a1 /= 2;
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
