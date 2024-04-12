#include <bits/stdc++.h>
#include "FibonacciHeap.cpp"
using namespace std;

/* The code snippet you provided is defining a templated class named `Priority_queue` that serves as a
priority queue implementation using a Fibonacci Heap. The template class takes two template
parameters `K` and `V` which represent the key and value types respectively. */
template <class K, class V>
class Priority_queue
{
    FibonacciHeap<K, V> heap;

public:
    /**
     * The above function appears to be a constructor for a priority queue in C++.
     */
    Priority_queue()
    {
    }

    /**
     * The insert function inserts a key-value pair into a heap data structure.
     * 
     * @param key The key parameter is the key used to insert the value into the data structure.
     * @param value The "value" parameter represents the value associated with the key that is being
     * inserted into the data structure.
     */
    void insert(K key, V value)
    {
        heap.insert(key, value);
    }

    /**
     * This function checks if a heap data structure is empty.
     * 
     * @return The `is_empty()` function is returning a boolean value, specifically whether the heap is
     * empty or not.
     */
    bool is_empty()
    {
        return heap.is_empty();
    }

    /**
     * The function "extract_max" returns and removes the maximum element from a heap data structure.
     * 
     * @return A pair containing a key-value pair (K, V) is being returned.
     */
    pair<K, V> extract_max()
    {
        return heap.extract_max();
    }

    /**
     * The function `increase_key` increases the key of a value in a heap data structure.
     * 
     * @param value The `value` parameter represents the value in the heap that you want to update with
     * a new key.
     * @param new_key The `new_key` parameter represents the new key value that you want to assign to
     * the specified element in the heap.
     */
    void increase_key(V value, K new_key)
    {
        heap.increase_key(value, new_key);
    }

    /**
     * The Delete function removes a specified value from a heap data structure.
     * 
     * @param value The `value` parameter represents the value that you want to delete from the heap.
     */
    void Delete(V value)
    {
        heap.Delete(value);
    }

    /**
     * The function melds two priority queues into a new priority queue.
     * 
     * @param pq The `pq` parameter in the `meld` function is a reference to another priority queue of
     * type `Priority_queue<K, V>`.
     * 
     * @return The `meld` function is returning a new priority queue `newPQ` that is the result of
     * merging the current priority queue's heap with the heap of the priority queue passed as a
     * parameter (`pq`).
     */
    Priority_queue<K, V> meld(Priority_queue<K, V> &pq)
    {
        Priority_queue<K, V> newPQ;
        newPQ.heap = heap.meld(pq.heap);
        return newPQ;
    }

    /**
     * The function find_max() returns the maximum element in a heap.
     * 
     * @return The `find_max` function is returning a `pair<K, V>` which is the maximum element in the
     * heap.
     */
    pair<K, V> find_max()
    {
        return heap.find_max();
    }

    /**
     * The function returns the size of a heap data structure.
     * 
     * @return The `size()` function is returning the size of the `heap` data structure.
     */
    int size()
    {
        return heap.size();
    }

    /**
     * The print function calls the print method of the heap object.
     */
    void print()
    {
        heap.print();
    }
};
