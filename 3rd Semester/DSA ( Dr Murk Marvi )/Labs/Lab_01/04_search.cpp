#include<iostream>
using namespace std ;

int binarySearch( int arr[] , int n , int target ) {
    int low = 0 , high = n - 1 ;
    while( low <= high ) {
        int mid = low + (high - low) / 2 ;

        if( arr[mid] == target )
            return mid ;
        else if( arr[mid] < target )
            low = mid + 1 ;
        else 
            high = mid - 1 ;
    }
    return -1 ;
}

int custom_lower_bound(int arr[] , int n , int value) {
    int low = 0;
    int high = n - 1 ;
    int res = low ; // OR initialize high = n ; while( low < high ) and do high = mid and return low.

    while (low <= high) {
        int mid = low + (high - low) / 2;
        
        if ( arr[mid] < value)
            low = mid + 1;  // Look for larger-value.
        else {
            res = mid ;
            high = mid - 1 ;  // We found a candidate, but keep searching on the left side for lowest-place.
        }
        
    }

    return res;
}

int main(){
    int arr[] = { -1,0,3,5,9,9,12 } ;
    int n = sizeof(arr) / sizeof( arr[0] ) ;
    cout << "Found 9 at index = " << binarySearch( arr , n , 9 ) << endl ;
    cout << "Found 2 at index = " << binarySearch( arr , n , 2 ) << endl ;
    cout << custom_lower_bound( arr , n , 9 ) << endl ;
    return 0;
}