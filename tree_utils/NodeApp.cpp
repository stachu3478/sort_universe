#include <iostream>
#include <iomanip>
#include <time.h>

#include "NodeApp.h"
#include "BSTNode.h"
#include "../array_generators/down_to_up/down_to_up.h"
#include "../array_generators/random/random.h"
#include "../utils/is_down_to_up.h"

using namespace std;

class ClockNotStartedException {};
class MyClock
{
    public:
        MyClock()
        {
            started = 0;
        };
        void start()
        {
            time = clock();
            started = 1;
        };
        bool has_started() { return started; };
        void reset() { started = 0; };
        void stop() { time = clock() - time; };
        int get_time() { return time; };
    private:
        clock_t time;
        bool started;
};

typedef void measured_algorithm(int val, MyClock* s);

int safeReadInteger()
{
    int value;
    while (!(cin >> value))
    {
        cout << "Failed to read a number, try again.\n";
        cin.clear();
        cin.ignore();
    }
    return value;
}

int safeReadLength()
{
    cout << "Type length of the array\n";
    int length = safeReadInteger();
    while (length < 1)
    {
        cout << "Length should be positive, try again.\n";
        length = safeReadInteger();
    };
    return length;
}

int* type_array(int length)
{
	int* arr = new int[length];
	for (int i = 0; i < length; i++)
	{
		cout << "Give " << i << ". element" << endl;
		arr[i] = safeReadInteger();
	};
	return arr;
}

int* typeSafeDownToUpArray(int length)
{
    int* arr = type_array(length);
    while (!is_down_to_up(arr, length))
    {
        cout << "The array is not sorted properly. Try again." << endl;
        arr = type_array(length);
    };
    return arr;
}

bool checkRoot(BSTNode* root)
{
    if (root == NULL)
    {
        cout << "Good computing! The root node is nullified!\n";
        return 1;
    };
    return 0;
};

void fastMeasure(measured_algorithm alg)
{
    int instanceType = 0,
        baseSize = 1,
        threshold = 100,
        delta = 10,
        measurements = 10;
    MyClock* clk = new MyClock();

    cout << setw(10) << "Size" << setw(2) << "|" << setw(15) << "Average time (ms)\n";
    cout << string(35, '-') << endl;

    cout << fixed << setprecision(1);

    double output_time = 0;
    int inc = baseSize;
    while (measurements > 0)
    {
        if (output_time < 10)
        {
            baseSize *= 10;
            inc = baseSize;
        }
        else
            baseSize += inc;
        measurements--;
        int alg_time = 0;
        for (int i = 0; i < 10; i++)
        {
            clk->reset();
            alg(baseSize, clk);
            if (!clk->has_started()) throw new ClockNotStartedException();
            alg_time += clk->get_time();
        }
        output_time = (double)alg_time / 10;
        cout << setw(10) << baseSize << setw(2) << "|" << setw(10) << output_time << endl;
    };
};

void buildAVL(int s, MyClock* c)
{
    int* arr = down_to_up(s);
    c->start();
    BSTNode* root = BSTNode::avlFromSorted(arr, s);
    c->stop();
    delete root;
}

void buildBST(int s, MyClock* c)
{
    int* arr = random_list(s);
    c->start();
    BSTNode* root = new BSTNode(arr, s);
    c->stop();
    delete root;
}

void findLeastAVL(int s, MyClock* c)
{
    BSTNode* root = BSTNode::avlFromSorted(down_to_up(s), s);
    c->start();
    root->getLeast();
    c->stop();
    delete root;
}

void findLeastBST(int s, MyClock* c)
{
    BSTNode* root = new BSTNode(random_list(s), s);
    c->start();
    root->getLeast();
    c->stop();
    delete root;
}

void verboseAVL(int s, MyClock* c)
{
    BSTNode* root = BSTNode::avlFromSorted(down_to_up(s), s);
    c->start();
    root->inOrderVerbose();
    c->stop();
    delete root;
}

void verboseBST(int s, MyClock* c)
{
    BSTNode* root = new BSTNode(random_list(s), s);
    c->start();
    root->inOrderVerbose();
    c->stop();
    delete root;
}

void flattenBST(int s, MyClock* c)
{
    BSTNode* root = new BSTNode(random_list(s), s);
    c->start();
    root->flatten();
    c->stop();
    delete root;
}

NodeApp::NodeApp()
{
    BSTNode* root;
    while (1)
    {
        int alg_type = 0;
        cout<< "Choose an operation on node trees or exit:\n"
        << "1. Generate AVL from generated sorted list\n"
        << "2. Generate AVL from typed sorted list\n"
        << "3. Generate BST from generated random list\n"
        << "4. Generate BST from typed list\n"
        << "5. Find least element\n"
        << "6. Find highest element\n"
        << "7. Remove elements from tree\n"
        << "8. Output elements pre-order\n"
        << "9. Output elements in-order\n"
        << "10. Delete root\n"
        << "11. Flatten tree through rotations\n"
        << "12. AVL building time measurement\n"
        << "13. BST building time measurement\n"
        << "14. Finding least element in AVL time measurement\n"
        << "15. Finding least element in BST time measurement\n"
        << "16. Output from AVL in-order measurement\n"
        << "17. Output from BST in-order measurement\n"
        << "18. BST tree flattening time measurement\n"
        << "0. Exit\n";
        cin >> alg_type;

        switch (alg_type)
        {
            case 1:
                {
                    int length = safeReadLength();
                    root = BSTNode::avlFromSorted(down_to_up(length), length);
                    cout << "[i] Height: " << root->getHeight() << endl;
                }
                break;
            case 2:
                {
                    int length = safeReadLength();
                    root = BSTNode::avlFromSorted(type_array(length), length);
                    cout << "[i] Height: " << root->getHeight() << endl;
                }
                break;
            case 3:
                {
                    int length = safeReadLength();
                    root = new BSTNode(down_to_up(length), length);
                    cout << "[i] Height: " << root->getHeight() << endl;
                }
                break;
            case 4:
                {
                    int length = safeReadLength();
                    root = new BSTNode(type_array(length), length);
                    cout << "[i] Height: " << root->getHeight() << endl;
                }
                break;
            case 5:
                {
                    if (checkRoot(root)) break;
                cout << "<root> ";
                BSTNode* found = root->getLeast(true);
                cout << "\b <end>\n";
                }
                break;
            case 6:
                {
                    if (checkRoot(root)) break;
                cout << "<root> ";
                BSTNode* found = root->getHighest(true);
                cout << "\b <end>\n";
                }
                break;
            case 7:
                {
                    if (checkRoot(root)) break;
                cout << "Asking for array of elements to be removed.\n";
                int length = safeReadLength();
                int* arr = type_array(length);
                for (int i = 0; i < length; i++)
                {
                    if (root->getValue() == arr[i])
                    {
                        if (root->getLeftChild() != NULL)
                            root->rotateRight();
                        else if (root->getRightChild() != NULL)
                            root->rotateLeft();
                        else
                        {
                            cout << "[i] The root node has been removed. Value: " << arr[i] << endl;
                            root = NULL;
                            break;
                        }
                        cout << "[i] The root node has been moved due to its removal.\n";
                    };
                    BSTNode* removed = root->removeChild(arr[i]);
                    if (removed != NULL)
                        cout << "[i] Node removed. Value: " << arr[i] << endl;
                    else
                        cout << "[i] Node not found. Value: " << arr[i] << endl;
                };
                }
                break;
            case 8:
                {
                    if (checkRoot(root)) break;
                cout << "<root> ";
                root->preOrderVerbose();
                cout << "\b <end>\n";
                }
                break;
            case 9:
                {
                    if (checkRoot(root)) break;
                cout << "<root> ";
                root->inOrderVerbose();
                cout << "\b <end>\n";
                }
                break;
            case 10:
                {
                    if (checkRoot(root)) break;
                delete root;
                cout << "[i] The root node has been removed. Don't try to compute it in the future.\n";
                }
                break;
            case 11:
                {
                    if (checkRoot(root)) break;
                BSTNode* newRoot = root->flatten();
                cout << "[i] Root node has been flattened\n";
                if (newRoot == root)
                    cout << "[i] The root node has not changed\n";
                else
                    cout << "[i] The root node has changed\n";
                }
                break;
            case 12: fastMeasure(buildAVL); break;
            case 13: fastMeasure(buildBST); break;
            case 14: fastMeasure(findLeastAVL); break;
            case 15: fastMeasure(findLeastBST); break;
            case 16: fastMeasure(verboseAVL); break;
            case 17: fastMeasure(verboseBST); break;
            case 18: fastMeasure(flattenBST); break;
            case 0: return;
            default: cout << "Work in progress.\n";
        };
    };
}

NodeApp::~NodeApp()
{
    //dtor
}
