#include<iostream>
#include<queue>
using namespace std ;

struct Node {
    int val ;
    Node* left ;
    Node* right ;
    Node( int val ) : val(val) , left(nullptr), right(nullptr) {}

    void deleteTree(Node* root) {
        if ( root ) {
            deleteTree( root -> left ) ;
            deleteTree( root -> right ) ;
            delete root;
            root = nullptr ;
        }
    }
} ;

int countEdges( Node* root , int key ) {
    Node* cur = root ;
    int count = 0 ; // Start from '0' as to count edges.
    while( cur ) {
        if( cur -> val > key )
            cur = cur -> left ;
        else if( cur -> val < key )
            cur = cur -> right ;
        else
            return count ;
        count++ ;
    }

    return -1 ;
}

Node* LCA( Node* root , int x , int y ) {
    if( !root )
        return nullptr ;
    
    if( root -> val > x && root -> val > y )
        return LCA( root -> left, x , y  ) ;
    else if( root -> val < x && root -> val < y )
        return LCA( root -> right, x , y ) ;
    
    return root ;
}

int minDistance( Node* root , int x , int y ) {
    Node* ancestor = LCA( root , x , y ) ;
    if( !ancestor )
        return -1 ;
    
    return countEdges( ancestor, x ) + countEdges( ancestor , y ) ; // As min-path will pass through that ancestor.
}

int main(){
    Node* root = new Node(50) ;
    root -> left = new Node(40) ;
    root -> left -> left = new Node(35) ;
    root -> left -> right = new Node(45) ;
    root -> right = new Node(70) ;
    root -> right -> left = new Node(65) ;
    root -> right -> right = new Node(75) ;

    cout << minDistance( root , 35 , 75 ) << endl;
    root -> deleteTree( root ) ;
    return 0;
}