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
    for (auto graphEdge : graph)
    {
        int flag = 0;
        for (auto mst : msts)
        {
            for (auto mstEdge : mst)
            {
                if (mstEdge == graphEdge)
                {
                    flag++;
                    continue;
                }
            }
        }
        if (flag == 0)
        {
            cout << "none" << endl;
        }

        else if (flag == msts.size())
        {
            cout << "any" << endl;
        }

        else
        {
            cout << "at least one" << endl;
        }
    }
    // fclose(stdin);
    return 0;
}
