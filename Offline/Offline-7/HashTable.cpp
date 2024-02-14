#include <bits/stdc++.h>
using namespace std;

template <class K, class V>
class HashTable
{
    vector<list<pair<K, V>>> separateChain;
    vector<pair<K, V>> doubleHash;
    vector<pair<K, V>> customProbe;
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
    int Hash1(K key)
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
    int Hash2(K key)
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

    int auxHash(K key)
    {
        string word = key;
        int l = word.size() - 1;
        int k = 0;
        for (char c : word)
        {
            k += ((c - 'a') * (1 << l));
            l--;
        }

        float A = (sqrt(5) - 1) / 2;
        int hashValue = floor(capacity * (k * A - floor(k * A)));
        return hashValue;
    }

    void separateChaining(pair<K, V> p, int index)
    {
        separateChain[index].push_back(p);
        size++;
    }

    void doubleHashing(pair<K, V> p)
    {
        int hashValue = 0;
        if (hashNo == 1)
        {
            for (int i = 0; i < capacity; i++)
            {
                hashValue = (Hash1(p.first) + i * auxHash(p.first)) % capacity;
                if (doubleHash[hashValue].first == K())
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
                if (doubleHash[hashValue].first == K())
                {
                    doubleHash[hashValue] = p;
                    return;
                }
            }
        }
    }

    void customProbing(pair<K, V> p)
    {
        int hashValue = 0;
        int C1 = 2;
        int C2 = 3;
        if (hashNo == 1)
        {
            for (int i = 0; i < capacity; i++)
            {
                hashValue = (Hash1(p.first) + C1 * i * auxHash(p.first) + C2 * i * i) % capacity;
                if (customProbe[hashValue].first == K())
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
                if (customProbe[hashValue].first == K())
                {
                    customProbe[hashValue] = p;
                    return;
                }
            }
        }
    }

    int averageProbCount()
    {
        int threshold = 0.1 * capacity;
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
                    return 0.1 * count / threshold;
                }
            }
        }
    }

    float loadFactor()
    {
        return size / capacity;
    }

    void rehash(int C)
    {
        cout << "Average probe count: " << averageProbCount() << endl;
        cout << "Load factor: " << loadFactor() << endl;
        cout << "Maximum chain length: " << C << endl;

        if (collisionStrategy == 's')
        {
            vector<list<pair<K, V>>> temp = separateChain;
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
            separateChain.resize(capacity, list<pair<K, V>>());
            for (int i = 0; i < temp.size(); i++)
            {
                for (auto it = temp[i].begin(); it != temp[i].end(); ++it)
                {
                    insert(it->first, it->second);
                }
            }
        }

        // else if (collisionStrategy == 'd')
        // {
        //     vector<pair<K, V>> temp = doubleHash;
        //     capacity = nextPrime(2 * capacity);
        //     doubleHash.clear();
        //     doubleHash.resize(capacity, pair<K, V>());
        //     for (int i = 0; i < temp.size(); i++)
        //     {
        //         if (temp[i].first != K())
        //         {
        //             insert(temp[i].first, temp[i].second);
        //         }
        //     }
        // }

        // else if (collisionStrategy == 'c')
        // {
        //     vector<pair<K, V>> temp = customProbe;
        //     capacity = nextPrime(2 * capacity);
        //     customProbe.clear();
        //     customProbe.resize(capacity, pair<K, V>());
        //     for (int i = 0; i < temp.size(); i++)
        //     {
        //         if (temp[i].first != K())
        //         {
        //             insert(temp[i].first, temp[i].second);
        //         }
        //     }
        // }

        cout << "Average probe count: " << averageProbCount() << endl;
        cout << "Load factor: " << loadFactor() << endl;
        cout << "Maximum chain length: " << C << endl;
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
        this->separateChain.resize(capacity);
        this->doubleHash.resize(capacity);
        this->customProbe.resize(capacity);
    }

    void insert(K key, V value)
    {
        insertionCount++;
        pair<K, V> p = make_pair(key, value);
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
            if (find(key) == V())
            {
                list<pair<K, V>> list = separateChain[index];
                auto it = list.begin();
                separateChain[index].insert(it, p);
                size++;
            }

            else
            {
                separateChaining(p, index);
            }

            if (insertionCount >= 5)
            {
                int maxChainLength = 0;
                for (int i = 0; i < separateChain.size(); i++)
                {
                    maxChainLength = max(maxChainLength, int(separateChain[i].size()));
                }
                rehash(maxChainLength);
            }
        }

        else if (collisionStrategy == 'd')
        {
            if (doubleHash[index].first == K())
            {
                doubleHash[index] = p;
            }

            else
            {
                doubleHashing(p);
            }
        }

        else if (collisionStrategy == 'c')
        {
            if (doubleHash[index].first == K())
            {
                customProbe[index] = p;
            }

            else
            {
                customProbing(p);
            }
        }
    }

    void Delete(K key)
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
            if (separateChain[index] == list<pair<K, V>>())
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
            if (doubleHash[index] == pair<K, V>())
            {
                cout << "Key not found" << endl;
                return;
            }

            if (doubleHash[index].first == key)
            {
                doubleHash[index] = pair<K, V>();
                return;
            }
        }

        else if (collisionStrategy == 'c')
        {
            if (customProbe[index] == pair<K, V>())
            {
                cout << "Key not found" << endl;
                return;
            }

            if (customProbe[index].first == key)
            {
                customProbe[index] = pair<K, V>();
                return;
            }
        }
        size--;
    }

    V find(K key)
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
            if (separateChain[index] == list<pair<K, V>>())
            {
                return V();
            }

            for (auto it = separateChain[index].begin(); it != separateChain[index].end(); ++it)
            {
                probCount++;
                if (it->first == key)
                {
                    return it->second;
                }
            }
            return V();
        }

        else if (collisionStrategy == 'd')
        {
            if (doubleHash[index] == pair<K, V>())
            {
                return V();
            }

            if (doubleHash[index].first == key)
            {
                return doubleHash[index].second;
            }
            return V();
        }

        else if (collisionStrategy == 'c')
        {
            if (customProbe[index] == pair<K, V>())
            {
                return V();
            }

            if (customProbe[index].first == key)
            {
                return customProbe[index].second;
            }
            return V();
        }
    }
};
