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
        parent.resize(vertices);
        bfsVisited.assign(vertices, false);
        dfsVisited.assign(vertices, false);
    }

    bool BFS()
    {
        queue<int> q;
        q.push(source);
        parent[source] = -1;
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto &edge : residualGraph[u])
            {
                int v = edge.first;
                if (!bfsVisited[v])
                {
                    q.push(v);
                    parent[v] = u;
                    bfsVisited[v] = true;
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
                        residualGraph[v].push_back({u, minPathFlow});
                    }
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
