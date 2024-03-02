#include <bits/stdc++.h>
#include "RandomWordGenerator.cpp"
#include "HashTable.cpp"
#include "Report.cpp"
using namespace std;

#define MAX_CHAIN_LENGTH 15
#define TOTAL_WORD 10000
#define MIN_WORD_LENGTH 5
#define MAX_WORD_LENGTH 10
#define TEST_WORD_COUNT 1000
#define TEST_WORD_SIZE 10000

int main()
{
    RandomWordGenerator rwg;
    vector<string> words = rwg.generateRandomWords(TOTAL_WORD, MIN_WORD_LENGTH, MAX_WORD_LENGTH);

    vector<int> sizeOfWords = {5000, 10000, 20000};
    map<long long, map<char, vector<pair<long long, double>>>> report;

    for (int &size : sizeOfWords)
    {
        for (int i = 1; i <= 2; i++)
        {
            HashTable hts(size, i, MAX_CHAIN_LENGTH, 's');
            HashTable htd(size, i, MAX_CHAIN_LENGTH, 'd');
            HashTable htc(size, i, MAX_CHAIN_LENGTH, 'c');
            long long count = 1;

            for (auto &word : words)
            {
                hts.insert(word, count);
                htd.insert(word, count);
                htc.insert(word, count);
                count++;
            }

            hts.resetProbe();
            htd.resetProbe();
            htc.resetProbe();

            srand(time(NULL));
            for (int k = 0; k < TEST_WORD_COUNT; k++)
            {
                int j = rand() % TOTAL_WORD;
                hts.find(words[j]);
                htd.find(words[j]);
                htc.find(words[j]);
            }

            report[size]['s'].push_back({hts.getCollision(), 1.0 * hts.getProbe() / TEST_WORD_COUNT});
            report[size]['d'].push_back({htd.getCollision(), 1.0 * htd.getProbe() / TEST_WORD_COUNT});
            report[size]['c'].push_back({htc.getCollision(), 1.0 * htc.getProbe() / TEST_WORD_COUNT});
        }
    }

    Report rp(report);
    rp.createReport();
    return 0;
}
