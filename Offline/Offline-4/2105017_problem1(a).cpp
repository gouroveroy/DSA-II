#include <bits/stdc++.h>
#include "Ford_Fulkerson.h"
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> graph;
    int u, v, c;
    for(int i = 0; i < M; i++)
    {
        cin >> u >> v >> c;
        graph[u].push_back({v, c});
    }
    int s, t;
    cin >> s >> t;
    FordFulkerson ff(graph, N, s, t);
    cout << ff.maximumFlow() << endl;
    return 0;
}
