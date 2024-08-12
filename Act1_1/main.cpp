#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


void merge(vector<double> &A, int p, int q, int r){

    const int n1 = q-p+1;
    const int n2 = r-q;

    double* L = new double[n1];
    double* R = new double[n2];


    for (int i = 0;i<n1;i++){
        L[i] = A[p+i];
    }
    for (int j = 0;j<n2;j++){
        R[j] = A[q+1+j]; 
    }

    int i=0, j=0, k=p;

    while(i<n1 && j<n2){
        if (L[i] <= R[j]){
            A[k] = L[i];
            i++;
        }else{
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i< n1){
        A[k] = L[i];
        i++;
        k++;
    }

    while(j<n2){
        A[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;

}

void mergeSort(vector<double> &A, int p, int r){

    if (p>=r){
        return;
    }
    int q = (p+r)/2;
    mergeSort(A, p, q);
    mergeSort(A, q+1, r);
    return merge(A, p, q, r);

}



int main(){
    //comando para compilar: g++ main.cpp -o a.out
    //comando para ejecutar: ./a.out o ./a.out < in.txt

    //Merge sort
    //vector<int> test_merge = {37,-8,20,51,16,-4,9,-2,41,5,-12,33,18,7,-6,28,15,3,50,-9,22,11,13,26,35};

    // ifstream infile("in.txt");  // Abrir el archivo de entrada
    ifstream infile("three.txt");  // Abrir el archivo de entrada
    // ifstream infile("three.txt");  // Abrir el archivo de entrada

    // if (!infile) {
    //     cout << "Error al abrir el archivo." << endl;
    //     return 1;
    // }

    int N;
    infile >> N;  // Lee el primer numero que es N, el tamaño del vector
    cout << "N: " << N << endl;

    vector<double> test_merge(N);  // Crear un vector de tamaño N

    for (int i = 0; i < N; i++) {
        infile >> test_merge[i];  // Leer los numeros y almacenarlos en el vector
        cout << test_merge[i] << " ";
    }

    cout << endl;

    infile.close(); 
    
    mergeSort(test_merge, 0, N-1);
    
    cout << "Merge Sort: ";
    for (int i = 0; i< N; i++){
        cout << test_merge[i] <<" ";
    }

    return 0;
}