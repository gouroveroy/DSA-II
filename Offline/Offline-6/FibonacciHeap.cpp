#include <bits/stdc++.h>
#include "Node.cpp"
using namespace std;

/* The code snippet provided defines a C++ template class `FibonacciHeap` that represents a Fibonacci
Heap data structure. Here is a breakdown of the key components of the class: */
template <class K, class V>
class FibonacciHeap
{
    Node<K, V> *maxRoot;
    unordered_map<V, Node<K, V> *> nodesByValue;
    int nodeCount;

    /**
     * The function "make_heap" creates a new Node object and returns a pointer to it.
     * 
     * @return A pointer to a newly created Node object is being returned.
     */
    Node<K, V> *make_heap()
    {
        Node<K, V> *newNode = new Node<K, V>();
        return newNode;
    }

    /**
     * The function `fibonacciLink` is used to link two nodes in a Fibonacci heap data structure.
     * 
     * @param x Node<K, V> pointer representing the parent node in a Fibonacci heap.
     * @param y In the given code snippet, the parameter `y` is a pointer to a Node object of type
     * `Node<K, V>`. This function `fibonacciLink` is used to perform a Fibonacci heap linking
     * operation between two nodes `x` and `y`.
     */
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

    /**
     * The function `consolidate` consolidates nodes in a Fibonacci heap data structure.
     */
    void consolidate()
    {
        double base = (sqrt(5) + 1.0) / 2;
        int D = log(nodeCount) / log(base);
        vector<Node<K, V> *> auxArray(D, NULL);
        Node<K, V> *rootList = maxRoot;
        do
        {
            int degree = rootList->degree;
            while (auxArray[degree] != NULL)
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

                auxArray[degree] = NULL;
                degree++;
            }
            auxArray[degree] = rootList;
            rootList = rootList->right;
        } while (rootList != maxRoot);

        maxRoot = NULL;
        for (int i = 0; i < D; i++)
        {
            if (auxArray[i] != NULL)
            {
                auxArray[i]->left = auxArray[i];
                auxArray[i]->right = auxArray[i];
                if (maxRoot == NULL)
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

                if (maxRoot == NULL)
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

    /**
     * The cut function removes a node from a Fibonacci heap and adjusts the pointers accordingly.
     * 
     * @param x Node<K, V> *x is a pointer to a node in a data structure.
     * @param y In the provided code snippet, the parameter `y` is a pointer to a Node object of type
     * `Node<K, V>`. It is used within the `cut` function to perform certain operations on the node `y`
     * and its child nodes.
     */
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

    void printTree(Node<K, V> *root)
    {
        if (root == NULL || root->child == NULL)
        {
            return;
        }
        Node<K, V> *children = root->child;
        do
        {
            cout << "(" << children->data.first << "," << children->data.second << ")";
            if (children->right != root->child)
            {
                cout << ", ";
            }
            children = children->right;
        } while (children != root->child);
        cout << endl;
        do
        {
            if (children->child != NULL)
            {
                cout << "        (" << children->data.first << "," << children->data.second << ") -> ";
                printTree(children);
            }
            children = children->right;
        } while (children != root->child);
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

    pair<K, V> extract_max()
    {
        if (nodeCount == 0)
        {
            return {numeric_limits<K>::min(), V()};
        }

        Node<K, V> *max = maxRoot;
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
        nodesByValue.erase(max->data.second);
        return max->data;
    }

    void increase_key(V value, K newKey)
    {
        if (nodesByValue.find(value) == nodesByValue.end())
        {
            cout << "Key is not found" << endl;
            return;
        }
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

            else if (newKey < newNode->data.first)
            {
                cout << "Key is not greater than the previous key" << endl;
            }

            else
            {
                cout << "Key is same as the previous key" << endl;
            }
        }
    }

    void Delete(V value)
    {
        if (nodesByValue.find(value) == nodesByValue.end())
        {
            cout << "Key is not found" << endl;
            return;
        }
        increase_key(value, numeric_limits<K>::max());
        extract_max();
        nodesByValue.erase(value);
    }

    FibonacciHeap<K, V> meld(FibonacciHeap<K, V> &heap1)
    {
        FibonacciHeap<K, V> heap;

        if (maxRoot == NULL)
        {
            return heap1;
        }

        if (heap1.maxRoot == NULL)
        {
            return *this;
        }

        Node<K, V> *leftMaxRoot = maxRoot->left;
        Node<K, V> *rightMaxRoot = heap1.maxRoot->left;

        leftMaxRoot->right = heap1.maxRoot;
        heap1.maxRoot->left = leftMaxRoot;

        rightMaxRoot->right = maxRoot;
        maxRoot->left = rightMaxRoot;

        if (heap1.maxRoot->data.first > maxRoot->data.first)
        {
            heap.maxRoot = heap1.maxRoot;
        }
        else
        {
            heap.maxRoot = maxRoot;
        }

        heap.nodeCount = nodeCount + heap1.nodeCount;
        heap.nodesByValue.insert(heap1.nodesByValue.begin(), heap1.nodesByValue.end());
        return heap;
    }

    pair<K, V> find_max()
    {
        return maxRoot->data;
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
                cout << "(" << rootList->data.first << "," << rootList->data.second << ")";
                if (rootList->child != NULL)
                {
                    cout << " -> ";
                }
                printTree(rootList);
                if (rootList->child == NULL)
                {
                    cout << endl;
                }
                rootList = rootList->right;
                treeNum++;
            } while (rootList != maxRoot);
        }
        else
        {
            cout << "Priority queue is empty." << endl;
        }
    }

    int size()
    {
        return nodeCount;
    }
};
