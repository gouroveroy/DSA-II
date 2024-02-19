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

    // HashTable ht(5000, 1, 100, 'd');
    // int count = 1;
    // for (auto &word : words)
    // {
    //     // cout << word << endl;
    //     ht.insert(word, count);
    //     count++;
    // }
    // cout << ht.getCollision() << endl;
    // ht.resetProbe();
    // srand(time(NULL));
    // for(int i = 0; i < 1000; i++)
    // {
    //     int j = rand() % TOTAL_WORD;
    //     ht.find(words[j]);
    // }
    // cout << 1.0 * ht.getProbe() / 1000 << endl;

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

            cout << hts.getProbe() << " " << htc.getProbe() << " " << htd.getProbe() << endl;

            report[size]['s'].push_back({hts.getCollision(), 1.0 * hts.getProbe() / TEST_WORD_COUNT});
            report[size]['d'].push_back({htd.getCollision(), 1.0 * htd.getProbe() / TEST_WORD_COUNT});
            report[size]['c'].push_back({htc.getCollision(), 1.0 * htc.getProbe() / TEST_WORD_COUNT});
        }
    }

    cout << report[TEST_WORD_SIZE]['s'][0].first << " " << fixed << setprecision(3) << report[TEST_WORD_SIZE]['s'][0].second << endl;
    cout << report[TEST_WORD_SIZE]['d'][0].first << " " << fixed << setprecision(3) << report[TEST_WORD_SIZE]['d'][0].second << endl;
    cout << report[TEST_WORD_SIZE]['c'][0].first << " " << fixed << setprecision(3) << report[TEST_WORD_SIZE]['c'][0].second << endl;
    cout << report[TEST_WORD_SIZE]['s'][1].first << " " << fixed << setprecision(3) << report[TEST_WORD_SIZE]['s'][1].second << endl;
    cout << report[TEST_WORD_SIZE]['d'][1].first << " " << fixed << setprecision(3) << report[TEST_WORD_SIZE]['d'][1].second << endl;
    cout << report[TEST_WORD_SIZE]['c'][1].first << " " << fixed << setprecision(3) << report[TEST_WORD_SIZE]['c'][1].second << endl;

    Report rp(report);
    rp.createReport();
    return 0;
}

/*
 _____________________________________________________________________
|            |                   | Hash Function 1 | Hash Function 2 |
|            |                   |___________________________________|
| Table Size | Resolution Method | Colls. | Probes | Colls. | Probes |
|____________________________________________________________________|
| N =    5000| Separate Chaining |     123     123 |     123     123 | 
|            | Double Hashing    |     123     123 |     123     123 | 
|            | Custom Probing    |     123     123 |     123     123 | 
|____________________________________________________________________|
| N =   10000| Separate Chaining |     123     123 |     123     123 | 
|            | Double Hashing    |     123     123 |     123     123 | 
|            | Custom Probing    |     123     123 |     123     123 | 
|____________________________________________________________________|
| N =   20000| Separate Chaining |     123     123 |     123     123 | 
|            | Double Hashing    |     123     123 |     123     123 | 
|            | Custom Probing    |     123     123 |     123     123 | 
|____________________________________________________________________|

*/
