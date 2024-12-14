#include<iostream>
#include<queue>
using namespace std ;

class ProductOfNumbers {
    private:
        queue<int> Q ;
    public:
        ProductOfNumbers() {}
        void add( int num ) { Q.push( num ); }
        int getProduct( int k ) { 
            if( k > Q.size() ) {
                cout << "k is out of range!\n" ;
                return INT_MIN ;
            }

            int n = Q.size() ;
            // To shift non-needed elements in last. As we needed to use O(1) space. so do inplace.
            for( int i = 0 ; i < n - k ; i++ ) {
                Q.push( Q.front() ) ;
                Q.pop() ;
            }

            int mult = 1 ;
            // Again shift so that Q has same order.
            for( int i = 1 ; i <= k ; i++ ) {
                mult *= Q.front() ;
                Q.push( Q.front() ) ;
                Q.pop() ;
            }
            return mult ;
        }

        void display( ) {
            queue<int> temp ;
            while( !Q.empty() ) {
                temp.push( Q.front() ) ;
                cout << Q.front( ) << " " ;
                Q.pop() ;
            }

            while( !temp.empty() ) {
                Q.push( temp.front() ) ;
                temp.pop() ;
            }
        }
        ~ProductOfNumbers() { while( !Q.empty() ) { Q.pop() ; } }
} ;

int main(){
    ProductOfNumbers* productOfNumbers = new ProductOfNumbers( ) ;
    productOfNumbers -> add( 3 ) ;
    productOfNumbers -> add( 0 ) ;
    productOfNumbers -> add( 2 ) ;
    productOfNumbers -> add( 5 ) ;
    productOfNumbers -> add( 4 ) ;
    cout << "Product of last 2 = " << productOfNumbers -> getProduct( 2 ) << endl ;
    cout << "Product of last 3 = " << productOfNumbers -> getProduct( 3 ) << endl ;
    cout << "Product of last 4 = " << productOfNumbers -> getProduct( 4 ) << endl ;
    productOfNumbers -> add( 8 ) ;
    cout << "Product of last 2 = " << productOfNumbers -> getProduct( 2 ) << endl ;
    productOfNumbers -> display() ;
    delete productOfNumbers ;
    return 0;
}