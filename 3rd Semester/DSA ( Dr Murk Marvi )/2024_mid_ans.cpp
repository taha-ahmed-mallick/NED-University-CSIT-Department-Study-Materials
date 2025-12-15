#include<iostream>
#include<vector>
#include"./Topic Codes/linked_list.cpp"
using namespace std ;

void solve( vector<vector<int>>& res , vector<int>& cur , int n , int f ) {
    if( n <= 0 ) {
        res.push_back( cur ) ;
        return ;
    }

    for( int i = 1 ; i <= f ; i++ ) {
        cur.push_back( i ) ;
        solve( res , cur , n - 1 , f ) ;
        cur.pop_back() ;
    }
}

vector<vector<int>> generateFaces( int n , int f ) {
    vector<vector<int>> res ;
    vector<int> temp ;
    solve( res , temp , n , f ) ;
    return res ;
}

void displayAns( vector<vector<int>>& ans ) {
    for( vector<int>& row : ans ) {
        cout << "{" ;
        for( int& num : row )
            cout << num << "," ;
        cout << "} " ;
    }
    cout << endl ;
}

void DeleteEachKthNode( Node* & head , int k ) {
    if( !head || k <= 0 )
        return ;
    
    Node* cur = head , *prev = nullptr ;
    while( cur ) {

        for( int i = 1 ; i <= k - 1 && cur ; i++ ) {
            prev = cur ; 
            cur = cur -> next ;
        }

        if( cur == head ) {
            Node* temp = head ;
            head = head -> next ;
            cur = head ;
            delete temp ;
            temp = nullptr ;
        }
        else {
            prev -> next = ( cur ) ? cur -> next : nullptr ;
            if( cur ) {
                Node* temp = cur ;
                cur = cur -> next ;
                delete temp ;
            }
        }
    }
}

int main(){
    vector<vector<int>> ans = generateFaces( 2 , 6 ) ;
    displayAns( ans ) ;

    LinkedList l ;
    l.insert( 5 ) ;
    l.insert( 4 ) ;
    l.insert( 1 ) ;
    l.insert( 2 ) ;
    DeleteEachKthNode( l.head , 2 ) ;

    l.display( l.head ) ;
    return 0;
}