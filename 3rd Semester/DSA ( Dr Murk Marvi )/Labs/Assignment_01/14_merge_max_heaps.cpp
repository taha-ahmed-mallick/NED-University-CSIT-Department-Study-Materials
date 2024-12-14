#include<iostream>
#include<vector>
#include<algorithm>
using namespace std ;

class MaxHeap {
    public:
        vector<int> arr ;
        MaxHeap() {}
        
        void insert( int key ) {
            arr.push_back( key ) ;
            int i = arr.size() - 1 ;

            while( i > 0 && arr[i] > arr[ ( i - 1 ) / 2 ] ) {
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
                int largest = 2 * i + 1 ; // Directly assign LC as smallest b/c its a complete-bin tree.

                if( RC < n && arr[largest] < arr[RC] )
                    largest = RC ;
                
                if( arr[i] > arr[largest] )
                    break ;
                
                swap( arr[i], arr[largest] ) ;
                i = largest ;
            }
        }

        int top() { return ( !arr.empty() ) ? arr[0] : -1 ; }
} ;

void heapify( vector<int>& arr , int i ) {
    int n = arr.size();

    while( ( 2 * i + 1 ) < n ) {
        int RC = 2 * i + 2 ;
        int largest = 2 * i + 1  ;

        if( RC < n && arr[largest] < arr[RC] )
            largest = RC ;
        
        if( arr[i] > arr[largest] )
            break ;

        swap( arr[i] , arr[largest] );
        i = largest ;
    }
}

// Time = O( m + n ) + O( log( m + n ) ) --> O(N) at-worst = O(N)
vector<int> mergeBinMaxHeaps( vector<int>& arr1 , vector<int>& arr2 , int m , int n ) {
    vector<int> res ;
    // 1st merge both arrays
    // for( int& num : arr1 )
    //     res.push_back( num ) ;

    // for( int& num : arr2 )
    //     res.push_back( num ) ;
    res.reserve( m  + n ) ; // For better memory-allocation can merge like this.
    copy( arr1.begin(), arr1.end(), back_inserter( res ) ) ;
    copy( arr2.begin(), arr2.end(), back_inserter( res ) ) ;

    // Build-Heap ; Start heapify from non-leaf level.
    int N = res.size() ;
    for( int i = ( N - 1 ) / 2 ; i >= 0 ; i-- )
        heapify( res , i ) ;

    return res ;

    /* OR can do like this

    for (int i = 0; i < n; i++)
        arr1[m + i] = arr2[i];
    
    for (int i = (m + n) / 2 - 1; i >= 0; i--)
        heapify( arr1, m + n, i);
    */
}

int main(){
    MaxHeap heap1; 
    heap1.insert(20) ;
    heap1.insert(40) ;
    heap1.insert(30) ;
    heap1.insert(50);
    heap1.insert(10) ;

    MaxHeap heap2 ;
    heap2.insert(45) ;
    heap2.insert(5) ;
    heap2.insert(15) ;
    heap2.insert(55) ;
    heap2.insert(25) ;
    heap2.insert(1) ;
    heap2.insert(17) ;
    
    vector<int> mergeHeap = mergeBinMaxHeaps( heap1.arr , heap2.arr , heap1.arr.size() , heap2.arr.size() ) ;
    for( int& num : mergeHeap )
        cout << num << " " ;
    cout << endl ;

    // cout << "Descending sort: " ;
    // while( !mergeHeap.empty() ) {
    //     cout << mergeHeap[0] << " " ;
    //     mergeHeap[0] = mergeHeap[ mergeHeap.size() - 1 ] ;
    //     mergeHeap.pop_back();
    //     heapify( mergeHeap , 0 ) ;
    // }

    return 0;
}