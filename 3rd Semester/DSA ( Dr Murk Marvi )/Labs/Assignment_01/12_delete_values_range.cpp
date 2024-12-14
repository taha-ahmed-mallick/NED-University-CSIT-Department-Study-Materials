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

Node* findSuccessor( Node* node ) {
    if( !node )
        return nullptr ;
    
    while( node -> left != nullptr )
        node = node -> left ;
    return node ;
}

Node* deleteNode( Node* node ) {
    if( node -> left == nullptr || node -> right == nullptr ) {
        Node* temp = ( node -> right ) ? node -> right : node -> left ;
        delete node ;
        node = nullptr ;
        return temp ;
    }
    
    Node* temp = findSuccessor( node -> right ) ;
    node -> val = temp -> val ;
    node -> right = deleteNode( temp ) ;
    return node ;
}

Node* removeInRange( Node* root , int start , int end ) {
    if( !root )
        return nullptr ;
    
    root -> left = removeInRange( root -> left, start, end ) ;
    root -> right = removeInRange( root -> right, start, end ) ;

    if( root -> val >= start && root -> val <= end )
        return deleteNode( root ) ; // Used post-order as then deletion will be easier to delete all range-values from the leaf-nodes.
    
    return root ;
}

// Easier way to delete outside range-values
Node* removeOutsideRange( Node* root , int low , int high ) {
    if ( !root ) 
        return nullptr;
    
    Node* left = removeOutsideRange(root -> left, low , high ) ;
    Node* right = removeOutsideRange( root -> right, low , high );
    
    // If curr node lies in the range, update its left and right nodes to original nodes and return curr node.
    if ( root -> val >= low && root -> val <= high ) {
        root -> left = left ;
        root -> right = right ;
        
        return root;
    }
    
    // If current node is less than range, then return the updated right subtree ( other-subtree which will have greater values than root )
    else if ( root -> val < low )
        return right ;

    return left ; // As it (left-subtree) will have smaller values than root.
}

void inorderTraversal( Node* node ) {
    if( node ) {
        inorderTraversal( node -> left );
        cout << node -> val << " " ;
        inorderTraversal( node -> right ) ;
    }
}

int main(){
    Node* root = new Node(50);
    root -> left = new Node(30);
    root -> right = new Node(70);
    root -> left -> right = new Node(40);
    root -> right -> right = new Node(80);
    root -> right -> left = new Node(60);
    root -> left -> left = new Node(20);
 
    cout << "Inorder Before deletion: ";
    inorderTraversal(root);
    // root = removeInRange(root, 50, 70);
    root = removeOutsideRange(root, 50, 70);
 
    cout << "\nInorder After deletion: ";
    inorderTraversal(root);
    cout << endl;
    root -> deleteTree( root ) ;
    return 0;
}