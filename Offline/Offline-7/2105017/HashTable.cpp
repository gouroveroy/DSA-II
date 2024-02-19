#include <bits/stdc++.h>
using namespace std;

#define REHASH_COUNT 100

class HashTable
{
    vector<list<pair<string, long long>>> separateChain;
    vector<pair<string, long long>> doubleHash;
    vector<pair<string, long long>> customProbe;
    long long probCount;
    long long N;
    long long capacity;
    long long size;
    long long hashNo;
    long long chainLength;
    long long insertionCount;
    long long deletionCount;
    long long collisionCount;
    char collisionStrategy;

    bool isPrime(long long num)
    {
        if (num <= 1)
        {
            return false;
        }
        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    long long nextPrime(long long prime)
    {
        long long nextPrime = prime;
        while (!isPrime(nextPrime))
        {
            nextPrime++;
        }
        return nextPrime;
    }

    long long Hash1(string key)
    {
        // long long p = 86969;
        // long long m = capacity;

        // string word = key;
        // long long l = word.size() - 1;
        // long long k = 0;
        // for (char c : word)
        // {
        //     k += ((c - 'a') * (1 << l));
        //     l--;
        // }

        // long long hashValue = ((54059 * k + 76963) % p) % m;
        // return hashValue;

        // long long p = 86969;
        // long long m = capacity;
        // int n = key.length();
        // long long k = 0;
        // int i = 1;
        // for (char c : key)
        // {
        //     k += (c - 'a') * power(31, (n - i));
        //     i++;
        // }

        // long long hashValue = ((54059 * k + 76963) % p) % m;
        // return hashValue;

        const long long p = nextPrime(2 * capacity);
        const long long m = capacity;

        long long hashValue = 0;
        for (char c : key)
        {
            hashValue = (hashValue * 31 + (c - 'a' + 1)) % p;
        }

        return hashValue % m;
    }

    long long Hash2(string key)
    {
        // long long p = nextPrime(5 * capacity);
        // long long m = capacity;

        // string word = key;
        // long long l = word.size() - 1;
        // long long k = 0;
        // for (char c : word)
        // {
        //     k += ((c - 'a') * (1 << l));
        //     l--;
        // }

        // long long hashValue = ((5 * k + 7) % p) % m;
        // return hashValue;

        const long long p = nextPrime(5 * capacity);
        const long long m = capacity;

        long long hashValue = 0;
        for (char c : key)
        {
            hashValue = (hashValue * 31 + (c - 'a' + 1)) % p;
        }

        return hashValue % m;
    }

    long long auxHash(string key)
    {
        string word = key;
        long long l = word.size() - 1;
        long long k = 0;
        for (char c : word)
        {
            k += ((c - 'a') * (1 << l));
            l--;
        }

        double A = (sqrt(5) - 1) / 2;
        long long hashValue = floor(capacity * (k * A - floor(k * A)));
        return hashValue;
    }

    void separateChaining(pair<string, long long> p, long long index)
    {
        separateChain[index].push_front(p);
        size++;
    }

    void doubleHashing(pair<string, long long> p)
    {
        long long hashValue = 0;
        if (hashNo == 1)
        {
            for (int i = 1; i < capacity; i++)
            {
                hashValue = (Hash1(p.first) + i * auxHash(p.first)) % capacity;
                probCount++;
                if (doubleHash[hashValue].first == "")
                {
                    doubleHash[hashValue] = p;
                    size++;
                    return;
                }
            }
        }

        else
        {
            for (int i = 1; i < capacity; i++)
            {
                hashValue = (Hash2(p.first) + i * auxHash(p.first)) % capacity;
                probCount++;
                if (doubleHash[hashValue].first == "")
                {
                    doubleHash[hashValue] = p;
                    size++;
                    return;
                }
            }
        }
    }

    void customProbing(pair<string, long long> p)
    {
        long long hashValue = 0;
        long long C1 = 2;
        long long C2 = 3;
        if (hashNo == 1)
        {
            for (long long i = 0; i < capacity; i++)
            {
                hashValue = (Hash1(p.first) + C1 * i * auxHash(p.first) + C2 * i * i) % capacity;
                probCount++;
                if (customProbe[hashValue].first == "")
                {
                    customProbe[hashValue] = p;
                    size++;
                    return;
                }
            }
        }

        else
        {
            for (long long i = 0; i < capacity; i++)
            {
                hashValue = (Hash2(p.first) + C1 * i * auxHash(p.first) + C2 * i * i) % capacity;
                probCount++;
                if (customProbe[hashValue].first == "")
                {
                    customProbe[hashValue] = p;
                    size++;
                    return;
                }
            }
        }
    }

    double averageProbeCount()
    {
        double threshold = 0.1 * capacity;
        long long searchCount = 0;
        long long count = 0;
        srand(time(NULL));

        for (int i = 0; i < capacity; i++)
        {
            int j = rand() % capacity;
            for (auto it = separateChain[j].begin(); it != separateChain[j].end(); ++it)
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
        return 1.0 * count / threshold;
    }

    double loadFactor()
    {
        return 1.0 * size / capacity;
    }

    void rehash(long long C)
    {
        cout << "Average probe count: " << averageProbeCount() << endl;
        cout << "Load factor: " << loadFactor() << endl;
        cout << "Maximum chain length: " << C << endl
             << endl;

        if (collisionStrategy == 's')
        {
            vector<list<pair<string, long long>>> temp = separateChain;
            if (C > chainLength)
            {
                capacity = nextPrime(2 * capacity);
                // cout << capacity << endl;
            }

            else if (C < 0.8 * chainLength)
            {
                if (nextPrime((capacity / 2) < N))
                {
                    return;
                }
                capacity = nextPrime((capacity / 2));
                // cout << capacity << endl;
            }

            separateChain.clear();
            separateChain.assign(capacity, list<pair<string, long long>>());
            for (int i = 0; i < temp.size(); i++)
            {
                for (auto it = temp[i].begin(); it != temp[i].end(); ++it)
                {
                    hashNo == 1 ? separateChaining(*it, Hash1(it->first)) : separateChaining(*it, Hash2(it->first));
                }
            }
        }

        cout << "Average probe count: " << averageProbeCount() << endl;
        cout << "Load factor: " << loadFactor() << endl;
        cout << "Maximum chain length: " << C << endl
             << endl;
    }

public:
    HashTable(long long capaCity = 1, long long hashNo = 1, long long chainLength = LONG_LONG_MAX, char collisionStrategy = 's')
    {
        this->capacity = nextPrime(capaCity);
        this->probCount = 0;
        this->N = capacity;
        this->hashNo = hashNo;
        this->chainLength = chainLength;
        this->insertionCount = 0;
        this->deletionCount = 0;
        this->collisionStrategy = collisionStrategy;
        this->size = 0;
        this->collisionCount = 0;
        this->separateChain.assign(capacity + 1, list<pair<string, long long>>());
        this->doubleHash.assign(capacity + 1, pair<string, long long>());
        this->customProbe.assign(capacity + 1, pair<string, long long>());
    }

    void resetProbe()
    {
        probCount = 0;
    }

    void resetCollision()
    {
        collisionCount = 0;
    }

    long long getProbe()
    {
        return probCount;
    }

    long long getCollision()
    {
        return collisionCount;
    }

    void insert(string &key, long long &value)
    {
        insertionCount++;
        pair<string, long long> p = make_pair(key, value);
        long long index = 0;
        if (hashNo == 1)
        {
            index = Hash1(key);
        }

        else
        {
            index = Hash2(key);
        }

        // cout << "insert index: " << index << endl;

        if (collisionStrategy == 's')
        {
            // cout << "key not exists" << endl;
            bool inserted = false;
            // cout << "list size: " << separateChain[index].size() << endl;
            if (separateChain[index].empty())
            {
                // cout << "key not found in insert" << endl;
                separateChain[index].insert(separateChain[index].begin(), p);
                // cout << "list size after insert " << separateChain[index].size() << endl;
                size++;
                inserted = true;
            }

            if (!inserted)
            {
                // cout << "key found in insert" << endl;
                for (auto it = separateChain[index].begin(); it != separateChain[index].end(); ++it)
                {
                    if (it->first == key)
                    {
                        return;
                    }
                }
                separateChaining(p, index);
                collisionCount++;
            }

            if (insertionCount >= REHASH_COUNT)
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
                probCount++;
                doubleHash[index] = p;
                size++;
            }

            else
            {
                collisionCount++;
                doubleHashing(p);
            }
        }

        else if (collisionStrategy == 'c')
        {
            if (customProbe[index].first == "")
            {
                probCount++;
                customProbe[index] = p;
                size++;
            }

            else
            {
                collisionCount++;
                customProbing(p);
            }
        }
    }

    void Delete(string key)
    {
        long long index = 0;
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
            if (separateChain[index] == list<pair<string, long long>>())
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
                    if (deletionCount >= REHASH_COUNT)
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
            if (doubleHash[index] == pair<string, long long>())
            {
                cout << "Key not found" << endl;
                return;
            }

            if (doubleHash[index].first == key)
            {
                doubleHash[index] = pair<string, long long>();
                return;
            }
        }

        else if (collisionStrategy == 'c')
        {
            if (customProbe[index] == pair<string, long long>())
            {
                cout << "Key not found" << endl;
                return;
            }

            if (customProbe[index].first == key)
            {
                customProbe[index] = pair<string, long long>();
                return;
            }
        }
        size--;
    }

    long long find(string key)
    {
        long long index = 0;
        if (hashNo == 1)
        {
            index = Hash1(key);
        }

        else
        {
            index = Hash2(key);
        }

        // cout << "find index: " << index << endl;

        if (collisionStrategy == 's')
        {
            if (separateChain[index].empty())
            {
                // cout << "Key not found in find" << endl;
                probCount++;
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
            if (doubleHash[index] == pair<string, long long>() || doubleHash[index].first != key)
            {
                int i = 1;
                while (i < size)
                {
                    probCount++;
                    hashNo == 1 ? index = (Hash1(key) + i * auxHash(key)) % capacity : index = (Hash2(key) + i * auxHash(key)) % capacity;
                    if (doubleHash[index].first == key)
                    {
                        return doubleHash[index].second;
                    }
                    i++;
                }
            }

            probCount++;
            if (doubleHash[index].first == key)
            {
                return doubleHash[index].second;
            }
            return 0;
        }

        else if (collisionStrategy == 'c')
        {
            if (customProbe[index] == pair<string, long long>() || customProbe[index].first != key)
            {
                int i = 1;
                while (i < size)
                {
                    probCount++;
                    hashNo == 1 ? index = (Hash1(key) + 2 * i * auxHash(key) + 3 * i * i) % capacity : index = (Hash2(key) + 2 * i * auxHash(key) + 3 * i * i) % capacity;
                    if (customProbe[index].first == key)
                    {
                        return customProbe[index].second;
                    }
                    i++;
                }
            }

            probCount++;
            if (customProbe[index].first == key)
            {
                return customProbe[index].second;
            }
            return 0;
        }
        return 0;
    }
};
