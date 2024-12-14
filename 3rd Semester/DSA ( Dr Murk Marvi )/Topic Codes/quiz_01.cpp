#include<iostream>
#include<stack>
#include<cctype>
#include<vector>
#include<cmath>
using namespace std ;

// Must use stack
void transferElements( stack<int>& s1 , stack<int>& s2 ) { // Transfer means move in same order not copy.
    stack<int> temp ;
    while( !s1.empty() ) {
        temp.push( s1.top() ) ;
        s1.pop( ) ;
    }

    while( !temp.empty() ) {
        s2.push( temp.top() ) ;
        temp.pop( ) ;
    }
}

void displayStack( stack<int> stk ) { // As not pass by reference so stack will not be empty originally.
    while( !stk.empty() ) {
        cout << stk.top() << " " ;
        stk.pop( ) ;
    }
    cout << endl ;
}

bool isPalindrome( string& str ) {
    string wordStr ;
    for( int i = 0 ; i < str.length() ; i++ ) {
        char ch = tolower( str[i] ) ;
        if( isalnum( ch ) )
            wordStr.push_back( ch ) ;
    }

    int n = wordStr.length() ;
    stack<char> stk ;
    for( int i = 0 ; i < n / 2 ; i++ ) {
        stk.push( wordStr[i] ) ;
    }

    int i = ( n % 2 == 0 ) ? n / 2 : n / 2 + 1 ; // Leave the middle char for odd len.
    for( ; i < n ; i++ ) {
        if( stk.top() != wordStr[i] )
            return false ;
        stk.pop() ;
    }
    return true ;
}

bool isPalindromeWord(const string &word, int left, int right) {
    if (left >= right)
        return true;
    
    // Check characters at left and right indices (case insensitive) with all cases.
    if( !isalnum( word[left] ) && !isalnum( word[right] ) )
        return isPalindromeWord(word, left + 1 , right - 1 ) ;
    else if( !isalnum( word[left] ) )
        return isPalindromeWord(word, left + 1 , right ) ;   
    else if ( !isalnum( word[right] ) )
        return isPalindromeWord(word, left , right - 1 ) ;

    if ( tolower(word[left]) != tolower(word[right]) )
        return false ;
    
    return isPalindromeWord(word, left + 1, right - 1);
}

// Return cubes from( 1 to n ) but by recursion.
vector<int> cubes( int n ) {
    if( n <= 1 )
        return { n } ;
    
    vector<int> res = cubes( n - 1 ) ;
    res.push_back( pow( n , 3 ) ) ;
    return res ;
}

// Print series 1 + 1 / 2 - 1 / 3 + 1 / 4 ... by recursion
double series( int n ) {
    static int count = 1 ;
    if( n == 0 ) {
        count++ ;
        return 1 ;
    }
    
    if( n % 2 == 0 )
        return series( n - 1 ) + 1.0 / ( ++count ) ;
    
    return series( n - 1 ) - 1.0 / ( ++count ) ;
}

int main(){
    stack<int> s1 ;
    for( int i = 5 ; i >= 1 ; i-- )
        s1.push( i ) ;
    
    displayStack( s1 ) ;
    stack<int> s2 ;
    transferElements( s1 , s2 ) ;
    displayStack( s2 ) ;

    string str = "\"Madam I'm Adam\"" ;
    string str2 = "A man, a plan, a canal: Panama" ;
    string str3 = "Hello, world!" ;
    cout << boolalpha << isPalindrome( str ) << endl ;
    cout << boolalpha << isPalindrome( str2 ) << endl ;
    cout << boolalpha << isPalindrome( str3 ) << endl ;

    vector<int> nums = cubes( 5 ) ;
    for( int n : nums )
        cout << n << " " ;
    cout << endl ; 

    cout << "Series = " << series( 3 ) << endl ;
    return 0;
}