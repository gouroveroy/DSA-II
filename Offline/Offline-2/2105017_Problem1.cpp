#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX

class Dijkstra
{
    vector<vector<vector<pair<int, pair<int, int>>>>> graph;
    vector<vector<int>> distance;
    vector<int> gas_prices;
    int vertices, source, destination, gas_capacity;

public:
    Dijkstra(vector<vector<vector<pair<int, pair<int, int>>>>> &graph, vector<int> &gas_prices, int vertices, int gas_capacity, int source, int destination)
    {
        this->vertices = vertices;
        this->graph = graph;
        this->gas_prices = gas_prices;
        this->gas_capacity = gas_capacity;
        this->source = source;
        this->destination = destination;
        distance.assign(101, vector<int>(101, INF));
    }

    void buildStateGraph()
    {
        for (int i = 1; i <= vertices; i++)
        {
            for (int j = 0; j <= gas_capacity; j++)
            {
                for (int k = j + 1; k <= gas_capacity; k++)
                {
                    int weight = (k - j) * gas_prices[i - 1];
                    graph[i][j].push_back({weight, {i, k}});
                }
            }
        }
    }

    int minMoney()
    {
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        pq.push({0, {source, 0}});
        distance[source][0] = 0;

        while (!pq.empty())
        {
            int u = pq.top().second.first;
            int u_gas = pq.top().second.second;
            int d = pq.top().first;
            pq.pop();

            for (auto &edge : graph[u][u_gas])
            {
                int v = edge.second.first;
                int v_gas = edge.second.second;
                int weight = edge.first;

                if (distance[v][v_gas] > distance[u][u_gas] + weight)
                {
                    distance[v][v_gas] = distance[u][u_gas] + weight;
                    pq.push({distance[v][v_gas], {v, v_gas}});
                }
            }
        }
        return distance[destination][0];
    }
};

int main()
{
    // freopen("in.txt", "r", stdin);
    int N, M, C;
    cin >> N >> M >> C;
    vector<int> gas_prices;

    for (int i = 0; i < N; i++)
    {
        int g;
        cin >> g;
        gas_prices.push_back(g);
    }

    int u, v, d;
    vector<vector<vector<pair<int, pair<int, int>>>>> graph(101, vector<vector<pair<int, pair<int, int>>>>(101, vector<pair<int, pair<int, int>>>()));
    for (int i = 0; i < M; i++)
    {
        cin >> u >> v >> d;
        if (d > C)
        {
            continue;
        }
        for (int j = 0; j <= C; j++)
        {
            for (int k = 0; k <= C; k++)
            {
                // This condition checks whether the sum of the weight of the road (w)
                // and the remaining fuel at vertex u (k) exceeds the gas tank capacity (C).
                // If this is true, it means that taking the road from u to v
                // and reaching v would require more fuel than the gas tank capacity allows.
                if (d + k > C)
                {
                    continue;
                }

                // This condition checks whether the difference between the weight of the road (w),
                // the remaining fuel at vertex u (k), and the remaining fuel at vertex v (j) is negative.
                // If this is true, it means that the calculation results in a negative value,
                // which is not meaningful in the context of fuel.
                else if (d + k - j < 0)
                {
                    continue;
                }

                else
                {
                    graph[u][j].push_back({(d + k - j) * gas_prices[u - 1], {v, k}});
                }
            }
        }
    }

    int S, D;
    cin >> S >> D;

    Dijkstra dj(graph, gas_prices, N, C, S, D);
    // This code works without running the buildStateGraph function, but I explicitly built the state graph.
    dj.buildStateGraph();
    int money = dj.minMoney();

    if (money == INF)
    {
        cout << "impossible" << endl;
    }

    else
    {
        cout << money << endl;
    }

    // fclose(stdin);
    return 0;
}
