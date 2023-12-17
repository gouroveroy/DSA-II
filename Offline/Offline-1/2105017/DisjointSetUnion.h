#include <bits/stdc++.h>
using namespace std;

// This class implements the disjoint set union data structure which contains 3 functions like make, find and union
class DisjointSetUnion
{
    vector<int> parent;
    vector<int> rank;

public:
    // This function creates node for disjoint set union data structure
    void Make(int i)
    {
        parent[i] = i;
        rank[i] = 1;
    }

    // Constructor
    DisjointSetUnion(int n = 0)
    {
        parent.resize(n + 1);
        rank.resize(n + 1);
        for (int i = 0; i <= n; i++)
        {
            Make(i);
        }
    }

    // This function finds the root or parent of a disjoint set
    int Find(int i)
    {
        if (parent[i] == i)
        {
            return i;
        }
        else
        {
            return parent[i] = Find(parent[i]);
        }
    }

    // This function combines two disjoint sets
    void Union(int a, int b)
    {
        a = Find(a);
        b = Find(b);
        if (a != b)
        {
            if (rank[a] < rank[b])
            {
                parent[a] = b;
            }
            else if (rank[a] > rank[b])
            {
                parent[b] = a;
            }
            else
            {
                parent[b] = a;
                rank[a]++;
            }
        }
    }
};
