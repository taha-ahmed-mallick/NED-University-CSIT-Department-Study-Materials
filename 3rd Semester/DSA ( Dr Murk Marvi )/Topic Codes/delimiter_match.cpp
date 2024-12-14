#include<iostream>
#include<stack>
using namespace std;

bool Matching(string exp){
	stack<char> data;
	for(int i=0; i<exp.size(); i++){
		if(exp[i]=='(' || exp[i]=='{' || exp[i]=='[')
			data.push(exp[i]);
		else if (exp[i]==')' || exp[i]=='}' || exp[i]==']'){
			if (data.empty())
				return 0;
			else if((data.top()=='(' && exp[i]==')') || (data.top()=='[' && exp[i]==']') || (data.top()=='{' && exp[i]=='}'))
				data.pop();
			else
				return false;
				}
	}
	return data.empty();
}

bool checkMatch(char c1, char c2){
    if (c1 == '(' && c2 == ')') return true;
    if (c1 == '[' && c2 == ']') return true;
    if (c1 == '{' && c2 == '}') return true;
    return false;
}

bool balanceBrackets( string exp ){
  
    // Initialize top to -1 (empty stack simulation)
    int top = -1;
    for ( int i = 0; i < exp.length(); i++ ) {
		if( exp[i] != '(' && exp[i] != ')' && exp[i] != '{' && exp[i] != '}' && exp[i] != '[' && exp[i] != ']' )
			continue;

        // Push char if stack is empty or no match
        if ( top < 0 || !checkMatch( exp[top] , exp[i] ) ){
            ++top ;
            exp[top] = exp[i];
        }
        else
            // Pop from stack if match found
            --top ;
		
		// cout << "Top = " << top << endl ;
    }
  
    // Return true if stack is empty (balanced)
    return top == -1;
}

int main(){
	string in="(a{+b)*}c";
	if(Matching(in))
		cout<<"Delimiter matching successful!"<<endl;
	else
		cout<<"Delimeter matching unsuccessful!"<<endl;
	if(balanceBrackets(in))
		cout<<"Delimiter matching successful!"<<endl;
	else
		cout<<"Delimeter matching unsuccessful!"<<endl;
	
	string in2 = "{()}[]" ;
	cout << boolalpha << Matching(in2) << endl << boolalpha << balanceBrackets(in2) << endl ;
}