#include <iostream>
#include <vector>
using namespace std;

template<typename T>
int partition(vector<T>& arr, int low, int high) {
    T pivot = tolower(arr[high]);
    int i = low - 1;

    for (int j = low; j < high; j++) {
        T ch = tolower(arr[j]);
        if (ch <= pivot) { 
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // Place the pivot in the correct position
    return i + 1; // Return the partitioning index
}

template<typename T>
void display(const vector<T>& arr) {
    for (const auto& elem : arr)
        cout << elem << " ";
    cout << endl;
}

template<typename T>
void quickSort(vector<T>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high); 
        display(arr);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    // char arr[] = {'G', 'd', 'E', 'c', 'b', 'e', 'A'};
    vector<int> arr = {5, 7, 2, 1, 3, 4, 10};
    int n = arr.size();
    quickSort(arr, 0, n - 1);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;

    return 0;
}