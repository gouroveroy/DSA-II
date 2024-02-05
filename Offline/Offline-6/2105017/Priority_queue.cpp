#include <bits/stdc++.h>
#include "FibonacciHeap.cpp"
using namespace std;

template <class K, class V>
class Priority_queue
{
    FibonacciHeap<K, V> heap;

public:
    Priority_queue()
    {
    }

    void insert(K key, V value)
    {
        heap.insert(key, value);
    }

    bool is_empty()
    {
        return heap.is_empty();
    }

    pair<K, V> extract_max()
    {
        return heap.extract_max();
    }

    void increase_key(V value, K new_key)
    {
        heap.increase_key(value, new_key);
    }

    void Delete(V value)
    {
        heap.Delete(value);
    }

    Priority_queue<K, V> meld(Priority_queue<K, V> &pq)
    {
        Priority_queue<K, V> newPQ;
        newPQ.heap = heap.meld(pq.heap);
        return newPQ;
    }

    pair<K, V> find_max()
    {
        return heap.find_max();
    }

    int size()
    {
        return heap.size();
    }

    void print()
    {
        heap.print();
    }
};
