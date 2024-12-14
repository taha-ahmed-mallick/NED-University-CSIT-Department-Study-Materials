#include<iostream>
#include<vector>
using namespace std ;

void permutations( vector<vector<int>> &res , vector<int>& cur , vector<int> &set , vector<bool> visited ) {
    if( cur.size() == set.size() ) {
        res.push_back( cur ) ;
        return ;
    }

    for( int i = 0; i < set.size(); i++ ) {
        if( !visited[i] ) {
            cur.push_back( set[i] ) ;
            visited[i] = true ;
            permutations( res , cur , set , visited ) ;
            cur.pop_back( ) ;
            visited[i] = false ;
        }
    }
}

void permutationsAnother( vector<vector<int>>& res , vector<int>& set , int low , int high ) {
    if( low == high ) {
        res.push_back( set ) ;
        return ;
    }

    for( int i = low ; i <= high ; i++ ) {
        swap( set[i] , set[low] ) ;
        permutationsAnother( res , set , low + 1 , high ) ; // Call low + 1 NOT i + 1 as we need to swap each part byLoop and recursion to separateParts.
        swap( set[i] , set[low] ) ; // Backtrack to remove swap.
    }
}

int main(){
    vector<int> set = { 1,2,3 } ;
    vector<vector<int>> result ;
    vector<int> temp ;
    // bool visited[ set.size() ] = {false} ; // This can cause error in standard C++ ;

    vector<bool> visited( set.size(), false ) ;  // Using vector<bool> for dynamic size
    permutations( result , temp , set , visited ) ;
    // permutationsAnother( result , set , 0 , set.size() - 1 ) ;
    for( int i = 0 ; i < result.size() ; i++ ) {
        cout << "{ " ;
        for( int j = 0 ; j < result[i].size() ; j++ ) {
            cout << result[i][j] ;
            if( j != result[i].size() - 1 )
                cout << ", " ;
        }
        cout << " }\n" ;
    }

    return 0;
}