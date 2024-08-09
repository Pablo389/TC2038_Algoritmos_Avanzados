#include <iostream>
#include <vector>
using namespace std;


void merge(vector<int> &A, int p, int q, int r){

    const int n1 = q-p+1;
    const int n2 = r-q;

    int* L = new int[n1];
    int* R = new int[n2];


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

void mergeSort(vector<int> &A, int p, int r){

    if (p>=r){
        return;
    }
    int q = (p+r)/2;
    mergeSort(A, p, q);
    mergeSort(A, q+1, r);
    return merge(A, p, q, r);

}



int main(){

    
    //Merge sort
    vector<int> test_merge = {37,-8,20,51,16,-4,9,-2,41,5,-12,33,18,7,-6,28,15,3,50,-9,22,11,13,26,35};
    
    mergeSort(test_merge, 0, test_merge.size());
    
    cout << "Merge Sort: ";
    for (int i = 0; i< test_merge.size(); i++){
        cout << test_merge[i] <<",";
    }

    cout << endl;
    return 0;
}