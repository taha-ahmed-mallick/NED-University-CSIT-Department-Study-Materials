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

int maxLevelSum( Node* root ) {
    if( !root )
        return 0 ;
    
    queue<Node*> q ;
    q.push( root );
    int maxSum = 0 ;
    while( !q.empty() ) {
        int size = q.size();
        int levelSum = 0 ;

        while( size-- ) {
            Node* cur = q.front() ;
            q.pop() ;

            levelSum += cur -> val ;
            if( cur -> left )
                q.push( cur -> left ) ;
            if( cur -> right )
                q.push( cur -> right ) ;
        }

        maxSum = max( maxSum, levelSum ) ;
    }
    return maxSum ;
}

int main(){
    Node* root1 = new Node(1);
    root1 -> left = new Node(5);
    root1 -> right = new Node(3);
    root1 -> left -> left = new Node(4);
    root1 -> left -> right = new Node(5);

    Node* root2 = new Node(1);
    root2 -> left = new Node(12);
    root2 -> right = new Node(3);
    root2 -> right -> left = new Node(4);
    root2 -> right -> right = new Node(5);

    cout << "Max level sum: " << maxLevelSum(root1) << endl;
    cout << "Max level sum: " << maxLevelSum(root2) << endl;

    root1 -> deleteTree( root1 );
    root2 -> deleteTree( root2 );
    return 0;
}