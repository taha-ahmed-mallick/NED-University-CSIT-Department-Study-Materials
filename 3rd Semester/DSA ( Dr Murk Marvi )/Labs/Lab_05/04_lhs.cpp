#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std ;

int findLHS(vector<int>& nums) {
    sort( nums.begin(), nums.end() ) ;

    int pre = 0, curr = 1, maxi = 0 ;
    bool doesExist = false;
    for(int i = 1; i < nums.size(); i++){
        if( nums[i] == nums[i - 1] )
            curr++ ;
        else {
            if( pre != 0 )
                maxi = max( maxi, curr + pre ) ;
            
            if( nums[i] == nums[i - 1] + 1 ){
                pre = curr ;
                doesExist = true ;
            }
            else 
                pre = 0 ;

            curr = 1 ;
        }
    }
    
    if( !doesExist && !pre ) // Used isExist to check whether found OR not only then return 0. Can avoid checking !pre.
        return 0 ;
        
    maxi = max(maxi, pre + curr ) ;
    return maxi;
}

/*
    int findLHS(vector<int>& nums) {
        unordered_map<int,int> hash ;
        for( int& num : nums )
            hash[ num ]++ ;
        
        int maxCount = 0;

        for ( auto& pair : hash ) {
            int num = pair.first;
            if ( hash.find(num - 1) != hash.end() ) // Don't check if != 0 as our sequence can be it will then count 1,1,1,1 also by itself.
                maxCount = max( maxCount, hash[num] + hash[num - 1] ) ;
        }

        return maxCount;
    }
*/
int main(){
    vector<int> a = {1,3,2,2,5,2,3,7} ; // 2,2,2,3,3
    cout << findLHS(a) << endl;
    vector<int> b = {1,2,3,4} ;
    cout << findLHS(b) << endl ;
    vector<int> c = {1,1,1,1} ;
    cout << findLHS(c) << endl ;
    return 0;
}