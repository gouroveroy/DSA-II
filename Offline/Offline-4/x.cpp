#include <bits/stdc++.h>
using namespace std;

class FordFulkerson
{
    vector<vector<pair<int, int>>> residualGraph;
    vector<int> parent;
    vector<bool> bfsVisited, dfsVisited;
    int vertices, source, sink, maxFlow;

    void memset()
    {
        parent.resize(vertices + 1);
        bfsVisited.assign(vertices + 1, false);
        dfsVisited.assign(vertices + 1, false);
    }

    bool BFS()
    {
        bfsVisited.assign(vertices + 1, false);
        queue<int> q;
        q.push(source);
        parent[source] = -1;
        bfsVisited[source] = true;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto &edge : residualGraph[u])
            {
                if(edge.second == 0) continue;
                int v = edge.first;
                if (!bfsVisited[v])
                {
                    q.push(v);
                    parent[v] = u;
                    bfsVisited[v] = true;
                    // if(v == sink)
                    // {
                    //     return true;
                    // }
                }
            }
        }
        return bfsVisited[sink];
    }

    void DFS(int vertex)
    {
        dfsVisited[vertex] = true;
        for (auto &edge : residualGraph[vertex])
        {
            if(edge.second == 0) continue;
            int v = edge.first;
            if (!dfsVisited[v])
            {
                dfsVisited[v] = true;
                DFS(v);
            }
        }
    }

public:
    FordFulkerson(vector<vector<pair<int, int>>> &residualGraph, int vertices, int source, int sink)
    {
        this->residualGraph = residualGraph;
        this->vertices = vertices;
        this->source = source;
        this->sink = sink;
        memset();
    }

    void fordFulkerson()
    {
        int x;
        maxFlow = 0;
        while (BFS())
        {
            int minPathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                for (auto &edge : residualGraph[u])
                {
                    if (edge.first == v)
                    {
                        int capacity = edge.second;
                        minPathFlow = min(minPathFlow, capacity);
                        break;
                    }
                }
            }
            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                for (auto &edge : residualGraph[u])
                {
                    if (edge.first == v)
                    {
                        edge.second -= minPathFlow;
                        break;
                    }
                }

                bool foundBackwardEdge = false;
                for (auto &edge : residualGraph[v])
                {
                    if (edge.first == u)
                    {
                        edge.second += minPathFlow;
                        foundBackwardEdge = true;
                        break;
                    }
                }

                if (!foundBackwardEdge)
                {
                    residualGraph[v].push_back({u, minPathFlow});
                }
            }
            maxFlow += minPathFlow;
        }
    }

    int maximumFlow()
    {
        fordFulkerson();
        return maxFlow;
    }
};

int main()
{
    freopen("in.txt", "r", stdin);
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
    cout << ff.maximumFlow() << endl;
    fclose(stdin);
    return 0;
}
