#include<iostream>
#include<queue>
using namespace std ;

struct Node {
    int val , height ;
    Node* left , *right ;
    Node( int val ) : val(val) , height(1) , left(nullptr) , right(nullptr) {}
} ;

class AVL {
    private:
        Node* root ;
        void deleteChild( Node* node ) {
            if( node ) {
                deleteChild( node -> left ) ;
                deleteChild( node -> right ) ;
                delete node ;
                node = nullptr ;
            }
        }

        void traversal_Inorder( Node* node ) {
            if( node ) {
                traversal_Inorder( node -> left ) ;
                cout << node -> val << " " ;
                traversal_Inorder( node -> right ) ;
                // cout << "BF = " << getBalanceFactor( root ) << endl ;
            }
        }

        void traversal_LevelOrder( Node* node ) {
            if( !node )
                return ;
            
            int level = 1 ;
            queue<Node*> q ;
            q.push( node ) ;
            while( !q.empty() ) {
                int size = q.size() ;
                cout << "Level " << level++ << " : " ;
                while( size-- ) {
                    Node* cur = q.front() ;
                    q.pop() ;

                    cout << cur -> val << " " ;
                    // cout << "Left = " << ( cur -> left ? cur -> left -> val : 0 ) << " Right = " << ( cur -> right ? cur -> right -> val : 0 ) << " " ;
                    if( cur -> left )
                        q.push( cur -> left ) ;
                    if( cur -> right )
                        q.push( cur -> right ) ;
                }
                cout << endl ;
            }
        }

        Node* leftRotation( Node* node ) {
            Node* temp = node -> right ;
            node -> right = temp -> left ;
            temp -> left = node ;

            setHeight( node ) ; // Since these 2 links are changed so reassign the height.
            setHeight( temp ) ;
            return temp ;
        }

        Node* rightRotation( Node* node ) {
            Node* temp = node -> left ;
            node -> left = temp -> right ;
            temp -> right = node ;
            setHeight( node ) ;
            setHeight( temp ) ;
            return temp ;
        }

        Node* balanceNode( Node* node ) {
            setHeight( node ) ;
            int BF = getBalanceFactor( node ) ;

            if( BF > 1 ) { // As its left-side heavy so rotate in right-direction.
                if( getBalanceFactor( node -> left ) < 0 )
                    node -> left = leftRotation( node -> left ) ;

                return rightRotation( node ) ;
            }

            if( BF < -1 ) {
                if( getBalanceFactor( node -> right ) > 0 )
                    node -> right = rightRotation( node -> right ) ;
                
                return leftRotation( node ) ;
            }
            return node ;
        }

        Node* insert_R( Node* node , int key ) {
            if( !node )
                return new Node( key );
            
            if( node -> val > key )
                node -> left = insert_R( node -> left, key ) ;
            else if( node -> val < key )
                node -> right = insert_R( node -> right, key ) ;
            else
                return node ;
            
            return balanceNode( node ) ;
        }

        Node* getSuccessor( Node* node ) {
            if( !node )
                return nullptr ;
            
            while( node -> left )
                node = node -> left ;
            
            return node ;
        }

        Node* delete_R( Node* node , int key ) {
            if( !node )
                return nullptr ;
            
            if( node -> val > key )
                node -> left = delete_R( node -> left, key ) ;
            else if( node -> val < key )
                node -> right = delete_R( node -> right, key ) ;
            else {
                if( node -> left == nullptr || node -> right == nullptr ) {
                    Node* temp = ( node -> right ) ? node -> right : node -> left ;
                    delete node ;
                    return balanceNode( temp ) ;
                }
                else {
                    Node* temp = getSuccessor( node -> right ) ;
                    node -> val = temp -> val ;
                    node -> right = delete_R( node -> right , temp -> val ) ;
                }
            }
            return balanceNode( node ) ;
        }

    public:
        AVL() : root(nullptr) {}
        int getHeight( Node* node ) { return (node) ? node -> height : 0 ; }
        int getBalanceFactor( Node* node ) { return (node) ? getHeight( node -> left ) - getHeight( node -> right ) : 0 ; }

        void setHeight( Node* node ) { 
            if( node ) 
                node -> height = max( getHeight( node -> left ) , getHeight( node -> right ) ) + 1 ; 
        }

        void insert( int key ) {
            root = insert_R( root , key ) ;
        }

        void DeleteKey( int key ) {
            root = delete_R( root , key ) ;
        }
        void inorderVisit( ) {
            cout << "Root = " << root -> val << endl ;
            // traversal_Inorder( root ) ;
            traversal_LevelOrder( root ) ;
            cout << endl ;
        }

        ~AVL() {    deleteChild( root ) ;   }
} ;

int main(){
    AVL t ;
    t.insert( 30 ) ;
    t.insert( 20 ) ;
    t.insert( 40 ) ;
    t.insert( 15 ) ;
    t.insert( 25 ) ;
    t.insert( 27 ) ;
    t.insert( 13 ) ;
    // t.DeleteKey( 40 ) ;
    // t.DeleteKey( 27 ) ;
    // t.DeleteKey( 30 ) ;
    t.inorderVisit( ) ;
    return 0;
}