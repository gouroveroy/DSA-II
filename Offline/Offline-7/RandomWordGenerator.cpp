#include <bits/stdc++.h>
using namespace std;

class RandomWordGenerator
{
    string generateRandomWord(int minLength, int maxLength)
    {
        static const string alphabet = "abcdefghijklmnopqrstuvwxyz";
        static random_device rd;
        static mt19937 gen(rd());
        uniform_int_distribution<int> lengthDist(minLength, maxLength);
        uniform_int_distribution<int> charDist(0, alphabet.size() - 1);

        int length = lengthDist(gen);
        string word;
        for (int i = 0; i < length; ++i)
        {
            word += alphabet[charDist(gen)];
        }
        return word;
    }

    void shuffle(vector<string> &words)
    {
        srand(time(0));
        int length = words.size();

        for (int i = 0; i < length; i++)
        {
            int j = rand() % length;
            swap(words[i], words[j]);
        }
    }

public:
    RandomWordGenerator() = default;

    vector<string> generateRandomWords(int count, int minLength, int maxLength)
    {
        vector<string> words;
        for (int i = 0; i < count; ++i)
        {
            words.push_back(generateRandomWord(minLength, maxLength));
        }
        shuffle(words);
        return words;
    }
};
