#include <bits/stdc++.h>
#include "Knapsack.cpp"
// #include "x.cpp"
using namespace std;

int main()
{
    /* The code snippet you provided is reading input from a file named "input.txt" instead of standard
    input. It redirects the standard input stream to read from this file using `freopen("input.txt",
    "r", stdin);`. */
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n, w;
    cin >> n >> w;
    vector<int> weight(n + 1), value(n + 1);

    for (int i = 1; i <= n; i++)
    {
        cin >> value[i] >> weight[i];
    }

    int v_max = *max_element(value.begin(), value.end());
    int maxVal = v_max * n;

    Knapsack knapsack(n + 1, w, weight, value, maxVal);
    pair<int, int> vw = knapsack.maxValueWeight();

    cout << "Original Instance: " << endl;
    cout << "Answer: " << vw.first << endl;
    cout << "Used Weight: " << vw.second << endl;
    cout << "Indices: ";

    vector<int> indices = knapsack.getIndices();
    for (auto v : indices)
    {
        cout << v << " ";
    }
    cout << endl
         << endl
         << endl;

    /* This part of the code is performing a rounding experiment on the original knapsack instance.
    Here's a breakdown of what it does for each epsilon value in the vector `epsilon`: */
    vector<double> epsilon = {0.5, 0.2, 0.1, 0.05};
    for (auto e : epsilon)
    {
        cout << "Rounded Instance with Eps: " << e << endl;
        /* The line `double theta = (double)(e * v_max) / (double)(2 * n);` is calculating the value of
        `theta` in the rounding experiment for a given epsilon value `e`. Here's a breakdown of the
        calculation: */
        double theta = (double)(e * v_max) / (double)(2 * n);

        cout << "Theta: " << setprecision(15) << theta << endl;

        /* The code snippet you provided is creating a vector `roundValues` of integers with a size of
        `n + 1`. Then, it iterates over each element from 1 to `n` (inclusive) and calculates a
        rounded value for each element based on the division of `value[i]` by `theta`. */
        vector<int> roundValues(n + 1);
        for (int i = 1; i <= n; i++)
        {
            roundValues[i] = ceil((double)(value[i] / theta));
        }
        /* The code snippet you provided is part of a rounding experiment on the original knapsack
        instance. Here's a breakdown of what it does: */
        int maxRoundValue = *max_element(roundValues.begin(), roundValues.end());

        maxRoundValue = maxRoundValue * n;
        Knapsack ks(n + 1, w, weight, roundValues, maxRoundValue);
        pair<int, int> reducedInstance = ks.maxValueWeight();
        cout << "Answer of reduced instance: " << reducedInstance.first << endl;
        cout << "Answer of reduced instance multiplied by theta: " << (double)(reducedInstance.first * theta) << endl;

        /* The code snippet you provided is retrieving the indices of the selected items in the
        knapsack for the reduced instance after rounding the values based on a specific epsilon
        value. Here's a breakdown of what it does: */
        vector<int> e_indices = ks.getIndices();
        cout << "Indices: ";
        for (auto v : e_indices)
        {
            cout << v << " ";
        }
        cout << endl;

        /* This part of the code snippet is calculating and displaying information related to the
        original knapsack instance after rounding up the values based on a specific epsilon value.
        Here's a breakdown of what it does: */
        int originalInstance = 0;
        int usedWeight = 0;
        for (auto index : e_indices)
        {
            originalInstance += value[index];
            usedWeight += weight[index];
        }
        cout << "Answer of original instance (rounded up): " << originalInstance << endl;
        cout << "Used Weight: " << usedWeight << endl;
        cout << "Ratio: " << setprecision(15) << (double)vw.first / (double)originalInstance << endl;
        cout << endl
             << endl;
    }
    return 0;
}
