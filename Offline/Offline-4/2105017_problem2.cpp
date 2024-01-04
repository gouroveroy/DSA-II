#include <bits/stdc++.h>
#include "Ford_Fulkerson.h"
using namespace std;

int main()
{
    int m, n;
    cin >> m >> n;
    vector<vector<int>> men;
    vector<vector<int>> women;
    vector<vector<pair<int, int>>> graph(m + n + 2);
    int height, age, isDivorced;

    for (int i = 0; i < m; i++)
    {
        cin >> height >> age >> isDivorced;
        men.push_back({height, age, isDivorced});
    }

    for (int i = 0; i < n; i++)
    {
        cin >> height >> age >> isDivorced;
        women.push_back({height, age, isDivorced});
    }

    for (int i = 1; i <= m; i++)
    {
        for (int j = m + 1; j <= m + n; j++)
        {
            if (abs(men[i - 1][0] - women[j - m - 1][0]) <= 10 && abs(men[i - 1][1] - women[j - m - 1][1]) <= 5 && (men[i - 1][2] == women[j - m - 1][2]))
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
