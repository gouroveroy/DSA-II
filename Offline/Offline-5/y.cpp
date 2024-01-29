#include <bits/stdc++.h>
using namespace std;

#define RED 0
#define BLACK 1

template <class I, class S>
class Node
{
public:
    pair<I, S> data;
    Node<I, S> *left_child;
    Node<I, S> *right_child;
    Node<I, S> *parent;
    int color;

    Node(I key = I(), S value = S(), Node<I, S> *parent = NULL, int color = RED)
    {
        data = {key, value};
        left_child = NULL;
        right_child = NULL;
        this->parent = parent;
        this->color = color;
    }
};

template <class I, class S>
class RedBlackTree
{
    Node<I, S> *root;
    Node<I, S> *leaf;
    int nodeCount;

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
            if (newNode->data.first < rootHelper->data.first)
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

    Node<I, S> *inorderSuccesor(Node<I, S> *root)
    {
        Node<I, S> *newNode = root->right_child;
        while (newNode->left_child != leaf)
        {
            newNode = newNode->left_child;
        }
        return newNode;
    }

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

    void deleteFix(Node<I, S> *node)
    {
        while (node != root && node->color == BLACK)
        {
            if (node == node->parent->left_child)
            {
                Node<I, S> *sibling = node->parent->right_child;

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
                Node<I, S> *sibling = node->parent->left_child;

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
            cout << "Key not found for deletion." << endl;
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

    void printRedBlackTreeHelp(Node<I, S> *root)
    {
        if (root == leaf)
        {
            return;
        }

        else if (root->left_child == leaf && root->right_child == leaf)
        {
            cout << root->data.first << "_" << root->data.second;
        }

        else if (root->left_child != leaf && root->right_child == leaf)
        {
            cout << root->data.first << "_" << root->data.second << '(';
            printRedBlackTreeHelp(root->left_child);
            cout << ",)";
        }

        else if (root->left_child == leaf && root->right_child != leaf)
        {
            cout << root->data.first << "_" << root->data.second << "(,";
            printRedBlackTreeHelp(root->right_child);
            cout << ")";
        }

        else if (root->left_child != leaf && root->right_child != leaf)
        {
            cout << root->data.first << "_" << root->data.second << '(';
            printRedBlackTreeHelp(root->left_child);
            cout << ",";
            printRedBlackTreeHelp(root->right_child);
            cout << ")";
        }
    }

public:
    RedBlackTree()
    {
        leaf = new Node<I, S>();
        leaf->color = BLACK;
        leaf->left_child = NULL;
        leaf->right_child = NULL;
        this->root = leaf;
        this->nodeCount = 0;
    }

    void insert(I key, S value)
    {
        insertHelp(key, value);
        nodeCount++;
    }

    void erase(I key)
    {
        deleteHelp(this->root, key);
    }

    void printRedBlackTree()
    {
        printRedBlackTreeHelp(root);
        cout << endl;
    }
};

int main()
{
    RedBlackTree<int, string> rbt;
    rbt.insert(5, "bird");
    rbt.insert(2, "animal");
    rbt.insert(3, "man");
    rbt.insert(4, "women");
    rbt.insert(6, "boy");
    rbt.insert(1, "dipu");
    rbt.insert(8, "bcd");
    rbt.printRedBlackTree();
    rbt.erase(1);
    rbt.printRedBlackTree();
    return 0;
}
