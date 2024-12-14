#include <iostream>
#include <vector>
using namespace std;

bool isSafe(const vector<vector<int>>& maze, int x, int y , const vector<vector<int>> &sol ) {
    int n = maze.size();
    int m = maze[0].size();
    return ( x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 1 && sol[x][y] == 0 );
}

void findAllPathsUtil( const vector<vector<int>>& maze, int x, int y, vector<vector<int>>& solution, vector<vector<vector<int>>>& allSolutions ) {
    int n = maze.size();
    int m = maze[0].size();

    if (x == n - 1 && y == m - 1) {
        solution[x][y] = 1;
        allSolutions.push_back(solution) ;
        solution[x][y] = 0 ; // Unmarking start from last solution.
        return;
    }

    if ( isSafe(maze, x, y , solution ) ) {
        solution[x][y] = 1;
        findAllPathsUtil(maze, x, y + 1, solution, allSolutions);
        findAllPathsUtil(maze, x + 1, y, solution, allSolutions);
        findAllPathsUtil(maze, x, y - 1, solution, allSolutions);
        findAllPathsUtil(maze, x - 1, y, solution, allSolutions);
        solution[x][y] = 0;
    }
}


void printSolution(const vector<vector<int>>& solution) {
    for (const auto& row : solution) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to find all solutions for the maze using backtracking
void findAllPaths(const vector<vector<int>>& maze) {
    int n = maze.size();
    int m = maze[0].size();

    // Initialize the solution matrix with zeros
    vector<vector<int>> solution(n, vector<int>(m, 0));

    // List to store all possible solutions
    vector<vector<vector<int>>> allSolutions;

    // Start from (0, 0) and try to find all paths in the maze
    findAllPathsUtil(maze, 0, 0, solution, allSolutions);

    if ( !allSolutions.empty() ) {
        cout << "Found " << allSolutions.size() << " solutions:" << endl;
        for ( const auto& sol : allSolutions ) {
            printSolution(sol);
        }
    } 
    else
        cout << "No solution exists" << endl ;
}

int main() {
    // Maze configuration (1 represents open path, 0 represents blocked path)
    vector<vector<int>> maze = { {1, 0, 0, 0},
                                 {1, 1, 0, 1},
                                 {0, 1, 1, 0},
                                 {1, 1, 1, 1} };
    findAllPaths(maze) ;

    return 0;
}
