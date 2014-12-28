#include <iostream>
#include <stdint.h>
#include <vector>
#include <functional>
#include <fstream>
#include <random>
#include <chrono>
#include <stdlib.h>

using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;


struct HashFunction {
    static std::default_random_engine m_generator;
    uint64_t a;
    uint32_t b;
    uint32_t m_prime;
    uint32_t m_size;

    HashFunction() {};
    HashFunction(uint32_t primeNum, uint32_t size) {
        m_prime = primeNum;
        m_size = size;
        std::uniform_int_distribution<uint32_t> distributionA(1, primeNum-1);
        std::uniform_int_distribution<uint32_t> distributionB(0, primeNum-1);
        a = distributionA(m_generator);
        b = distributionB(m_generator);
    }
    uint32_t getHash(int32_t value) const {
        uint64_t result = abs(a * value + b);
        result %= m_prime;
        return result % m_size;
    }
};

std::default_random_engine HashFunction::m_generator;

class HashTable {
    vector<int*> m_hashTable;
    HashFunction m_hashFunction;
    static const uint32_t PRIME = 2147483647;

public:
    explicit HashTable(const vector<int> &numbers) {
        if (numbers.size() == 0) {
            return;
        }
        uint32_t size = numbers.size() * numbers.size();
        if (size != 1 && size < 100) {
            size = 100; 
        }
        m_hashTable = vector<int*>(size, NULL);
        bool hasCollision;
        do {
            for (auto index = m_hashTable.begin(); index != m_hashTable.end(); ++index) {
                delete *index;
                *index = NULL;
            }
            hasCollision = false;
            m_hashFunction = HashFunction(PRIME, m_hashTable.size());
            for (auto index = numbers.begin(); index != numbers.end(); ++index) {
                uint32_t hashValue = m_hashFunction.getHash(*index);
                if (m_hashTable[hashValue] != NULL) {
                    hasCollision = true;
                    break;
                } else {
                    m_hashTable[hashValue] = new int;
                    *(m_hashTable[hashValue]) = *index;
                }
            }
        } while (hasCollision);
    }

    bool contains(int number) const {
        if (m_hashTable.size() == 0) {
            return false;
        }
        uint32_t hashValue = m_hashFunction.getHash(number);
        return  m_hashTable[hashValue] != NULL &&
                *(m_hashTable[hashValue]) == number;
    }
    friend std::ostream &operator<< (std::ostream &out, const HashTable &table);
};

std::ostream &operator<< (std::ostream &out, const HashTable &table)
{
    for (auto index = table.m_hashTable.begin(); index != table.m_hashTable.end(); ++index) {
        out << **index << " ";
    }
    return out;
}

class FixedSet {
    vector<HashTable> m_hashTables;
    HashFunction m_hashFunction;
    static const uint32_t PRIME = 2147483647;

public:
    void Initialize(const vector<int> &numbers) {
        uint64_t size = numbers.size();
        if (size != 1 && size < 100) {
            size = 100;
        }
        vector<vector<int> > firstLevelHash(size);
        uint64_t sum = 0;
        do {
            for (auto index = firstLevelHash.begin(); index != firstLevelHash.end(); ++index) {
                index->clear();
            }
            m_hashFunction = HashFunction(PRIME, firstLevelHash.size());
            for (auto index = numbers.begin(); index != numbers.end(); ++index) {
                uint32_t hashValue = m_hashFunction.getHash(*index);
                firstLevelHash[hashValue].push_back(*index);
            }
            for (auto index = firstLevelHash.begin(); index != firstLevelHash.end(); ++index) {
                sum += index->size() * index->size();
            }
        } while (sum >= 4 * numbers.size());
        for (auto index = firstLevelHash.begin(); index != firstLevelHash.end(); ++index) {
            m_hashTables.push_back(HashTable(*index));
        }
    }
    bool Contains(int number) const {
        uint32_t hashValue = m_hashFunction.getHash(number);
        return m_hashTables[hashValue].contains(number);
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);

    uint32_t numbersSize;
    cin >> numbersSize;
    std::vector<int> numbers(numbersSize);

    for (uint32_t index = 0; index < numbersSize; ++index) {
        cin >> numbers[index];
    }
    FixedSet set;
    set.Initialize(numbers);
    uint32_t querySize;
    cin >> querySize;

    int testNumber;
    for (uint32_t index = 0; index < querySize; ++index) {
        cin >> testNumber;
        cout << (set.Contains(testNumber) ? "Yes" : "No") << endl;
    }

    return 0;
}

