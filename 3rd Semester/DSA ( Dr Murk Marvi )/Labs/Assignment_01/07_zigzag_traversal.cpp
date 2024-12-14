#include<iostream>
#include<vector>
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

vector<vector<int>> spiralTraversal( Node* root ) {
    vector<vector<int>> res ;
    if( !root )
        return res ;

    bool leftToRight = true ;
    queue<Node*> q ;
    q.push( root ) ;
    while( !q.empty() ) {
        int size = q.size() ;
        vector<int> temp( size ) ; // Pre-initialize vector-size for zig-zag traversal.

        for( int i = 0 ; i < size ; i++ ) {
            Node* cur = q.front() ;
            q.pop() ;

            int index = ( leftToRight ) ? i : size - i - 1 ; // Start filling from end if flag is disabled.
            temp[ index ] = cur -> val ;
            if( cur -> left )
                q.push( cur -> left ) ;
            if( cur -> right )
                q.push( cur -> right ) ;
        }
                
        leftToRight = !leftToRight ;
        res.push_back( temp ) ;
    }
    return res ;
}

int main(){
    Node* root1 = new Node(1);
    root1 -> left = new Node(2);
    root1 -> right = new Node(3);
    root1 -> left -> left = new Node(4);
    root1 -> left -> right = new Node(5);
    root1 -> right -> left = new Node(6);
    root1 -> right -> right = new Node(7);

    vector<vector<int>> result1 = spiralTraversal(root1);
    for (vector<int>& level : result1) {
        for (int &val : level)
            cout << val << " ";
        cout << endl;
    }

    root1 -> deleteTree(root1);

    Node* root2 = new Node(10);
    root2 -> left = new Node(20);
    root2 -> right = new Node(30);
    root2 -> left -> left = new Node(40);
    root2 -> left -> right = new Node(50);
    root2 -> right -> left = new Node(60);
    root2 -> right -> right = new Node(70);

    vector<vector<int>> result2 = spiralTraversal(root2);
    for (vector<int>& level : result2) {
        for (int& val : level)
            cout << val << " ";
        cout << endl;
    }
    root2 -> deleteTree(root2);

    
    return 0;
}