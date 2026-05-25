#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// Node structure for the binary search tree
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class
class BST {
private:
    Node* root;

    // Helper: insert value into subtree rooted at node
    Node* insert(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        // duplicates ignored
        return node;
    }

    // Helper: search for value in subtree rooted at node
    bool contains(Node* node, int value) const {
        if (node == nullptr) return false;
        if (value == node->data) return true;
        if (value < node->data) return contains(node->left, value);
        return contains(node->right, value);
    }

    // Helper: print tree sideways
    void printTree(Node* node, int depth) const {
        if (node == nullptr) return;

        printTree(node->right, depth + 1);

        for (int i = 0; i < depth; ++i)
            cout << "    ";
        cout << node->data << endl;

        printTree(node->left, depth + 1);
    }

    // Helper: delete all nodes
    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    // Public insert
    void insert(int value) {
        if (value < 1 || value > 999) {
            cout << "Value " << value << " is out of range (1-999). Ignored.\n";
            return;
        }
        root = insert(root, value);
    }

    // Public search
    bool contains(int value) const {
        return contains(root, value);
    }

    // Public print
    void print() const {
        if (root == nullptr) {
            cout << "(empty tree)\n";
        } else {
            printTree(root, 0);
        }
    }

    // NEW: Load numbers from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Could not open file: " << filename << endl;
            return;
        }

        int value;
        while (file >> value) {
            insert(value);
        }

        cout << "Loaded numbers from " << filename << endl;
    }
};

int main() {
    BST tree;
    int choice = 0;

    cout << "Binary Search Tree Program\n";
    cout << "Values must be between 1 and 999.\n\n";

    while (true) {
        cout << "Menu:\n";
        cout << " 1) Insert numbers (space-separated)\n";
        cout << " 2) Search for a number\n";
        cout << " 3) Print tree\n";
        cout << " 4) Load numbers from numbers.txt\n";
        cout << " 5) Quit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Enter numbers (space-separated, 1-999): ";
            string line;
            getline(cin, line);
            stringstream ss(line);
            int value;
            while (ss >> value) {
                tree.insert(value);
            }
            cout << "Numbers inserted.\n\n";

        } else if (choice == 2) {
            cout << "Enter number to search for: ";
            int value;
            if (cin >> value) {
                if (tree.contains(value)) {
                    cout << value << " is in the tree.\n";
                } else {
                    cout << value << " is NOT in the tree.\n";
                }
            } else {
                cout << "Invalid number.\n";
                cin.clear();
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;

        } else if (choice == 3) {
            cout << "Current tree (rotated 90 degrees counterclockwise):\n";
            tree.print();
            cout << endl;

        } else if (choice == 4) {
            tree.loadFromFile("numbers.txt");
            cout << endl;

        } else if (choice == 5) {
            cout << "Goodbye.\n";
            break;

        } else {
            cout << "Invalid choice.\n\n";
        }
    }

    return 0;
}
