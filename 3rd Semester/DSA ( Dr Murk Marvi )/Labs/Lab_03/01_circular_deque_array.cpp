#include<iostream>
#include<optional>
using namespace std;

template<class T>
class MyCircularDeque {
    private:
        T *arr ;
        int front ;
        int rear ;
        int currentSize ;
        int size ;
    public:
        MyCircularDeque( int k ) : arr(nullptr) , front( 0 ) , rear( 0 ) , currentSize( 0 ) {
            size = k > 0 ? k : 2 ;
            arr = new T [size] ;
        }

        ~MyCircularDeque() { delete[] arr ; }
        bool isEmpty() const { return currentSize == 0 ; }
        bool isFull() const { return currentSize == size ; }

        bool insertFront( T val ) {
            if ( isFull() ) {
                cout << "Queue has become full!\t" ; // Can't throw as then it will not return.
                return false ;
            }

            front = (front - 1 + size) % size ; // To avoid -ve modulo use currentSize - 1 as removing from front. Also to avoid being overwriting 0th rear ; 1st modify front then insert unlike rear.
            arr[front] = val ;
            currentSize++ ;
            return true ;
        }

        bool insertLast( T val ) {
            if ( isFull() ) {
                cout << "Queue has become full!\t" ;
                return false ;
            }

            arr[rear] = val ;
            rear = (rear + 1) % size ;
            currentSize++ ;
            return true ;
        }

        bool deleteFront() {
            if ( isEmpty() ) {
                cout << "Queue is empty!\t" ;
                return false ;
            }

            front = (front + 1) % size ;
            currentSize-- ;
            return true ;
        }

        bool deleteLast() {
            if ( isEmpty() ) {
                cout << "Queue is empty!\t" ;
                return false ;
            }

            rear = (rear - 1 + size) % size ;
            currentSize-- ;
            return true ;
        }

        optional<T> getFront() const {
            if ( isEmpty() ) {
                // cout << "Queue is already empty!\t" ;
                return nullopt ;
            }

            return arr[front] ;
        }

        optional<T> getRear() const {
            if ( isEmpty() )  {
                // cout << "Queue is already empty!\t" ;
                return nullopt ;
            }
            return arr[(rear - 1 + size) % size] ;
        }

        void display() const {
            cout << "Queue Elements : " ;
            for ( int i = front , count = 0 ; count < currentSize ; count++ , i = ( i + 1 ) % size )
                cout << arr[i] << " " ;
            cout << endl;
        }
} ;

int main() {
    MyCircularDeque<int> myCircularDeque(3) ;
    cout << boolalpha << myCircularDeque.insertLast(1) << endl;
    // cout << myCircularDeque.getRear().value() << endl ;
    cout << boolalpha << myCircularDeque.insertLast(2) << endl;
    cout << boolalpha << myCircularDeque.insertFront(3) << endl;
    cout << boolalpha << myCircularDeque.insertFront(4) << endl;
    cout << "Rear = " << myCircularDeque.getRear().value_or(-1) << endl;
    cout << boolalpha << myCircularDeque.isFull() << endl;
    cout << myCircularDeque.deleteLast() << endl;
    cout << myCircularDeque.insertFront(4) << endl;
    cout << "Front = " << myCircularDeque.getFront().value_or(-1) << endl;
    myCircularDeque.display( ) ;

    cout << endl ;
    MyCircularDeque<string> m(2) ;
    cout << m.insertFront("Obaid") << endl ;
    cout << m.insertLast("Noobie") << endl ;
    cout << m.insertFront("ALli") << endl ;
    cout << m.getFront().value_or("Empty") << endl ;
    cout << m.deleteFront() << endl;
    cout << m.deleteFront() << endl;
    cout << m.getFront().value_or("Empty") << endl ;
    m.display( ) ;
    
    return 0;
}
