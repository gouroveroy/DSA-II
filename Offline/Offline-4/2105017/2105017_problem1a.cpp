#include <bits/stdc++.h>
#include "Ford_Fulkerson.h"
using namespace std;

int main()
{
    // freopen("in.txt", "r", stdin);
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> graph(N + 1);
    int u, v, c;
    for(int i = 0; i < M; i++)
    {
        cin >> u >> v >> c;
        graph[u].push_back({v, c});
    }
    
    int s, t;
    cin >> s >> t;
    FordFulkerson ff(graph, N, s, t);
    pair<int, int> max = ff.maximumNodeFlow();
    int n_max = max.first;
    int f_max = max.second;
    cout << n_max << " " << f_max << endl;
    // fclose(stdin);
    return 0;
}
