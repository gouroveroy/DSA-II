#include <bits/stdc++.h>
using namespace std;

using namespace std;

struct Item
{
    int value;
    int weight;
};

vector<Item> generateRandomItems(int numItems, int minValue, int maxValue, int minWeight, int maxWeight)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> valueDist(minValue, maxValue);
    uniform_int_distribution<int> weightDist(minWeight, maxWeight);

    vector<Item> items;
    for (int i = 0; i < numItems; ++i)
    {
        Item item;
        item.value = valueDist(gen);   // Generate random value within the specified range
        item.weight = weightDist(gen); // Generate random weight
        items.push_back(item);
    }

    return items;
}

int main()
{
    int numItems = 30;   // Number of items to generate
    int minValue = 561;  // Minimum value for an item
    int maxValue = 563; // Maximum value for an item
    int maxWeight = 29;  // Maximum weight for an item
    int minWeight = 27;  // Maximum weight for an item

    vector<Item> items = generateRandomItems(numItems, minValue, maxValue, minWeight, maxWeight);

    // Print the generated items
    cout << 60 << " " << 1020 << endl;
    for (const auto &item : items)
    {
        cout << item.value << " " << item.weight << endl;
        // cout << "Value: " << item.value << ", Weight: " << item.weight << endl;
    }
    return 0;
}
