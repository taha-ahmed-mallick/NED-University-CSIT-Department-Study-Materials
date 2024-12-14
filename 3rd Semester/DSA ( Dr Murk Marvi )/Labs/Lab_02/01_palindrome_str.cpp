#include<iostream>
#include<stack>
using namespace std ;

bool isPalindrome( string str ) {
    stack<char> stk ;
    int n = str.length() ;
    int i = 0 ;

    while( i < n / 2 )
        stk.push( str[i++] ) ;
    
    if( n % 2 != 0 )  // If the string has an odd length, skip the middle character
        i += 1 ;

    while( i < n ) {
        if( stk.top() != str[i] )
            return false ;
        
        stk.pop() ; i++ ;
    }
    return true ;
}

int main(){
    string str ;
    cout << "Enter a string for palindromic check : " ;
    getline( cin , str ) ;
    cout << boolalpha << isPalindrome("LAMAL") << endl ;
    cout << boolalpha << isPalindrome(str) << endl ;
    return 0;
}