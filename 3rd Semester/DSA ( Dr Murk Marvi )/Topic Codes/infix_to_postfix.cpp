#include<iostream>
#include<stack>
using namespace std ;

bool isOperand( char ch ) {
    return !( ch == '(' || ch == ')' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') ;
}

int precedOutsideStack( char ch ) {
    if( ch == '+' || ch == '-' )
        return 1 ;
    else if ( ch == '*' || ch == '/' )
        return 3 ;
    else if( ch == '^' ) // Higher precedence as its right-to-left associative.
        return 6 ;
    else if( ch == '(')
        return 7 ;
    return 0 ;
}

int precedInsideStack( char ch ) {
    if( ch == '+' || ch == '-' )
        return 2 ;
    else if ( ch == '*' || ch == '/' )
        return 4 ;
    else if( ch == '^' )
        return 5 ;
    
    return 0 ; // () have lowest precedence.
}

// MY-WAY
// string infixToPostfix( string & str ) {
//     string postfix ;
//     stack<char> stk ;
    
//     int i = 0 ;
//     while( str[i] != '\0' ) {
//         if( isOperand( str[i] ) )
//             postfix.push_back( str[i++] ) ;
//         else {
//             if( stk.empty() || ( precedOutsideStack( str[i] ) > precedInsideStack( stk.top() ) ) ) {
//                 stk.push( str[i++] ) ;
//             }
//             else if( precedOutsideStack( str[i] ) == precedInsideStack( stk.top() ) ) {
//                 stk.pop() ;
//                 i++ ; // Directly remove brackets. Also brackets have lowest precedence in stack.
//             }
//             else {
//                 postfix.push_back( stk.top() ) ;
//                 stk.pop() ;
//             }
//         }
//     }

//     // Pop-all remaining less-precedence things in stack.
//     while( !stk.empty() ) {
//         postfix.push_back( stk.top() ) ;
//         stk.pop() ;
//     }

//     return postfix ;
// }

string infixToPostfix(string& str) {
    string postfix;
    stack<char> stk;
    
    int i = 0;
    while (str[i] != '\0') {
        if (isOperand(str[i])) {
            postfix.push_back(str[i++]);
        } else {
            if (str[i] == ')') {
                // Pop until '(' is found
                while (!stk.empty() && stk.top() != '(') {
                    postfix.push_back(stk.top());
                    stk.pop();
                }
                stk.pop(); // Pop '('
                i++;
            } else {
                // For other operators and '('
                while (!stk.empty() && precedOutsideStack(str[i]) <= precedInsideStack(stk.top())) {
                    postfix.push_back(stk.top());
                    stk.pop();
                }
                stk.push(str[i++]);
            }
        }
    }

    // Pop any remaining operators in the stack
    while (!stk.empty()) {
        postfix.push_back(stk.top());
        stk.pop();
    }

    return postfix;
}

int main(){
    string input = "((A+B)/D)^((E-F)*G)" ;
    cout << infixToPostfix( input ) << endl ;
    return 0;
}