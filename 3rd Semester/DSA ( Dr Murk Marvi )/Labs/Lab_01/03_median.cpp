#include<iostream>
#include<algorithm>
#include<vector>
using namespace std ;

class MedianFinder {
	private:
		vector<int> arr ;
	public:
		MedianFinder( ) : arr( 0 ) { }
		void addNum( int x ) { 
			// Insert `num` into the sorted `arr` using binary search to maintain sorted order. So can avoid O( n log n ) sorting.
        	vector<int>::iterator pos = lower_bound( arr.begin(), arr.end(), x ) ;
			arr.insert( pos, x ) ;
		}
		double findMedian( ) {
			// sort( arr.begin() , arr.end() ) ; 
			int n = arr.size() ;
			if( n % 2 != 0 )
				return arr[ n / 2 ] ;
			else
				return ( arr[ (n - 1) / 2 ] + arr[ ( n + 1 ) / 2 ] ) / 2.0 ;

		}
		~MedianFinder( ) {
			arr.clear() ;
		}
};

int main() {
	MedianFinder *medianFinder = new MedianFinder();
	medianFinder -> addNum(1); // arr = [1]
	medianFinder -> addNum(2); // arr = [1, 2]
	cout << medianFinder -> findMedian() << endl ; // return 1.5 (i.e., (1 + 2) / 2)
	medianFinder -> addNum(3); // arr[1, 2, 3]
	cout << medianFinder -> findMedian() << endl ; // return 2.0
	delete medianFinder ;
	return 0 ;
}