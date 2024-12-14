#include<iostream>
#include<vector>
#include<queue>
using namespace std ;

class MinHeap {
    private:
        vector<int> arr ;
    public:
        MinHeap() {}
        
        void insert( int key ) {
            arr.push_back( key ) ;
            int i = arr.size() - 1 ;

            while( i > 0 && arr[i] < arr[ ( i - 1 ) / 2 ] ) {
                swap( arr[i], arr[ ( i - 1 ) / 2 ] ) ;
                i = ( i - 1 ) / 2 ;
            }
        }

        void DeleteTop( ) {
            if( arr.empty() ) {
                cout << "Heap is empty!\n" ;
                return ;
            }
            
            int n = arr.size() ;
            arr[0] = arr[n - 1] ;
            arr.pop_back() ;

            int i = 0 ;
            while( ( 2 * i + 1 ) < n ) { // Continue if there is at least one child
                int RC = 2 * i + 2 ;
                int smallest = 2 * i + 1 ; // Directly assign LC as smallest b/c its a complete-bin tree.

                if( RC < n && arr[smallest] > arr[RC] )
                    smallest = RC ;
                
                if( arr[i] < arr[smallest] )
                    break ;
                
                swap( arr[i], arr[smallest] ) ;
                i = smallest ;
            }
        }

        int top() { return ( !arr.empty() ) ? arr[0] : -1 ; }

        // void check() {
        //     while (!arr.empty()) {
        //         cout << top() << " ";
        //         DeleteTop();
        //     }
        //     cout << endl;
        // }

        int findMax() {
            if ( arr.empty() ) {
                throw invalid_argument("Heap is empty!\n") ;
            }

            int n = arr.size() ;

            int maxVal = arr[n / 2] ; // Start with 1st leaf node
            for ( int i = n / 2 + 1; i < n; i++ )
                maxVal = max( maxVal, arr[i] ) ;

            return maxVal;
        }
} ;

int main(){
    MinHeap heap ;

    heap.insert(10);
    heap.insert(30);
    heap.insert(20);
    heap.insert(50);
    heap.insert(15);
    heap.insert(80); // --> Max
    heap.insert(40);
    heap.insert(70);
    heap.insert(60);
    heap.insert(25);
    heap.insert(5);
    heap.insert(35);
    heap.insert(45);
    heap.insert(65);
    heap.insert(55);

    // heap.check(); // For checking.
    cout << heap.findMax() << endl ;
    return 0;
}