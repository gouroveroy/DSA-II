#include <bits/stdc++.h>
#include "Node.cpp"
using namespace std;

template <class K, class V>
class FibonacciHeap
{
    Node<K, V> *maxRoot;
    vector<vector<int>> nodeNo;
    unordered_map<V, Node<K, V> *> nodesByValue;
    int nodeCount;

    Node<K, V> *make_heap()
    {
        Node<K, V> *newNode = new Node<K, V>();
        return newNode;
    }

    void fibonacciLink(Node<K, V> *x, Node<K, V> *y)
    {
        y->left->right = y->right;
        y->right->left = y->left;

        if (x->right == x)
        {
            maxRoot = x;
        }

        y->left = y;
        y->right = y;
        y->parent = x;

        if (x->child == NULL)
        {
            x->child = y;
        }

        y->right = x->child;
        y->left = x->child->left;
        x->child->left->right = y;
        x->child->left = y;

        if (y->data.first > x->child->data.first)
        {
            x->child = y;
        }
        x->degree++;
    }

    void consolidate()
    {
        double base = (sqrt(5) + 1.0) / 2;
        int D = log(nodeCount) / log(base);
        // int D = log2(nodeCount);
        Node<K, V> *newNode = new Node<K, V>();
        vector<Node<K, V> *> auxArray(D, newNode);
        Node<K, V> *rootList = maxRoot;
        do
        {
            int degree = rootList->degree;
            while (auxArray[degree] != newNode)
            {
                Node<K, V> *other = auxArray[degree];
                if (rootList->data.first < other->data.first)
                {
                    Node<K, V> *temp = rootList;
                    rootList = other;
                    other = temp;
                }

                if (other == maxRoot)
                {
                    maxRoot = rootList;
                }

                fibonacciLink(rootList, other);

                if (rootList->right == rootList)
                {
                    maxRoot = rootList;
                }

                auxArray[degree] = newNode;
                degree++;
            }
            auxArray[degree] = rootList;
            rootList = rootList->right;
        } while (rootList != maxRoot);

        maxRoot = newNode;
        for (int i = 0; i < D; i++)
        {
            if (auxArray[i] != newNode)
            {
                auxArray[i]->left = auxArray[i];
                auxArray[i]->right = auxArray[i];
                if (maxRoot == newNode)
                {
                    maxRoot = auxArray[i];
                }

                else
                {
                    maxRoot->left->right = auxArray[i];
                    auxArray[i]->right = maxRoot;
                    auxArray[i]->left = maxRoot->left;
                    maxRoot->left = auxArray[i];
                    if (auxArray[i]->data.first > maxRoot->data.first)
                    {
                        maxRoot = auxArray[i];
                    }
                }

                if (maxRoot == newNode)
                {
                    maxRoot = auxArray[i];
                }

                else if (auxArray[i]->data.first > maxRoot->data.first)
                {
                    maxRoot = auxArray[i];
                }
            }
        }
    }

    Node<K, V> *findNodeByValue(Node<K, V> *root, V value)
    {
        Node<K, V> *max = root;
        Node<K, V> *node = NULL;
        if (value == max->data.second)
        {
            node = max;
            return node;
        }

        if (max->child != NULL)
        {
            node = findNodeByValue(max->child, value);
        }

        node = findNodeByValue(max->right, value);
        return node;
    }

    void cut(Node<K, V> *x, Node<K, V> *y)
    {
        if (x == x->right)
        {
            y->child = NULL;
        }
        x->left->right = x->right;
        x->right->left = x->left;
        if (x == y->child)
        {
            y->child = x->right;
        }
        y->degree--;
        x->left = x;
        x->right = x;
        maxRoot->left->right = x;
        x->left = maxRoot->left;
        x->right = maxRoot;
        maxRoot->left = x;
        x->parent = NULL;
        x->mark = false;
    }

    void cascadingCut(Node<K, V> *parent)
    {
        Node<K, V> *grandParent = parent->parent;
        if (grandParent != NULL)
        {
            if (parent->mark == false)
            {
                parent->mark = true;
            }

            else
            {
                cut(parent, grandParent);
                cascadingCut(grandParent);
            }
        }
    }

public:
    FibonacciHeap()
    {
        maxRoot = make_heap();
        nodeCount = 0;
    }

    bool is_empty()
    {
        return nodeCount == 0;
    }

    void insert(K key, V value)
    {
        Node<K, V> *newNode = new Node<K, V>(key, value);
        newNode->left = newNode;
        newNode->right = newNode;
        if (nodeCount == 0)
        {
            maxRoot = newNode;
        }

        else
        {
            maxRoot->left->right = newNode;
            newNode->left = maxRoot->left;
            newNode->right = maxRoot;
            maxRoot->left = newNode;
            if (newNode->data.first > maxRoot->data.first)
            {
                maxRoot = newNode;
            }
        }
        nodeCount++;
        nodesByValue[value] = newNode;
    }

    Node<K, V> *extract_max()
    {
        Node<K, V> *max = maxRoot;
        if (nodeCount != 0)
        {
            Node<K, V> *child = max->child;
            if (child != NULL)
            {
                Node<K, V> *sibling;
                Node<K, V> *mainChild = child;
                do
                {
                    sibling = child->right;
                    max->left->right = child;
                    child->right = max;
                    child->left = max->left;
                    max->left = child;
                    if (child->data.first > max->data.first)
                    {
                        max = child;
                    }
                    child->parent = NULL;
                    child = sibling;
                } while (child != mainChild);
            }
            max->left->right = max->right;
            max->right->left = max->left;
            maxRoot = max->right;

            if (max == max->right)
            {
                maxRoot = NULL;
            }

            else
            {
                maxRoot = max->right;
                consolidate();
            }
            nodeCount--;
        }
        return max;
    }

    void increase_key(V value, K newKey)
    {
        // Node<K, V> *newNode = findNodeByValue(maxRoot, value);
        Node<K, V> *newNode = nodesByValue[value];
        if (newNode != NULL)
        {
            if (newKey > newNode->data.first)
            {
                newNode->data.first = newKey;
                Node<K, V> *parent = newNode->parent;
                if (parent != NULL && newNode->data.first > parent->data.first)
                {
                    cut(newNode, parent);
                    cascadingCut(parent);
                }

                if (newNode->data.first > maxRoot->data.first)
                {
                    maxRoot = newNode;
                }
            }
        }
    }

    void Delete(V value)
    {
        if (nodesByValue.find(value) == nodesByValue.end())
        {
            return;
        }
        increase_key(value, 100001);
        extract_max();
    }

    FibonacciHeap<K, V> meld(FibonacciHeap<K, V> &heap1)
    {
        FibonacciHeap<K, V> heap;
        heap.maxRoot = maxRoot;
        heap.maxRoot->left->right = heap1.maxRoot;
        heap1.maxRoot->left->right = heap.maxRoot;
        Node<K, V> *left = heap.maxRoot->left;
        heap.maxRoot->left = heap1.maxRoot->left;
        heap1.maxRoot->left = left;
        return heap;
    }

    pair<K, V> find_max()
    {
        return maxRoot->data;
    }

    void printTree(Node<K, V> *root, int depth)
    {
        // Print the current node
        cout << "(" << root->data.first << ", " << root->data.second << ")";

        // Print children recursively
        if (root->child)
        {
            cout << " -> ";
            Node<K, V> *child = root->child;
            do
            {
                printTree(child, depth + 1);
                child = child->right;
                if (child != root->child)
                    cout << ", ";
            } while (child != root->child);
        }
    }

    void print()
    {
        if (nodeCount != 0)
        {
            Node<K, V> *rootList = maxRoot;
            int treeNum = 1;
            do
            {
                cout << "Tree " << treeNum << ": ";
                printTree(rootList, 0);
                cout << endl;
                rootList = rootList->right;
                treeNum++;
            } while (rootList != maxRoot);
        }
        else
        {
            cout << "The heap is empty." << endl;
        }
    }

    int size()
    {
        return nodeCount;
    }
};

int main()
{
    FibonacciHeap<int, int> fibHeap;
    FibonacciHeap<int, int> fibHeap2;
    fibHeap2.insert(54, 1);
    fibHeap2.insert(44, 50);
    fibHeap2.insert(34, 11);
    fibHeap2.insert(74, 9);

    fibHeap2.insert(2, 100);
    fibHeap2.insert(544, 0);


    // Insert some nodes into the Fibonacci heap
    fibHeap.insert(55, 3);
    fibHeap.insert(45, 5);
    fibHeap.insert(32, 4);
    fibHeap.insert(7, 8);

    fibHeap.insert(24, 7);
    fibHeap.insert(5, 10);
    fibHeap.extract_max();
    fibHeap.increase_key(4, 40);
    fibHeap.Delete(8);


    // Print the Fibonacci heap
    cout << fibHeap.size() << endl;
    fibHeap.print();
    cout << endl;
    fibHeap2.extract_max();
    fibHeap2.print();
    cout << endl;
    fibHeap.meld(fibHeap2);
    fibHeap.extract_max();
    fibHeap.print();

    return 0;
}
