#include <bits/stdc++.h>
using namespace std;

#define N 100
#define V 2000

class Knapsack
{
    vector<double> weight;
    vector<double> value;
    vector<vector<double>> dp;
    double maximumValue;
    double minimumWeight;
    double columnSize;
    double n, w;

public:
    Knapsack(double n, double w, vector<double> &weight, vector<double> &value, double maxVal)
    {
        this->n = n;
        this->w = w;
        this->maximumValue = 0;
        this->minimumWeight = 0;
        this->weight = weight;
        this->value = value;
        this->columnSize = maxVal;
        dp.resize(n + 1, vector<double>(columnSize + 1, -1));
    }

    double knapsack(double n, double v)
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

        double ans = knapsack(n - 1, v);

        if (v - value[n] >= 0)
        {
            ans = min(ans, knapsack(n - 1, v - value[n]) + weight[n]);
        }

        return dp[n][v] = ans;
    }

    pair<double, double> maxValueWeight()
    {
        double max_value = columnSize;
        for (double i = max_value; i >= 0; i--)
        {
            knapsack(n, i);
        }
        for (double i = max_value; i >= 0; i--)
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
        for (double j = maximumValue; j > 0;)
        {
            for (double i = n; i > 0;)
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
