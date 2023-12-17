#include <bits/stdc++.h>
#include "DisjointSetUnion.h"
#include "GraphCombination.h"
using namespace std;

// This function is used to find all minimum spanning trees of a given graph
set<vector<pair<int, pair<int, int>>>> findAllMSTs(vector<pair<int, pair<int, int>>> graph, int n)
{
    // Krushkal algorithm for finding the minimum spanning tree
    sort(graph.begin(), graph.end());
    DisjointSetUnion dsu(n);
    int totalWeight = 0;
    for (auto &edge : graph)
    {
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if (dsu.Find(u) != dsu.Find(v))
        {
            dsu.Union(u, v);
            totalWeight += wt;
        }
    }

    set<vector<pair<int, pair<int, int>>>> msts;
    set<vector<pair<int, pair<int, int>>>> probableMsts = allPossibleGraphCombinations(graph, n - 1, totalWeight);

    // Checking the graphs contains cycles or not
    for (auto &mst : probableMsts)
    {
        DisjointSetUnion dsu2(n);
        bool flag = true;
        for (auto &edge : mst)
        {
            int u = edge.second.first;
            int v = edge.second.second;
            dsu2.Make(u);
            dsu2.Make(v);
        }
        for (auto &edge : mst)
        {
            int u = edge.second.first;
            int v = edge.second.second;
            if (dsu2.Find(u) != dsu2.Find(v))
            {
                dsu2.Union(u, v);
            }
            else
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            msts.insert(mst);
        }
    }
    return msts;
}
