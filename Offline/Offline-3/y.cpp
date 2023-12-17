// Leetcode problem
#include <bits/stdc++.h>
using namespace std;

class Solution {
    vector<pair<int, pair<int, int>>> graph;
    vector<vector<int>> shortestPath;
    int vertices, thresholdCost;

    void buildMatrix()
    {
        for (int i = 0; i < vertices; i++)
        {
            shortestPath[i][i] = 0;
        }

        for (auto &edge : graph)
        {
            int u = edge.second.first;
            int v = edge.second.second;
            int w = edge.first;
            shortestPath[u][v] = w;
            shortestPath[v][u] = w;
        }
    }
public:
    int findTheCity(vector<pair<int, pair<int, int>>>& graph, int n, int distanceThreshold) {
        this->vertices = n;
        this->thresholdCost = distanceThreshold;
        this->graph = graph;
        // for(auto &edge : edges)
        // {
        //     graph.push_back({edge[2], {edge[0], edge[1]}});
        // }
        shortestPath.assign(vertices + 1, vector<int>(vertices + 1, INT_MAX));
        buildMatrix();
        floydWarshall();
        return printCity();
    }

    void floydWarshall()
    {
        for (int k = 0; k < vertices; k++)
        {
            for (int i = 0; i < vertices; i++)
            {
                for (int j = 0; j < vertices; j++)
                {
                    if (shortestPath[i][k] != INT_MAX && shortestPath[k][j] != INT_MAX)
                    {
                        shortestPath[i][j] = min(shortestPath[i][j], shortestPath[i][k] + shortestPath[k][j]);
                    }
                }
            }
        }
    }

    int printCity()
    {
        int cityCount = INT_MAX;
        int ans;
        for(int i = 0; i < vertices; i++)
        {
            int count = 0;
            for(int j = 0; j < vertices; j++)
            {
                if(shortestPath[i][j] <= thresholdCost && i != j)
                {
                    count++;
                }
            }
            if(count <= cityCount)
            {
                ans = i;
                cityCount = count;
            }
        }
        return ans;
    }
};

int main()
{
    freopen("in.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<pair<int, pair<int, int>>> graph;
    int u, v, w;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        graph.push_back({w, {--u, --v}});
    }

    int cost;
    cin >> cost;

    Solution sl;
    cout << sl.findTheCity(graph, n, cost) << endl;
    return 0;
}
