#include <iostream>
#include <vector>
using namespace std;

void ToColumnMajor(int **arr, int rows, int col[], vector<int>& result) {
    int maxCols = 0;
    for ( int i = 0; i < rows; i++ ) 
        maxCols = max( maxCols, col[i] ) ;
    // result.resize(rows * maxCols) ;

    int k = 0 ; 
    for ( int j = 0 ; j < maxCols ; j++ ) {
        for ( int i = 0; i < rows; i++ ) {
            if ( j < col[i] )  // Check if the current row has the j-th column due to jagged array.
                // result[k++] = arr[i][j] ;
                result.push_back( arr[i][j] ) ;
        }
    }
}

void display1DArray(const vector<int>& arr) {
    for (int val : arr) 
        cout << val << " ";
    cout << endl;
}

int main() {
    int r;
    cout << "Enter number of rows: ";
    cin >> r;

    int **arr = new int*[r];
    int col[r] ;

    for ( int i = 0; i < r ; i++ ) {
        cout << "Enter number of elements to be inserted in Row " << i + 1 << ": ";
        cin >> col[i] ;
        arr[i] = new int[ col[i] ] ;

        cout << "Enter total " << col[i] << " elements: " ;
        for ( int j = 0 ; j < col[i] ; j++ )
            cin >> arr[i][j] ;
    }

    vector<int> result;
    ToColumnMajor(arr, r, col, result);
    cout << "1D array in column-major order:" << endl;
    display1DArray(result);
    for ( int i = 0; i < r ; i++ ) 
        delete arr[i] ;
    delete[] arr;

    return 0;
}