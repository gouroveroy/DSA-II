#include <bits/stdc++.h>
#include "Ford_Fulkerson.h"
using namespace std;

int main()
{
    freopen("in.txt", "r", stdin);
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> graph(N + 1);
    int u, v, c;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v >> c;
        graph[u].push_back({v, c});
    }

    int s, t;
    cin >> s >> t;
    FordFulkerson ff(graph, N, s, t);
    pair<pair<vector<int>, vector<int>>, int> minCut = ff.minCut();
    vector<int> cut1 = minCut.first.first;
    vector<int> cut2 = minCut.first.second;
    int maxFlow = minCut.second;
    cout << "[{";
    for (int i = 0; i < cut1.size() - 1; i++)
    {
        cout << cut1[i] << ",";
    }
    cout << cut1[cut1.size() - 1] << "}, {";
    for (int i = 0; i < cut2.size() - 1; i++)
    {
        cout << cut2[i] << ",";
    }
    cout << cut2[cut2.size() - 1] << "}]" << endl;
    cout << maxFlow << endl;
    fclose(stdin);
    return 0;
}
