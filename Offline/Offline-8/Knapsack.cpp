#include <bits/stdc++.h>
using namespace std;

#define N 100
#define V 2000

/* This code snippet defines a class named `Knapsack` in C++. The class has member variables `weight`,
`value`, `dp`, `maximumValue`, `minimumWeight`, `columnSize`, `n`, and `w`. Here is a brief
explanation of each member variable: */
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
    /**
     * The function initializes a Knapsack object with given parameters and creates a 2D vector for
     * dynamic programming.
     * 
     * @param n The parameter `n` in the `Knapsack` function represents the number of items available
     * for selection in the knapsack problem.
     * @param w The parameter `w` in the `Knapsack` function represents the maximum weight capacity of
     * the knapsack. This value determines the maximum weight that the knapsack can hold.
     * @param weight The `weight` parameter in the `Knapsack` function represents a vector containing
     * the weights of the items that can be selected for the knapsack problem. Each element in the
     * `weight` vector corresponds to the weight of an item at the same index in the `value` vector.
     * @param value The `value` parameter in the `Knapsack` function represents the values of the items
     * that can be selected for the knapsack problem. Each item has a corresponding value that
     * indicates its worth or benefit. In the context of the knapsack problem, the goal is to maximize
     * the total
     * @param maxVal The `maxVal` parameter in the `Knapsack` function represents the maximum value
     * that can be achieved in the knapsack problem. It is used to determine the size of the dynamic
     * programming table that will be created to store intermediate results during the knapsack
     * algorithm execution.
     */
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

    /**
     * The function `knapsack` implements a dynamic programming solution to the knapsack problem to
     * find the maximum value that can be obtained within a given weight limit.
     * 
     * @param n The parameter `n` in the `knapsack` function represents the number of items available
     * for selection in the knapsack problem. It is typically used to keep track of the current item
     * being considered while solving the knapsack problem recursively.
     * @param v The parameter `v` in the `knapsack` function represents the remaining capacity of the
     * knapsack at a particular stage of the recursive function. It indicates how much weight can still
     * be accommodated in the knapsack.
     * 
     * @return The function `knapsack` is a recursive function that calculates the maximum value that
     * can be obtained within a given weight limit `v` using items from 1 to `n`. The function returns
     * the maximum value that can be achieved within the weight limit `v`.
     */
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

    /**
     * The function `maxValueWeight` calculates the maximum value that can be achieved within a given
     * weight limit using a knapsack algorithm.
     * 
     * @return The `maxValueWeight` function returns a pair of integers, where the first integer
     * represents the maximum value that can be achieved within the weight limit, and the second
     * integer represents the minimum weight required to achieve that maximum value.
     */
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

    /**
     * The function `getIndices` returns a vector of indices based on certain conditions and
     * calculations.
     * 
     * @return The function `getIndices()` returns a vector of integers containing the indices of
     * selected items based on certain conditions in the given code snippet.
     */
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
