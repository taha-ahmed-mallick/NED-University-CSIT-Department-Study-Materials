#include<iostream>
#include<vector>
using namespace std ;

void merge( vector<int>& arr , int low , int mid , int high ) {
    int i = low , j = mid + 1 ;
    int k = low ;
    vector<int> temp( high - low + 1 ) ;

    while( i <= mid && j <= high ) {
        if( arr[i] < arr[j] )
            temp[k++] = arr[i++] ;
        
        else
            temp[k++] = arr[j++] ;
    }

    for( ; i <= mid ; i++ )
        temp[k++] = arr[i] ;
    
    for( ; j <= high ; j++ )
        temp[k++] = arr[j] ;
    
    for( int index = low ; index <= high ; index++ )
        arr[index] = temp[index] ;
}

void mergeSort( vector<int>& arr ) {
   int n = arr.size();
    for (int pass = 1 ; pass < n; pass *= 2 ) {
        for (int i = 0 ; i < n ; i += 2 * pass ) {
            int low = i ;
            int mid = min( i + pass - 1 , n - 1 ) ; // Used min() as it was not merging for last array.
            int high = min( i + 2 * pass - 1 , n - 1 ) ;
            if ( mid < high ) // Only merge if there are at least two parts to merge
                merge( arr, low, mid, high ) ;
        }
    }
}

int main(){
    vector<int> arr = {2,1,8,4,3,5};
    mergeSort( arr ) ;
    for( int n : arr )
        cout << n << " " ;
    cout << endl ;
    return 0;
}