#include<iostream>
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

bool areIdentical( Node* root1 , Node* root2 ) {
    if( !root1 || !root2 )
        return ( root1 == root2 ) ;
    
    if( root1 -> val != root2 -> val )
        return false ;
    
    return areIdentical( root1 -> left, root2 -> left ) && areIdentical( root1 -> right, root2 -> right ) ;
}

int main(){
    Node* root1 = new Node(1);
    root1 -> left = new Node(2);
    root1 -> right = new Node(3);

    Node* root2 = new Node(1);
    root2 -> left = new Node(2);
    root2 -> right = new Node(3);
    // root2 -> right = new Node(4);

    cout << "Are the tree1 AND tree2 identical =  " << boolalpha << areIdentical( root1 , root2 ) << endl;

    root1 -> deleteTree( root1 ) ;
    root2 -> deleteTree( root2 ) ;
    return 0;
}