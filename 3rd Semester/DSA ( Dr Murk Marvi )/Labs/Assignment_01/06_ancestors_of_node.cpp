#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
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

bool solve( Node* root , int key , vector<int>& res ) {
    if( !root )
        return false ;
    
    if( root -> val == key )
        return true ;
    
    res.push_back( root -> val ) ;
    bool isPresent = solve( root -> left , key , res ) || solve( root -> right , key , res ) ;
    if( isPresent )
        return true ;

    res.pop_back() ; // Used bool to help determine whether found OR not so that can do push OR pop.
    return false ;
}

vector<int> nodeAncestors( Node* root , int key ) {
    vector<int> res ;
    solve( root , key , res ) ;
    return res ;
}

vector<int> nodeAncestors_I(Node* root, int key) {
    vector<int> res;
    if ( !root ) 
        return res ;

    // From above logic ; we can see that we are only pushing in res ; if both left AND right give true after traversal so LRN i.e. postorder traversal can be used where we keep checking for key while going left of every right OR left.
    stack<Node*> stk ;
    Node* cur = root ;
    while( !stk.empty() || cur ) {
        while( cur != nullptr ) {
            if( cur -> val == key ) {
                while( !stk.empty() ) {
                    res.push_back( stk.top() -> val ) ;
                    stk.pop() ;
                }

                reverse( res.begin(), res.end() ) ;
                return res ;
            }

            stk.push( cur ) ;
            cur = cur -> left ;
        }

        Node* temp = stk.top() -> right ;
        if( temp == nullptr ) {
            temp = stk.top() ;
            stk.pop() ;
            
            while( !stk.empty() && temp == stk.top() -> right ) {
                temp = stk.top() ;
                stk.pop() ;
            }
        }
        else
            cur = temp ; // Assign the last valid right-node.
    }

    return res ;
}

int main(){
    Node* root1 = new Node(1);
    root1 -> left = new Node(2);
    root1 -> right = new Node(3);
    root1 -> left -> left = new Node(4);
    root1 -> left -> right = new Node(5);
    root1 -> right -> right = new Node(6);

    int key1 = 6;
    vector<int> ancestors1 = nodeAncestors(root1, key1);
    cout << "Ancestors of " << key1 << ": ";
    for (int& val : ancestors1)
        cout << val << " " ;
    cout << endl;

    root1 -> deleteTree( root1 ) ;

    Node *root2 = new Node(1);
    root2 -> left = new Node(2);
    root2 -> right = new Node(3);
    root2 -> left -> left  = new Node(4);
    root2 -> left -> right = new Node(5);
    root2 -> left -> left -> left  = new Node(7);

    
    int key2 = 7;
    vector<int> ancestors2 = nodeAncestors_I(root2, key2);
    cout << "Ancestors of " << key2 << ": ";
    for (int& val : ancestors2)
        cout << val << " " ;
    cout << endl;

    root2 -> deleteTree( root2 ) ;
    
    return 0;
}