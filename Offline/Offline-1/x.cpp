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

int weight(vector<pair<int, pair<int, int>>> graph)
{
    int totalWeight = 0;
    for (auto &edge : graph)
    {
        totalWeight += edge.first;
    }
    return totalWeight;
}

void edgeCombinations(int index, int mstEdge, vector<pair<int, pair<int, int>>> &graph, set<vector<pair<int, pair<int, int>>>> &combinatons, vector<pair<int, pair<int, int>>> &trees)
{
    if (mstEdge == 0)
    {
        combinatons.insert(trees);
    }

    if (index >= graph.size())
    {
        return;
    }

    trees.push_back(graph[index]);
    edgeCombinations(index + 1, mstEdge - 1, graph, combinatons, trees);
    trees.pop_back();
    edgeCombinations(index + 1, mstEdge, graph, combinatons, trees);
}

set<vector<pair<int, pair<int, int>>>> allPossibleGraphCombinations(vector<pair<int, pair<int, int>>> &graph, int mstEdge, int mstWeight)
{
    set<vector<pair<int, pair<int, int>>>> mstCombinations;
    set<vector<pair<int, pair<int, int>>>> combinations;
    vector<pair<int, pair<int, int>>> trees;
    edgeCombinations(0, mstEdge, graph, combinations, trees);
    for (auto &combination : combinations)
    {
        int totalWeight = weight(combination);
        if (totalWeight > mstWeight)
        {
            continue;
        }
        mstCombinations.insert(combination);
    }
    return mstCombinations;
}

void findAllMSTs(vector<pair<int, pair<int, int>>> &graph, int n)
{
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
            }
        }
        if (flag)
        {
            msts.insert(mst);
        }
    }
    cout << "MSTs: " << endl;
    int count = 0;
    for (auto &mst : msts)
    {
        cout << ++count << " : [";
        cout << "[" << mst[0].second.first << "," << mst[0].second.second << "," << mst[0].first << "]";
        for (int i = 1; i < mst.size(); i++)
        {
            cout << ", [" << mst[i].second.first << "," << mst[i].second.second << "," << mst[i].first << "]";
        }
        cout << "]" << endl;
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    int a, b, w;
    vector<pair<int, pair<int, int>>> graph(n, pair<int, pair<int, int>>());
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> w;
        graph.push_back({w, {a, b}});
    }
    findAllMSTs(graph, n);
    fclose(stdin);
    return 0;
}
