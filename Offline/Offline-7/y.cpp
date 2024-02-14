#include <bits/stdc++.h>
using namespace std;

class HashTable
{
    vector<list<pair<string, int>>> separateChain;
    vector<pair<string, int>> doubleHash;
    vector<pair<string, int>> customProbe;
    int probCount;
    int N;
    int capacity;
    int size;
    int hashNo;
    int chainLength;
    int insertionCount;
    int deletionCount;
    char collisionStrategy;

    bool isPrime(int n)
    {
        if (n <= 1)
        {
            return false;
        }

        if (n <= 3)
        {
            return true;
        }

        if (n % 2 == 0 || n % 3 == 0)
        {
            return false;
        }

        for (int i = 5; i * i <= n; i += 6)
        {
            if (n % i == 0 || n % (i + 2) == 0)
            {
                return false;
            }
        }
        return true;
    }

    int nextPrime(int n)
    {
        if (n <= 1)
        {
            return 2;
        }
        int prime = n;
        bool found = false;
        while (!found)
        {
            if (isPrime(prime))
            {
                found = true;
            }
            prime++;
        }
        return prime;
    }

    /**
     * The function Hash1 calculates a hash value for a given key using a combination of bitwise
     * operations and modular arithmetic.
     *
     * @param key The key parameter is of type K, which represents the type of the key being hashed. It
     * is used to calculate the hash value for the given key.
     *
     * @return The function `Hash1` returns an integer value, which is the hash value of the given key.
     */
    int Hash1(string key)
    {
        int p = nextPrime(2 * capacity);
        int m = capacity;

        string word = key;
        int l = word.size() - 1;
        int k = 0;
        for (char c : word)
        {
            k += ((c - 'a') * (1 << l));
            l--;
        }

        int hashValue = ((2 * k + 3) % p) % m;
        return hashValue;

        // const int p = nextPrime(2 * capacity);
        // const int m = capacity;

        // int hashValue = 0;
        // for (char c : key)
        // {
        //     hashValue = (hashValue * 31 + (c - 'a' + 1)) % p; // Using a prime multiplier and adding character value
        // }

        // return hashValue % m;
    }

    /**
     * The function Hash2 calculates a hash value for a given key using a combination of bitwise
     * operations and modular arithmetic.
     *
     * @param key The key parameter is of type K, which is not specified in the code snippet. It could
     * be any type that can be converted to a string, such as a string itself or a custom class with a
     * conversion operator to string.
     *
     * @return the hash value of the given key.
     */
    int Hash2(string key)
    {
        int p = nextPrime(5 * capacity);
        int m = capacity;

        string word = key;
        int l = word.size() - 1;
        int k = 0;
        for (char c : word)
        {
            k += ((c - 'a') * (1 << l));
            l--;
        }

        int hashValue = ((5 * k + 7) % p) % m;
        return hashValue;
    }

    int auxHash(string key)
    {
        string word = key;
        int l = word.size() - 1;
        int k = 0;
        for (char c : word)
        {
            k += ((c - 'a') * (1 << l));
            l--;
        }

        double A = (sqrt(5) - 1) / 2;
        int hashValue = floor(capacity * (k * A - floor(k * A)));
        return hashValue;
    }

    void separateChaining(pair<string, int> p, int index)
    {
        separateChain[index].push_front(p);
        size++;
    }

    void doubleHashing(pair<string, int> p)
    {
        int hashValue = 0;
        if (hashNo == 1)
        {
            for (int i = 0; i < capacity; i++)
            {
                hashValue = (Hash1(p.first) + i * auxHash(p.first)) % capacity;
                if (doubleHash[hashValue].first == "")
                {
                    doubleHash[hashValue] = p;
                    return;
                }
            }
        }

        else
        {
            for (int i = 0; i < capacity; i++)
            {
                hashValue = (Hash2(p.first) + i * auxHash(p.first)) % capacity;
                if (doubleHash[hashValue].first == "")
                {
                    doubleHash[hashValue] = p;
                    return;
                }
            }
        }
    }

    void customProbing(pair<string, int> p)
    {
        int hashValue = 0;
        int C1 = 2;
        int C2 = 3;
        if (hashNo == 1)
        {
            for (int i = 0; i < capacity; i++)
            {
                hashValue = (Hash1(p.first) + C1 * i * auxHash(p.first) + C2 * i * i) % capacity;
                if (customProbe[hashValue].first == "")
                {
                    customProbe[hashValue] = p;
                    return;
                }
            }
        }

        else
        {
            for (int i = 0; i < capacity; i++)
            {
                hashValue = (Hash2(p.first) + C1 * i * auxHash(p.first) + C2 * i * i) % capacity;
                if (customProbe[hashValue].first == "")
                {
                    customProbe[hashValue] = p;
                    return;
                }
            }
        }
    }

    double averageProbeCount()
    {
        double threshold = 0.1 * capacity;
        int searchCount = 0;
        int count = 0;
        for (int i = 0; i < capacity; i++)
        {
            for (auto it = separateChain[i].begin(); it != separateChain[i].end(); ++it)
            {
                searchCount++;
                find(it->first);
                count += probCount;
                probCount = 0;
                if (searchCount > threshold)
                {
                    return 1.0 * count / threshold;
                }
            }
        }
    }

    double loadFactor()
    {
        return 1.0 * size / capacity;
    }

    void rehash(int C)
    {
        cout << "Average probe count: " << averageProbeCount() << endl;
        cout << "Load factor: " << loadFactor() << endl;
        cout << "Maximum chain length: " << C << endl
             << endl;

        if (collisionStrategy == 's')
        {
            vector<list<pair<string, int>>> temp = separateChain;
            if (C > chainLength)
            {
                capacity = nextPrime(2 * capacity);
            }

            else if (C < 0.8 * chainLength)
            {
                if (nextPrime(int(capacity / 2) < N))
                {
                    return;
                }
                capacity = nextPrime(int(capacity / 2));
            }

            separateChain.clear();
            separateChain.assign(capacity, list<pair<string, int>>());
            for (int i = 0; i < temp.size(); i++)
            {
                for (auto it = temp[i].begin(); it != temp[i].end(); ++it)
                {
                    hashNo == 1 ? separateChaining(*it, Hash1(it->first)) : separateChaining(*it, Hash2(it->first));
                }
            }
        }

        // else if (collisionStrategy == 'd')
        // {
        //     vector<pair<string, int>> temp = doubleHash;
        //     capacity = nextPrime(2 * capacity);
        //     doubleHash.clear();
        //     doubleHash.resize(capacity, pair<string, int>());
        //     for (int i = 0; i < temp.size(); i++)
        //     {
        //         if (temp[i].first != 0)
        //         {
        //             insert(temp[i].first, temp[i].second);
        //         }
        //     }
        // }

        // else if (collisionStrategy == 'c')
        // {
        //     vector<pair<string, int>> temp = customProbe;
        //     capacity = nextPrime(2 * capacity);
        //     customProbe.clear();
        //     customProbe.resize(capacity, pair<string, int>());
        //     for (int i = 0; i < temp.size(); i++)
        //     {
        //         if (temp[i].first != 0)
        //         {
        //             insert(temp[i].first, temp[i].second);
        //         }
        //     }
        // }

        cout << "Average probe count: " << averageProbeCount() << endl;
        cout << "Load factor: " << loadFactor() << endl;
        cout << "Maximum chain length: " << C << endl
             << endl;
    }

public:
    HashTable(int capacity = 1, int hashNo = 1, int chainLength = INT_MAX, char collisionStrategy = 's')
    {
        this->capacity = nextPrime(capacity);
        this->probCount = 0;
        this->N = capacity;
        this->hashNo = hashNo;
        this->chainLength = chainLength;
        this->insertionCount = 0;
        this->deletionCount = 0;
        this->collisionStrategy = collisionStrategy;
        this->size = 0;
        this->separateChain.assign(capacity + 1, list<pair<string, int>>(capacity + 1));
        this->doubleHash.assign(capacity + 1, pair<string, int>());
        this->customProbe.assign(capacity + 1, pair<string, int>());
    }

    void insert(string key, int value)
    {
        insertionCount++;
        pair<string, int> p = make_pair(key, value);
        int index = 0;
        if (hashNo == 1)
        {
            index = Hash1(key);
        }

        else
        {
            index = Hash2(key);
        }

        cout << index << endl;

        if (collisionStrategy == 's')
        {
            if (find(key) != 0)
            {
                return;
            }
            bool inserted = false;
            if (separateChain[index].empty())
            {
                cout << "hello123" << endl;
                separateChain[index].insert(separateChain[index].begin(), p);
                size++;
                inserted = true;
            }

            if (!inserted)
            {
                for (auto it = separateChain[index].begin(); it != separateChain[index].end(); ++it)
                {
                    if (it->first == key)
                    {
                        return;
                    }
                }
                separateChaining(p, index);
            }

            if (insertionCount >= 10)
            {
                int maxChainLength = 0;
                for (int i = 0; i < separateChain.size(); i++)
                {
                    maxChainLength = max(maxChainLength, int(separateChain[i].size()));
                }
                rehash(maxChainLength);
                insertionCount = 0;
            }
        }

        else if (collisionStrategy == 'd')
        {
            if (doubleHash[index].second == 0)
            {
                cout << "hello" << endl;
                doubleHash[index] = p;
            }

            else
            {
                doubleHashing(p);
            }
        }

        else if (collisionStrategy == 'c')
        {
            if (doubleHash[index].first == "")
            {
                customProbe[index] = p;
            }

            else
            {
                customProbing(p);
            }
        }
    }

    void Delete(string key)
    {
        int index = 0;
        if (hashNo == 1)
        {
            index = Hash1(key);
        }
        else
        {
            index = Hash2(key);
        }

        if (collisionStrategy == 's')
        {
            if (separateChain[index] == list<pair<string, int>>())
            {
                cout << "Key not found" << endl;
                return;
            }

            for (auto it = separateChain[index].begin(); it != separateChain[index].end(); ++it)
            {
                if (it->first == key)
                {
                    separateChain[index].erase(it);
                    deletionCount++;
                    int maxChainLength = 0;
                    if (deletionCount > 100)
                    {
                        for (int i = 0; i < separateChain.size(); i++)
                        {
                            maxChainLength = max(maxChainLength, int(separateChain[i].size()));
                        }
                        rehash(maxChainLength);
                        deletionCount = 0;
                    }
                    return;
                }
            }
            cout << "Key not found" << endl;
        }

        else if (collisionStrategy == 'd')
        {
            if (doubleHash[index] == pair<string, int>())
            {
                cout << "Key not found" << endl;
                return;
            }

            if (doubleHash[index].first == key)
            {
                doubleHash[index] = pair<string, int>();
                return;
            }
        }

        else if (collisionStrategy == 'c')
        {
            if (customProbe[index] == pair<string, int>())
            {
                cout << "Key not found" << endl;
                return;
            }

            if (customProbe[index].first == key)
            {
                customProbe[index] = pair<string, int>();
                return;
            }
        }
        size--;
    }

    int find(string key)
    {
        int index = 0;
        if (hashNo == 1)
        {
            index = Hash1(key);
        }

        else
        {
            index = Hash2(key);
        }

        if (collisionStrategy == 's')
        {
            if (separateChain[index].empty())
            {
                return 0;
            }

            for (auto it = separateChain[index].begin(); it != separateChain[index].end(); ++it)
            {
                probCount++;
                if (it->first == key)
                {
                    return it->second;
                }
            }
            return 0;
        }

        else if (collisionStrategy == 'd')
        {
            if (doubleHash[index] == pair<string, int>())
            {
                return 0;
            }

            if (doubleHash[index].first == key)
            {
                return doubleHash[index].second;
            }
            return 0;
        }

        else if (collisionStrategy == 'c')
        {
            if (customProbe[index] == pair<string, int>())
            {
                return 0;
            }

            if (customProbe[index].first == key)
            {
                return customProbe[index].second;
            }
            return 0;
        }
        return 0;
    }
};
