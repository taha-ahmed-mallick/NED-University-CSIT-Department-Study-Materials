#include<iostream>
#include<queue>
using namespace std ;

int josephus( queue<int>& Q , int k ) {
    while( Q.size( ) > 1 ) {
        for( int i = 1 ; i <= k - 1 ; i++ ) { // Move the turn to 'k - 1' persons i.e. fronts to end.
            Q.push( Q.front() ) ;
            Q.pop() ;
        }
        Q.pop() ; // After that remove k-th each person.
    }
    return Q.front() ;
}

int main(){
    int n = 5 , n2 = 41 , k = 2 ;
    // cout << "Enter total no.of persons: " ;
    // cin >> n ;

    queue<int> Q , Q2;
    for( int i = 1 ; i <= n ; i++ )
        Q.push( i ) ; 
    for( int i = 1 ; i <= n2 ; i++ )
        Q2.push( i ) ;
    
    // k-- ; // We have to remove the k-th person not after that so decrement it.
    cout << josephus( Q , k ) << endl ;
    cout << josephus( Q2 , k ) << endl ;
    return 0;
}