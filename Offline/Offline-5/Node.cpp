#include <bits/stdc++.h>
using namespace std;

#define RED 0
#define BLACK 1

/* The code snippet defines a template class called `Node` which represents a node in a binary search
tree. */
template <class I, class S>
class Node
{
public:
    pair<I, S> data;
    Node<I, S> *left_child;
    Node<I, S> *right_child;
    Node<I, S> *parent;
    int color;

    /**
     * The Node constructor initializes a node with a key, value, parent node, and color.
     *
     * @param key The key parameter is of type I, which represents the data type of the key for the
     * node. It is initialized with the default constructor I().
     * @param value The value parameter is of type S and represents the value associated with the key
     * in the node.
     * @param parent A pointer to the parent node of the current node. It is initialized to NULL if the
     * current node is the root node of the tree.
     * @param color The color parameter is used to determine the color of the node in a red-black tree.
     * It can have two possible values: RED or BLACK.
     */
    Node(I key = I(), S value = S(), Node<I, S> *parent = NULL, int color = RED)
    {
        data = {key, value};
        left_child = NULL;
        right_child = NULL;
        this->parent = parent;
        this->color = color;
    }

    /**
     * The above function is a destructor for a Node class in C++ that deletes the left and right child
     * nodes if they exist.
     */
    ~Node()
    {
        if (left_child != NULL)
        {
            delete left_child;
        }

        if (right_child != NULL)
        {
            delete right_child;
        }
    }

    Node(const Node<I, S> &other)
    {
        data = other.data;
        left_child = (other.left_child != NULL) ? new Node<I, S>(*other.left_child) : NULL;
        right_child = (other.right_child != NULL) ? new Node<I, S>(*other.right_child) : NULL;
        parent = NULL; // The parent pointer is set to NULL in the copy.
        color = other.color;
    }

    /**
     * The function overloads the assignment operator for the Node class, allowing for deep copying of
     * data and child nodes from another Node object.
     *
     * @return a reference to the current object (Node<I, S>).
     */
    Node<I, S> &operator=(const Node<I, S> &other)
    {
        if (this != &other)
        {
            // Copy data from "other" to the current object
            data = other.data;
            color = other.color;

            // Delete existing child nodes
            if (left_child != NULL)
            {
                delete left_child;
                left_child = NULL;
            }

            if (right_child != NULL)
            {
                delete right_child;
                right_child = NULL;
            }

            // Copy child nodes from "other"
            if (other.left_child != NULL)
            {
                left_child = new Node<I, S>(*other.left_child);
                left_child->parent = this;
            }

            if (other.right_child != NULL)
            {
                right_child = new Node<I, S>(*other.right_child);
                right_child->parent = this;
            }
        }
        return *this;
    }
};
