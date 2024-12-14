#include<iostream>
#include<queue>
using namespace std ;

class DataStream {
    private:
        queue<int> Q ;
        int val , k ; // OR can use another variable 'count' And if another variable found so set count = 0 else count++ ; return count >= k.
        // int count ;
    public:
        DataStream( int value , int k ) : val( value ) , k( k ) {}
        bool consec( int num ) {
            Q.push( num ) ;
            int n = Q.size() ;
            if( k > n )
                return false ; // To avoid irregular traversal OR use n >= k with both for-and-while loops with AND.
            
            for( int i = 0 ; i < n - k ; i++ ) {
                Q.push( Q.front() ) ;
                Q.pop() ;
            }

            // Old Method
            // bool check = false ;
            // int i ;
            // for( i = 1 ; i <= k ; i++ ) {
            //     if( Q.front() == val )
            //         check = true ;
            //     else {
            //         check = false ;
            //         // i-- ; // As I am pushing ; pooping in last ( Wrong it will make pus previous again also )
            //         break ;
            //     }
                
            //     Q.push( Q.front() ) ;
            //     Q.pop() ;
            // }
            // while( i <= k ) {
            //     Q.push( Q.front() ) ;
            //     Q.pop() ;
            //     i++ ;
            // }

            bool check = true ;
            for( int i = 1 ; i <= k ; i++ ) {
                check &= ( val == Q.front() ) ;
                Q.push( Q.front() ) ;
                Q.pop() ;
            }
            return check ;
        }

        /*bool consec(int num) {
        Q.push(num);
        
        if (num == val)
            count++;
        else
            count = 0;

        if (Q.size() > k) {
            int front = Q.front();
            Q.pop();
            if ( front == val )
                count--;
        }

        // Check if we have at least k consecutive occurrences of val
        return count >= k;
    }*/

        void display( ) {
            queue<int> temp = Q;
            while ( !temp.empty() ) {
                cout << temp.front() << " " ;
                temp.pop() ;
            }
            cout << endl ;
        }

        ~DataStream() { while( !Q.empty() ) Q.pop(); }
} ;

int main(){
    DataStream dataStream( 4 ,3 ) ;
    cout << boolalpha << dataStream.consec( 4 ) << " " ;
    dataStream.display( ) ;
    cout << boolalpha << dataStream.consec( 4 ) << " " ;
    dataStream.display( ) ;
    cout << boolalpha << dataStream.consec( 4 ) << " " ;
    dataStream.display( ) ;
    cout << boolalpha << dataStream.consec( 3 ) << " " ;
    dataStream.display( ) ;
    return 0;
}