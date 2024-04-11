#include <bits/stdc++.h>
#include "RedBlackTree.cpp"
using namespace std;

/* The code is defining a template class called `Map` that uses two template parameters `I` and `S`.
The class contains a private member variable `rbt` of type `RedBlackTree<I, S>`. This `rbt` variable
is an instance of the `RedBlackTree` class with template arguments `I` and `S`. */
template <class I, class S>
class Map
{
    RedBlackTree<I, S> rbt;

public:
    /**
     * The code snippet defines a constructor for a class named "Map" in C++.
     */
    Map()
    {
    }

    /**
     * The Map copy constructor initializes a new Map object by copying the RedBlackTree object from
     * another Map object.
     *
     * @param other The parameter "other" is a constant reference to an object of type Map<I, S>.
     */
    Map(const Map<I, S> &other)
    {
        rbt = other.rbt; // Calls the RedBlackTree copy constructor
    }

    // Assignment operator overload
    /**
     * The function overloads the assignment operator for the Map class, allowing one Map object to be
     * assigned the value of another Map object.
     *
     * @return a reference to the current object, which is denoted by `*this`.
     */
    Map<I, S> &operator=(const Map<I, S> &other)
    {
        if (this != &other)
        {
            rbt = other.rbt; // Calls the RedBlackTree assignment operator
        }
        return *this;
    }

    /**
     * The operator[] overload allows you to access values using the square bracket notation.
     * If the key is present, it returns the associated value; otherwise, it inserts a default-constructed
     * value for the key and returns a reference to it.
     *
     * @param key The key parameter is the value for which you want to retrieve or set the associated value.
     *
     * @return A reference to the value associated with the specified key.
     */
    S &operator[](I key)
    {
        return rbt[key];
    }

    /**
     * The Insert function inserts a key-value pair into a red-black tree.
     *
     * @param key The key parameter is of type I, which represents the data type of the key being
     * inserted into the data structure.
     * @param value The value parameter is the value associated with the key that needs to be inserted
     * into the data structure.
     */
    void Insert(pair<I, S> &p)
    {
        I key = p.first;
        S value = p.second;
        rbt.insert(key, value);
    }

    /**
     * The function "Erase" removes an element with the specified key from a red-black tree.
     *
     * @param key The key parameter is the value that you want to erase from the red-black tree.
     */
    void Erase(I key)
    {
        rbt.erase(key);
    }

    /**
     * The function "Clear" clears the contents of a red-black tree and returns a boolean value
     * indicating whether the operation was successful.
     *
     * @return a boolean value.
     */
    bool Clear()
    {
        return rbt.clear();
    }

    /**
     * The function "Find" checks if a given key exists in a red-black tree and returns a boolean value
     * indicating the result.
     *
     * @param key The key parameter is the value that you want to search for in the red-black tree.
     *
     * @return a boolean value.
     */
    bool Find(I key)
    {
        return rbt.find(key);
    }

    /**
     * The function checks if a red-black tree is empty.
     *
     * @return a boolean value.
     */
    bool Empty()
    {
        return rbt.empty();
    }

    /**
     * The Size() function returns the size of a red-black tree.
     *
     * @return The size of the red-black tree.
     */
    int Size()
    {
        return rbt.size();
    }

    /**
     * The Iteration function performs an inOrder traversal on a red-black tree.
     */
    void Iteration()
    {
        rbt.inOrderTraversal();
    }

    /**
     * The function "print" calls the "printRedBlackTree" function of an object named "rbt".
     */
    void print()
    {
        rbt.printRedBlackTree();
    }
};
