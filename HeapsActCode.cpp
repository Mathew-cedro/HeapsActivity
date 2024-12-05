// Mathew R Cedro, BSCS-2A 

#include <vector> 
#include <iostream>
#include <iomanip> // For formatted output
#include <string>  // For getline function
#include <algorithm> // For the find function
using namespace std;

// Function to display the main menu and take user input
char mainmenu() {
    char value;
    cout << "|" << setw(55) << "|\n";
    cout << "|" << setw(34) << "CELEBRITY NETWORTH" << setw(21) << "|\n";
    cout << "|" << setw(31) << "-Main Menu-" << setw(24) << "|\n";
    cout << "|" << setw(30) << "-Options-" << setw(25) << "|\n";
    cout << "|" << setw(30) << "A. Insert" << setw(25) << "|\n";
    cout << "|" << setw(31) << "B. Heapify" << setw(24) << "|\n";
    cout << "|" << setw(30) << "C. Remove" << setw(25) << "|\n";
    cout << "|" << setw(31) << "D. Display" << setw(24) << "|\n";
    cout << "|" << setw(29) << "E. Exit" << setw(26) << "|\n";
    cout << setw(30) << "Input: ";
    cin >> value;
    return value;
}

// Function to display the heap in a tree-like structure
void displaythree(const vector<int>& numbertree, const vector<string>& nametree, int index = 0, int indent = 0) {
    if (nametree.empty() && numbertree.empty()) {
        cout << "|||| THE LIST IS EMPTY ||||\n";
        return;
    }
    if (index >= numbertree.size()) return;


    // Recursively print the right child (mirrored for tree-like display)
    displaythree(numbertree, nametree, 2 * index + 2, indent + 4);

    // Print current node with indentation
    if (indent) cout << setw(indent) << ' ';
    cout << nametree[index] << " : " << numbertree[index] << endl;

    // Recursively print the left child
    displaythree(numbertree, nametree, 2 * index + 1, indent + 4);

    // for (int num : numbertree){
    //     cout << num << " ";
    // }
    
}

// Generic function to swap two elements
template <class swap>
void swapnumbers(swap* a, swap* b) {
    swap temp = *a;
    *a = *b;
    *b = temp;
}

// Max-heapify function to maintain heap property for a given node
void maxheapify(vector<int>& HT, vector<string>& HT2, int index) {
    int largest = index;          // Assume current node is the largest
    int left = (2 * index) + 1;   // Left child index
    int right = (2 * index) + 2;  // Right child index

    // Check if left child exists and is greater than current largest
    if (left < HT.size() && HT[left] > HT[largest]) largest = left;

    // Check if right child exists and is greater than current largest
    if (right < HT.size() && HT[right] > HT[largest]) largest = right;

    // If largest is not the current node, swap and recurse
    if (largest != index) {
        swapnumbers(&HT[largest], &HT[index]);
        swapnumbers(&HT2[largest], &HT2[index]);
        maxheapify(HT, HT2, largest);
    }
}

// Function to build a max heap
void maxheap(vector<int>& HT, vector<string>& HT2) {
    int lastParent = (HT.size() / 2) - 1; // Index of last non-leaf node
    for (int i = lastParent; i >= 0; i--) {
        maxheapify(HT, HT2, i);
    }
}

// Min-heapify function to maintain heap property for a given node
void minheapify(vector<int>& HT, vector<string>& HT2, int index) {
    int smallest = index;        // Assume current node is the smallest
    int left = (2 * index) + 1;  // Left child index
    int right = (2 * index) + 2; // Right child index

    // Check if left child exists and is smaller than current smallest
    if (left < HT.size() && HT[left] < HT[smallest]) smallest = left;

    // Check if right child exists and is smaller than current smallest
    if (right < HT.size() && HT[right] < HT[smallest]) smallest = right;

    // If smallest is not the current node, swap and recurse
    if (smallest != index) {
        swapnumbers(&HT[smallest], &HT[index]);
        swapnumbers(&HT2[smallest], &HT2[index]);
        minheapify(HT, HT2, smallest);
    }
}

// Sort functions

// Function to build a min heap
void minheap(vector<int>& HT, vector<string>& HT2) {
    int lastParent = (HT.size() / 2) - 1; // Index of last non-leaf node
    for (int i = lastParent; i >= 0; i--) {
        minheapify(HT, HT2, i);
    }
}

// Function to choose heap type (min or max) and heapify the array
bool heapchoice(vector<int>& HT, vector<string>& HT2) {
    char choice;
    while (true) {
        cout << "|" << setw(31) << "A. Minheapify" << setw(24) << "|\n";
        cout << "|" << setw(31) << "B. Maxheapify" << setw(24) << "|\n";
        cout << setw(30) << "Input: ";
        cin >> choice;

        switch (choice) {
            case 'a': case 'A':
                minheap(HT, HT2);
                cout << "|" << setw(33) << "MinHeapified!" << setw(23) << "|\n\n";
                return true;

            case 'b': case 'B':
                maxheap(HT, HT2);
                cout << "|" << setw(33) << "MaxHeapified!" << setw(23) << "|\n\n";
                return false;

            default:
                cout << "|" << setw(26) << "Not a valid option" << setw(31) << "|\n\n";
                break;
        }
    }
}

// Function to insert a new celebrity and their net worth
void insert(vector<string>& nametree, vector<int>& Numtree, bool isminheap) {
    int newNetWorth;
    string newName;

    // Input celebrity details
    cout << "|  Input the name of the Celebrity: ";
    cin.ignore();
    getline(cin, newName);
    cout << "|  Input the net worth of the Celebrity: ";
    cin >> newNetWorth;

    // Insert into the heap
    nametree.push_back(newName);
    Numtree.push_back(newNetWorth);

    // Reheapify to maintain max-heap property
    int current = Numtree.size() - 1;
    while (current > 0) {
        int parent = (current - 1) / 2;
        if ( isminheap && Numtree[current] < Numtree[parent]) {
            swapnumbers(&Numtree[current], &Numtree[parent]);
            swapnumbers(&nametree[current], &nametree[parent]);
            current = parent;
        } else if(!isminheap && Numtree[current] > Numtree[parent]) {
            swapnumbers(&Numtree[current], &Numtree[parent]);
            swapnumbers(&nametree[current], &nametree[parent]);
            current = parent;
        }else{
             break;
        }
    }
    cout << "|" << setw(35) << "New value inserted!" << setw(20) << "|\n";
}

// Function to delete a node (celebrity) by name
void deletion(vector<int>& Numtree, vector<string>& nametree, bool isMinHeap) {
    string name;
    cout << "Enter the name of the celebrity to be deleted\n";
    cout << "Input: ";
    cin.ignore(); // Clear buffer
    getline(cin, name); // Properly read the name

    // Search for the node to delete
    auto it = std::find(nametree.begin(), nametree.end(), name);
    if (it != nametree.end()) {
        int index = distance(nametree.begin(), it);

        // Swap with last element and remove
        swapnumbers(&Numtree[index], &Numtree.back());
        swapnumbers(&nametree[index], &nametree.back());
        Numtree.pop_back();
        nametree.pop_back();

        // Reheapify to maintain heap property
        if (isMinHeap) {
            minheapify(Numtree, nametree, index);
        } else {
            maxheapify(Numtree, nametree, index);
        }

        cout << "Deleted node: " << name << '\n';
    } else {
        cout << "Celebrity not found!\n";
    }
}


// Main function
int main() {
    vector<int> numbercheese;
    vector<string> namecheese;
    // vector<int> numbercheese = {10, 20, 30, 5, 25, 15};
    // vector<string> namecheese = {"1","2","3","4","5","6"};
    bool isMinHeap = true;  // Default heap type
    bool programRunning = true;

    while (programRunning) {
        char choice = mainmenu();
        switch (choice) {
            case 'A': case 'a':
                insert(namecheese, numbercheese, isMinHeap);
                break;
            case 'B': case 'b':
                isMinHeap = heapchoice(numbercheese, namecheese);
                break;
            case 'C': case 'c':
                deletion(numbercheese, namecheese, isMinHeap);
                break;
            case 'D': case 'd':
                displaythree(numbercheese, namecheese);
                break;
            case 'E': case 'e':
                programRunning = false;
                cout << "|" << setw(29) << "Exiting..." << setw(27) << "|\n";
                break;
            default:
                cout << "|" << setw(29) << "Invalid Option!" << setw(26) << "|\n";
                break;
        }
    }
    return 0;
}
