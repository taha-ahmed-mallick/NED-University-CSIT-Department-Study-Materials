#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int findMax(const vector<int>& arr, int n) {
    int maxIndex = 0;
    for ( int i = 1 ; i <= n ; i++ ) {
        if ( arr[i] > arr[maxIndex] )
            maxIndex = i ;
    }
    return maxIndex;
}

void pancakeSort(vector<int>& arr) {
    int n = arr.size();
    
    for ( int currSize = n - 1 ; currSize > 0 ; currSize-- ) { // 0th-index will automatically be sorted.
        // int maxIndex = findMax(arr, currSize); // From n to 2 ; and find max from i = 0 < n.
        int maxIndex = findMax( arr , currSize ) ;
        if( maxIndex != currSize ) {
            if( maxIndex != 0 )
                reverse( arr.begin() , arr.begin() + maxIndex + 1 ) ; // +1 to cover last element also.
            
            reverse( arr.begin() , arr.begin() + currSize + 1 ) ;
        }
    }
}

int main() {
    vector<int> arr = {3, 2, 4, 1, 5};
    
    cout << "Original array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    pancakeSort(arr);

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
