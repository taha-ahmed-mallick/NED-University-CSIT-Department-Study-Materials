#include<iostream>
#include<stack>
using namespace std ;

bool areEqual( string str1 , string str2 ) {
    stack<char> stk1 ;
    for( int i = 0; i < str1.length(); i++ ) {
        if( str1[i] == '#' ) {
            if( !stk1.empty() ) // To avoid popping-out if nothing is pushed.
                stk1.pop( ) ;
        }
        else    
            stk1.push( str1[i] );
    }

    stack<char> stk2 ;
    for( int i = 0; i < str2.length(); i++ ) {
        if( str2[i] == '#' ) {
            if( !stk2.empty() )
                stk2.pop();
        }
        else
            stk2.push( str2[i] ) ;
    }

    if( stk1.size() != stk2.size() )
        return false ;
    
    while( !stk1.empty() && !stk2.empty() ) {
        if( stk1.top() != stk2.top() ) 
            return false ;
        stk1.pop( ) ; stk2.pop( ) ;
    }
    return true ;
}

bool areEqualUsingSingleStack( string str1 , string str2 ) {
    stack<char> stk;
    
    for ( char ch : str1 ) {
        if( ch == '#' ) {
            if( !stk.empty() ) 
                stk.pop( ) ;
        }
        else    
            stk.push( ch );
    }
    
    for( int i = str2.length() - 1 ; i >= 0 ; i-- ) {
        if( str2[i] != '#' ) {
            if( str2[i] != stk.top() )
                return false ;
            stk.pop( ) ;
        }
        else 
            i-- ; // If # is found so skip previous char
    }
    return true ;
}

int main(){
    cout << boolalpha << areEqual("ab#c" , "ad#c") << "  " << boolalpha << areEqualUsingSingleStack("ab#c" , "ad#c") << endl ;
    cout << boolalpha << areEqual("a#c" , "b") << "  " << boolalpha << areEqualUsingSingleStack("a#c" , "b") << endl ;
    cout << boolalpha << areEqual("#c" , "b#c") << "  " << boolalpha << areEqualUsingSingleStack("#c" , "b#c") << endl ;
    return 0;
}