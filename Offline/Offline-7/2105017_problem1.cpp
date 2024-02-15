#include <bits/stdc++.h>
#include "RandomWordGenerator.cpp"
#include "x.cpp"
// #include "y.cpp"
// #include "hashtable.cpp"

int main()
{
    HashTable ht(75, 1, 10);
    RandomWordGenerator rwg;

    vector<string> words = rwg.generateRandomWords(100, 5, 10);

    int count = 1;
    for (auto &word : words)
    {
        // cout << word << endl;
        ht.insert(word, count);
        count++;
    }
    return 0;
}
