#include<iostream>
#include<vector>
using namespace std ;

bool isPrime( int num ) {
    for( int i = 2 ; i < num ; i++ ) {
        if( num % i == 0 )
            return false ;
    }
    return true ;
}

// Old Time = O( n^2 )
vector<int> primeFactors( int num ) {
    vector<int> res ;
    for ( int factor = 2; factor <= num; factor++ ) {
        while ( isPrime(factor) && num % factor == 0 ) { // It will check all same-factor at once.
            res.push_back(factor) ;
            num /= factor ; // Keep dividing num by the factor
        }
    }
    return res ;
}

// New Time = O( n * log(log(N) )
vector<int> sieveOfEratosthenes( int num ) {
    vector<bool> isPrime( num + 1 , true ) ;
    isPrime[0] = isPrime[1] = false ; // '0' and '1' dependent on Condition but are not considered prime for SIEVE.

    for( int i = 2 ; i * i <= num ; i++ ) { // OR i <= sqrt(num) as all above will covered if factors.
        if( isPrime[i] ) {
            for( int j = i * i ; j <= num ; j += i ) // Start multiples from i * i rather than 2 * i as they will be marked previously.
                isPrime[j] = false ;
        }
    } 

    vector<int> res ;
    for( int i = 0 ; i <= num ; i++ ) {
        if( isPrime[i] )
            res.push_back( i ) ;
    }
    return res ;
}

void display( vector<int>& arr ) {
    for( int& n : arr )
        cout << n << " " ;
    cout << endl ;
}

int main(){
    vector<int> a = primeFactors( 15 ) ;
    display( a ) ;
    vector<int> b = sieveOfEratosthenes( 15 ) ;
    display( b ) ;
    return 0;
}