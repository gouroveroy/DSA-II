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

    int bellManFord(int start)
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
        int previousDistance = bellManFord(source);
        int distance1 = distance[nodeA];
        int previousDistance2 = bellManFord(nodeB);
        int distance2 = distance[destination];
        int distance3 = distance[nodeA];
        int ans = 0;

        if (distance3 == INF)
        {
            ans = distance1 + lowerWeight + distance2;
            if (ans < previousDistance)
            {
                return {lowerWeight, ans};
            }

            else
            {
                return {lowerWeight, INF};
            }
        }

        else
        {
            distance3 = -distance3;
            ans = distance1 + distance2;
            if (distance3 < lowerWeight)
            {
                ans += lowerWeight;
                if (ans < previousDistance)
                {
                    return {lowerWeight, ans};
                }

                else
                {
                    return {lowerWeight, INF};
                }
            }

            else if (lowerWeight <= distance3 <= upperWeight)
            {
                ans += distance3;
                if (ans < previousDistance)
                {
                    return {distance3, ans};
                }

                else
                {
                    return {lowerWeight, INF};
                }
            }

            else
            {
                return {lowerWeight, INF};
            }
        }
    }
};

int main()
{
    freopen("in.txt", "r", stdin);
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

    fclose(stdin);
    return 0;
}
