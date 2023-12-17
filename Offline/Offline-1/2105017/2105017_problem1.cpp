#include <bits/stdc++.h>
#include "AllMST.h"
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    int a, b, w;
    vector<pair<int, pair<int, int>>> graph;
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> w;
        graph.push_back({w, {a, b}});
    }
    set<vector<pair<int, pair<int, int>>>> msts = findAllMSTs(graph, n);
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
    // fclose(stdin);
    return 0;
}
