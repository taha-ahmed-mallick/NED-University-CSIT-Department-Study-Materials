#include<iostream>
using namespace std ;

struct Node {
    int val ;
    Node* left ;
    Node* right ;
    Node( int val ) : val(val) , left(nullptr), right(nullptr) {}

    void deleteChild( Node* child ) {
        if( child ) {
            deleteChild( child -> left ) ;
            deleteChild( child -> right ) ;
            delete child ;
            child = nullptr ;
        }
    }
} ;

/*
Preorder and Inorder can generate the same sequence only in degenerate trees ( Right-skewed trees )*/

int countLeaves( Node* root ) {
    if( !root )
        return 0 ;
    
    if( !root -> left && !root -> right )
        return 1 ;
    
    return countLeaves( root -> left ) + countLeaves( root -> right ) ;
}

int countRightChildren( Node* root ) {
    if( !root || !root -> right ) 
        return 0 ;
    
    return 1 + countRightChildren( root -> left ) + countRightChildren( root -> right ) ;
}

bool isPerfectlyBalanced(Node* root, int& height) {
    // Base case: If the node is NULL, it's balanced with height 0
    if (root == nullptr) {
        height = 0;
        return true;
    }

    int leftHeight = 0, rightHeight = 0;

    bool leftBalanced = isPerfectlyBalanced(root->left, leftHeight);
    bool rightBalanced = isPerfectlyBalanced(root->right, rightHeight);

    // Current node is balanced if:
    // 1. Left and right subtrees are balanced
    // 2. The height difference between the left and right subtrees is 1 or less
    if (leftBalanced && rightBalanced && abs(leftHeight - rightHeight) <= 1) {
        height = max(leftHeight, rightHeight) + 1;
        return true;
    }

    // If any condition fails, the tree is not balanced
    height = max(leftHeight, rightHeight) + 1;
    return false;
}

bool checkPerfectlyBalanced(Node* root) {
    int height = 0;
    return isPerfectlyBalanced(root, height);
}

Node* deleteLeaves( Node* root ) {
    if( !root )
        return nullptr ;
    
    if( !root -> left && !root -> right ) {
        delete root ;
        return nullptr ;
    }

    root -> left = deleteLeaves( root -> left ) ;
    root -> right = deleteLeaves( root -> right ) ;
    return root ;
}

void preOrder( Node* root ) { 
    if( !root )
        return ;

    cout << root -> val << " " ;
    preOrder( root -> left ) ;
    preOrder( root -> right ) ;
}

void mirror(Node* root) {
    if (root == nullptr)
        return; 

    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);
}

/*
// Function to delete a node using Knuth's deleteByCopying() algorithm
Node* deleteNodeByCopying(Node* root, int key) {
    if (!root) return root;

    // If the key to be deleted is smaller than the root's key, go to the left subtree
    if (key < root->key) {
        root->left = deleteNodeByCopying(root->left, key);
    }
    // If the key to be deleted is larger than the root's key, go to the right subtree
    else if (key > root->key) {
        root->right = deleteNodeByCopying(root->right, key);
    }
    // If key is same as root's key, then this is the node to be deleted
    else {
        // Case 1: Node has only one child or no child
        if (!root->left) {
            Node* temp = root;
            root = root->right;
            delete temp;
        }
        else if (!root->right) {
            Node* temp = root;
            root = root->left;
            delete temp;
        }
        // Case 2: Node has two children
        else {
            // Replace node with its right child (or left child if you prefer)
            Node* temp = root->right;
            root->key = temp->key; // Copy the value of the right child to the current node
            root->right = deleteNodeByCopying(root->right, temp->key); // Recursively delete the right child
        }
    }
    return root;
}

Printing infix tree
// Helper function to check if a string is an operand (e.g., a number or variable)
bool isOperand(const string& str) {
    return !str.empty() && (isdigit(str[0]) || isalpha(str[0]));
}

// Function to print the parenthesized infix expression without redundant parentheses
void printInfix(Node* root, bool isLeft = true, bool isParentOperator = false) {
    if (root == nullptr) {
        return;
    }

    if (isOperand(root->data)) {
        cout << root->data;
        return;
    }

    bool needParentheses = false;
    
    // If the current node is an operator, check its precedence and whether it's redundant
    if (isParentOperator) {
        needParentheses = true;
    }

    if (needParentheses) {
        cout << "(";
    }

    if (root->left != nullptr) {
        printInfix(root->left, true, true);
    }

    // data -> string here.
    cout << " " << root->data << " ";

    if (root->right != nullptr) {
        printInfix(root->right, false, true);
    }

    if (needParentheses) {
        cout << ")";
    }
}

// Function to search for a node with key K in the BST
Node* search(Node* root, int key) {
    while (root != nullptr && root->key != key) {
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}

// Function to divide the BST into two subtrees: T1 with keys < K, T2 with keys >= K
void divideTree(Node* root, int K, Node*& T1, Node*& T2) {
    if (root == nullptr) return;

    // Search for the node containing key K in the BST
    Node* node = search(root, K);
    if (node == nullptr) return;

    // The left subtree of node is T1 (keys < K)
    T1 = node->left;

    // The right subtree of node should be part of T2, and node itself should go to T2
    T2 = node->right;
    
    // Disconnect the left child of node from node
    node->left = nullptr;

    // Now, node with key K is part of the right tree (T2)
    // The tree rooted at node is now the root of T2
    node->right = T2;

    cout << "Tree 1 (keys < K): ";
    inorder(T1);
    cout << "\nTree 2 (keys >= K): ";
    inorder(T2);
    cout << endl;
}

// Perform in-order traversal and store the values in a vector
void inorderTraversal(TreeNode* root, vector<int>& vec) {
    if (!root) return;
    inorderTraversal(root->left, vec);
    vec.push_back(root->val);
    inorderTraversal(root->right, vec);
}

// Merge two sorted vectors
vector<int> mergeVectors(const vector<int>& vec1, const vector<int>& vec2) {
    vector<int> merged;
    int i = 0, j = 0;
    while (i < vec1.size() && j < vec2.size()) {
        if (vec1[i] < vec2[j]) {
            merged.push_back(vec1[i++]);
        } else {
            merged.push_back(vec2[j++]);
        }
    }
    // Append remaining elements
    while (i < vec1.size()) merged.push_back(vec1[i++]);
    while (j < vec2.size()) merged.push_back(vec2[j++]);
    return merged;
}

// Convert a sorted vector to a balanced BST --> O( n + m ) while traditional approach = O((n+m)log(n+m))
TreeNode* sortedArrayToBST(const vector<int>& vec, int start, int end) {
    if (start > end) return nullptr;
    int mid = (start + end) / 2;
    TreeNode* node = new TreeNode(vec[mid]);
    node->left = sortedArrayToBST(vec, start, mid - 1);
    node->right = sortedArrayToBST(vec, mid + 1, end);
    return node;
}

// Merge two BSTs into one BST
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
    vector<int> vec1, vec2;
    
    // Step 1: Perform in-order traversal of both trees to get sorted arrays
    inorderTraversal(root1, vec1);
    inorderTraversal(root2, vec2);

    // Step 2: Merge the two sorted arrays
    vector<int> mergedVec = mergeVectors(vec1, vec2);

    // Step 3: Convert the merged sorted array to a balanced BST
    return sortedArrayToBST(mergedVec, 0, mergedVec.size() - 1);
}*/

int main() {
    // Create a binary tree
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    
    // Test the functions
    cout << "Number of leaves: " << countLeaves(root) << endl;
    cout << "Number of right children: " << countRightChildren(root) << endl;
    cout << "Is perfect-balance tree: " << boolalpha << checkPerfectlyBalanced( root ) << endl;
    
    // Delete leaves
    preOrder( root ) ;
    cout << "\nMirrored = " ;
    mirror( root ) ;
    preOrder( root ) ;
    root = deleteLeaves(root);
    cout << "\nTree after deleting leaves." << endl;
    preOrder( root ) ;
    root -> deleteChild( root );
    return 0;
}
