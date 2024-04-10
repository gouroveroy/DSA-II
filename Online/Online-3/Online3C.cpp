#include <bits/stdc++.h>
#include "C:\Users\User\OneDrive - BUET\BOOKS 2-1\CSE-207\Offline_Online\Offline\Offline-4\Ford_Fulkerson.h"
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<int>> men;
    vector<vector<int>> women;
    vector<vector<pair<int, int>>> graph(m + n + 2);
    int height, age, id;

    for (int i = 0; i < m; i++)
    {
        cin >> height >> age >> id;
        men.push_back({height, age, id});
    }

    for (int i = 0; i < n; i++)
    {
        cin >> height >> age >> id;
        women.push_back({height, age, id});
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = m + 1; j <= m + n; j++)
        {
            if (abs(men[i - 1][0] - women[j - m - 1][0]) <= 10 && abs(men[i - 1][1] - women[j - m - 1][1]) <= 5)
            {
                graph[i].push_back({j, 1});
            }
        }
    }

    for (int i = 1; i <= m; i++)
    {
        graph[0].push_back({i, 1});
    }

    for (int i = m + 1; i <= m + n; i++)
    {
        graph[i].push_back({m + n + 1, 1});
    }

    FordFulkerson ff(graph, m + n + 2, 0, m + n + 1);
    cout << ff.fordFulkerson() << endl;
    return 0;
}
