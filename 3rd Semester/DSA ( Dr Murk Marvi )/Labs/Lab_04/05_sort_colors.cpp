#include<iostream>
#include<vector>
using namespace std ;

void firstWay( vector<int>& arr ) {
    int zeros = 0 , ones = 0 , twos = 0 ;
    int n = arr.size( ) ;
    for( int i = 0; i < n ; i++ ) {
        if( arr[i] == 0 )
            zeros++ ;
        else if( arr[i] == 1 )
            ones++ ;
        else if( arr[i] == 2 )
            twos++ ;
    }

    int k = 0 ;
    for( int i = 1 ; i <= zeros ; i++ )
        arr[k++] = 0 ;
    
    for( int i = 1 ; i <= ones ; i++ )
        arr[k++] = 1 ;
    
    for( int i = 1 ; i <= twos ; i++ )
        arr[k++] = 2 ;
}

/*
The Dutch-Flag problem is similar to “Segregate 0s and 1s in an array”. The idea is to sort the array of size N using three pointers: lo = 0, mid = 0 and hi = N – 1 such that the array is divided into three parts:

    arr[0] to arr[lo – 1]: This part will have all the zeros.
    arr[lo] to arr[mid – 1]: This part will have all the ones.
    arr[hi + 1] to arr[N – 1]: This part will have all the twos.    */
void divideAndConquer( vector<int>& arr ) {
    int n = arr.size() ;
    int low = 0 , mid = 0 , high = n - 1 ;

    while( mid <= high ) {
        if( arr[mid] == 0 ) {
            swap( arr[low], arr[mid] ) ;
            low++ ; mid++ ;
        }

        else if( arr[mid] == 1 ) {
            mid++ ;
        }

        else if( arr[mid] == 2 ) {
            swap( arr[mid] , arr[high] ) ;
            // mid++ ; high-- ; MY-Mistake, Don't increment mid as boundary should be b/w high and 'n' for 2.
            high-- ;
        }
    }
}

int main(){
    vector<int> arr1 = {2,0,2,1,1,0} ;
    vector<int> arr2 = {2,0,1} ;
    vector<int> arr3 = arr1 ;
    vector<int> arr4 = arr2 ;
    firstWay( arr1 ) ;
    firstWay( arr2 ) ;
    divideAndConquer( arr3 ) ;
    divideAndConquer( arr4 ) ;
    for( int i = 0 ; i < arr1.size() ; i++ )
        cout << arr1[i] << " " ;
    cout << endl ;

    for( int n : arr2 )
        cout << n << " " ;
    cout << endl ;

    for( int n : arr3 )
        cout << n << " " ;
    cout << endl ;
    return 0;
}