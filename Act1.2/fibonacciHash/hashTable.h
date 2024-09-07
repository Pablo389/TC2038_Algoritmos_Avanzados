#ifndef DYNAMICHASHTABLE_H
#define DYNAMICHASHTABLE_H

#include <iostream>
#include <vector>

using namespace std;

class DynamicHashTable {
private:
    vector<pair<int, int>> table;
    int num_elements;
    float load_factor_threshold;

    void resizeTable();

public:
    DynamicHashTable();
    void createKey(int key, int value);
    int readKey(int key);
    void updateKey(int key, int new_value);
    void deleteKey(int key);
    void printTable();
};

#endif // DYNAMICHASHTABLE_H