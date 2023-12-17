#include <bits/stdc++.h>
#include "AllMST.h"
using namespace std;

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> v;
    vector<pair<int, pair<int, int>>> graph;

    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        v.push_back(x);
    }

    int a, b, w;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> w;
        graph.push_back({w, {a, b}});
    }

    for (int i = 1; i <= n; i++)
    {
        graph.push_back({v[i - 1], {0, i}});
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
