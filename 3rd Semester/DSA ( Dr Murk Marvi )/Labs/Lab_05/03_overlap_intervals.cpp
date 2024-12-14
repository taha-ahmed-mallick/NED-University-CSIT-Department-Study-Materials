#include<iostream>
#include<vector>
#include<algorithm>
using namespace std ;

void overlapEvents( vector<vector<int>>& intervals ) {
    sort( intervals.begin(), intervals.end() ) ;

    // OR can return res vector ; and check its back()[1] overlap.
    int i = 0 ;
    while (i < intervals.size() - 1) {
        if (intervals[i][1] >= intervals[i + 1][0]) {
            intervals[i][1] = max( intervals[i][1], intervals[i + 1][1] ) ;
            intervals.erase( intervals.begin() + i + 1 ) ;
        } 
        else
            i++ ;
    }
}

int main(){
    vector<vector<int>> a = {{1,3},{2,6},{8,10},{15,18}} ;
    overlapEvents(a) ;
    for( vector<int>& row : a )
        cout << "[" << row[0] << "," << row[1] << "]" << " ";
    cout << endl ;

    vector<vector<int>> b = {{1,3},{2,6}} ;
    overlapEvents(b) ;
    for( vector<int> row : b )
        cout << "[" << row[0] << "," << row[1] << "]" << " ";
    return 0;
}