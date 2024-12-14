#include<iostream>
#include<queue>
#include<stack>
using namespace std ;

struct Node {
    char val ;
    Node* left ;
    Node* right ;
    Node( char val ) : val(val) , left(nullptr), right(nullptr) {}

    void deleteTree(Node* root) {
        if ( root ) {
            deleteTree( root -> left ) ;
            deleteTree( root -> right ) ;
            delete root;
            root = nullptr ;
        }
    }
} ;

bool isOperand( char ch ) {
    return isalnum( ch ) ;
}

Node* createInfixTree( string& postfix ) {
    stack<Node*> stk ;
    int n = postfix.length() ; // Just like infixToPostfix ; we will keep on appending operands till operator found then push that in-order traversal way i.e. LNR so return the last inserted exp i.e. top().

    for( int i = 0 ; i < n ; i++ ) {
        if( isOperand( postfix[i] ) )
            stk.push( new Node( postfix[i] ) ) ;
        else {
            // It is supposed that postfix is VALID always OR can check if( stk.size() < 2 ) return nullptr here.
            Node* val2 = stk.top() ;
            stk.pop() ;
            Node* val1 = stk.top() ;
            stk.pop() ;

            Node* op = new Node( postfix[i] ) ; // Make the operator as root of that subtree.
            op -> left = val1 ;
            op -> right = val2 ;
            stk.push( op ) ; // MY-MISTAKE push the expression formed again in-stack.
        }
    }

    return ( !stk.empty() ) ? stk.top() : nullptr ;
}

void inorderTraversal( Node* node ) {
    if ( node ) {
        // If it is an operator, add parentheses around its subtree
        if ( !isOperand( node -> val ) )
            cout << "(" ;
        inorderTraversal(node -> left);
        cout << node -> val ;
        inorderTraversal(node -> right) ;

        if ( !isOperand( node -> val ) )
            cout << ")" ;
    }
}

int main(){
    string postfix1 = "ab+c*" ; // Ans = ( a + b ) * c.
    Node* root1 = createInfixTree(postfix1) ;
    cout << "For tree1 : " ;
    inorderTraversal(root1) ;
    cout << endl;
    root1 -> deleteTree(root1) ;

    string postfix2 = "abc*+de/-"; // Ans = ( a + ( b * c ) ) - ( d / e )
    Node* root2 = createInfixTree(postfix2) ;
    cout << "For tree2 : " ;
    inorderTraversal(root2) ;
    cout << endl;
    root2 -> deleteTree(root2) ;
    return 0;
}