#include<iostream>
using namespace std ;

void TOH( int n, char sourceRod, char destinationRod, char auxiliaryRod ) {
    if (n == 1) {
        // Base case: only one disk, move it from source to destination
        cout << "Move disk 1 from " << sourceRod << " to " << destinationRod << endl;
        return;
    }
    // Step 1: Move n-1 disks from source to auxiliary rod using destination as auxiliary
    TOH(n - 1, sourceRod, auxiliaryRod, destinationRod);
    // Step 2: Move the nth disk from source to destination
    cout << "Move disk " << n << " from " << sourceRod << " to " << destinationRod <<endl;
    // Step 3: Move n-1 disks from auxiliary to destination rod using source as auxiliary
    TOH(n - 1, auxiliaryRod, destinationRod, sourceRod);

}
int main(){
    TOH( 3 , 'A' , 'C' , 'B' ) ;
    return 0;
}