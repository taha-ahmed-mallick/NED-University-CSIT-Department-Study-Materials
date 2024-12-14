#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <numeric>
using namespace std;

class HashTable {
private:
    int tableSize;
    int totalElements;
    string rollNo;
    vector<list<string>> hashTable;

    int hashFunction( string &word, int rollSum ) {
        int asciiSum = accumulate(word.begin(), word.end(), 0);
        asciiSum += rollSum;
        return asciiSum % tableSize;
    }

    // Calculate roll number sum (e.g., CT-23025 -> 2 + 3 + 0 + 2 + 5 = 12)
    int calculateRollNumberSum( string &rollNo ) {
        int sum = 0;
        for (char& ch : rollNo) {
            if (isdigit(ch))
                sum += ch - '0';
        }
        return sum;
    }

    void rehash() {
        int oldTableSize = tableSize;
        tableSize *= 2;
        vector<list<string>> newHashTable(tableSize);

        for (int i = 0; i < oldTableSize; i++) {
            for (string &word : hashTable[i]) {
                int rollSum = calculateRollNumberSum(rollNo);
                int newIndex = hashFunction(word, rollSum);
                newHashTable[newIndex].push_back(word);
            }
        }

        hashTable = move(newHashTable); // Update the hash table
        cout << "Rehashing completed. New table size: " << tableSize << endl;
    }

    double loadFactor() const {
        return ( totalElements * 1.0 ) / tableSize;
    }

public:
    HashTable(int size, const string &rn = "") 
        : tableSize(size), totalElements(0), rollNo(rn), hashTable(size) {}

    void insert(string &word) {
        if (search(word)) {
            cout << word << " is already memorized, skipping insertion." << endl;
            return;
        }

        int rollSum = calculateRollNumberSum(rollNo);
        int index = hashFunction(word, rollSum);
        hashTable[index].push_back(word);
        totalElements++;

        // Check load factor and rehash if necessary
        if (loadFactor() > 0.75)
            rehash();
    }

    bool search(string &word) {
        int rollSum = calculateRollNumberSum(rollNo);
        int index = hashFunction(word, rollSum);
        for (string &w : hashTable[index]) {
            if (w == word)
                return true;
        }
        return false;
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < tableSize; i++) {
            cout << "Index " << i << ": ";
            if (hashTable[i].empty())
                cout << "Empty";
            else {
                for (string &word : hashTable[i])
                    cout << word << " -> ";
                cout << "nullptr ";
            }
            cout << endl;
        }
    }

    void countNodes() {
        for (int i = 0; i < tableSize; i++)
            cout << "Index " << i << ": " << hashTable[i].size() << " node(s)" << endl;
    }
};

int main() {
    // List of words already memorized
    vector<string> words = {"Kindness", "Politeness", "Understandable", "Empathy", "Knowledge",
                            "Gratitude", "Patience", "Righteous", "Appreciate", "Easy"};

    HashTable hashTable(20, "CT-23025");
    for (string &word : words)
        hashTable.insert(word);

    cout << "Hash Table:" << endl;
    hashTable.display();

    cout << "\nNode count at each index:" << endl;
    hashTable.countNodes();

    string searchWord;
    cout << "\nEnter a word to search: ";
    cin >> searchWord;

    if (hashTable.search(searchWord))
        cout << searchWord << " is already memorized." << endl;
    else
        cout << searchWord << " is not in the list. You can memorize it." << endl;

    // Insert more words to demonstrate rehashing
    // vector<string> newWords = {"Harmony", "Friendship", "Loyalty", "Truth", "Justice", "Faith", "Hope"};
    // for (string &word : newWords)
    //     hashTable.insert(word);
    
    // cout << "\nHash Table after inserting new words:" << endl;
    // hashTable.display();
    return 0;
}
