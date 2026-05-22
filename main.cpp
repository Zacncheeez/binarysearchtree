#include <iostream>
#include <queue>
using namespace std;

// Template class for the Node of a Binary Tree
template <typename T>
class Node {
public:
    // Data held by the node
    T data;  
    // Pointer to the left child
    Node* left;  
    // Pointer to the right child
    Node* right;  

    // Constructor to initialize the node with a value
    Node(T value) : data(value), left(nullptr), right(nullptr) {}
};
