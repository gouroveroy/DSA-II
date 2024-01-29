#include <bits/stdc++.h>
#include "color.hpp"
#include "Node.cpp"
using namespace dye;
using namespace std;

/* The above code is defining a template class called `RedBlackTree` in C++. It has two template
parameters `I` and `S`. It has a private member variable `root` of type `Node<I, S>*` which
represents the root of the red-black tree. It also has a private member variable `leaf` of type
`Node<I, S>*` which represents a leaf node in the red-black tree. The class also has a private
member variable `nodeCount` of type `int` which represents the number of nodes in the red-black
tree. */
template <class I, class S>
class RedBlackTree
{
    Node<I, S> *root;
    Node<I, S> *leaf;
    int nodeCount;

    /**
     * The function performs a left rotation on a binary tree node.
     *
     * @param node The "node" parameter is a pointer to a Node object.
     */
    void leftRotate(Node<I, S> *node)
    {
        Node<I, S> *leftRotator = node->right_child;
        node->right_child = leftRotator->left_child;
        if (leftRotator->left_child != leaf)
        {
            leftRotator->left_child->parent = node;
        }
        leftRotator->parent = node->parent;
        if (node->parent == NULL)
        {
            this->root = leftRotator;
        }

        else if (node == node->parent->left_child)
        {
            node->parent->left_child = leftRotator;
        }

        else
        {
            node->parent->right_child = leftRotator;
        }
        leftRotator->left_child = node;
        node->parent = leftRotator;
    }

    /**
     * The function performs a right rotation on a binary tree node.
     *
     * @param node A pointer to the node that needs to be right rotated.
     */
    void rightRotate(Node<I, S> *node)
    {
        Node<I, S> *rightRotator = node->left_child;
        node->left_child = rightRotator->right_child;
        if (rightRotator->right_child != leaf)
        {
            rightRotator->right_child->parent = node;
        }
        rightRotator->parent = node->parent;
        if (node->parent == NULL)
        {
            this->root = rightRotator;
        }

        else if (node == node->parent->right_child)
        {
            node->parent->right_child = rightRotator;
        }

        else
        {
            node->parent->left_child = rightRotator;
        }
        rightRotator->right_child = node;
        node->parent = rightRotator;
    }

    /**
     * The function `insertFix` is used to fix the red-black tree after inserting a node.
     *
     * @param node A pointer to the node that was just inserted into the red-black tree.
     */
    void insertFix(Node<I, S> *node)
    {
        Node<I, S> *uncle;
        while (node->parent->color == RED)
        {
            if (node->parent == node->parent->parent->right_child)
            {
                uncle = node->parent->parent->left_child;
                if (uncle->color == RED)
                {
                    uncle->color = BLACK;
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }

                else
                {
                    if (node == node->parent->left_child)
                    {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }

            else
            {
                uncle = node->parent->parent->right_child;
                if (uncle->color == RED)
                {
                    uncle->color = BLACK;
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                }

                else
                {
                    if (node == node->parent->right_child)
                    {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            }

            if (node == root)
            {
                break;
            }
        }
        root->color = BLACK;
    }

    /**
     * The function inserts a new node with a key-value pair into a binary search tree and performs
     * necessary fix operations to maintain the red-black tree properties.
     *
     * @param key The key parameter is of type I, which represents the data type of the key being
     * inserted into the binary search tree.
     * @param value The value parameter is of type S, which represents the value associated with the
     * key in the binary search tree.
     *
     * @return The function does not have a return type specified, so it does not explicitly return
     * anything. However, there are several return statements within the function that can cause the
     * function to exit early.
     */
    void insertHelp(I key, S value)
    {
        Node<I, S> *newNode = new Node<I, S>(key, value);
        newNode->left_child = leaf;
        newNode->right_child = leaf;
        Node<I, S> *helperNode = NULL;
        Node<I, S> *rootHelper = this->root;

        while (rootHelper != leaf)
        {
            helperNode = rootHelper;
            if (newNode->data.first == rootHelper->data.first)
            {
                rootHelper->data.second = value;
                return;
            }

            else if (newNode->data.first < rootHelper->data.first)
            {
                rootHelper = rootHelper->left_child;
            }

            else
            {
                rootHelper = rootHelper->right_child;
            }
        }

        newNode->parent = helperNode;
        if (helperNode == NULL)
        {
            root = newNode;
        }

        else if (newNode->data.first < helperNode->data.first)
        {
            helperNode->left_child = newNode;
        }

        else
        {
            helperNode->right_child = newNode;
        }

        if (newNode->parent == NULL)
        {
            newNode->color = BLACK;
            return;
        }

        if (newNode->parent->parent == NULL)
        {
            return;
        }

        insertFix(newNode);
    }

    /**
     * The function `inorderSuccesor` returns the inorder successor of a given node in a binary tree.
     *
     * @param root A pointer to the root node of the binary search tree.
     *
     * @return the inorder successor of the given root node.
     */
    Node<I, S> *inorderSuccesor(Node<I, S> *root)
    {
        Node<I, S> *newNode = root->right_child;
        while (newNode->left_child != leaf)
        {
            newNode = newNode->left_child;
        }
        return newNode;
    }

    /**
     * The redBlackTransplant function replaces one node with another in a red-black tree while
     * maintaining the tree's properties.
     *
     * @param u The node that needs to be replaced with another node.
     * @param v The parameter `v` is a pointer to a `Node` object.
     */
    void redBlackTransplant(Node<I, S> *u, Node<I, S> *v)
    {
        if (u->parent == NULL)
        {
            root = v;
        }

        else if (u == u->parent->left_child)
        {
            u->parent->left_child = v;
        }

        else
        {
            u->parent->right_child = v;
        }

        v->parent = u->parent;
    }

    /**
     * The deleteFix function is used to fix the red-black tree after a node is deleted.
     *
     * @param node A pointer to the node that needs to be fixed after deletion.
     */
    void deleteFix(Node<I, S> *node)
    {
        Node<I, S> *sibling;
        while (node != root && node->color == BLACK)
        {
            if (node == node->parent->left_child)
            {
                sibling = node->parent->right_child;
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    leftRotate(node->parent);
                    sibling = node->parent->right_child;
                }

                if (sibling->left_child->color == BLACK && sibling->right_child->color == BLACK)
                {
                    sibling->color = RED;
                    node = node->parent;
                }

                else
                {
                    if (sibling->right_child->color == BLACK)
                    {
                        sibling->left_child->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = node->parent->right_child;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->right_child->color = BLACK;
                    leftRotate(node->parent);
                    node = root;
                }
            }

            else
            {
                sibling = node->parent->left_child;
                if (sibling->color == RED)
                {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rightRotate(node->parent);
                    sibling = node->parent->left_child;
                }

                if (sibling->right_child->color == BLACK && sibling->left_child->color == BLACK)
                {
                    sibling->color = RED;
                    node = node->parent;
                }

                else
                {
                    if (sibling->left_child->color == BLACK)
                    {
                        sibling->right_child->color = BLACK;
                        sibling->color = RED;
                        leftRotate(sibling);
                        sibling = node->parent->left_child;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    sibling->left_child->color = BLACK;
                    rightRotate(node->parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }

    /**
     * The function `deleteHelp` is used to delete a node from a red-black tree and fix the tree to
     * maintain the red-black properties.
     *
     * @param rootHelp The root node of the binary search tree from which the node with the specified
     * key needs to be deleted.
     * @param key The key is the value that we want to delete from the binary search tree.
     *
     * @return The function does not return any value.
     */
    void deleteHelp(Node<I, S> *rootHelp, I key)
    {
        Node<I, S> *nodeToBeDeleted = rootHelp;
        Node<I, S> *succPrec, *succPrecChild;

        while (nodeToBeDeleted != leaf && nodeToBeDeleted->data.first != key)
        {
            if (key < nodeToBeDeleted->data.first)
            {
                nodeToBeDeleted = nodeToBeDeleted->left_child;
            }
            else
            {
                nodeToBeDeleted = nodeToBeDeleted->right_child;
            }
        }

        if (nodeToBeDeleted == leaf)
        {
            return;
        }

        int originalColorOfNodeToBeDeleted = nodeToBeDeleted->color;

        if (nodeToBeDeleted->left_child == leaf)
        {
            succPrecChild = nodeToBeDeleted->right_child;
            redBlackTransplant(nodeToBeDeleted, nodeToBeDeleted->right_child);
        }
        else if (nodeToBeDeleted->right_child == leaf)
        {
            succPrecChild = nodeToBeDeleted->left_child;
            redBlackTransplant(nodeToBeDeleted, nodeToBeDeleted->left_child);
        }
        else
        {
            succPrec = inorderSuccesor(nodeToBeDeleted);
            originalColorOfNodeToBeDeleted = succPrec->color;
            succPrecChild = succPrec->right_child;

            if (succPrec->parent == nodeToBeDeleted)
            {
                succPrecChild->parent = succPrec;
            }
            else
            {
                redBlackTransplant(succPrec, succPrec->right_child);
                succPrec->right_child = nodeToBeDeleted->right_child;
                succPrec->right_child->parent = succPrec;
            }

            redBlackTransplant(nodeToBeDeleted, succPrec);
            succPrec->left_child = nodeToBeDeleted->left_child;
            succPrec->left_child->parent = succPrec;
            succPrec->color = nodeToBeDeleted->color;
        }

        delete nodeToBeDeleted;
        if (originalColorOfNodeToBeDeleted == BLACK)
        {
            deleteFix(succPrecChild);
        }
    }

    /**
     * The function recursively clears a binary tree by deleting each node.
     *
     * @param root A pointer to the root node of the binary tree.
     *
     * @return nothing (void).
     */
    void clearHelp(Node<I, S> *root)
    {
        if (root == leaf)
        {
            return;
        }
        clearHelp(root->left_child);
        clearHelp(root->right_child);
        delete root;
    }

    /**
     * The function `findHelp` recursively searches for a key in a binary search tree and returns true
     * if the key is found, false otherwise.
     *
     * @param root The root node of the binary search tree.
     * @param key The key parameter is the value that we are searching for in the binary search tree.
     *
     * @return a boolean value. It returns true if the key is found in the binary search tree, and
     * false otherwise.
     */
    bool findHelp(Node<I, S> *root, I key)
    {
        if (root == leaf)
        {
            return false;
        }

        if (key != root->data.first)
        {
            if (key < root->data.first)
            {
                return findHelp(root->left_child, key);
            }

            else if (key > root->data.first)
            {
                return findHelp(root->right_child, key);
            }
        }

        else if (key == root->data.first)
        {
            return true;
        }
        return false;
    }

    /**
     * The function performs an inorder traversal of a binary tree and prints the data stored in each
     * node, highlighting the color of the node.
     *
     * @param root A pointer to the root node of the binary tree.
     *
     * @return The function is not returning any value. It is a void function, so it does not have a
     * return statement.
     */
    void inorderTraversalHelp(Node<I, S> *root)
    {
        if (root == leaf)
        {
            return;
        }

        inorderTraversalHelp(root->left_child);
        if (root->color == RED)
        {
            cout << red(root->data.first) << " => " << red(root->data.second) << endl;
        }

        if (root->color == BLACK)
        {
            cout << black(root->data.first) << " => " << black(root->data.second) << endl;
        }
        // cout << root->data.first << " ⇒ " << root->data.second << endl;
        inorderTraversalHelp(root->right_child);
    }

    /**
     * The function `printRedBlackTreeHelp` is used to print the elements of a Red-Black Tree in a
     * specific format.
     *
     * @param root The root parameter is a pointer to the root node of the Red-Black Tree.
     *
     * @return The function does not have a return type specified, so it does not explicitly return
     * anything.
     */
    void printRedBlackTreeHelp(Node<I, S> *root)
    {
        if (root == leaf)
        {
            return;
        }

        else if (root->left_child == leaf && root->right_child == leaf)
        {
            if (root->color == RED)
            {
                cout << red(root->data.first) << "_" << red(root->data.second);
            }

            if (root->color == BLACK)
            {
                cout << black(root->data.first) << "_" << black(root->data.second);
            }
            // cout << root->data.first << "_" << root->data.second;
        }

        else if (root->left_child != leaf && root->right_child == leaf)
        {
            if (root->color == RED)
            {
                cout << red(root->data.first) << "_" << red(root->data.second) << '(';
            }

            if (root->color == BLACK)
            {
                cout << black(root->data.first) << "_" << black(root->data.second) << '(';
            }
            // cout << root->data.first << "_" << root->data.second << '(';
            printRedBlackTreeHelp(root->left_child);
            cout << ",)";
        }

        else if (root->left_child == leaf && root->right_child != leaf)
        {
            if (root->color == RED)
            {
                cout << red(root->data.first) << "_" << red(root->data.second) << "(,";
            }

            if (root->color == BLACK)
            {
                cout << black(root->data.first) << "_" << black(root->data.second) << "(,";
            }
            // cout << root->data.first << "_" << root->data.second << "(,";
            printRedBlackTreeHelp(root->right_child);
            cout << ")";
        }

        else if (root->left_child != leaf && root->right_child != leaf)
        {
            if (root->color == RED)
            {
                cout << red(root->data.first) << "_" << red(root->data.second) << '(';
            }

            if (root->color == BLACK)
            {
                cout << black(root->data.first) << "_" << black(root->data.second) << '(';
            }
            // cout << root->data.first << "_" << root->data.second << '(';
            printRedBlackTreeHelp(root->left_child);
            cout << ",";
            printRedBlackTreeHelp(root->right_child);
            cout << ")";
        }
    }

    /**
     * The function `copyTree` recursively copies a binary tree, preserving the structure and data of
     * each node.
     *
     * @param srcNode The source node that we want to copy. It is of type Node<I, S> and represents the
     * node that we want to create a copy of.
     * @param parentOfCopy parentOfCopy is a pointer to the parent node of the copyNode that is being
     * created. It is used to set the parent pointer of the copyNode to the correct value.
     *
     * @return a pointer to a copy of the source node.
     */
    Node<I, S> *copyTree(const Node<I, S> *srcNode, Node<I, S> *parentOfCopy)
    {
        if (srcNode == leaf)
        {
            return leaf;
        }

        Node<I, S> *copyNode = new Node<I, S>(srcNode->data.first, srcNode->data.second);
        copyNode->color = srcNode->color;
        copyNode->parent = parentOfCopy;
        copyNode->left_child = copyTree(srcNode->left_child, copyNode);
        copyNode->right_child = copyTree(srcNode->right_child, copyNode);

        return copyNode;
    }

public:
    /**
     * The RedBlackTree constructor initializes a Red-Black Tree with a black leaf node as the root and
     * sets the node count to 0.
     */
    RedBlackTree()
    {
        leaf = new Node<I, S>();
        leaf->color = BLACK;
        leaf->left_child = NULL;
        leaf->right_child = NULL;
        this->root = leaf;
        this->nodeCount = 0;
    }

    /**
     * The destructor for a Red-Black Tree calls a recursive helper function to delete all nodes and
     * then deletes the leaf node.
     */
    ~RedBlackTree()
    {
        // Call the recursive helper function to delete all nodes
        clearHelp(root);
        // Delete the leaf node
        delete leaf;
    }

    /**
     * The RedBlackTree constructor performs a deep copy of another Red-Black Tree.
     *
     * @param other The "other" parameter is a reference to another RedBlackTree object that we want to
     * copy.
     */
    RedBlackTree(const RedBlackTree<I, S> &other)
    {
        // Perform a deep copy of the other Red-Black Tree
        leaf = new Node<I, S>();
        leaf->color = BLACK;
        leaf->left_child = NULL;
        leaf->right_child = NULL;
        root = copyTree(other.root, leaf);
        nodeCount = other.nodeCount;
    }

    /**
     * The function performs a deep copy of a Red-Black Tree object, clearing the current tree and
     * copying the nodes from the other tree.
     *
     * @return a reference to the RedBlackTree object that is being assigned to.
     */
    RedBlackTree<I, S> &operator=(const RedBlackTree<I, S> &other)
    {
        if (this != &other)
        {
            // Clear the current Red-Black Tree
            clearHelp(root);

            // Perform a deep copy of the other Red-Black Tree
            leaf = new Node<I, S>();
            leaf->color = BLACK;
            leaf->left_child = NULL;
            leaf->right_child = NULL;
            root = copyTree(other.root, leaf);
            nodeCount = other.nodeCount;
        }
        return *this;
    }

    /**
     * This function overloads the [] operator to allow accessing and modifying values in a binary
     * search tree based on a given key.
     *
     * @return a reference to the value associated with the key.
     */
    S &operator[](const I &key)
    {
        Node<I, S> *current = root;
        while (current != leaf)
        {
            if (key == current->data.first)
            {
                return current->data.second; // Return a reference to the value associated with the key
            }
            else if (key < current->data.first)
            {
                current = current->left_child;
            }
            else
            {
                current = current->right_child;
            }
        }

        // If key not found, insert a new node with default value and return a reference to its value.
        S default_value = S(); // Assuming S has a default constructor
        insert(key, default_value);
        return operator[](key); // Recursive call to get the reference after insertion
    }

    /**
     * The insert function inserts a key-value pair into a data structure and increments the node
     * count.
     *
     * @param key The key parameter is of type I, which represents the type of the key being inserted.
     * @param value The value parameter is of type S, which represents the value associated with the
     * key being inserted.
     */
    void insert(I key, S value)
    {
        insertHelp(key, value);
        nodeCount++;
    }

    /**
     * The erase function deletes a node with the specified key from the binary search tree.
     *
     * @param key The key parameter is the value that needs to be deleted from the binary search tree.
     */
    void erase(I key)
    {
        deleteHelp(this->root, key);
        nodeCount--;
    }

    /**
     * The clear function clears all nodes in a binary tree and resets the root and node count.
     *
     * @return a boolean value. If the condition `nodeCount == 0` is true, then the function returns
     * `false`. Otherwise, it returns `true`.
     */
    bool clear()
    {
        if (nodeCount == 0)
        {
            return false;
        }
        clearHelp(root);
        root = leaf;
        nodeCount = 0;
        return true;
    }

    /**
     * The find function checks if a given key exists in a binary search tree.
     *
     * @param key The key parameter is the value that we are searching for in the data structure.
     *
     * @return a boolean value.
     */
    bool find(I key)
    {
        return findHelp(root, key);
    }

    /**
     * The function checks if a data structure is empty by comparing the nodeCount variable to zero.
     *
     * @return a boolean value, which indicates whether the nodeCount is equal to 0.
     */
    bool empty()
    {
        return nodeCount == 0;
    }

    /**
     * The function "size" returns the number of nodes in a data structure.
     *
     * @return The method is returning the value of the variable "nodeCount".
     */
    int size()
    {
        return nodeCount;
    }

    /**
     * The function performs an inorder traversal of a binary tree.
     *
     * @return nothing (void).
     */
    void inorderTraversal()
    {
        if (root == leaf)
        {
            return;
        }
        inorderTraversalHelp(root);
    }

    /**
     * The function "printRedBlackTree" is used to print the elements of a red-black tree.
     */
    void printRedBlackTree()
    {
        printRedBlackTreeHelp(root);
        cout << endl;
    }
};
