#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

class FloydWarshall
{
    vector<pair<int, pair<int, int>>> graph;
    vector<vector<int>> shortestPath;
    int vertices, thresholdCost;

    void buildMatrix()
    {
        for (int i = 1; i <= vertices; i++)
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
    FloydWarshall(vector<pair<int, pair<int, int>>> &graph, int vertices, int cost)
    {
        this->graph = graph;
        this->vertices = vertices;
        this->thresholdCost = cost;
        shortestPath.assign(vertices + 1, vector<int>(vertices + 1, INF));
        buildMatrix();
    }

    void floydWarshall()
    {
        for (int k = 1; k <= vertices; k++)
        {
            for (int i = 1; i <= vertices; i++)
            {
                for (int j = 1; j <= vertices; j++)
                {
                    if (shortestPath[i][k] != INF && shortestPath[k][j] != INF)
                    {
                        shortestPath[i][j] = min(shortestPath[i][j], shortestPath[i][k] + shortestPath[k][j]);
                    }
                }
            }
        }
    }

    void printCity()
    {
        map<int, int> city;
        int cityCount = INT_MAX;
        for(int i = 1; i <= vertices; i++)
        {
            int count = 0;
            for(int j = 1; j <= vertices; j++)
            {
                if(shortestPath[i][j] <= thresholdCost && shortestPath[i][j] != 0)
                {
                    count++;
                }
            }
            city[i] = count;
            if(count <= cityCount)
            {
                cityCount = count;
            }
        }
        for(int i = 1; i <= vertices; i++)
        {
            if(city[i] == cityCount)
            {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    void printMatrix()
    {
        for (int i = 1; i <= vertices; i++)
        {
            for (int j = 1; j <= vertices; j++)
            {
                if (shortestPath[i][j] == INF)
                {
                    cout << 'I' << " ";
                }

                else
                {
                    cout << shortestPath[i][j] << " ";
                }
            }
            cout << endl;
        }
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
        graph.push_back({w, {u, v}});
    }

    int cost;
    cin >> cost;

    FloydWarshall fw(graph, n, cost);
    fw.floydWarshall();
    fw.printMatrix();
    cout << endl;
    fw.printCity();

    fclose(stdin);
    return 0;
}
