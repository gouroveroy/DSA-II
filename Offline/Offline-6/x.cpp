#include <bits/stdc++.h>
#include "Node.cpp"
using namespace std;

template <class K, class V>
class FibonacciHeap
{
    Node<K, V> *maxRoot;
    vector<vector<int>> nodeNo;
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

    void printChild(Node<K, V> *root, Node<K, V> *node, vector<vector<Node<K, V> *>> &trees, int &treesCount)
    {
        Node<K, V> *child = node;
        int count = 0;
        do
        {
            count++;
            trees[treesCount].push_back(child);
            child = child->right;
        } while (child != root);
        nodeNo[treesCount].push_back(count);

        do
        {
            printChild(child->child, child->child, trees, treeCount);
            child = child->right;
        } while (child != root);
    }

    void printTree(Node<K, V> *root, Node<K, V> *node, vector<vector<Node<K, V> *>> &trees, int &treesCount)
    {
        if (node == root)
        {
            return;
        }

        trees[treesCount].push_back(node);
        if (child != NULL)
        {
            printChild(node.child, node.child, trees, treesCount);
        }
        printTree(root, node->right, trees, treesCount + 1);
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

    void print()
    {
        if (nodeCount != 0)
        {
            vector<vector<Node<K, V> *>> trees(nodeCount);
            int treesCount = 0;
            printTree(maxRoot, maxRoot, trees, treesCount);
            treesCount = 1;
            for (vector<Node<K, V> *> &tree : trees)
            {
                if (!tree.empty())
                {
                    cout << "Tree " << treesCount << ": ";
                    Node<K, V> *node = tree[0];
                    cout << "(" << node.data.first << "," << node.data.second << ")";
                }
            }
        }
    }
};
