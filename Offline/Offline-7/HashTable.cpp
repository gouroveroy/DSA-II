#include <bits/stdc++.h>
using namespace std;

#define REHASH_COUNT 100

/* The above code is defining a class `HashTable` in C++. The class contains member variables such as
vectors for separate chaining, double hashing, and custom probing, as well as various counters and
parameters related to the hash table operations. The class likely implements different collision
resolution strategies (separate chaining, double hashing, custom probing) for handling collisions in
a hash table. The class may also include methods for inserting, deleting, and searching for
key-value pairs in the hash table, as well as functions for calculating hash values and handling
collisions. */
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

    /**
     * The function checks if a given number is prime or not.
     * 
     * @param num The `num` parameter in the `isPrime` function represents the number that is being
     * checked for primality. The function determines whether this number is a prime number or not by
     * iterating through numbers from 2 to the square root of `num` and checking if `num` is divisible
     * by any
     * 
     * @return The function `isPrime` returns a boolean value - `true` if the input number `num` is a
     * prime number, and `false` otherwise.
     */
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

    /**
     * The function `nextPrime` returns the next prime number after the input prime number.
     * 
     * @param prime The parameter `prime` in the `nextPrime` function represents the current prime
     * number for which you want to find the next prime number. The function will return the smallest
     * prime number greater than the input `prime` value.
     * 
     * @return The function `nextPrime` returns the next prime number after the input `prime`.
     */
    long long nextPrime(long long prime)
    {
        long long nextPrime = prime;
        while (!isPrime(nextPrime))
        {
            nextPrime++;
        }
        return nextPrime;
    }

    /**
     * The function `Hash1` calculates a hash value for a given string key using a polynomial rolling
     * hash function.
     * 
     * @param key The `key` parameter in the `Hash1` function is a string that represents the input
     * value for which you want to calculate the hash value.
     * 
     * @return The function `Hash1` is returning a `long long` value, which is the hash value of the
     * input `key`.
     */
    long long Hash1(string key)
    {
        const long long p = nextPrime(2 * capacity);
        const long long m = capacity;

        long long hashValue = 0;
        for (char c : key)
        {
            hashValue = (hashValue * 31 + (c - 'a' + 1)) % p;
        }

        return hashValue % m;
    }

    /**
     * The function `Hash2` calculates a hash value for a given string key using a polynomial rolling
     * hash function with prime number and modulo operations.
     * 
     * @param key The `key` parameter is a string that represents the input value for which we want to
     * calculate the hash value.
     * 
     * @return The `Hash2` function is returning a `long long` value, which is the final hash value
     * calculated based on the input `key`.
     */
    long long Hash2(string key)
    {
        const long long p = nextPrime(5 * capacity);
        const long long m = capacity;

        long long hashValue = 0;
        for (char c : key)
        {
            hashValue = (hashValue * 31 + (c - 'a' + 1)) % p;
        }

        return hashValue % m;
    }

    /**
     * The function `auxHash` calculates a hash value for a given string key using a specific formula
     * involving bitwise operations and a constant value.
     * 
     * @param key The `auxHash` function takes a string `key` as input and calculates a hash value
     * based on the characters in the string. The hash value is calculated using a formula that
     * involves the characters in the string, the size of the string, and a constant value.
     * 
     * @return The `auxHash` function is returning a `long long` hash value calculated based on the
     * input `key`.
     */
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

    /**
     * The function `separateChaining` inserts a key-value pair into a linked list at a specific index
     * in a separate chaining hash table.
     * 
     * @param p The parameter `p` is a pair consisting of a string and a long long integer.
     * @param index The `index` parameter is used to determine the position in the separate chaining
     * data structure where the pair `p` will be inserted. It helps in organizing the key-value pairs
     * into different linked lists based on their hash values.
     */
    void separateChaining(pair<string, long long> p, long long index)
    {
        separateChain[index].push_front(p);
        size++;
    }

    /**
     * The function `doubleHashing` implements double hashing to insert a key-value pair into a hash
     * table with collision resolution.
     * 
     * @param p The parameter `p` is a pair containing a string and a long long value.
     * 
     * @return In the given code snippet, the `return` statement is used to exit the `doubleHashing`
     * function after inserting the pair `p` into the `doubleHash` array at the calculated `hashValue`
     * index. The `return` statement is used to immediately exit the function once the insertion is
     * done, without continuing the loop iterations.
     */
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

    /**
     * The function customProbing implements custom probing technique for resolving collisions in a
     * hash table.
     * 
     * @param p The function `customProbing` takes a pair consisting of a string and a long long value
     * as input. The pair is represented as `pair<string, long long> p`. The string represents the key
     * for hashing, and the long long value is associated with that key.
     * 
     * @return In the `customProbing` function, if a suitable empty slot is found in the `customProbe`
     * array for the given pair `p`, the pair `p` is inserted into that slot, and then the function
     * returns.
     */
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
        if(N < 8000 and size >= 0.95 * capacity)
        {
            return;
        }
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
