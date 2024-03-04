#include <bits/stdc++.h>
#include "Knapsack.cpp"
// #include "x.cpp"
using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
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

    vector<double> epsilon = {0.5, 0.2, 0.1, 0.05};
    for (auto e : epsilon)
    {
        cout << "Rounded Instance with Eps: " << e << endl;
        double theta = (double)(e * v_max) / (double)(2 * n);

        cout << "Theta: " << setprecision(15) << theta << endl;

        vector<int> roundValues(n + 1);
        for (int i = 1; i <= n; i++)
        {
            roundValues[i] = ceil((double)(value[i] / theta));
        }
        int maxRoundValue = *max_element(roundValues.begin(), roundValues.end());

        maxRoundValue = maxRoundValue * n;
        Knapsack ks(n + 1, w, weight, roundValues, maxRoundValue);
        pair<int, int> reducedInstance = ks.maxValueWeight();
        cout << "Answer of reduced instance: " << reducedInstance.first << endl;
        cout << "Answer of reduced instance multiplied by theta: " << (double)(reducedInstance.first * theta) << endl;

        vector<int> e_indices = ks.getIndices();
        cout << "Indices: ";
        for (auto v : e_indices)
        {
            cout << v << " ";
        }
        cout << endl;

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
