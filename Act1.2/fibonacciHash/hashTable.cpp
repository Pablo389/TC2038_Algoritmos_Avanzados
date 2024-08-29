#include "hashTable.h"

// Constructor implementation
DynamicHashTable::DynamicHashTable() : num_elements(0), load_factor_threshold(0.8) {
    table.resize(8, make_pair(-1, -1)); // Initialize with empty pairs
}

// Resize the table when load factor exceeds threshold
void DynamicHashTable::resizeTable() {
    int new_size = table.size() * 2;
    vector<pair<int, int>> new_table(new_size, make_pair(-1, -1));

    // Reinsert all existing elements into the new table
    for (const auto &entry : table) {
        if (entry.first != -1) {
            for (int i = 0; i < new_size; ++i) {
                if (new_table[i].first == -1) {
                    new_table[i] = entry;
                    break;
                }
            }
        }
    }

    table = std::move(new_table);
}

// Create operation
void DynamicHashTable::createKey(int key, int value) {
    if (num_elements >= table.size() * load_factor_threshold) {
        resizeTable();
    }

    for (int i = 0; i < table.size(); ++i) {
        if (table[i].first == -1) { // Empty slot found
            table[i] = make_pair(key, value);
            num_elements++;
            return;
        }
    }
}

// Read operation
int DynamicHashTable::readKey(int key) {
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].first == key) {
            return table[i].second;
        }
    }
    return -1; // Return an invalid value to indicate not found
}

// Update operation
void DynamicHashTable::updateKey(int key, int new_value) {
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].first == key) {
            table[i].second = new_value;
            return;
        }
    }
}

// Delete operation
void DynamicHashTable::deleteKey(int key) {
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].first == key) {
            table[i] = make_pair(-1, -1);
            num_elements--;
            return;
        }
    }
}

// Print the contents of the table
void DynamicHashTable::printTable() {
    cout << endl << "Table contents:" << endl;
    for (int i = 0; i < table.size(); ++i) {
        if (table[i].first != -1) {
            cout << "Index " << i << ": Key = " << table[i].first << ", Value = " << table[i].second << endl;
        } else {
            cout << "Index " << i << ": Empty" << endl;
        }
    }
}