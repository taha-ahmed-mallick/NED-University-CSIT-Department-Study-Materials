#include <iostream>
#include <stack>
using namespace std;

void transfer(stack<int>& s1, stack<int>& s2) {
    int size = s1.size();
    int temp;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            s2.push( s1.top() ) ;
            s1.pop();
        }

        temp = s1.top(); // Take the lastElement in stack and store in Stack s2.
        s1.pop();

        for (int j = 0; j < size - i - 1; j++) {
            s1.push(s2.top());
            s2.pop();
        }

        s2.push(temp);
    }
}

int main() {
    stack<int> s1, s2;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(4);
    s1.push(5);
    
    transfer(s1, s2);

    while (!s2.empty()) {
        cout << s2.top() << " ";
        s2.pop();
    }
}