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
    vector<int> criticalEdge, pseudoCriticalEdge;
    int counter = 0;
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
            continue;
        }

        else if (flag == msts.size())
        {
            criticalEdge.push_back(counter);
        }

        else
        {
            pseudoCriticalEdge.push_back(counter);
        }
        counter++;
    }
    cout << "Critical edges: ";
    if (criticalEdge.size() == 0)
    {
        cout << "[]," << endl;
    }
    else if (criticalEdge.size() == 1)
    {
        cout << "[" << criticalEdge[0] << "]," << endl;
    }
    else
    {
        cout << "[" << criticalEdge[0];
        for (int i = 1; i < criticalEdge.size(); i++)
        {
            cout << "," << criticalEdge[i];
        }
        cout << "] " << endl;
    }

    cout << "Pseudo critical edges: ";
    if (pseudoCriticalEdge.size() == 0)
    {
        cout << "[]," << endl;
    }
    else if (pseudoCriticalEdge.size() == 1)
    {
        cout << "[" << pseudoCriticalEdge[0] << "]," << endl;
    }
    else
    {
        cout << "[" << pseudoCriticalEdge[0];
        for (int i = 1; i < pseudoCriticalEdge.size(); i++)
        {
            cout << "," << pseudoCriticalEdge[i];
        }
        cout << "] " << endl;
    }
    // fclose(stdin);
    return 0;
}
