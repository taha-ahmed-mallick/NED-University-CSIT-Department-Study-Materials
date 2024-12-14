#include<iostream>
#include<vector>
#include<unordered_map>
#include<list>
#include<queue>
#include<algorithm>
#include<cstring>
using namespace std ;

void q1_shortestPath( unordered_map<char, vector<pair<char,int>>>& adj , char source ) {
    unordered_map<char,int> dist ;
    for ( auto& node : adj )
        dist[node.first] = INT_MAX;  
    
    dist[source] = 0 ;
    priority_queue<pair<int,char> , vector<pair<int,char>> , greater<pair<int,char>>> pq ;
    pq.push( {0 , source } ) ;
    while( !pq.empty() ) {
        char node = pq.top().second ;
        pq.pop() ;

        for( pair<char,int>& neighbor : adj[node] ) {
            char adjNode = neighbor.first ;
            int wt = neighbor.second ;

            if( dist[node] + wt < dist[adjNode] ) {
                dist[adjNode] = dist[node] + wt ;
                pq.push( { dist[adjNode] , adjNode } ) ;
            }
        }
    }

    for( auto& itr : dist )
        cout << "Dist from A to " << itr.first << " = " << itr.second << endl ; 
}

class DisjointSet {
    vector<int> parent , size ;
public:
    DisjointSet( int n ) : size( n + 1 , 1 ) {
        parent.resize( n + 1 ) ;
        for( int i = 0; i <= n ; i++ )
            parent[i] = i ;
    }

    int findParent( int node ) {
        if( node == parent[node] )
            return node ;
        
        return parent[node] = findParent( parent[node] ) ;
    }

    void unionBySize( int u , int v ) {
        int pU = findParent( u ) ;
        int pV = findParent( v ) ;
        if( pU == pV )
            return ;
        
        if( size[pU] < size[pV] ) {
            parent[pU] = pV ;
            size[pV] += size[pU] ;
        }
        else {
            parent[pV] = pU ;
            size[pU] += size[pV] ;
        }
    }
} ;

void minSpanningTreeKruskal( vector<vector<int>>& adjMatrix ) {
    int V = adjMatrix.size();
    vector<pair<int, pair<int, int>>> edges;

    for (int i = 0; i < V; i++) {
        for ( int j = i + 1; j < V; j++ ) {  // Avoid duplicates, only upper half of the matrix
            if (adjMatrix[i][j] != 0)
                edges.push_back( { adjMatrix[i][j], {i, j} } ) ;
        }
    }

    // Sort edges by weight
    sort(edges.begin(), edges.end());
    DisjointSet dsu(V);
    // vector<pair<int, int>> MST;
    for ( pair<int,pair<int,int>>& edge : edges) {
        int weight = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;

        if ( dsu.findParent(u) != dsu.findParent(v) ) { // To avoid cycle.
            dsu.unionBySize(u, v);
            // MST.push_back({u, v});
            cout << "Edge (" << u << ", " << v << ") with weight " << weight << endl;
        }
    }
}

void minSpanningTreePrims( vector<vector<int>>& adjMatrix ) {
    int V = adjMatrix.size();
    vector<bool> inMST(V, false);
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    dist[0] = 0; // Start from the first node OR can do from any-other also.

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push( {0, 0} ) ;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;
        for (int v = 0; v < V; v++) {
            if (adjMatrix[u][v] != 0 && !inMST[v] && adjMatrix[u][v] < dist[v]) {
                dist[v] = adjMatrix[u][v];
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    // int cost = 0 ;
    for ( int i = 1; i < V; i++ ) {
        cout << "Edge (" << parent[i] << ", " << i << ") with weight " << adjMatrix[i][parent[i]] << endl;
        // cost += adjMatrix[i][parent[i]];
    }
}

void q2_minSpanningTree( vector<vector<int>>& adjMatrix ) {
    cout << "Running Kruskal's Algorithm:\n";
    minSpanningTreeKruskal(adjMatrix);
    
    cout << "\nRunning Prim's Algorithm:\n";
    minSpanningTreePrims(adjMatrix);
}

void heapifyDown( vector<int>& heap , int bound , int i ) {
    while( i < bound ) {
        int largest = i ;
        int LC = 2 * i + 1 , RC = 2 * i + 2 ;
        if( LC < bound && heap[LC] > heap[largest] )
            largest = LC ;
        
        if( RC < bound && heap[RC] > heap[largest] )
            largest = RC ;
        
        if( largest == i )
            break ;
        swap( heap[i], heap[largest] ) ;
        i = largest ;
    }
}
void q3_HeapSort( vector<int>& arr ) {
    int n = arr.size() ;
    for( int i = ( n - 1 ) / 2 ; i >= 0 ; i-- )
        heapifyDown( arr , n , i ) ;
    
    int index = n - 1 ;
    while( index > 0 ) {
        swap( arr[0], arr[index] ) ;
        heapifyDown( arr , index , 0 ) ;
        index-- ;
    }

    cout << "HeapSort: " ;
    for( int& n : arr )
        cout << n << " " ;
    cout << endl ;
}

void q6_HashTable( vector<int>& keys ) {
    int s = 13 ;
    int hashTable[s] ;
    memset( hashTable, -1, sizeof( hashTable ) ) ;

    for( int& key : keys ) {
        int i = 0;
        int pos;
        int h1 = key % s ;
        int h2 = 7 - ( key % 7 ) ;

        do {
            pos = (h1 + i * h2) % s;  // Double hashing formula
            if (hashTable[pos] == -1) {  // If the slot is empty, insert the key
                hashTable[pos] = key;
                // cout << "Inserted " << key << " at position " << pos << endl;
                break ;
            }
            i++;  // For collision try all.
        } while (i < s);
    }

    cout << "\nFinal Hash Table: \n";
    for (int i = 0; i < s; i++ ) {
        if (hashTable[i] == -1)
            cout << "Index " << i << ": Empty\n";
        else
            cout << "Index " << i << ": " << hashTable[i] << endl;
    }
}

class BrowserHistory {
private: 
    struct Node {
        string val ;
        Node* next ;
        Node* prev ;
        Node( string str ) : val( str ) , next(nullptr) , prev(nullptr) {}
    } ;
    Node* cur ;
public:
    BrowserHistory() : cur(nullptr) {}

    void visit( string url ) {
        Node* newNode = new Node( url ) ;
        newNode -> prev = cur ;

        // 1st delete all forward history.
        if( cur ) {
            Node* temp = cur -> next ;
            while( temp ) {
                Node* front = temp -> next ;
                delete temp ;
                temp = front ;
            }
            cur -> next = newNode ;
        }
        cur = newNode ; // Update pointer after each visit.
    }

    string back( int steps ) {
        while( steps && cur -> prev ) {
            cur = cur -> prev ;
            steps-- ;
        }
        return ( steps == 0 ) ? cur -> val : "Invalid" ;
    }

    string forward( int steps ) {
        while( steps && cur -> next ) {
            cur = cur -> next ;
            steps-- ;
        }
        return ( steps == 0 ) ? cur -> val : "Invalid" ;
    }

    ~BrowserHistory() {
        while( cur -> next )
            cur = cur -> next ;
        
        while( cur ) {
            Node* temp = cur -> prev ;
            delete cur ;
            cur = temp ;
        }
    }
} ;

class BST {
    struct Node {
        int key ;  // City name or unique ID (could be any type)
        int val;   // Population of the city
        Node* left;
        Node* right;
        Node(int k, int value) : key(k) , val(value), left(nullptr), right(nullptr) {}
    };
    Node* root ;

    void deleteChild( Node* root ) {
	 	if( root ) {
	 		deleteChild( root -> left ) ;
	 		deleteChild( root -> right ) ;
	 		delete root ;
	 		root = nullptr ;
		 }
	 }

    void solve( Node* root , int& k ) {
        if( !root || k == 0 )
            return ;
        
        solve( root -> right , k ) ;
        if( k > 0 ) {
            cout << root -> key << " " << root -> val << endl ;
            k-- ;
        }
        solve( root -> left , k ) ;
    }

     Node* insertRec(Node* node, int key , int val) {
        if (node == nullptr)
            return new Node(key , val);
        if ( val < node -> val )
            node->left = insertRec(node->left, key , val);
        else if ( val > node->val)
            node->right = insertRec(node->right, key , val);

        return node;
	}

public:
    BST( ) : root(nullptr) {}
    ~BST() {
        deleteChild(root) ;
    }

    void insert(int key , int val) {
	 	root = insertRec(root, key, val);
	}

    void largestCitiesPopulation( int k = 25 ) {
        solve( root , k ) ;
    }
} ;

void q9_TopologicalSort(unordered_map<int, vector<int>>& graph) {
    unordered_map<int, int> indegree;
    queue<int> q;
    vector<int> result;
    
    for (auto& node : graph) {
        for (int& neighbor : node.second) {
            indegree[neighbor]++;
        }
    }
    
    for (auto& node : graph) {
        if ( indegree[node.first] == 0 && indegree.find( node.first ) != indegree.end() )
            q.push(node.first);
    }
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        
        for (int& neighbor : graph[node]) {
            indegree[neighbor]--;
            if (indegree[neighbor] == 0)
                q.push(neighbor);
            
        }
    }
    
    if ( result.size() == graph.size() ) {
        cout << "Topological Sort Order: ";
        for (int& node : result) // There can be other topoSort orders also but with correct prerequisite-adjacent afterwards.
            cout << node << " ";
        
        cout << endl;
    } 
    else
        cout << "Cycle detected! Topological sort not possible." << endl;
}

class Outputs {
    struct Customer {
        string name ;
        bool isSenior ;
    } ;
public:
    void serveCustomers( ) {
        Customer cus[] = { {"Ahmed" , false} , {"Bilal", true} , {"Kiran" , false} , {"Elsa" , true} , {"Evan" , false} } ;
        queue<Customer> customerQueue ;
        for( int i = 0 ; i < 5 ; i++ )
            customerQueue.push( cus[i] ) ;

        while( !customerQueue.empty() ) {
            bool foundSenior = false ;
            int queueSize = customerQueue.size() ;
            for( int i = 0 ; i < queueSize ; ++i ) {
                Customer current = customerQueue.front() ;
                customerQueue.pop() ;

                if( !foundSenior && current.isSenior ) {
                    cout << "Serving : " << current.name << endl ;
                    foundSenior = true ;
                }
                else
                    customerQueue.push(current) ;
                
                if( foundSenior )
                    break ;
            }
            if( !foundSenior ) {
                Customer current = customerQueue.front() ;
                customerQueue.pop() ;
                cout << "Serving : " << current.name << endl ;
            }
        }
    }

    int X( ) {
        const vector<int> arr = {7,10,4,3,20,15} ;
        int k1 = 3 , k2 = 6 ;
        priority_queue<int,vector<int> , greater<int>> minHeap( arr.begin() , arr.end() ) ;

        for( int i = 1 ; i < k1 ; i++ )
            minHeap.pop() ;
        
        k1 = minHeap.top() ;
        for( int i = k1 ; i < k2 ; i++ )
            minHeap.pop() ;
        
        k2 = minHeap.top() ;
        int sum = 0 ;
        for( int i = 0 ; i < arr.size() ; i++ ) {
            if( arr[i] > k1 && arr[i] < k2 )
                sum += arr[i] ;
        }
        cout << "Sum = " << sum << endl ;
        return sum ;
    }

    void Y( ) {
        int A = 0 , B = 5 ;
        vector<vector<int>> graph = { {1,2} , {0,3,4} , {0,4} , {1,5}, {1,2,5} , {3,4} } ;
        int n = graph.size() ;
        vector<bool> visited( n , false ) ;
        vector<int> parent( n , -1 ) ;

        queue<int> q ;
        q.push( A ) ; visited[A] = true ;
        while( !q.empty() ) {
            int current = q.front() ;
            q.pop() ;

            for( n = 0 ; n < graph[current].size() ; n++ ) {
                if( !visited[n] ) {
                    visited[n] = true ;
                    parent[n] = current ;
                    q.push(n) ;

                    if( n == B )
                        break ;
                }
            }
        }

        cout << "Parent Array = " ;
        for( int i = 0 ; i < parent.size() ; i++ )
            cout << parent[i] << " " ;

        cout << "\nVisited Array = " ;
        for( int i = 0 ; i < visited.size() ; i++ )
            cout << boolalpha << visited[i] << " " ;
        cout << endl ;
    }
} ;

int main(){
    // unordered_map<char, vector<pair<char, int>>> graph1 = {
    //     { 'A', { {'E', 1}, {'H', 10} } },
    //     { 'B', { {'C', 2} } },
    //     { 'C' , {} } ,
    //     { 'D', { {'A', 4}, {'H', 1} } },   
    //     { 'E', { {'F', 3} } },              
    //     { 'F', { {'B', 1}, {'I', 1} , {'C' , 3} , {'G' , 7} } },
    //     { 'G' , {} } ,
    //     { 'H' , { {'E' , 5} , {'I' , 9} } } ,
    //     { 'I' , { {'J' , 2} } } ,
    //     {'J' , { {'G' , 1} } }    
    // };
    // q1_shortestPath( graph1 , 'A' ) ;

    // vector<vector<int>> adjMatrix1 = { {0,4,0,0,0,0,0,8,0},
    //                                    {4,0,8,0,0,0,0,11,0},
    //                                    {0,8,0,7,0,4,0,0,2},
    //                                    {0,0,7,0,9,14,0,0,0},
    //                                    {0,0,0,9,0,10,0,0,0},
    //                                    {0,0,4,14,10,0,2,0,0},
    //                                    {0,0,0,0,0,2,0,1,6},
    //                                    {8,11,0,0,0,0,1,0,7},
    //                                    {0,0,2,0,0,0,6,0,0} } ;
    // q2_minSpanningTree( adjMatrix1 ) ;

    // vector<int> array1 = {9,4,3,8,10,2,5} ;
    // q3_HeapSort( array1 ) ;

    // vector<int> keys1 = {18,41,22,44,59,32,31,73} ;
    // q6_HashTable( keys1 ) ;

    // BrowserHistory q7_History ;
    // q7_History.visit("leetcode.com") ;
    // q7_History.visit("google.com") ;
    // q7_History.visit("facebook.com") ;
    // q7_History.visit("youtube.com") ;
    // cout << q7_History.back(1) << endl ;
    // cout << q7_History.back(1) << endl ;
    // cout << q7_History.forward(1) << endl ;
    // q7_History.visit("linkedin.com") ;
    // cout << q7_History.back(3) << endl ;

    // BST tree;
    // tree.insert(1, 500000); 
    // tree.insert(2, 1200000);
    // tree.insert(3, 800000);
    // tree.insert(4, 1500000);
    // tree.insert(5, 2000000);
    // tree.insert(6, 1000000);
    // tree.insert(7, 400000);
    // tree.largestCitiesPopulation();

    // unordered_map<int, vector<int>> graph9 ;
    // graph9[2] = {} ;
    // graph9[3] = {8,10} ;
    // graph9[5] = {11} ;
    // graph9[7] = {8,11} ;
    // graph9[8] = {9} ;
    // graph9[9] = {} ; graph9[10] = {} ;
    // graph9[11] = {2,9,10} ;
    // q9_TopologicalSort( graph9 ) ;

    // Outputs out ;
    // out.serveCustomers();
    // out.X() ; out.Y() ;
    return 0;
}