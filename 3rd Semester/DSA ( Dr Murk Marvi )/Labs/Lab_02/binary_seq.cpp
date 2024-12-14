#include<iostream>
#include<vector>
using namespace std ;

void binarySequence( vector<string>& res , string temp , int n ) {
    if( n == 0 ) {
        res.push_back( temp ) ;
        return ;
    }

    // binarySequence( res , temp + '0' , n - 1 ) ;
    // binarySequence( res , temp + '1' , n - 1 ) ; // OR
    temp.push_back('0') ;
    binarySequence( res , temp , n - 1 ) ;
    temp.pop_back() ;
    temp.push_back('1') ;
    binarySequence( res , temp , n - 1 ) ;
    temp.pop_back() ;
}

int main(){
    vector<string> res ;
    string temp = "" ;
    binarySequence( res , temp , 3 ) ;
    for( string& str : res )
        cout << str << " " ;
    cout << endl ;

    return 0;
}