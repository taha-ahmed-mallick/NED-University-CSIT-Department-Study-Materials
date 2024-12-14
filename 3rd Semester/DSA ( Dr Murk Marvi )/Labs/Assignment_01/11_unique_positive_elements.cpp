#include<iostream>
#include<unordered_set>
#include<vector>
using namespace std ;

struct Node {
    int val ;
    Node* left ;
    Node* right ;
    Node( int val ) : val(val) , left(nullptr) , right(nullptr) {}

    void deleteTree(Node* root) {
        if ( root ) {
            deleteTree( root -> left ) ;
            deleteTree( root -> right ) ;
            delete root;
            root = nullptr ;
        }
    }
} ;

Node* insert_BST( Node* root , int key ) {
    if( !root )
        return new Node( key ) ;
    
    if( root -> val > key )
        root -> left = insert_BST( root -> left, key ) ;
    else if( root -> val < key )
        root -> right = insert_BST( root -> right, key ) ;
    
    return root ;
}

// METHOD-1 
void inorderAdd( Node* root , unordered_set<int>& set ) {
    if( root ) {
        inorderAdd( root -> left , set ) ;
        set.insert( root -> val ) ;
        inorderAdd( root -> right , set ) ;
    }
}

bool checkAllNodes( Node* root , unordered_set<int>& set ) {
    if( !root )
        return true ;
    
    if( set.find( root -> val ) == set.end() )
        return false ;
    
    set.erase( root -> val ) ; // Remove root's val if want all elements to-be unique.

    return checkAllNodes( root -> left , set ) && checkAllNodes( root -> right , set ) ;
}

bool uniqueElement_BST( Node* root1 , Node* root2 ) {
    unordered_set<int> hash ;
    inorderAdd( root1 , hash ) ;

    return checkAllNodes( root2 , hash ) && hash.empty() ; // Don't only check equal ; but also hash-size() as root1 can have more elements.
}

// METHOD-2 check all values by storing in vector.
void appendNodes( Node* root, vector<int> &arr ) {
    if ( !root ) 
        return ;
    
    appendNodes( root -> left, arr ) ;
    arr.push_back( root -> val ) ;
    appendNodes( root -> right, arr ) ;
}

bool checkBSTs(Node* root1, Node* root2) {
    
    vector<int> arr1, arr2;
    appendNodes( root1, arr1 );
    appendNodes( root2, arr2 );
    if ( arr1.size() != arr2.size() )
        return false;

    // Check any-where in other array as inorder of both will be equal.  
    for (int i = 0 ; i < arr1.size(); i++ ) {
        if ( arr1[i] != arr2[i] ) 
            return false;
    }
    return true;
}

int main(){
    Node* root1 = nullptr ;
    root1 = insert_BST( root1 , 10 ) ;
    root1 = insert_BST( root1 , 5 ) ;
    root1 = insert_BST( root1 , 20 ) ;
    root1 = insert_BST( root1 , 15 ) ;
    root1 = insert_BST( root1 , 30 ) ;
    // root1 = insert_BST( root1 , 25 ) ; // More-elements

    Node* root2 = nullptr ;
    root2 = insert_BST( root2 , 10 ) ;
    root2 = insert_BST( root2 , 20 ) ;
    root2 = insert_BST( root2 , 15 ) ;
    root2 = insert_BST( root2 , 30 ) ;
    root2 = insert_BST( root2 , 5 ) ;

    Node* root3 = nullptr ;
    root3 = insert_BST( root3 , 10 ) ;
    root3 = insert_BST( root3 , 15 ) ;
    root3 = insert_BST( root3 , 30 ) ;
    root3 = insert_BST( root3 , 20 ) ;
    root3 = insert_BST( root3 , 25 ) ;

    cout << boolalpha << "Tree1 and Tree2 have unique elements = " << uniqueElement_BST( root1 , root2 ) << endl ;
    cout << boolalpha << "Tree1 and Tree2 have unique elements = " << checkBSTs( root1 , root2 ) << endl ;
    cout << boolalpha << "Tree1 and Tree3 have unique elements = " << uniqueElement_BST( root1 , root3 ) << endl ;
    cout << boolalpha << "Tree1 and Tree3 have unique elements = " << checkBSTs( root1 , root3 ) << endl ;

    root1 -> deleteTree( root1 ) ;
    root2 -> deleteTree( root2 ) ;
    root3 -> deleteTree( root3 ) ;
    return 0;
}