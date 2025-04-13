#include <iostream>
using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;
    Node(int val) : key(val), left(nullptr), right(nullptr) {}
};

// Insert
Node *insert(Node *root, int key)
{
    if (!root)
        return new Node(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

// Find min node (for delete)
Node *findMin(Node *node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

// Delete
Node *deleteNode(Node *root, int key)
{
    if (!root)
        return root;
    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else
    {
        if (!root->left)
        {
            Node *tmp = root->right;
            delete root;
            return tmp;
        }
        else if (!root->right)
        {
            Node *tmp = root->left;
            delete root;
            return tmp;
        }
        Node *tmp = findMin(root->right);
        root->key = tmp->key;
        root->right = deleteNode(root->right, tmp->key);
    }
    return root;
}

// Search
bool search(Node *root, int key)
{
    if (!root)
        return false;
    if (key == root->key)
        return true;
    return key < root->key ? search(root->left, key) : search(root->right, key);
}

// Inorder
void inorder(Node *root)
{
    if (root)
    {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Height
int height(Node *root)
{
    if (!root)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

// Count nodes
int countNodes(Node *root)
{
    if (!root)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

// Print Tree sơ đồ
void printTree(Node *root, string indent = "", bool last = true)
{
    if (root != nullptr)
    {
        cout << indent;
        if (last)
        {
            cout << "`-- ";
            indent += "    ";
        }
        else
        {
            cout << "|-- ";
            indent += "|   ";
        }

        cout << root->key << "\n";
        printTree(root->left, indent, false);
        printTree(root->right, indent, true);
    }
}

// Main test
int main()
{
    Node *root = nullptr;
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 1);
    root = insert(root, 6);
    root = insert(root, 4);
    root = insert(root, 7);
    root = insert(root, 14);

    cout << "Inorder: ";
    inorder(root);
    cout << "\nHeight: " << height(root);
    cout << "\nTotal Nodes: " << countNodes(root);
    cout << "\n\nTree Structure:\n";
    printTree(root);

    return 0;
}
