#include <bits/stdc++.h>
using namespace std;

// This function returns the total weight of a given graph
int weight(vector<pair<int, pair<int, int>>> graph)
{
    int totalWeight = 0;
    for (auto &edge : graph)
    {
        totalWeight += edge.first;
    }
    return totalWeight;
}

// This function returns all possible graphs containing given number of edges from a given graph
void edgeCombinations(int index, int mstEdge, vector<pair<int, pair<int, int>>> &graph, set<vector<pair<int, pair<int, int>>>> &combinatons, vector<pair<int, pair<int, int>>> &trees)
{
    if (mstEdge == 0)
    {
        combinatons.insert(trees);
    }

    if (index >= graph.size())
    {
        return;
    }

    trees.push_back(graph[index]);
    edgeCombinations(index + 1, mstEdge - 1, graph, combinatons, trees);
    trees.pop_back();
    edgeCombinations(index + 1, mstEdge, graph, combinatons, trees);
}

// This function returns all possible graph with given number of edges of a graph that weighs the mst weight of the graph
set<vector<pair<int, pair<int, int>>>> allPossibleGraphCombinations(vector<pair<int, pair<int, int>>> &graph, int mstEdge, int mstWeight)
{
    set<vector<pair<int, pair<int, int>>>> mstCombinations;
    set<vector<pair<int, pair<int, int>>>> combinations;
    vector<pair<int, pair<int, int>>> trees;
    edgeCombinations(0, mstEdge, graph, combinations, trees);
    for (auto &combination : combinations)
    {
        int totalWeight = weight(combination);
        if (totalWeight > mstWeight)
        {
            continue;
        }
        mstCombinations.insert(combination);
    }
    return mstCombinations;
}
