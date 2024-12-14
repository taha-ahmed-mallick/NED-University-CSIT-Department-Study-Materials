#include<iostream>
#include<vector>
using namespace std;

vector<int> binarySearch( vector<vector<int>> arr , int target ) {
	int col = arr[0].size() ;
	int low = 0 ;
	int high = ( arr.size() * col ) - 1 ; // 2D array flattened into 1D for binary search
	
	while( low <= high ) {
		int mid = low + ( high - low ) / 2 ;
		int e = arr[ mid / col ][ mid % col ] ; // ( mid / col ) gives the position in array like for '60' ; 11 / 4 = 3 ; and ( mid % col ) gives it position from left side in that row i.e. cols.
		
		if( e == target )
			return { mid / col , mid % col } ;
		else if( e < target )
			low = mid + 1 ;
		else
			high = mid - 1 ;
	}
	
	return { -1 , -1 } ;
}

int main(){
	vector<vector<int>> arr = { { 1 , 3, 5 , 7 } , 
								{ 10 , 11 , 16 , 20 } ,
								{ 23 , 30 , 34 , 60  } } ;
	
	int target ;
	for( int i = 0 ; target != -1 ; i++ ) {
		cout << "Enter target element ( -1 To exit searching ): " ;
		cin >> target ;	
		vector<int> indices = binarySearch( arr , target ) ;		
		cout << "Found " << target << " at row = " << indices[0] << " ; col = " << indices[1] << endl ;
	}

	return 0 ;
}