#include <bits/stdc++.h>
#include "C:\Users\User\OneDrive - BUET\BOOKS 2-1\CSE-207\Offline_Online\Offline\Offline-4\Ford_Fulkerson.h"
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> graph(M + N + 2);
    vector<int> workerStrengths;
    vector<int> taskStrengths;
    for (int i = 0; i < N; i++)
    {
        int x;
        cin >> x;
        workerStrengths.push_back(x);
    }
    for (int i = 0; i < M; i++)
    {
        int x;
        cin >> x;
        taskStrengths.push_back(x);
    }
    for(int i = 1; i <= N; i++)
    {
        for(int j = N + 1; j <= M + N; j++)
        {
            if(workerStrengths[i - 1] >= taskStrengths[j - N - 1])
            {
                graph[i].push_back({j, 1});
            }
        }
    }
    for (int i = 1; i <= N; i++)
    {
        graph[0].push_back({i, 1});
    }
    for (int i = N + 1; i <= M + N; i++)
    {
        graph[i].push_back({M + N + 1, 1});
    }
    FordFulkerson ff(graph, M + N + 2, 0, M + N + 1);
    cout << ff.fordFulkerson() << endl;
    return 0;
}
