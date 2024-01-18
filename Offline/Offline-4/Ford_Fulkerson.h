#include <bits/stdc++.h>
using namespace std;

class FordFulkerson
{
    vector<vector<pair<int, int>>> residualGraph;
    vector<int> parent, inflow, outflow;
    vector<bool> bfsVisited, dfsVisited;
    int vertices, source, sink, maxFlow;

    // The `memset()` function is a helper function used in the `FordFulkerson` class. It is used to initialize the `parent`, `inflow`, `outflow`, `bfsVisited`, and `dfsVisited` vectors with their initial values.
    void memset()
    {
        parent.resize(vertices + 1);
        inflow.assign(vertices + 1, 0);
        outflow.assign(vertices + 1, 0);
        bfsVisited.assign(vertices + 1, false);
        dfsVisited.assign(vertices + 1, false);
    }

    // The `BFS()` function in the `FordFulkerson` class is used to perform a Breadth-First Search (BFS) traversal on the residual graph to find an augmenting path from the source vertex to the sink vertex. Here's a step-by-step explanation of what the function does:
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

    // The `DFS` function in the `FordFulkerson` class is used to perform a Depth-First Search (DFS) traversal on the residual graph. It starts at a given vertex and recursively explores all the vertices reachable from it.
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
    // The `FordFulkerson` constructor initializes the `residualGraph`, `vertices`, `source`, and `sink` variables of the `FordFulkerson` class. It takes in a `residualGraph` which is a vector of vectors of pairs representing the residual graph, `vertices` which is the number of vertices in the graph, `source` which is the source vertex, and `sink` which is the sink vertex.
    FordFulkerson(vector<vector<pair<int, int>>> &residualGraph, int vertices, int source, int sink)
    {
        this->residualGraph = residualGraph;
        this->vertices = vertices;
        this->source = source;
        this->sink = sink;
        memset();
    }

    // The `fordFulkerson()` function implements the Ford-Fulkerson algorithm to find the maximum flow in a flow network. Here's a step-by-step explanation of what the function does:
    int fordFulkerson()
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
                        inflow[v] += minPathFlow;
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
        return maxFlow;
    }

    // The `maximumNodeFlow()` function is used to find the node in the graph with the maximum flow.
    pair<int, int> maximumNodeFlow()
    {
        fordFulkerson();
        int maxInOutFlow = INT_MIN;
        int maxNodeFlow = source;
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
        maxInOutFlow = max(inflow[maxNodeFlow], outflow[maxNodeFlow]);
        return {maxNodeFlow, maxInOutFlow};
    }

    // The `minCut()` function in the `FordFulkerson` class is used to find the minimum cut in the flow network. Here's a step-by-step explanation of what the function does:
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
