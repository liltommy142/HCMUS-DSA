#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Node structure for AVL tree
struct Node
{
    int key;
    Node *left;
    Node *right;
    int height;
};

//---------------------- Helper Functions ----------------------

// Get the height of a node (returns 0 for nullptr)
int getHeight(Node *node)
{
    if (node == nullptr)
        return 0;
    return node->height;
}

// Calculate balance factor of a node
int getBalance(Node *node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Update height based on children
void updateHeight(Node *node)
{
    if (node != nullptr)
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// Right rotation for rebalancing
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x; // New root
}

// Left rotation for rebalancing
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y; // New root
}

// Find minimum value node (leftmost leaf)
Node *findMinValueNode(Node *node)
{
    Node *current = node;
    while (current && current->left != nullptr)
        current = current->left;
    return current;
}

// Count total nodes in tree
int countNodes(Node *root)
{
    if (root == nullptr)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

//---------------------- Main AVL Operations ----------------------

// 1. Create a new Node from a given value
Node *newNode(int data)
{
    Node *node = new Node();
    node->key = data;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // New node starts at height 1
    return node;
}

// 2. Insert a new value into an AVL Tree
Node *insertNode(Node *root, int data)
{
    // Standard BST insertion
    if (root == nullptr)
        return newNode(data);

    if (data < root->key)
        root->left = insertNode(root->left, data);
    else if (data > root->key)
        root->right = insertNode(root->right, data);
    else
        return root; // Duplicate keys not allowed

    // Update height
    updateHeight(root);

    // Get balance factor and rebalance if needed
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && data < root->left->key)
        return rightRotate(root);

    // Right Right Case
    if (balance < -1 && data > root->right->key)
        return leftRotate(root);

    // Left Right Case
    if (balance > 1 && data > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Left Case
    if (balance < -1 && data < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 3. Search a Node with a given value from an AVL Tree
Node *searchNode(Node *root, int data)
{
    if (root == nullptr || root->key == data)
        return root;

    if (data < root->key)
        return searchNode(root->left, data);

    return searchNode(root->right, data);
}

// 4. Delete a Node with a given value from an AVL Tree
Node *deleteNode(Node *root, int data)
{
    // Standard BST delete
    if (root == nullptr)
        return root;

    if (data < root->key)
        root->left = deleteNode(root->left, data);
    else if (data > root->key)
        root->right = deleteNode(root->right, data);
    else
    {
        // Node with one child or no children
        if (root->left == nullptr || root->right == nullptr)
        {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr)
            {
                temp = root;
                root = nullptr;
            }
            else               // One child case
                *root = *temp; // Copy contents of non-empty child

            delete temp;
        }
        else
        {
            // Node with two children
            Node *temp = findMinValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If tree had only one node
    if (root == nullptr)
        return root;

    // Update height and rebalance
    updateHeight(root);
    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

//---------------------- Tree Traversals ----------------------

// Pre-order traversal (Node, Left, Right)
void NLR(Node *root)
{
    if (root != nullptr)
    {
        cout << root->key << " ";
        NLR(root->left);
        NLR(root->right);
    }
}

// In-order traversal (Left, Node, Right)
void LNR(Node *root)
{
    if (root != nullptr)
    {
        LNR(root->left);
        cout << root->key << " ";
        LNR(root->right);
    }
}

// Post-order traversal (Left, Right, Node)
void LRN(Node *root)
{
    if (root != nullptr)
    {
        LRN(root->left);
        LRN(root->right);
        cout << root->key << " ";
    }
}

// Level-order traversal (BFS)
void LevelOrder(Node *root)
{
    if (root == nullptr)
        return;

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *current = q.front();
        cout << current->key << " ";
        q.pop();

        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}

//---------------------- Tree Properties ----------------------

// Print balance factors of all nodes (in-order)
void printBalance(Node *root)
{
    if (root != nullptr)
    {
        printBalance(root->left);
        cout << "Node " << root->key << " has balance factor: " << getBalance(root) << endl;
        printBalance(root->right);
    }
}

// 1. Check if the given AVL Tree is a full tree
bool isFull(Node *root)
{
    // Empty tree is full
    if (root == nullptr)
        return true;

    // If node has no children, it's a leaf
    if (root->left == nullptr && root->right == nullptr)
        return true;

    // If both children exist, check both subtrees
    if (root->left != nullptr && root->right != nullptr)
        return isFull(root->left) && isFull(root->right);

    // One child missing, not full
    return false;
}

// 2. Check if the given AVL Tree is a complete tree
bool isCompleteUtil(Node *root, int index, int nodeCount)
{
    if (root == nullptr)
        return true;

    // If index assigned to current node is >= number of nodes, not complete
    if (index >= nodeCount)
        return false;

    // Check both subtrees
    return isCompleteUtil(root->left, 2 * index + 1, nodeCount) &&
           isCompleteUtil(root->right, 2 * index + 2, nodeCount);
}

bool isComplete(Node *root)
{
    int count = countNodes(root);
    return isCompleteUtil(root, 0, count);
}

// 3. Check if the given AVL Tree is a perfect tree
bool isPerfect(Node *root)
{
    // Get height
    int h = getHeight(root);

    // Count nodes
    int nodeCount = countNodes(root);

    // Perfect binary tree has 2^h - 1 nodes
    return nodeCount == (1 << h) - 1;
}

// 4. Find the least common ancestor for two given nodes in AVL Tree
int findCommonAncestor(Node *root, int x, int y)
{
    if (root == nullptr)
        return -1; // Error case

    // Both values smaller than current node, go left
    if (x < root->key && y < root->key)
        return findCommonAncestor(root->left, x, y);

    // Both values larger than current node, go right
    if (x > root->key && y > root->key)
        return findCommonAncestor(root->right, x, y);

    // Split point found or one value equals root
    return root->key;
}

// 5. Find all nodes with 2 child nodes, where left child is a divisor of right child
void collectSpecialNodes(Node *root, vector<int> &specialNodes)
{
    if (root == nullptr)
        return;

    // In-order traversal to collect nodes in ascending order
    collectSpecialNodes(root->left, specialNodes);

    // Check if node has 2 children and left child is divisor of right child
    if (root->left && root->right && root->right->key % root->left->key == 0)
        specialNodes.push_back(root->key);

    collectSpecialNodes(root->right, specialNodes);
}

void printSpecialNodes(Node *root)
{
    vector<int> specialNodes;
    collectSpecialNodes(root, specialNodes);

    cout << "Nodes with 2 children where left child is divisor of right child: ";
    if (specialNodes.empty())
        cout << "None";
    else
        for (int node : specialNodes)
            cout << node << " ";
    cout << endl;
}

//---------------------- Main Function ----------------------

int main()
{
    Node *root = nullptr;

    // Create AVL tree
    cout << "Creating AVL tree with values: 8, 6, 5, 7, 10, 9" << endl;
    root = insertNode(root, 8);
    root = insertNode(root, 6);
    root = insertNode(root, 5);
    root = insertNode(root, 7);
    root = insertNode(root, 10);
    root = insertNode(root, 9);

    // Additional nodes for testing properties
    root = insertNode(root, 15); // 5 divides 15
    root = insertNode(root, 14); // 7 divides 14

    // Tree traversals
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

    cout << "Level-order: ";
    LevelOrder(root);
    cout << endl;

    // Check balance factors
    cout << "\n--- Balance Factors ---" << endl;
    printBalance(root);

    // Test tree properties
    cout << "\n--- Tree Properties ---" << endl;
    cout << "Is Full Tree: " << (isFull(root) ? "Yes" : "No") << endl;
    cout << "Is Complete Tree: " << (isComplete(root) ? "Yes" : "No") << endl;
    cout << "Is Perfect Tree: " << (isPerfect(root) ? "Yes" : "No") << endl;

    // Test common ancestor
    int x = 5, y = 7;
    cout << "Least Common Ancestor of " << x << " and " << y << ": "
         << findCommonAncestor(root, x, y) << endl;

    // Test special nodes
    printSpecialNodes(root);

    // Search operation
    int searchKey = 9;
    Node *result = searchNode(root, searchKey);
    cout << "\nSearching for key " << searchKey << ": "
         << (result ? "Found" : "Not Found") << endl;

    searchKey = 12;
    result = searchNode(root, searchKey);
    cout << "Searching for key " << searchKey << ": "
         << (result ? "Found" : "Not Found") << endl;

    // Delete operation
    cout << "\nDeleting key 8 (root)" << endl;
    root = deleteNode(root, 8);
    cout << "Level-order after deletion: ";
    LevelOrder(root);
    cout << endl;

    // Check tree properties after deletion
    cout << "\n--- Tree Properties after deletion ---" << endl;
    cout << "Is Full Tree: " << (isFull(root) ? "Yes" : "No") << endl;
    cout << "Is Complete Tree: " << (isComplete(root) ? "Yes" : "No") << endl;

    cout << "\n--- Balance Factors after deletion ---" << endl;
    printBalance(root);

    return 0;
}