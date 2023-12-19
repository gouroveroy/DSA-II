#include <bits/stdc++.h>
using namespace std;

vector<int> dist;
vector<int> prec;

void dijkstra(vector<vector<pair<int, int>>> &graph, int N)
{
    dist.assign(N + 1, INT_MAX);
    prec.assign(N + 1, -1);
    dist[1] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, 1});
    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();
        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;
            if (dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                prec[v] = u;
            }
        }
    }
    cout << dist[N] << endl;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> graph(N + 1);
    vector<int> tax(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> tax[i];
    }
    int u, v;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v;
        graph[u].push_back({v, tax[v]});
        graph[v].push_back({u, tax[u]});
    }
    dijkstra(graph, N);
    return 0;
}
