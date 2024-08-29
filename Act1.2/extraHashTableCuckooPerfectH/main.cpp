#include <iostream>
#include <vector>
#include <cmath>
#include <string>
using namespace std;

const int INITIAL_TABLE_SIZE = 8;

class CuckooHashing {
private:
    vector<double> table1;
    vector<double> table2;
    vector<bool> occupied1;
    vector<bool> occupied2;
    int table_size;
    int num_elements;

    int hash1(double key);
    int hash2(double key);
    
    void rehash();

public:
    CuckooHashing();
    void createKey(double key); // Unified Create operation
    bool readKey(double key); // Unified Read operation
    void updateKey(double old_key, double new_key); // Unified Update operation
    void deleteKey(double key); // Unified Delete operation
    double convertToDouble(const string &str);
    double convertToDouble(int key);
    void printTable();
};

// Constructor implementation
CuckooHashing::CuckooHashing()
    : table_size(INITIAL_TABLE_SIZE),
      num_elements(0),
      table1(INITIAL_TABLE_SIZE, -1),
      table2(INITIAL_TABLE_SIZE, -1),
      occupied1(INITIAL_TABLE_SIZE, false),
      occupied2(INITIAL_TABLE_SIZE, false) {}

// Universal hashing function
int CuckooHashing::hash1(double key) {
    int a = 5;  // Fixed value as specified
    int b = 7;
    int p = 101; // a large prime number
    return static_cast<int>(fmod((a * key + b), p)) % table_size;
}

// Multiplication method hashing function
int CuckooHashing::hash2(double key) {
    double A = 0.6180339887; // Knuth's suggested value for A
    return static_cast<int>(floor(table_size * fmod(key * A, 1.0)));
}

// Convert string to a double key
double CuckooHashing::convertToDouble(const string &str) {
    double key = 0;
    for (char ch : str) {
        key = key * 31 + static_cast<int>(ch); // Using a small prime like 31 helps reduce collisions
    }
    return key;
}

// Convert integer to a double key
double CuckooHashing::convertToDouble(int key) {
    return static_cast<double>(key);
}

// Rehash when load factor exceeds 0.8
void CuckooHashing::rehash() {
    int new_table_size = table_size * 2;
    vector<double> old_table1 = table1;
    vector<double> old_table2 = table2;
    vector<bool> old_occupied1 = occupied1;
    vector<bool> old_occupied2 = occupied2;

    table_size = new_table_size;
    table1.assign(new_table_size, -1);
    table2.assign(new_table_size, -1);
    occupied1.assign(new_table_size, false);
    occupied2.assign(new_table_size, false);

    num_elements = 0;
    for (int i = 0; i < old_table1.size(); ++i) {
        if (old_occupied1[i]) {
            createKey(old_table1[i]);
        }
    }
    for (int i = 0; i < old_table2.size(); ++i) {
        if (old_occupied2[i]) {
            createKey(old_table2[i]);
        }
    }
}

// Unified Create operation (inserts double key into the hash tables)
void CuckooHashing::createKey(double key) {
    if (num_elements >= table_size * 0.8) {
        rehash();
    }

    double current_key = key;
    for (int i = 0; i < table_size; ++i) {
        int hash_value1 = hash1(current_key);

        if (!occupied1[hash_value1]) {
            table1[hash_value1] = current_key;
            occupied1[hash_value1] = true;
            num_elements++;
            cout << "Key " << current_key << " inserted into Table1 at index " << hash_value1 << endl;
            return;
        } else {
            swap(current_key, table1[hash_value1]);
        }

        int hash_value2 = hash2(current_key);

        if (!occupied2[hash_value2]) {
            table2[hash_value2] = current_key;
            occupied2[hash_value2] = true;
            num_elements++;
            cout << "Key " << current_key << " inserted into Table2 at index " << hash_value2 << endl;
            return;
        } else {
            swap(current_key, table2[hash_value2]);
        }
    }

    cout << "Insertion failed due to high congestion." << endl;
}

// Unified Read operation (search for double key in the hash tables)
bool CuckooHashing::readKey(double key) {
    int hash_value1 = hash1(key);

    if (occupied1[hash_value1] && table1[hash_value1] == key) {
        cout << "Key " << key << " found in Table1 at index " << hash_value1 << endl;
        return true;
    }

    int hash_value2 = hash2(key);

    if (occupied2[hash_value2] && table2[hash_value2] == key) {
        cout << "Key " << key << " found in Table2 at index " << hash_value2 << endl;
        return true;
    }

    cout << "Key " << key << " not found." << endl;
    return false;
}

// Unified Update operation (replace old key with new key)
void CuckooHashing::updateKey(double old_key, double new_key) {
    deleteKey(old_key);
    createKey(new_key);
}

// Unified Delete operation (delete double key from the hash tables)
void CuckooHashing::deleteKey(double key) {
    int hash_value1 = hash1(key);

    if (occupied1[hash_value1] && table1[hash_value1] == key) {
        table1[hash_value1] = -1;
        occupied1[hash_value1] = false;
        num_elements--;
        cout << "Key " << key << " deleted from Table1 at index " << hash_value1 << endl;
        return;
    }

    int hash_value2 = hash2(key);

    if (occupied2[hash_value2] && table2[hash_value2] == key) {
        table2[hash_value2] = -1;
        occupied2[hash_value2] = false;
        num_elements--;
        cout << "Key " << key << " deleted from Table2 at index " << hash_value2 << endl;
        return;
    }

    cout << "Key " << key << " not found for deletion." << endl;
}

void CuckooHashing::printTable() {
    cout << "Table1: ";
    for (int i = 0; i < table_size; ++i) {
        if (occupied1[i]) {
            cout << table1[i] << " ";
        } else {
            cout << "- ";
        }
    }
    cout << endl;

    cout << "Table2: ";
    for (int i = 0; i < table_size; ++i) {
        if (occupied2[i]) {
            cout << table2[i] << " ";
        } else {
            cout << "- ";
        }
    }
    cout << endl;
}

int main() {
    CuckooHashing hashing;

    // Create keys (as integers)
    hashing.createKey(hashing.convertToDouble(10));
    hashing.createKey(hashing.convertToDouble(5));
    hashing.createKey(hashing.convertToDouble(3));

    // Create keys (as strings)
    hashing.createKey(hashing.convertToDouble("he0-1.4l33o"));
    hashing.createKey(hashing.convertToDouble("w4rld0.2"));
    cout << endl;
    hashing.printTable();
    cout << endl;
    // Read keys (as integers)
    hashing.readKey(hashing.convertToDouble(5));

    // Read keys (as strings)
    hashing.readKey(hashing.convertToDouble("he0-1.4l33o"));

    // Update keys
    hashing.updateKey(hashing.convertToDouble(10), hashing.convertToDouble(15)); // update integer key
    hashing.updateKey(hashing.convertToDouble("he0-1.4l33o"), hashing.convertToDouble("HELLO")); // update string key

    // Delete keys
    hashing.deleteKey(hashing.convertToDouble(3));
    hashing.deleteKey(hashing.convertToDouble("w4rld0.2"));

    return 0;
}