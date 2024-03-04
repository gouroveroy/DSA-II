#include <bits/stdc++.h>
using namespace std;

#define N 100
#define V 2000

class Knapsack
{
    vector<int> weight;
    vector<int> value;
    vector<vector<int>> dp;
    int maximumValue;
    int minimumWeight;
    int columnSize;
    int n, w;

public:
    Knapsack(int n, int w, vector<int> &weight, vector<int> &value, int maxVal)
    {
        this->n = n;
        this->w = w;
        this->maximumValue = 0;
        this->minimumWeight = 0;
        this->weight = weight;
        this->value = value;
        this->columnSize = maxVal;
        dp.resize(n + 1, vector<int>(columnSize + 1, -1));
    }

    int knapsack(int n, int v)
    {
        if (v <= 0)
        {
            return 0;
        }

        if (n == 0)
        {
            return 1e4;
        }

        if (dp[n][v] != -1)
        {
            return dp[n][v];
        }

        int ans = knapsack(n - 1, v);

        if (v - value[n] >= 0)
        {
            ans = min(ans, knapsack(n - 1, v - value[n]) + weight[n]);
        }

        return dp[n][v] = ans;
    }

    pair<int, int> maxValueWeight()
    {
        int max_value = columnSize;
        for (int i = max_value; i >= 0; i--)
        {
            knapsack(n, i);
        }
        for (int i = max_value; i >= 0; i--)
        {
            if (dp[n][i] <= w)
            {
                maximumValue = i;
                minimumWeight = dp[n][i];
                break;
            }
        }
        return {maximumValue, minimumWeight};
    }

    vector<int> getIndices()
    {
        vector<bool> items(n + 1, false);
        for (int j = maximumValue; j > 0;)
        {
            for (int i = n; i > 0;)
            {
                if (dp[i][j] != dp[i - 1][j])
                {
                    items[i] = true;
                    j = j - value[i];
                    i--;
                }

                else
                {
                    i--;
                }
            }
        }

        vector<int> indices;
        for (int i = 1; i < n; i++)
        {
            if (items[i])
            {
                indices.push_back(i);
            }
        }
        reverse(indices.begin(), indices.end());
        return indices;
    }
};
