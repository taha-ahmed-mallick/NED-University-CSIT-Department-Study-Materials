#include<iostream>
#include<vector>
#include<algorithm>
using namespace std ;

bool carPooling(vector<vector<int>>& trips, int capacity) {
    // int maxLocation = 0 ;
    // for (const auto& trip : trips)
    //     maxLocation = max( maxLocation, trip[2] ) ;
    int maxLocation = max_element( trips.begin() , trips.end() , [](const vector<int>& a, const vector<int>& b) {
    return a[2] < b[2] ; } ) -> at(2) ;

    vector<int> passengerCount(maxLocation + 1, 0);
    
    for ( vector<int>& trip : trips) {
        int numPassengers = trip[0];
        int from = trip[1];
        int to = trip[2];
        passengerCount[from] += numPassengers;   // Pick up passengers
        passengerCount[to] -= numPassengers;     // Drop off passengers
    }
    
    int currentPassengers = 0;
    for (int i = 0; i <= maxLocation; i++) {
        currentPassengers += passengerCount[i] ;
        if ( currentPassengers > capacity ) // If at any point more passengers are available.
            return false ;
    }
    
    return true ;
}

bool carPoolingSort(vector<vector<int>>& trips, int capacity) {
    vector<pair<int, int>> events;

    for (const auto& trip : trips) {
        int numPassengers = trip[0] ;
        int from = trip[1] ;
        int to = trip[2] ;
        events.push_back( {from, numPassengers} );
        events.push_back( {to, -numPassengers} ) ;
    }

    // Sort events: first by location, then by passenger change
    // If the locations are the same, prioritize drop-offs (i.e., negative passenger change)
    sort( events.begin(), events.end() , [](const pair<int, int>& a, const pair<int, int>& b) {
        if (a.first == b.first)
            return a.second < b.second ;

        return a.first < b.first ;
    } ) ;

    int currentPassengers = 0;
    
    for (const auto& event : events) {
        currentPassengers += event.second ;
        if (currentPassengers > capacity) 
            return false;
    }

    return true;
}

int main(){
    vector<vector<int>> a = {{2,1,5} , {3,3,7}} ;
    cout << boolalpha << carPooling( a , 4 ) << endl;
    cout << boolalpha << carPooling( a , 5 ) << endl;
    cout << boolalpha << carPoolingSort( a , 4 ) << endl;
    cout << boolalpha << carPoolingSort( a , 5 ) << endl;
    return 0;
}