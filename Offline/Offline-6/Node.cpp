#include <bits/stdc++.h>
using namespace std;

/* The code snippet is defining a template class called `Node` that represents a node in a data
structure. The template class takes two template parameters `K` and `V`, which represent the types
of the key and value stored in the node. */
template <class K, class V>
class Node
{
public:
    pair<K, V> data;
    Node<K, V> *left;
    Node<K, V> *right;
    Node<K, V> *child;
    Node<K, V> *parent;
    int degree;
    bool mark;

    /**
     * The Node constructor initializes the data, left, right, child, parent, degree, and mark
     * variables.
     * 
     * @param key The key parameter is of type K and represents the key of the node. It is initialized
     * with the default value of K().
     * @param value The value parameter is the value associated with the key in the node. It is of type
     * V, which represents the value type.
     * @param left The "left" parameter is a pointer to the left sibling of the current node in a
     * linked list structure.
     * @param right The "right" parameter is a pointer to the right sibling of the current node in a
     * linked list structure.
     * @param child A pointer to the leftmost child of the node. If the node has no children, this
     * pointer is set to NULL.
     * @param parent The parent parameter is a pointer to the parent node of the current node.
     * @param degree The degree of a node is the number of children it has. In this case, it represents
     * the number of children of the node.
     * @param mark The "mark" parameter is a boolean flag that is used in some algorithms, such as
     * Fibonacci heaps, to keep track of whether a node has lost a child since the last time it became
     * a child of another node. It is typically used to optimize certain operations, such as decrease
     * key or delete,
     */
    Node(K key = K(), V value = V(), Node<K, V> *left = NULL, Node<K, V> *right = NULL, Node<K, V> *child = NULL, Node<K, V> *parent = NULL, int degree = 0, bool mark = false)
    {
        this->data = {key, value};
        this->left = left;
        this->right = right;
        this->child = child;
        this->parent = parent;
        this->degree = degree;
        this->mark = mark;
    }
};
