#include <iostream>
#include <string>
#include <vector>

struct Elem {
    bool deleted = false;
    bool empty = true;
    std::string value;

    Elem() : value(""), deleted(false), empty(true) {};
};

class HashT {
public:
    HashT() : capacity(INITIAL_SIZE), elemCount(0), table(new Elem[INITIAL_SIZE]) {};

    HashT(const HashT &) = delete;
    HashT(HashT &&) = delete;
    HashT &operator=(const HashT &) = delete;
    HashT &operator=(HashT &&) = delete;

    ~HashT() {
        delete [] table;
    };

    bool addElem(std::string str) {

        if ((double) elemCount / capacity >= RESIZE_COEF)
            reHash();

        int hashVal = firstHash(str, capacity);
        int hashStep = secondHash(str, capacity);
        int check = 0;

        if (hasElem(str)) { return false; }
        else {
            while (!table[hashVal].empty && check < capacity) {
                hashVal = (hashVal + hashStep) % capacity;
                check++;
            }

            if (table[hashVal].deleted || table[hashVal].empty) {
                table[hashVal].value = str;
                table[hashVal].empty = false;
                table[hashVal].deleted = false;
            }
            elemCount++;
            return true;
        }
    };

    void print() {
        for (size_t i = 0; i < capacity; i++) {
            std::cout << "[" << i << "] |" << table[i].value << "|"
                      << ", deleted = " << table[i].deleted << ", empty = " << table[i].empty << std::endl;
        }
    }

    bool delElem(std::string str) {
        int hashVal = firstHash(str, capacity);
        int hashStep = secondHash(str, capacity);
        int check = 0;

        while (table[hashVal].value != "" && check < capacity) {
            if (table[hashVal].value == str && !table[hashVal].deleted){
                table[hashVal].deleted = true;
                return true;
            }
            hashVal = (hashVal + hashStep) % capacity;
            check++;
        }
        return false;
    };

    bool hasElem(std::string str) {
        int hashVal = firstHash(str, capacity);
        int hashStep = secondHash(str, capacity);
        int check = 0;

        while (table[hashVal].value != "" && check < capacity) {
            if (table[hashVal].value == str && !table[hashVal].deleted)
                return true;
            hashVal = (hashVal + hashStep) % capacity;
            check++;
        }
        return false;
    };

private:
    const int INITIAL_SIZE = 8;
    const int FIRST_COEF = 101;
    const int SECOND_COEF = 193;
    const double RESIZE_COEF = 0.75;

    int capacity;
    int elemCount;
    Elem *table = new Elem[capacity];

    int firstHash(std::string &str, int M) {
        int hash = 0;
        unsigned long size = str.size();
        for (int i = 0; i < size; i++)
            hash = (hash * FIRST_COEF + str[i]) % M;
        return hash;
    };

    int secondHash(std::string &str, int M) {
        int hash = 0;
        unsigned long size = str.size();
        for (int i = 0; i < size; i++)
            hash = (hash * SECOND_COEF + str[i]) % M;
        return (2 * hash + 1) % M;
    };


    void reHash() {
        int newCapacity = capacity * 2;
        Elem *newTable = new Elem[newCapacity];
        for (int i = 0; i < capacity; i++) {
            if (!table[i].empty) {
                if (!table[i].deleted) {
                    int hashVal = firstHash(table[i].value, newCapacity);
                    int hashStep = secondHash(table[i].value, newCapacity);
                    int check = 0;

                    while (!newTable[hashVal].empty && check < newCapacity) {
                        hashVal = (hashVal + hashStep) % newCapacity;
                        ++check;
                    }
                    newTable[hashVal] = table[i];
                }
            }
        }
        table = newTable;
        capacity = newCapacity;
    };
};

int main() {
    HashT table;
    char com = 0;
    std::string key;

    while (std::cin >> com >> key) {
        if (com == '?') {
            std::cout << (table.hasElem(key) ? "OK" : "FAIL") << std::endl;
            table.print();
        } else if (com == '+') {
            std::cout << (table.addElem(key) ? "OK" : "FAIL") << std::endl;
            table.print();
        } else if (com == '-') {
            std::cout << (table.delElem(key) ? "OK" : "FAIL") << std::endl;
            table.print();
        } else
            return 0;
    }
}