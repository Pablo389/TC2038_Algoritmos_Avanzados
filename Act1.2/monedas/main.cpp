/*
El programa recibe un numero entero N, seguido de N valores enteros (uno en cada línea) 
    que representan las diferentes denominaciones disponibles de las monedas. 
    Seguido de esto, el programa recibe dos números enteros: P y Q, (uno en cada línea) por
    la entrada estándar, que representan P: el precio de un producto dado y Q: es el 
    billete o moneda con el que se paga dicho producto. La salida del programa es una lista
    de N valores correspondientes al número de monedas de cada denominación, 
    de mayor a menor, una en cada línea, que se tienen que dar para dar el cambio por el 
    producto pagado, primero utilizando programación dinámica, y luego utilizando un 
    algoritmo avaro.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

// Solves the change-making problem using a Greedy Algorithm
void GAmoneyChange(vector<int>& denominations, int N, int C) {
    vector<int> nCoinsUsed(N, 0); 
    int originalC = C;  // og amount of change
    for (int i = 0; i < N; i++) { // for each denomination in the list
        while (C >= denominations[i]) { // while the change is greater than the denomination
            C -= denominations[i]; // subtract the denomination from the change
            nCoinsUsed[i]++; // increment the number of coins used
        }
    }
    for (int i = 0; i < N; i++) { // for each denomination in the list
        if (nCoinsUsed[i] > 0) { // if the number of coins used is greater than 0
            cout << "Denomination: " << denominations[i] << " Quantity: " << nCoinsUsed[i] << " (Greedy)" << endl;
        } // print the denomination and the number of coins used
    }
    if (C > 0) { // if the change is greater than 0
        cout << "The Greedy algorithm was unable to complete the change and lacked " << C << " units." << endl;
    }
}
// Solves the change-making problem using Dynamic Programming
void DPmoneyChange(vector<int>& denominations, int N, int C) { //
    vector<int> f(C + 1, INT_MAX); // C+1 is the size of the vector, INT_MAX is the maximum value for an int
    vector<int> usedCoin(C + 1, -1); //we use a vector named usedCoin to store the index of the denomination used to make the change, -1 is the default value
    f[0] = 0; // first element of the vector
    for (int i = 1; i <= C; i++) { // for each element in the vector
        for (int j = 0; j < N; j++) { // for each denomination in the list
            if (i >= denominations[j] && f[i - denominations[j]] != INT_MAX && f[i - denominations[j]] + 1 < f[i]) { // if the change is greater than the denomination, the value of the previous change is not the maximum value for an int and the value of the previous change plus 1 is less than the value of the current change
                f[i] = f[i - denominations[j]] + 1; // the value of the current change is the value of the previous change plus 1
                usedCoin[i] = j; // the index of the denomination used to make the change is stored in the vector usedCoin
            }
        }
    }

    vector<int> nCoinsUsed(N, 0); // vector to store the number of coins used

    if (f[C] == INT_MAX) { // if the value of the change is the maximum value for an int
        cout << "No solution possible with given denominations." << endl; //
        return;
    }

    while (C > 0 && usedCoin[C] != -1) { // while the change is greater than 0 and the index of the denomination used to make the change is not -1
        nCoinsUsed[usedCoin[C]]++; // increment the number of coins used
        C -= denominations[usedCoin[C]]; // subtract the denomination from the change
    }

    for (int i = 0; i < N; i++) { // for each denomination in the list
        if (nCoinsUsed[i] > 0) { // if the number of coins used is greater than 0
            cout << "Denomination: " << denominations[i] << " Quantity: " << nCoinsUsed[i] << " (Dynamic)" << endl;
        }
    }
}

int main() {
    //comando para compilar: g++ main.cpp -o a.out
    //comando para ejecutar: ./a.out o ./a.out < in.txt
    int N;
    cin >> N;

    if (cin.fail() || N <= 0) {
        cout << "Invalid number of denominations." << endl;
        return 1;
    }

    vector<int> denominations(N);

    for (int i = 0; i < N; i++) {
        cin >> denominations[i];
        if (cin.fail() || denominations[i] <= 0) {
            cout << "Invalid denomination. Please try another." << endl;
            return 1;
        }
    }
    sort(denominations.begin(), denominations.end(), greater<int>());

    int P, Q;
    cin >> P >> Q;
    if (cin.fail() || P <= 0 || Q <= 0) {
        cout << "Invalid price or payment quantity. Please retry." << endl;
        return 1;
    }

    int C = Q - P;

    if (C < 0) {
        cout << "Invalid amount paid. Please retry." << endl;
        return 1;
    } else if (C == 0) {
        cout << "No change needed." << endl;
        return 0;
    }

    cout << "\nChange w Dynamic Programming:" << endl;
    DPmoneyChange(denominations, N, C);

    cout << "\nChange w Greedy Algorithm:" << endl;
    GAmoneyChange(denominations, N, C);

    return 0;
}