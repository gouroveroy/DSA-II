#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

class BellManFord
{
    vector<pair<int, pair<int, int>>> graph;
    vector<int> distance;
    int vertices, nodeA, nodeB, lowerWeight, upperWeight, source, destination;

public:
    BellManFord(vector<pair<int, pair<int, int>>> &graph, int vertices, int nodeA, int nodeB, int lowerWeight, int upperWeight, int source, int destination)
    {
        this->graph = graph;
        this->vertices = vertices;
        this->nodeA = nodeA;
        this->nodeB = nodeB;
        this->lowerWeight = lowerWeight;
        this->upperWeight = upperWeight;
        this->source = source;
        this->destination = destination;
    }

    int bellManFord()
    {
        distance.assign(vertices + 1, INF);
        distance[source] = 0;
        for (int i = 1; i < vertices; i++)
        {
            for (auto &edge : graph)
            {
                int u = edge.second.first;
                int v = edge.second.second;
                int w = edge.first;
                if (distance[v] > distance[u] + w)
                {
                    distance[v] = distance[u] + w;
                }
            }
        }

        for (auto &edge : graph)
        {
            int u = edge.second.first;
            int v = edge.second.second;
            int w = edge.first;
            if (distance[v] > distance[u] + w)
            {
                return INF;
            }
        }

        return distance[destination];
    }

    pair<int, int> minDistance()
    {
        int minimumDistance = INF;
        int minimumWeight = INF;
        int previousDistance = bellManFord();
        for (int weight = lowerWeight; weight <= upperWeight; weight++)
        {
            graph.push_back({weight, {nodeA, nodeB}});
            int mind = bellManFord();
            if (mind < previousDistance)
            {
                minimumDistance = mind;
                minimumWeight = weight;
                return {minimumWeight, minimumDistance};
            }
            graph.pop_back();
        }
        return {minimumWeight, minimumDistance};
    }
};

int main()
{
    // freopen("in.txt", "r", stdin);
    int N, M;
    cin >> N >> M;
    vector<pair<int, pair<int, int>>> graph;
    int u, v, w;
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v >> w;
        graph.push_back({w, {u, v}});
    }

    int A, B, L, H, S, D;
    cin >> A >> B;
    cin >> L >> H;
    cin >> S >> D;

    BellManFord bf(graph, N, A, B, L, H, S, D);
    pair<int, int> minimum = bf.minDistance();
    if (minimum.second == INF)
    {
        cout << "impossible" << endl;
    }

    else
    {
        cout << minimum.first << " " << minimum.second << endl;
    }

    // fclose(stdin);
    return 0;
}
