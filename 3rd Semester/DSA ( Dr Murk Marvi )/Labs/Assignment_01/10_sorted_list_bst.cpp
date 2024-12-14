#include<iostream>
using namespace std ;

struct List {
    int val ;
    List* next ;
    List( int val ) : val(val) , next(nullptr) {}

    void deleteList( List* &head ) {
        while( head ) {
            List* front = head -> next ;
            delete head ;
            head = front ;
        }
    }
} ;

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

List* middleNode( List* head , List* &leftTail ) {
    if( !head )
        return nullptr ;
        
    List* slow = head ;
    List* fast = head -> next ;
    leftTail = nullptr ;
    while( fast && fast -> next ) {
        leftTail = slow ;
        fast = fast -> next -> next ;
        slow = slow -> next ;
    }
    return slow ;
}

Node* createTree( List* head ) {
    if( !head )
        return nullptr ;
    if( ! head -> next ) // If only there is 1-node left directly create it as --> if( middle != head ) avoids infinite recursion and only create-branches if there are more than 1-childs.
        return new Node( head -> val ) ;
    
    List* leftTail = nullptr ;
    List* middle = middleNode( head , leftTail ) ; // Find the inorder root of that BST.
    List* rightHead = middle -> next ; 
    
    if( leftTail ) // We break the link of previousOF middle-node as to split both segments UNLIKE mergeSort where we won't as it would then merge in end. Here indices spilt would be similar like inStart --> inRoot - 1 AND inRoot + 1 --> inEnd.
        leftTail -> next = nullptr ;

    Node* root = new Node( middle -> val ) ;
    if( middle != head ) // Prevents reusing the same middle node in left recursion
        root -> left = createTree( head ) ;
    root -> right = createTree( rightHead ) ;
    
    // delete middle ; // Delete as this node is exhausted. BUT was giving error in odd-length.
    return root ;
}

void inorderTraversal( Node* node ) {
    if( node ) {
        inorderTraversal( node -> left );
        cout << node -> val << " " ;
        inorderTraversal( node -> right ) ;
    }
}

int main(){
    List* head = new List(1) ;
    head -> next = new List(2) ;
    head -> next -> next = new List(3) ;
    head -> next -> next -> next = new List(4) ;
    head -> next -> next -> next -> next = new List(5) ;
    head -> next -> next -> next -> next -> next = new List(6) ;
    head -> next -> next -> next -> next -> next -> next = new List(7) ;
    head -> next -> next -> next -> next -> next -> next -> next = new List(8) ;

    Node* root = createTree( head );
    inorderTraversal( root ) ;
    head -> deleteList( head ) ;
    root -> deleteTree( root ) ;
    return 0;
}