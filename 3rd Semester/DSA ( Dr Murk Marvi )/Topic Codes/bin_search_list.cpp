#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insert(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    Node* findMiddle(Node* start, Node* end) {
        if (start == nullptr) return nullptr;

        Node* slow = start;
        Node* fast = start;

        while (fast != end && fast->next != end) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    // O( n * log(n) ) for linked-list.
    Node* binarySearch(Node* start, Node* end, int target) {
        if (start == end) return nullptr; // Base case

        Node* mid = findMiddle(start, end);

        if (mid->data == target) {
            return mid; // Found the target
        }
        else if (mid->data > target) {
            return binarySearch(start, mid, target); // Search left half
        }
        else {
            return binarySearch(mid->next, end, target); // Search right half
        }
    }

    Node* search(int target) {
        return binarySearch(head, nullptr, target);
    }

    void display() {
        Node* current = head;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    LinkedList list;
    list.insert(8);
    list.insert(5);
    list.insert(4);
    list.insert(3);
    list.insert(1);
    list.display();

    int target = 4;
    Node* result = list.search(target);
    if (result) 
        cout << "Found: " << result->data << endl;
    else
        cout << "Not Found" << endl;
    

    return 0;
}
