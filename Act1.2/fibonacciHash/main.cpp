#include <iostream>
#include "./hashTable.h"

using namespace std;

int fibonacci(int n, DynamicHashTable &hash){
    int value = hash.readKey(n);
    if (value != -1) {
        cout << "Ingresa el: " << n << " y el valor es " << value << endl;
        return value;
    }else {
        hash.createKey(n,fibonacci(n-1,hash) + fibonacci(n-2,hash));
        return fibonacci(n-1,hash) + fibonacci(n-2,hash);
    }
}

int main(){
    DynamicHashTable hash;
    hash.createKey(0,0);
    hash.createKey(1,1);
    int input;
    cout << "Ingresa n: ";
    cin >> input;
    int res = fibonacci(input, hash);

    hash.printTable();

    cout << endl << endl << "Resultado: " << res;
    return 0;
}