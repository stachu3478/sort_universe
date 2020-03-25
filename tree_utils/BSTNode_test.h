#ifndef BSTNODE_TEST_H_INCLUDED
#define BSTNODE_TEST_H_INCLUDED

#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include "BSTNode.h"
#include "../array_generators/random/random.h"
#include "../sort_algorithms/bubble/bubble.h"
#include "../array_generators/down_to_up/down_to_up.h"

using namespace std;

int BSTNode_test()
{
    cout << "> Empty comstructor" << endl;
    BSTNode* node = new BSTNode();
    if (node->getValue() != NULL) return 1;
    if (node->getRightChild() != NULL) return 1;
    if (node->getLeftChild() != NULL) return 1;
    cout << "> Single value constructor" << endl;
    int val1 = rand();
    node = new BSTNode(val1);
    if (node->getValue() != val1) return 1;
    if (node->getRightChild() != NULL) return 1;
    if (node->getLeftChild() != NULL) return 1;
    cout << "> Array constructor" << endl;
    cout << "Root should have one of the array values" << endl;
    int arr = random_list(100);
    node = new BSTNode(arr, 100);
    int root = node->getValue();
    bool found = 0;
    for (int i = 0; i < 100; i++)
        if (root == arr[i])
            found = 1;
    if (!found) return 1;
    cout << "Should have at least one child" << endl;
    if (node->getLeftChild() == NULL && node->getRightChild() == NULL) return 1;
    cout << "> Value setting & getting" << endl;
    int val2 = rand();
    node = new BSTNode();
    node->setValue(val2);
    if (node->getValue() != val2) return 1;
    cout << "> Left child get & set" << endl;
    BSTNode* node1 = new BSTNode();
    BSTNode* node2 = new BSTNode();
    node1->setLeftChild(node2);
    if (node1->getLeftChild() != node2) return 1;
    cout << "> Right child get & set" << endl;
    BSTNode* node3 = new BSTNode();
    BSTNode* node4 = new BSTNode();
    node3->setRightChild(node4);
    if (node3->getRightChild() != node4) return 1;
    cout << "> Proper height measurement" << endl;
    // TODO
    cout << "> Proper comparison" << endl;
    cout << "Equal" << endl;
    int val3 = rand();
    BSTNode* node5 = new BSTNode(val);
    BSTNode* node6 = new BSTNode(val);
    if (node5 != node6) return 1;
    cout << "Different" << endl;
    node6 = new BSTNode(val + rand() + 1);
    if (node5 == node6) return 1;
    cout << "Higher" << endl;
    if (node5 > node6) return 1;
    if (node5 >= node6) return 1;
    if (node6 < node5) return 1;
    if (node6 <= node5) return 1;
    if (!(node6 > node5)) return 1;
    if (!(node6 >= node5)) return 1;
    if (!(node5 < node6)) return 1;
    if (!(node5 <= node6)) return 1;
    cout << "> Proper least element" << endl;
    arr = random_list(100);
    int random_sub = -rand();
    arr[rand() % 100] = random_sub;
    node = new BSTNode(arr, 100);
    if (node->getLeast()->getValue() != random_sub) return 1;
    cout << "> Proper highest element" << endl;
    arr = random_list(100);
    int random_over = INT_MAX - rand();
    arr[rand() % 100] = random_over;
    node = new BSTNode(arr, 100);
    if (node->getHighest()->getValue() != random_over) return 1;
    cout << "> AVL constructor" << endl;
    for (int i = 0; i < 10; i++)
    {
        int* rand_arr = bubble_sort(random_list(3));
        node = BSTNode::avlFromSorted(rand_arr, 3);
        if (node->getLeftChild() == NULL || node->getRightChild() == NULL) return 1;
    }
    cout << "> Finding child from value" << endl;
    arr = random_list(100);
    random_over = INT_MAX - rand();
    node = new BSTNode(arr, 100);
    for (int i = 0; i < 100; i++)
    {
        if (node->findChild(arr[i]) == NULL) return 1;
    }
    if (node->findChild(random_over) != NULL) return 1;
    cout << "> Removing child from value" << endl;
    for (int i = 0; i < 100; i++)
    {
        node->removeChild(arr[i]); // TODO do it better
        if (node->findChild(arr[i]) != NULL) return 1;
    }
    cout << "> Left neigh" << endl;
    arr = down_to_up(100);
    node = new BSTNode(arr, 100);
    for (int i = 1; i < 100; i++)
    {
        if (node->nearestLower(arr[i]) != arr[i - 1]) return 1;
    }
    cout << "> Right neigh" << endl;
    arr = down_to_up(100);
    node = new BSTNode(arr, 100);
    for (int i = 0; i < 99; i++)
    {
        if (node->nearestLower(arr[i]) != arr[i + 1]) return 1;
    }
    cout << "> Rotating left" << endl;
    arr = down_to_up(100);
    node = BSTNode::avlFromSorted(arr, 100);
    BSTNode* node_l = node->getLeftChild();
    BSTNode* node_r = node->getRightChild();
    node->rotateLeft();
    if (node->getLeftChild() != node_l) return 1;
    if (node->getRightChild() == node_r) return 1;
    if (node_r->getLeftChild() != node) return 1;
    cout << "> Rotating right" << endl;
    arr = down_to_up(100);
    node = BSTNode::avlFromSorted(arr, 100);
    node_l = node->getLeftChild();
    node_r = node->getRightChild();
    node->rotateRight();
    if (node->getLeftChild() == node_l) return 1;
    if (node->getRightChild() != node_r) return 1;
    if (node_l->getRightChild() != node) return 1;
    cout << "> Flattening" << endl;
    // TODO hmmm
    return 0;
}

#endif // BSTNODE_TEST_H_INCLUDED