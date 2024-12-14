#include <iostream>
#include <vector>
using namespace std;

bool isWord(vector<vector<char>> &board, string &word, int r, int c, int i) {
    if ( r < 0 || r >= board.size() || c < 0 || c >= board[0].size() || board[r][c] != word[i] )
        return false ;

    if ( i == word.length() - 1 ) // As it will only run for last-char if equal so NO-NEED to call 4-times extra.
        return true ;

    char temp = board[r][c];
    board[r][c] = '#'; // Modify as visited.

    bool found = isWord(board, word, r, c + 1, i + 1) || // Right
                 isWord(board, word, r + 1, c, i + 1) || // Down
                 isWord(board, word, r, c - 1, i + 1) || // Left
                 isWord(board, word, r - 1, c, i + 1) ;  // Up

    // Backtrack for original char.
    board[r][c] = temp;

    return found;
}

bool contains(vector<vector<char>> &board, string word) {
    for ( int r = 0; r < board.size(); r++ ) {
        for (int c = 0; c < board[0].size(); c++) {
            if ( board[r][c] == word[0] && isWord( board, word, r, c, 0 ) ) 
                return true;
        }
    }
    return false;
}

int main() {
    vector<vector<char>> board = {  {'A', 'B', 'C', 'E'},
                                    {'S', 'F', 'C', 'S'},
                                    {'A', 'D', 'E', 'E'}  };

    cout << boolalpha << contains(board, "ABCCED") << endl; 
    cout << boolalpha << contains(board, "ABCB") << endl; 
    return 0;
}
