#include <bits/stdc++.h>
#include "C:\Users\User\OneDrive - BUET\BOOKS 2-1\CSE-207\Offline_Online\Offline\Offline-4\Ford_Fulkerson.h"
using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<pair<int, int>>> graph(M + N + 2);
    string s;
    vector<int> v;
    for (int i = 0; i < M; i++)
    {
        char ch;
        cin >> ch;
        getline(cin, s);
        for (int j = 0; j < s.length(); j++)
        {
            if (s[j] != ' ')
            {
                v.push_back(s[j] - '0' + N);
            }
        }
        int x = ch - '0';
        for (int j = 0; j < v.size(); j++)
        {
            graph[x].push_back({v[j], 1});
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
