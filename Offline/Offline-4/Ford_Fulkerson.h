#include <bits/stdc++.h>
using namespace std;

class FordFulkerson
{
    vector<vector<pair<int, int>>> residualGraph;
    vector<int> parent, inflow, outflow;
    vector<bool> bfsVisited, dfsVisited;
    int vertices, source, sink, maxFlow;

    void memset()
    {
        parent.resize(vertices + 1);
        inflow.assign(vertices + 1, 0);
        outflow.assign(vertices + 1, 0);
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
                if (edge.second == 0)
                {
                    continue;
                }
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
            if (edge.second == 0)
            {
                continue;
            }
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
        int maxPathFlow = INT_MIN;
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
                        inflow[v] += edge.second;
                        outflow[u] += minPathFlow;
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

    pair<int, int> maximumNodeFlow()
    {
        fordFulkerson();
        int maxInOutFlow = INT_MIN;
        int maxNodeFlow;
        for (int i = 1; i <= vertices; i++)
        {
            if (i != source && i != sink)
            {
                if (inflow[i] + outflow[i] > maxInOutFlow)
                {
                    maxInOutFlow = inflow[i] + outflow[i];
                    maxNodeFlow = i;
                }
            }
        }
        maxInOutFlow = max(inflow[maxNodeFlow], outflow[maxInOutFlow]);
        return {maxNodeFlow, maxInOutFlow};
    }

    pair<pair<vector<int>, vector<int>>, int> minCut()
    {
        fordFulkerson();
        DFS(source);
        vector<int> cut1, cut2;
        cut1.push_back(source);
        for (int i = 1; i <= vertices; i++)
        {
            if (i != source && i != sink)
            {
                if (dfsVisited[i])
                {
                    cut1.push_back(i);
                }

                else
                {
                    cut2.push_back(i);
                }
            }
        }
        cut2.push_back(sink);
        return {{cut1, cut2}, maxFlow};
    }
};
