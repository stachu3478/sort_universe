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
}

int BSTNode::getHeight()
{
    if (this->height_present)
        return this->height;
    return NULL;
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

BSTNode* BSTNode::flatten()
{
    BSTNode* currentRoot = this;
    BSTNode* topRoot = this;
    bool isTop = 1;
    int length = 1;
    while (1)
    {
        BSTNode* newRoot = currentRoot->rotateRight();
        if (newRoot == currentRoot)
        {
            if (isTop)
            {
                isTop = 0;
                topRoot = currentRoot;
            };
            newRoot = currentRoot->rightChild;
            if (newRoot == NULL)
                break;
            length++;
        };
        currentRoot = newRoot;
    };
    int sizeNeeded = 2;
    while (length > sizeNeeded)
    {
        topRoot = topRoot->rotateLeft();
        currentRoot = topRoot;
        while (currentRoot->rightChild != NULL)
        {
            currentRoot = currentRoot->rightChild;
            currentRoot = currentRoot->rotateLeft();
        };
        sizeNeeded <<= 1;
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
