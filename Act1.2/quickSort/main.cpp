#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &vec, int low, int high) {
    int pivot = vec[high]; // last element becomes the pivot
    int i = (low - 1); // the index of elemment just before the last element is used to swap

    for (int j = low; j <= high - 1; j++) {
        if (vec[j] <= pivot) {// if the element is less than or equal to the pivot
            i++; // increment the index
            swap(vec[i], vec[j]); // swap the elements
        }
    }
    swap(vec[i + 1], vec[high]); // swap the elements by making the pivot the middle element
    return (i + 1); // return the index of the pivot
}

void quickSort(vector<int> &vec, int low, int high) {
    if (low < high) { // index low is lesser than the ending index high
        int p = partition(vec, low, high); // p is partitioning index, arr[p] is now at right place

        quickSort(vec, low, p - 1); // recursively sort elements before partition
        quickSort(vec, p + 1, high); // recursively sort elements after partition
    }
}

int main() {
    vector<int> vec = {10, 7, 8, 9, 1, 5};
    int N = vec.size();
    cout << "Unsorted Array: \n";
    for (auto i : vec) {
        cout << i << " ";
    }
    cout << endl;

    quickSort(vec, 0, N - 1); // O(n) = nlog(n)

    cout << "Sorted Array: \n";
    for (auto i : vec) {
        cout << i << " ";
    }
    return 0;
}