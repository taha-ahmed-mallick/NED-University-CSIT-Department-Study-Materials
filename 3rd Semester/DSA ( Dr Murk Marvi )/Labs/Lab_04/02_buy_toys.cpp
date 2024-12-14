#include<iostream>
#include<vector>
using namespace std ;

int bySeletionSort( vector<int>& arr , int sum ) {
    int n = arr.size() ;
    int count = 0 ;
    cout << "Out of " << n << " toys ; only toys with prices " ;
    for( int i = 0 ; i < n - 1 ; i++ ) {
        int minIdx = i ;
        for( int j = i ; j < n ; j++ ) {
            if( arr[j] < arr[minIdx] )
                minIdx = j ;
        }

        if( minIdx != i ) {
            swap( arr[i], arr[minIdx] ) ;
        }

        if( sum >= arr[i] ) {
            sum -= arr[i] ;
            count++ ;
            cout << arr[i] << " " ;
        }
    }
    cout << endl ;
    return count ;
}

int knapsack( vector<int>& arr , int n , int sum ) {
    if( n == 0 || sum == 0 )
        return 0 ;
    
    if( arr[n - 1] > sum )
        return knapsack( arr, n - 1, sum ) ;
    
    cout << arr[n - 1] << " " ;
    return knapsack( arr, n - 1, sum - arr[n - 1] ) + 1 ;
}

int main(){
    vector<int> arr = {1, 12, 5, 111, 200, 1000, 10} ;
    cout << bySeletionSort( arr , 50 ) << endl ;
    cout << "Purchased = " ;
    int count = knapsack( arr , arr.size() , 50 ) ;
    cout << endl << count << endl ;
    return 0;
}