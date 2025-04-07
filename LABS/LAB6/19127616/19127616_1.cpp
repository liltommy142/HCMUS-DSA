#include <iostream>
#include <queue>

using namespace std;

struct Node
{
    int key;
    Node *left, *right;
};

// 1. Calculate the height of a given Binary Search Tree.
int height(Node *root)
{
    if (!root)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return 1 + max(leftHeight, rightHeight);
}

// 2. Count the number of Node from a given Binary Search Tree.
int countNode(Node *root)
{
    if (!root)
        return 0;
    return 1 + countNode(root->left) + countNode(root->right);
}

// 3. Count the number of internal nodes (non-leaf nodes) from a given Binary Search Tree.
int countInternal(Node *root)
{
    if (!root || (!root->left && !root->right))
        return 0;
    return 1 + countInternal(root->left) + countInternal(root->right);
}

// 4. Calculate the total value of all Nodes from a given Binary Search Tree:
int sumNode(Node *root)
{
    if (!root)
        return 0;
    return root->key + sumNode(root->left) + sumNode(root->right);
}

// 5. Count the number leaves from a given Binary Search Tree.
int countLeaf(Node *root)
{
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return countLeaf(root->left) + countLeaf(root->right);
}

// 6. Count the number of Nodes with key value less than a given value.
int countLess(Node *root, int x)
{
    if (!root)
        return 0;
    if (root->key >= x)
        return countLess(root->left, x);
    else
        return 1 + countLess(root->left, x) + countLess(root->right, x);
}

// 7. Count the number of Nodes with key value greater than a given value.
int countGreater(Node *root, int x)
{
    if (!root)
        return 0;
    if (root->key <= x)
        return countGreater(root->right, x);
    else
        return 1 + countGreater(root->left, x) + countGreater(root->right, x);
}

// 1. Create a new Node from a given value.
Node *newNode(int data)
{
    Node *node = new Node();
    node->key = data;
    node->left = node->right = nullptr;
    return node;
}

// 2. Insert a new value into a Binary Search Tree.
Node *insert(Node *root, int data)
{
    if (!root)
        return newNode(data);
    if (data < root->key)
        root->left = insert(root->left, data);
    else if (data > root->key)
        root->right = insert(root->right, data);
    else
        return root; // Duplicate keys are not allowed

    return root;
}

// 3. Search a Node with a given value from a Binary Search Tree. Return NULL if not found
Node *search(Node *root, int data)
{
    if (!root || root->key == data)
        return root;
    if (data < root->key)
        return search(root->left, data);
    return search(root->right, data);
}

Node *minValueNode(Node *node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

// 4. Delete a Node with a given value from a Binary Search Tree.
Node *deleteNode(Node *root, int data)
{
    if (!root)
        return root;
    if (data < root->key)
        root->left = deleteNode(root->left, data);
    else if (data > root->key)
        root->right = deleteNode(root->right, data);
    else
    {
        if (!root->left)
            return root->right;
        if (!root->right)
            return root->left;
        Node *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }

    return root;
}

// 5. Traversal in Pre-order, In-order, Post-order and Level-order.
// Pre-order: NLR
void NLR(Node *root)
{
    if (root)
    {
        cout << root->key << " ";
        NLR(root->left);
        NLR(root->right);
    }
}

// In-order: LNR
void LNR(Node *root)
{
    if (root)
    {
        LNR(root->left);
        cout << root->key << " ";
        LNR(root->right);
    }
}

// Post-order: LRN
void LRN(Node *root)
{
    if (root)
    {
        LRN(root->left);
        LRN(root->right);
        cout << root->key << " ";
    }
}

// Level-order: BFS
void LevelOrder(Node *root)
{
    if (!root)
        return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *node = q.front();
        q.pop();
        cout << node->key << " ";
        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
}

int main()
{
    // Initialize empty tree
    Node *root = nullptr;

    // Create a binary search tree
    cout << "Creating BST with values: 8, 6, 5, 7, 10, 9" << endl;
    root = insert(root, 8);
    root = insert(root, 6);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 10);
    root = insert(root, 9);
    // Tree structure:
    //        8
    //       / \
    //      6  10
    //     / \  /
    //    5  7 9

    // Display tree using traversals
    cout << "\n--- Tree Traversals ---" << endl;

    cout << "Pre-order (NLR): ";
    NLR(root);
    cout << endl;

    cout << "In-order (LNR): ";
    LNR(root);
    cout << endl;

    cout << "Post-order (LRN): ";
    LRN(root);
    cout << endl;

    // Delete root node (8)
    cout << "\nDeleting node with value 8 (root)" << endl;
    root = deleteNode(root, 8);

    cout << "Level Order after deletion: ";
    LevelOrder(root);
    cout << endl;

    // Exercise 2 implementations
    cout << "\n--- Tree Properties (Exercise 2) ---" << endl;

    cout << "1. Height of the tree: " << height(root) << endl;

    cout << "2. Number of nodes: " << countNode(root) << endl;

    cout << "3. Number of internal nodes: " << countInternal(root) << endl;

    cout << "4. Sum of all node values: " << sumNode(root) << endl;

    cout << "5. Number of leaf nodes: " << countLeaf(root) << endl;

    int x = 7;
    cout << "6. Number of nodes with value less than " << x << ": " << countLess(root, x) << endl;

    cout << "7. Number of nodes with value greater than " << x << ": " << countGreater(root, x) << endl;

    return 0;
}