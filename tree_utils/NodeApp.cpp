#include <iostream>
#include <iomanip>
#include <time.h>

#include "NodeApp.h"
#include "BSTNode.h"
#include "../array_generators/down_to_up/down_to_up.h"
#include "../array_generators/random/random.h"
#include "../utils/is_down_to_up.h"
#include "../read_utils.h"

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
    int baseSize = 1,
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

// x1 000 000
void findLeastAVL(int s, MyClock* c)
{
    BSTNode* root = BSTNode::avlFromSorted(down_to_up(s, 1, 1), s);
    c->start();
    for (int i = 0; i < 1000000; i++)
        root->getLeast();
    c->stop();
    delete root;
}

// x1 000 000
void findLeastBST(int s, MyClock* c)
{
    BSTNode* root = new BSTNode(random_list(s), s);
    c->start();
    for (int i = 0; i < 1000000; i++)
        root->getLeast();
    c->stop();
    delete root;
}

// x100
void verboseAVL(int s, MyClock* c)
{
    BSTNode* root = BSTNode::avlFromSorted(down_to_up(s), s);
    c->start();
    for (int i = 0; i < 100; i++)
        root->inOrderCycle();
    c->stop();
    delete root;
}

// x100
void verboseBST(int s, MyClock* c)
{
    BSTNode* root = new BSTNode(random_list(s), s);
    c->start();
    for (int i = 0; i < 100; i++)
        root->inOrderCycle();
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
        << "14. Finding least element in AVL time measurement x1 000 000\n"
        << "15. Finding least element in BST time measurement x1 000 000\n"
        << "16. Output from AVL in-order measurement x100\n"
        << "17. Output from BST in-order measurement x100\n"
        << "18. BST tree flattening time measurement\n"
        << "0. Exit\n";
        cin >> alg_type;

        switch (alg_type)
        {
            case 1:
            {
                    int length = safeReadLength();
                    root = BSTNode::avlFromSorted(down_to_up(length, 1, 1), length);
                    cout << "[i] Height: " << root->getHeight() << endl;
            }
                break;
            case 2:
            {
                    int length = safeReadLength();
                    root = BSTNode::avlFromSorted(typeSafeDownToUpArray(length), length);
                    cout << "[i] Height: " << root->getHeight() << endl;
            }
                break;
            case 3:
            {
                    int length = safeReadLength();
                    root = new BSTNode(random_list(length), length);
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
                cout << "<root>\n";
                root->getLeast(true);
                cout << " <end>\n";
            }
                break;
            case 6:
            {
                    if (checkRoot(root)) break;
                cout << "<root>\n";
                root->getHighest(true);
                cout <<  " <end>\n";
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
                cout << "<start>\n";
                root->preOrderVerbose();
                cout << " <end>\n";
            }
                break;
            case 9:
            {
                    if (checkRoot(root)) break;
                cout << "<root>\n";
                root->inOrderVerbose();
                cout << " <end>\n";
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
                root = newRoot;
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
