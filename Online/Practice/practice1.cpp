#include <bits/stdc++.h>
using namespace std;

vector<int> BFS(vector<vector<int>> &v, int N, int i)
{
    vector<bool> visited(N + 1, false);
    vector<int> distance(N + 1, INT_MAX);
    queue<int> q;
    q.push(i);
    visited[i] = true;
    distance[i] = 0;
    while (!q.empty())
    {
        int node = q.front();
        q.pop();
        for (int j = 0; j < v[node].size(); j++)
        {
            if (!visited[v[node][j]])
            {
                q.push(v[node][j]);
                visited[v[node][j]] = true;
                distance[v[node][j]] = distance[node] + 1;
            }
        }
    }
    return distance;
}

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int>> v(N + 1, vector<int>());
    for (int i = 0; i < M; i++)
    {
        int x, y;
        cin >> x >> y;
        v[x].push_back(y);
    }
    vector<int> distance1 = BFS(v, N, 1);
    vector<int> distance2 = BFS(v, N, 2);
    int Q;
    cin >> Q;
    int min = INT_MAX;
    int a, b;
    for (int i = 0; i < Q; i++)
    {
        int x, y;
        cin >> x >> y;
        if (distance1[x] + distance2[y] + 1 < min)
        {
            min = distance1[x] + distance2[y] + 1;
            a = x;
            b = y;
        }
    }
    cout << a << " " << b << endl;
    cout << min << endl;
    return 0;
}
