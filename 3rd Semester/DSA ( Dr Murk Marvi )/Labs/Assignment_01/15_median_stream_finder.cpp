#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class MedianStream {
    private:
        priority_queue<int> maxHeap; // For-lower half
        priority_queue<int, vector<int>, greater<int>> minHeap; // For-Upper half

        void balanceHeaps() {
            if ( maxHeap.size() > minHeap.size() + 1 ) { // For odd-length ; median should be in maxHeap so used +1 with minHeap. i.e. diff at-worst becomes (n + 2) after insertion.
                minHeap.push( maxHeap.top() ) ;
                maxHeap.pop() ;
            } 
            else if ( minHeap.size() > maxHeap.size() ) { // MinHeap size is (n + 1) ; Max = 'n'.
                maxHeap.push( minHeap.top() ) ;
                minHeap.pop();
            }
        }

    public:
        bool empty() {
            return maxHeap.empty() ; // As single-element will be in lower-half only.
        }

        // Time = O( log(n) ) ; Best-Time = O(1) if size was equal.
        void insert(int value) {
            if ( maxHeap.empty() || value <= maxHeap.top() )
                maxHeap.push(value) ;
            else
                minHeap.push(value) ;

            balanceHeaps(); // If both's size was equal before insertion i.e. n == n ; So let-it insert accordingly. But if any heap's size become greater than ( n + 1 ) than other 'n' so pop() that's element and insert in other.
        }

        void removeTop() {
            if ( empty() )
                throw runtime_error("Heap is empty.");
            
            maxHeap.pop(); // Remove 1st-middle for even-length case.
            balanceHeaps();
        }

        double top() { 
            if( empty() )
                throw runtime_error("Heap is empty.");

            if( maxHeap.size() > minHeap.size() ) // As for odd-elements ; we are storing 1-extra element in maxHeap OR else equal.
                return maxHeap.top() ;
            
            return ( minHeap.top() + maxHeap.top() ) / 2.0 ;
        }

        // // For verification.
        // void display() const {
        //     priority_queue<int> temp = maxHeap ;
        //     priority_queue<int , vector<int> , greater<int>> temp2 = minHeap ;

        //     while( !temp.empty() ) {
        //         cout << temp.top() << " " ;
        //         temp.pop() ;
        //     }

        //     while( !temp2.empty() ) {
        //         cout << temp2.top() << " " ;
        //         temp2.pop() ;
        //     }
        //     cout << endl ;
        // }
} ;

int main() {
    MedianStream mpq;
    mpq.insert(11);
    mpq.insert(7);
    mpq.insert(3);
    mpq.insert(4);
    mpq.insert(15);

    cout << "Middle Element = " << mpq.top() << endl;
    mpq.removeTop() ;
    cout << "Middle Element = " << mpq.top() << endl ;
    // mpq.display() ;
    return 0;
}