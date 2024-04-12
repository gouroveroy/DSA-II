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

    /**
     * The cascadingCut function recursively marks and cuts nodes in a Fibonacci heap to maintain the
     * heap structure.
     * 
     * @param parent A pointer to the parent node in a tree structure.
     */
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

    /**
     * The function `printTree` recursively prints the nodes of a tree structure starting from the
     * given root node.
     * 
     * @param root The `printTree` function you provided is a recursive function that prints the nodes
     * of a tree structure. The `root` parameter is a pointer to the root node of the tree. The
     * function first prints the children of the root node in a circular doubly linked list fashion,
     * and then recursively prints the
     * 
     * @return The `printTree` function returns `void`, which means it does not return any value. It is
     * a function used for printing the contents of a tree structure.
     */
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
    /**
     * The FibonacciHeap constructor initializes a new Fibonacci heap with a maximum root node and zero
     * node count.
     */
    FibonacciHeap()
    {
        maxRoot = make_heap();
        nodeCount = 0;
    }

    /**
     * The function `is_empty()` returns true if the nodeCount is 0, indicating that the data structure
     * is empty.
     * 
     * @return The `is_empty()` function is returning a boolean value, specifically `true` if the
     * `nodeCount` is equal to 0, indicating that the data structure is empty, and `false` otherwise.
     */
    bool is_empty()
    {
        return nodeCount == 0;
    }

    /**
     * The insert function creates a new node with a key and value, inserts it into a circular doubly
     * linked list, updates the maximum root node if necessary, and stores the node in a map based on
     * its value.
     * 
     * @param key The `key` parameter in the `insert` function represents the key of the key-value pair
     * that you want to insert into the data structure. It is used to uniquely identify the value
     * associated with it.
     * @param value The `value` parameter in the `insert` function represents the value associated with
     * the key that you want to insert into the data structure. It could be any type of data that you
     * want to store in the data structure along with the corresponding key.
     */
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

    /**
     * The function `extract_max` extracts and returns the maximum key-value pair from a data
     * structure, updating the structure accordingly.
     * 
     * @return The `extract_max` function returns a `pair<K, V>` which represents the maximum element
     * in the data structure. The pair consists of the key `K` and value `V` of the maximum element. If
     * the data structure is empty, it returns a pair with the minimum possible key value and a
     * default-constructed value of type `V`.
     */
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

    /**
     * The function `increase_key` updates the key of a node in a data structure and performs necessary
     * operations based on the new key value.
     * 
     * @param value The `value` parameter in the `increase_key` function represents the value of the
     * node whose key you want to increase. This function is used in a data structure where each node
     * has a key-value pair, and you are trying to update the key of a specific node identified by its
     * value.
     * @param newKey The `newKey` parameter in the `increase_key` function represents the new key value
     * that you want to update for a specific node in your data structure. This function is designed to
     * update the key value of a node with a specific value in a data structure that seems to be a max
     * Fibonacci heap
     * 
     * @return In the provided code snippet, the function `increase_key` is not explicitly returning
     * any value. It either prints a message to the console or performs certain operations based on the
     * conditions. If none of the conditions are met, the function simply exits without returning
     * anything.
     */
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

    /**
     * The Delete function removes a node with a specific value from a data structure and updates the
     * structure accordingly.
     * 
     * @param value The `value` parameter in the `Delete` function represents the value of the node
     * that you want to delete from the data structure.
     * 
     * @return The function `Delete` returns `void`, which means it does not return any value.
     */
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

    /**
     * The `meld` function merges two Fibonacci heaps by linking their maximum roots and updating the
     * node count and nodes by value accordingly.
     * 
     * @param heap1 `heap1` is a reference to another FibonacciHeap object of type `FibonacciHeap<K,
     * V>`.
     * 
     * @return The `meld` function returns a new FibonacciHeap that is the result of merging two input
     * FibonacciHeaps `heap1` and `this` (the current FibonacciHeap instance).
     */
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

    /**
     * The function `find_max` returns the data stored in the node with the maximum key in a binary
     * search tree.
     * 
     * @return The `find_max` function is returning a `pair` containing the key (`K`) and value (`V`)
     * of the maximum element in the data structure.
     */
    pair<K, V> find_max()
    {
        return maxRoot->data;
    }

    /**
     * The function `print` prints the elements of a priority queue implemented as a Fibonacci heap.
     */
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

    /**
     * The `size()` function returns the number of nodes in a data structure.
     * 
     * @return The `size()` function is returning the value of the variable `nodeCount`.
     */
    int size()
    {
        return nodeCount;
    }
};
