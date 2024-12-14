#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Graph {
private:
    bool isDirected;               
    bool useAdjList;              
    vector<vector<int>> adjMatrix; 
    vector<list<int>> adjList;   // Or can use unordered_map also instead of vector.
    int numNodes;

public:
    Graph(bool directed, bool adjListMode) : isDirected(directed), useAdjList(adjListMode), numNodes(0) {}

    void addNode() {
        if (useAdjList) {
            adjList.emplace_back(); // Add an empty list for the new node
        } 
        else {
            // Add a new row and column to the adjacency matrix
            for (vector<int>& row : adjMatrix) row.push_back(0);
            adjMatrix.emplace_back(numNodes + 1, 0); // Use emplace() instead of push_back() to correctly initialize all neighbors.
        }
        numNodes++;
    }

    void addEdge(int u, int v) {
        if (u >= numNodes || v >= numNodes) {
            cout << "Error: Node index out of range.\n";
            return;
        }
        if (useAdjList) {
            adjList[u].push_back(v);
            if (!isDirected) adjList[v].push_back(u); // Add u to v's adjacency list for undirected graph
        } else {
            adjMatrix[u][v] = 1;
            if (!isDirected) adjMatrix[v][u] = 1;
        }
    }

    void removeEdge(int u, int v) {
        if (u >= numNodes || v >= numNodes) {
            cout << "Error: Node index out of range.\n";
            return;
        }
        if (useAdjList) {
            adjList[u].remove(v); // remove() doesn't modify the size so use this instead of erase().
            if (!isDirected) adjList[v].remove(u); // Remove u from v's adjacency list for undirected graph
        } else {
            adjMatrix[u][v] = 0;
            if (!isDirected) adjMatrix[v][u] = 0;
        }
    }

    void removeNode(int node) {
        if (node >= numNodes) {
            cout << "Error: Node index out of range.\n";
            return;
        }
        if (useAdjList) {
            adjList[node].clear();
            for (list<int>& neighbors : adjList)
                neighbors.remove(node);
            
        } 
        else {
            // Remove row and column from adjacency matrix
            adjMatrix.erase(adjMatrix.begin() + node);
            for (vector<int>& row : adjMatrix) 
                row.erase(row.begin() + node);
        }
        numNodes--;
    }

    void printGraph() const {
        if (useAdjList) {
            cout << "Graph (Adjacency List):\n";
            for (int i = 0; i < adjList.size(); i++) {
                cout << i << ": ";
                for (int neighbor : adjList[i]) {
                    cout << neighbor << " ";
                }
                cout << "\n";
            }
        } 
        else {
            cout << "Graph (Adjacency Matrix):\n";
            for (const auto& row : adjMatrix) {
                for (int val : row) cout << val << " ";
                cout << "\n";
            }
        }
    }
};

int main() {
    bool directed, useAdjList;
    cout << "Enter 1 for directed graph, 0 for undirected: ";
    cin >> directed;
    cout << "Enter 1 for adjacency list, 0 for adjacency matrix: ";
    cin >> useAdjList;

    Graph graph(directed, useAdjList);

    graph.addNode();
    graph.addNode();
    graph.addNode();

    graph.addEdge(0, 1);
    graph.addEdge(1, 2);

    cout << "Graph after adding edges:\n";
    graph.printGraph();

    graph.removeEdge(1, 2);
    cout << "Graph after removing edge (1, 2):\n";
    graph.printGraph();

    graph.removeNode(1);
    cout << "Graph after removing node 1:\n";
    graph.printGraph();

    return 0;
}
