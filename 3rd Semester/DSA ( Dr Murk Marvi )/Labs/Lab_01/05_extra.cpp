#include<iostream>
#include<vector>
#include<thread>
#include<chrono>
using namespace std;

// Which is in-fact maxColumns
int maxRowLength( vector<vector<int>> arr ) {
	int maxRowLen = 0 ;
	for( vector<int>& row : arr ) {
		if( row.size() > maxRowLen ) 
			maxRowLen = row.size() ;
	}

	return maxRowLen ;
}

vector<int> binarySearch( vector<vector<int>> arr , int target ) {
	if( arr.empty() || arr[0].empty() )
		return { -1 , -1 } ;

	// int col = arr[0].size() ;
	int col = maxRowLength( arr ) ; // By using this my code will also worked with jagged arrays.
	
	int low = 0 ;
	int high = ( arr.size() * col ) - 1 ; // 2D array flattened into 1D for binary search. As arr.size() can't be jagged so direct use.
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

vector<int> anotherBinarySearch( vector<vector<int>> arr , int target ) {
	if (arr.empty() || arr[0].empty())
        return {-1, -1};

    int rows = arr.size();
    int cols = arr[0].size();
    
    // Binary search to find the correct row
    int low = 0, high = rows - 1;
    int targetRow = -1;

    while (low <= high) {
        int mid = (low + high) / 2;

        if (arr[mid][0] <= target && arr[mid][cols - 1] >= target) { // If in row range.
            targetRow = mid ;
            break ;
        }
        else if ( arr[mid][cols - 1] < target ) 
            low = mid + 1 ;
        else
            high = mid - 1 ;
    }

    if ( targetRow == -1 ) 
        return {-1, -1} ; 

    low = 0;
    high = cols - 1 ;

    while (low <= high) {
        int mid = (low + high) / 2;

        if ( arr[targetRow][mid] == target ) 
            return { targetRow, mid } ;
        else if ( arr[targetRow][mid] < target ) 
            low = mid + 1 ;
        else
            high = mid - 1 ;
    }

    return { -1, -1 } ; 
}

int main(){
	vector<vector<int>> arr = { { 1 , 3, 5 , 7 } , 
								{ 10 , 11 , 16 , 20 } ,
								{ 23 , 30 , 34 , 60 } } ;
	int target = 11 ;
	
	auto start = chrono::high_resolution_clock::now() ;
	vector<int> indices = binarySearch( arr , target ) ;
	vector<int> indices_2 = anotherBinarySearch( arr , target ) ;
	auto end = chrono::high_resolution_clock::now() ;
			
	cout << "Found " << target << " at row = " << indices[0] << " ; col = " << indices[1] << endl ;
	cout << "Found " << target << " at row = " << indices_2[0] << " ; col = " << indices_2[1] << endl ;
	chrono::duration<double , micro> time = end - start ;
	cout << "Time = " << time.count() << " micro seconds." << endl ;
	return 0 ;
}