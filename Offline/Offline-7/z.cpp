#include <bits/stdc++.h>
using namespace std;

int main()
{
    map<int, map<char, vector<pair<int, int>>>> report;

    // Initialize report
    for (int i = 0; i < 10; ++i)
    {
        for (char c = 'a'; c <= 'z'; ++c)
        {
            // Initialize inner map
            report[i][c] = vector<pair<int, int>>();

            // Populate vector with pairs
            for (int j = 0; j < 5; ++j)
            {
                report[i][c].push_back(make_pair(j, j * 10));
            }
        }
    }

    // Access and print some values
    cout << "report[3]['c'][2].first: " << report[3]['c'][2].first << endl;
    cout << "report[3]['c'][2].second: " << report[3]['c'][2].second << endl;

    return 0;
}
