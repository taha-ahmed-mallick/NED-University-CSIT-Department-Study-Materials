#include <iostream>
#include <vector>
#include<thread>
#include<chrono>

using namespace std;

class Sort {
    private:
        int comparisons ;
        int swaps ;
        chrono::duration<double , milli> timeTaken ;

        void resetCounters() {
            comparisons = 0 ;
            swaps = 0 ;
            timeTaken = chrono::duration<double, milli>(0) ; // Reset like this not simple = 0.
        }

        void insertionSort(vector<int>& arr) {
            resetCounters();
            auto start = chrono::high_resolution_clock::now() ;
            int n = arr.size() ;
            for (int i = 1; i < n ; i++) {
                int key = arr[i];
                int j = i - 1;
                while (j >= 0 && arr[j] > key) {
                    comparisons++;
                    arr[j + 1] = arr[j];
                    j--;
                    swaps++;
                }
                comparisons++;
                arr[j + 1] = key;
                swaps++;
            }
            auto end = chrono::high_resolution_clock::now() ;
            timeTaken = end - start ;
            printResults(arr, "Insertion", comparisons, swaps , timeTaken );
        }

        void selectionSort(vector<int>& arr) {
            resetCounters();
            auto start = chrono::high_resolution_clock::now() ;
            int n = arr.size() ;
            for (int i = 0; i < n - 1; i++) {
                int minIndex = i;
                for ( int j = i + 1; j < n ; j++ ) {
                    comparisons++;
                    if ( arr[j] < arr[minIndex] )
                        minIndex = j ;
                }
                if (minIndex != i) {
                    swap(arr[i], arr[minIndex]);
                    swaps++;
                }
            }
            auto end = chrono::high_resolution_clock::now() ;
            timeTaken = end - start ;
            printResults(arr, "Selection", comparisons, swaps , timeTaken );
        }

        void bubbleSort(vector<int>& arr) {
            resetCounters();
            auto start = chrono::steady_clock::now() ;
            int n = arr.size() ;
            for (int i = 0; i < n - 1; i++) {
                bool flag = false ;
                for (int j = 0; j < n - i - 1; j++) {
                    comparisons++;
                    if ( arr[j] > arr[j + 1] ) {
                        swap(arr[j], arr[j + 1]);
                        swaps++;
                        flag = true ;
                    }
                }
                if( !flag )
                    break ;
            }
            auto end = chrono::steady_clock::now() ;
            timeTaken = end - start ;
            printResults(arr, "Bubble", comparisons, swaps , timeTaken );
        }
    public:
        Sort() : comparisons(0), swaps(0) , timeTaken(0) {}
        void sort(vector<int>& arr, const string& method) {
            if (method == "insertion")
                insertionSort(arr);
            else if (method == "selection")
                selectionSort(arr);
            else if (method == "bubble")
                bubbleSort(arr);
            else
                cout << "Invalid sorting method!" << endl;
        }

        void analyze(vector<int>& arr, const string& method) {
            if (method == "insertion")
                insertionSort(arr);
            else if (method == "selection")
                selectionSort(arr);
            else if (method == "bubble")
                bubbleSort(arr);
        }

        void printResults(const vector<int>& arr, const string& method, int comparisons, int swaps , chrono::duration<double , milli>& timeTaken ) {
            cout << method << " sort:\n";
            cout << "Sorted Array: ";
            for (const int& num : arr) {
                cout << num << " ";
            }
            cout << "\nComparisons: " << comparisons << ", Swaps: " << swaps << " , Time-Elapsed = " << timeTaken.count() << " milliseconds.\n" ;
        }
};

int main() {
    srand(static_cast<unsigned int>( time(0) ) ) ;
    Sort sorter;

    while (true) {
        cout << "\nSorting Menu:\n";
        cout << "1. Insertion Sort\n";
        cout << "2. Selection Sort\n";
        cout << "3. Bubble Sort\n";
        cout << "4. Exit\n";
        cout << "Choose a sorting method (1-4): ";
        int choice;
        cin >> choice;

        if (choice == 4)
            break ;

        int size ;
        cout << "Enter size of random vector: " ;
        cin >> size ;

        vector<int> arr(size) ; 
        for ( int i = 0; i < size ; i++ ) {
            if( rand() % 2 == 0 )
                arr[i] = rand() % 100 + 1 ;
            else
                arr[i] = ( ( rand() % 100 ) * -1 ) - 1 ;
        }
        
        string method;
        switch (choice) {
            case 1:
                method = "insertion";
                break;
            case 2:
                method = "selection";
                break;
            case 3:
                method = "bubble";
                break;
            default:
                cout << "Invalid choice! Please select again.\n";
                continue;
        }

        sorter.analyze(arr, method);
    }

    return 0;
}
