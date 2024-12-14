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

int countNodes_R( Node* root ) {
    if( !root ) 
        return 0;
    
    if ( ( root -> left == nullptr ) ^ ( root -> right == nullptr ) ) // Since I want both 1,1 OR 0,0 to return 0, so use X_NOR OR directly null with XOR. As simple root was not working with ^. Also directly giving 0 will not count further.
        return countNodes_R( root -> left ) + countNodes_R( root -> right ) ;

    return countNodes_R( root -> left ) + countNodes_R( root -> right ) + 1 ;
}

int countNodes_I( Node* root ) {
    if( !root )
        return 0;
    
    queue<Node*> q ;
    q.push( root ) ;
    int count = 0 ;
    while( !q.empty() ) {
        Node* cur = q.front() ;
        q.pop() ;

        if( ( cur -> left && cur -> right ) || ( !cur -> left && !cur -> right ) )
            count++ ;
        if( cur -> left )
            q.push( cur -> left ) ;
        if( cur -> right )
            q.push( cur -> right ) ;
    }
    return count ;
}

int main(){
    Node* root = new Node(1) ;
    root -> left = new Node(4) ;
    root -> right = new Node(6) ;
    root -> left -> left = new Node(7) ;
    root -> right -> left = new Node(8) ;
    root -> right -> right = new Node(9) ;

    cout << countNodes_I(root) << endl ;
    cout << countNodes_R(root) << endl ;
    root -> deleteTree( root ) ;
    return 0;
}