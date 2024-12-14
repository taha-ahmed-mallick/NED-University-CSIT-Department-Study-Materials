#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include<windows.h>
using namespace std;

class Call {
    public:
        int callID ;
        string customerName ;
        int arrivalTurn ;

        Call(int id, const string& name, int time) : callID(id), customerName(name), arrivalTurn(time) {}

        void display() const {
            cout << "Call ID: " << callID << ", Customer: " << customerName 
            << ", Arrival Time: " << arrivalTurn << endl ;
        }
} ;

class CallCenter {
    private:
        queue<Call> callQueue ;
        int numCSRs ;
        vector<bool> csrAvailable ;

        void simulateCallProcessing(int csrID) {
            Sleep( 1750 ) ;
            // After processing the call, mark CSR as available again
            csrAvailable[csrID] = true;
            cout << "CSR " << csrID + 1 << " has completed the call and is now available." << endl;
        }

    public:
        CallCenter(int numCSRs) : numCSRs(numCSRs), csrAvailable(numCSRs, true) {}

        void addCall(const Call& newCall) {
            callQueue.push(newCall);
            cout << "New call added to queue: " ;
            newCall.display() ;
            Sleep( 925 ) ;
        }

        void processCalls() {
            while ( !callQueue.empty() ) {
                for ( int i = 0; i < numCSRs; i++ ) {
                    // Check if CSR is available and there are calls waiting
                    if ( csrAvailable[i] && !callQueue.empty() ) {
                        Call currentCall = callQueue.front();
                        callQueue.pop() ;

                        csrAvailable[i] = false ; // Marked busy.
                        cout << "CSR " << i + 1 << " is handling the following call: ";
                        currentCall.display() ;
                        simulateCallProcessing(i) ;
                    }
                }

                Sleep( 1000 ) ;
            }
        }
} ;

int main() {
    CallCenter callCenter(3) ;
    callCenter.addCall( Call(1, "Alice", 1) ) ;
    callCenter.addCall( Call(2, "Bob", 2) ) ;
    callCenter.addCall( Call(3, "Charlie", 3) ) ;
    callCenter.addCall( Call(4, "David", 4) ) ;
    callCenter.processCalls();

    return 0;
}
