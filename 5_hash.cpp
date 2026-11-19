// Using Array create Hash Table and demonstrate chaining with and without probing(define insert, and
// search operations)

#include <iostream>
using namespace std;

const int SIZE = 10;

// Node for chaining
struct Node {
    int data;
    Node* next;
};

// Hash function
int hashFunction(int key) {
    return key % SIZE;
}

// Linear Probing
int linearTable[SIZE];

// Insert using Linear Probing
void insertLinear(int key) {
    int index = hashFunction(key);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;

        if (linearTable[pos] == -1) {
            linearTable[pos] = key;
            cout << "Inserted successfully\n";
            return;
        }
    }

    cout << "Hash Table is full\n";
}

// Search using Linear Probing
void searchLinear(int key) {
    int index = hashFunction(key);

    for (int i = 0; i < SIZE; i++) {
        int pos = (index + i) % SIZE;

        if (linearTable[pos] == key) {
            cout << "Key found at index " << pos << endl;
            return;
        }

        if (linearTable[pos] == -1)
            break;
    }

    cout << "Key not found\n";
}

// Chaining
Node* chainTable[SIZE] = {NULL};

// Insert using Chaining
void insertChain(int key) {
    int index = hashFunction(key);

    Node* newNode = new Node;
    newNode->data = key;
    newNode->next = NULL;

    if (chainTable[index] == NULL) {
        chainTable[index] = newNode;
    } else {
        Node* temp = chainTable[index];

        while (temp->next != NULL)
            temp = temp->next;

        temp->next = newNode;
    }

    cout << "Inserted successfully\n";
}

// Search using Chaining
void searchChain(int key) {
    int index = hashFunction(key);
    Node* temp = chainTable[index];

    while (temp != NULL) {
        if (temp->data == key) {
            cout << "Key found\n";
            return;
        }

        temp = temp->next;
    }

    cout << "Key not found\n";
}

int main() {
    for (int i = 0; i < SIZE; i++)
        linearTable[i] = -1;

    int choice, key;

    do {
        cout << "\n1. Insert Linear Probing";
        cout << "\n2. Search Linear Probing";
        cout << "\n3. Insert Chaining";
        cout << "\n4. Search Chaining";
        cout << "\n5. Exit";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key: ";
                cin >> key;
                insertLinear(key);
                break;

            case 2:
                cout << "Enter key: ";
                cin >> key;
                searchLinear(key);
                break;

            case 3:
                cout << "Enter key: ";
                cin >> key;
                insertChain(key);
                break;

            case 4:
                cout << "Enter key: ";
                cin >> key;
                searchChain(key);
                break;
        }

    } while (choice != 5);

    return 0;
}
















/*
========== SAMPLE INPUT FOR Q5 ==========

--- LINEAR PROBING ---

1
23
1
43
1
13
1
27
1
37

--- SEARCH LINEAR PROBING ---

2
23
2
13
2
99

--- CHAINING ---

3
23
3
43
3
13
3
27
3
37

--- SEARCH CHAINING ---

4
23
4
13
4
99

--- EXIT ---

5

========== EXPECTED RESULTS ==========

LINEAR PROBING:
23 -> Index 3
43 -> Index 4
13 -> Index 5
27 -> Index 7
37 -> Index 8

Search 23 -> Key found at index 3
Search 13 -> Key found at index 5
Search 99 -> Key not found

CHAINING:
Index 3: 23 -> 43 -> 13
Index 7: 27 -> 37

Search 23 -> Key found
Search 13 -> Key found
Search 99 -> Key not found

=======================================
*/