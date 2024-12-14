#include<iostream>
#include<vector>
#include<stack>
using namespace std ;

// int partition(vector<int>& arr, int low, int high) {
//     int pivot = arr[high];
//     int i = low - 1; // MISTAKE: do (low - 1) not only -1.

//     for (int j = low; j < high; j++) {
//         if (arr[j] <= pivot) {
//             i++;
//             swap(arr[i], arr[j]); // Swap if element is smaller than or equal to pivot
//         }
//     }
//     swap(arr[i + 1], arr[high]); // Move pivot to correct position
//     return i + 1; // Return the partition index
// }

int partition( vector<int>& arr , int low, int high ) {
    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while ( i <= j ) {
        while ( i <= j && arr[i] <= pivot ) 
            i++ ;
        while ( i <= j && arr[j] > pivot ) 
            j-- ;

        if ( i < j )
            swap(arr[i], arr[j]) ;
    }

    // Place the pivot in the correct position
    swap(arr[low], arr[j]);
    return j ;
}

void iterativeQuickSort(vector<int>& arr) {
    stack<int> stack;

    stack.push(0);
    stack.push(arr.size() - 1);
    while (!stack.empty()) {
        int high = stack.top();
        stack.pop();
        int low = stack.top();
        stack.pop();

        // Set pivot element at its correct position
        int pivotIndex = partition(arr, low, high);

        // If there are elements on the left side of the pivot, push them to the stack
        if ( low <= pivotIndex - 1 ) {
            stack.push( low );
            stack.push( pivotIndex - 1 ) ;
        }

        // If there are elements on the right side of the pivot, push them to the stack
        if ( pivotIndex + 1 <= high ) {
            stack.push(pivotIndex + 1);
            stack.push(high);
        }
    }
}

/* Instead of stack can use simple loop also. */
void iterativeQuickSortWithoutStack(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) 
        return ;

    int low = 0, high = n - 1;

    while (low < high) {
        int pivotIndex = partition(arr, low, high);

        if ( low < pivotIndex - 1 )
            high = pivotIndex - 1;
        else
            low = pivotIndex + 1; 

        // If no more elements need sorting, break out of the loop
        if ( low >= high )
            break;
    }
}


int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    cout << "Unsorted array: ";
    for ( int num : arr )
        cout << num << " " ;
    cout << endl;

    vector<int> arr2 = arr ;
    iterativeQuickSort(arr);
    iterativeQuickSortWithoutStack( arr2 ) ;

    cout << "Sorted array: ";
    for ( int num : arr )
        cout << num << " " ;
    cout << endl;
    cout << "2nd arr = " ;
    for ( int num : arr2 )
        cout << num << " " ;
    cout << endl;

    return 0;
}