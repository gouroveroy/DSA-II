#include <bits/stdc++.h>
#include "C:\Users\User\OneDrive - BUET\BOOKS 2-1\CSE-207\Offline_Online\Offline\Offline-1\DisjointSetUnion.h"
using namespace std;

int ManhattanDistance(pair<int, int> a, pair<int, int> b)
{
    return abs(a.first - b.first) + abs(a.second - b.second);
}

int main()
{
    int n;
    cin >> n;
    vector<pair<int, int>> house;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        house.push_back({x, y});
    }
    vector<pair<int, pair<int, int>>> graph;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            graph.push_back({ManhattanDistance(house[i], house[j]), {i, j}});
        }
    }
    sort(graph.begin(), graph.end());
    DisjointSetUnion dsu(n);
    int totalCost = 0;
    for (auto &edge : graph)
    {
        int wt = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if (dsu.Find(u) != dsu.Find(v))
        {
            dsu.Union(u, v);
            totalCost += wt;
        }
    }
    cout << totalCost << endl;
    return 0;
}
