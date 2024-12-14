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

bool hasPathSum(Node* root, int targetSum) {
    if( !root )
        return false ;
    
    // OR check here --> targetSum -= root -> val ;
    if( !root -> left && !root -> right )
        return targetSum == root -> val ; // As I am substracting after condition so check whether the left-sum is equal to leaf-node OR not.
    
    return hasPathSum( root -> left , targetSum - root -> val ) || hasPathSum( root -> right , targetSum - root -> val ) ;
}

int main(){
    Node* root1 = new Node(5);
    root1 -> left = new Node(4);
    root1 -> right = new Node(8);
    root1 -> left -> left = new Node(11);
    root1 -> left -> left -> left = new Node(7);
    root1 -> left -> left -> right = new Node(2);
    root1 -> right -> left = new Node(13);
    root1 -> right -> right = new Node(4);
    root1 -> right -> right -> right = new Node(1);

    Node* root2 = new Node(1);
    root2 -> left = new Node(2);
    root2 -> right = new Node(3);

    int targetSum1 = 22;
    cout << "Has path sum " << targetSum1 << ": " << boolalpha << hasPathSum(root1, targetSum1)<< endl;
    int targetSum2 = 5;
    cout << "Has path sum " << targetSum1 << ": " << boolalpha << hasPathSum(root2, targetSum2)<< endl;
    
    root1 -> deleteTree( root1 ) ;
    root2 -> deleteTree( root2 ) ;
    return 0;
}