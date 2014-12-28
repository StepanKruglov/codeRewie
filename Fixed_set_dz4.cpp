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

    /*= 
    1. Тип a -- uint64_t, но ему присваивается значение не более чем primeNum-1 (uint32_t) 
    2. Тип m_size -- uint32_t, но тип размера в стандартных векторах совсем не очевидно, что 32-битный.
    Лучше всегда использовать для size стандартный тип size_t (который может быть как 32, так и 64 битным)
    =*/
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

    /*= Константы такого вида более естественно задавать в шестнадцатеричном виде =*/
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

	/*= Если уж пользуешься стандартом C++11, то используй nullptr вместо макроса NULL =*/
        m_hashTable = vector<int*>(size, NULL);

	/*= Полезно завести привычку всегда инициализировать переменную при объявлении некоторым
	  начальным значением =*/
        bool hasCollision;
        do {
            for (auto index = m_hashTable.begin(); index != m_hashTable.end(); ++index) {
                /*= Баг! Здесь обязательно нужна проверка на nullptr перед выполнением delete =*/
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
		    /*= Для этого выделения памяти (по факту -- последнего в цикле) нет очистки. 
                        После выполнения данной программы наблюдаем утечку в размере numbersSize*4 байт =*/
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

    /*= Эта константа уже была ранее объявлена в классе HashTable. Если в HashTable объявить ее в public,
      то здесь она становится не нужна. Еще вариант -- объявить ее не на уровне классов, а на уровне модуля =*/
    static const uint32_t PRIME = 2147483647;

public:
    /*= В классе HashTable имена методов начинаются с малелькой буквы, а в этом -- с большой.
      Стиль должен быть единообразным =*/
    void Initialize(const vector<int> &numbers) {
        uint64_t size = numbers.size();
        if (size != 1 && size < 100) {
            size = 100;
        }
        vector<vector<int> > firstLevelHash(size);
        uint64_t sum = 0;
        do {
	    /*= Во всех циклах ниже напрашивается конструкция C++11 вида for (item : container),
	      а не for (init; check; modify) 
	      Более того, в Яндексе принято по возможности использовать вместо циклов стандартные
	      алгоритмы STL.
	      В данном случае, первый цикл -- это std::for_each, второй -- std::transform, третий -- std::accumulate.
	      Hint: если используешь C++11, то в качестве аргументов-операций этих стандартных функций
	      удобно пользоваться lambda-выражениями (см. https://en.wikipedia.org/wiki/C%2B%2B11#Lambda_functions_and_expressions ) =*/
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

