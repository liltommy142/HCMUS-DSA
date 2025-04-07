#include <iostream>
#include <queue>
using namespace std;

enum Color
{
    RED,
    BLACK
};

struct Node
{
    int key;
    Color color;
    Node *left;
    Node *right;
    Node *parent;
};

// 1. Create a new Node with a given value
Node *newNode(int data)
{
    Node *node = new Node;
    node->key = data;
    node->color = RED; // New nodes are always initially RED
    node->left = nullptr;
    node->right = nullptr;
    node->parent = nullptr;
    return node;
}

// Helper functions for tree rotations
Node *leftRotate(Node *root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;

    if (y->left != nullptr)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;

    return root;
}

Node *rightRotate(Node *root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;

    if (x->right != nullptr)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;

    return root;
}

// Fix Red-Black Tree violations after insertion
Node *fixInsert(Node *root, Node *pt)
{
    Node *parent = nullptr;
    Node *grandparent = nullptr;

    while ((pt != root) && (pt->color != BLACK) && (pt->parent != nullptr && pt->parent->color == RED))
    {
        parent = pt->parent;
        grandparent = parent->parent;

        if (grandparent == nullptr)
            break;

        // Case A: Parent is left child of Grandparent
        if (parent == grandparent->left)
        {
            Node *uncle = grandparent->right;

            // Case 1A: Uncle is red - recolor
            if (uncle != nullptr && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                pt = grandparent;
            }
            else
            {
                // Case 2A: pt is right child - Left rotation
                if (pt == parent->right)
                {
                    root = leftRotate(root, parent);
                    pt = parent;
                    parent = pt->parent;
                }

                // Case 3A: pt is left child - Right rotation
                root = rightRotate(root, grandparent);
                swap(parent->color, grandparent->color);
                pt = parent;
            }
        }
        // Case B: Parent is right child of Grandparent
        else
        {
            Node *uncle = grandparent->left;

            // Case 1B: Uncle is red - recolor
            if (uncle != nullptr && uncle->color == RED)
            {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                pt = grandparent;
            }
            else
            {
                // Case 2B: pt is left child - Right rotation
                if (pt == parent->left)
                {
                    root = rightRotate(root, parent);
                    pt = parent;
                    parent = pt->parent;
                }

                // Case 3B: pt is right child - Left rotation
                root = leftRotate(root, grandparent);
                swap(parent->color, grandparent->color);
                pt = parent;
            }
        }
    }

    root->color = BLACK;
    return root;
}

// BST insertion
Node *bstInsert(Node *root, Node *pt)
{
    // Empty tree case
    if (root == nullptr)
        return pt;

    if (pt->key < root->key)
    {
        root->left = bstInsert(root->left, pt);
        root->left->parent = root;
    }
    else if (pt->key > root->key)
    {
        root->right = bstInsert(root->right, pt);
        root->right->parent = root;
    }
    // Equal keys are not allowed in BST

    return root;
}

// 2. Insert a new value into a Red-Black Tree
Node *insert(Node *root, int data)
{
    Node *newNode_ptr = newNode(data);

    // Do a normal BST insert
    root = bstInsert(root, newNode_ptr);

    // Fix Red-Black Tree properties
    return fixInsert(root, newNode_ptr);
}

// 3. Search for a Node with a given value
Node *search(Node *root, int data)
{
    // Base cases: root is null or key is present at root
    if (root == nullptr || root->key == data)
        return root;

    // Key is greater than root's key
    if (root->key < data)
        return search(root->right, data);

    // Key is smaller than root's key
    return search(root->left, data);
}

// Helper functions for deletion
Node *minValueNode(Node *node)
{
    Node *current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

// Fix Red-Black Tree violations after deletion
Node *fixDelete(Node *root, Node *x, Node *parent)
{
    while (x != root && (x == nullptr || x->color == BLACK))
    {
        if (parent == nullptr)
            break;

        if (x == parent->left)
        {
            Node *sibling = parent->right;

            if (sibling == nullptr)
                break;

            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                parent->color = RED;
                root = leftRotate(root, parent);
                sibling = parent->right;
            }

            if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                (sibling->right == nullptr || sibling->right->color == BLACK))
            {
                sibling->color = RED;
                x = parent;
                parent = x->parent;
            }
            else
            {
                if (sibling->right == nullptr || sibling->right->color == BLACK)
                {
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    sibling->color = RED;
                    root = rightRotate(root, sibling);
                    sibling = parent->right;
                }

                if (sibling != nullptr)
                {
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    root = leftRotate(root, parent);
                }
                x = root;
                parent = nullptr;
            }
        }
        else
        {
            Node *sibling = parent->left;

            if (sibling == nullptr)
                break;

            if (sibling->color == RED)
            {
                sibling->color = BLACK;
                parent->color = RED;
                root = rightRotate(root, parent);
                sibling = parent->left;
            }

            if ((sibling->right == nullptr || sibling->right->color == BLACK) &&
                (sibling->left == nullptr || sibling->left->color == BLACK))
            {
                sibling->color = RED;
                x = parent;
                parent = x->parent;
            }
            else
            {
                if (sibling->left == nullptr || sibling->left->color == BLACK)
                {
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    sibling->color = RED;
                    root = leftRotate(root, sibling);
                    sibling = parent->left;
                }

                if (sibling != nullptr)
                {
                    sibling->color = parent->color;
                    parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    root = rightRotate(root, parent);
                }
                x = root;
                parent = nullptr;
            }
        }
    }

    if (x != nullptr)
        x->color = BLACK;

    return root;
}

// 4. Delete a Node with a given value
Node *deleteNode(Node *root, int data)
{
    if (root == nullptr)
        return root;

    // Find the node to delete
    if (data < root->key)
        root->left = deleteNode(root->left, data);
    else if (data > root->key)
        root->right = deleteNode(root->right, data);
    else
    {
        // Node found, perform deletion

        // No children or one child case
        if (root->left == nullptr || root->right == nullptr)
        {
            Node *temp = root->left ? root->left : root->right;

            if (temp == nullptr)
            { // No children
                temp = root;
                root = nullptr;
            }
            else
            {                  // One child
                *root = *temp; // Copy child's data
            }

            Color origColor = temp->color;
            Node *parent = temp->parent;
            Node *replacement = nullptr;

            delete temp;

            if (origColor == BLACK)
                root = fixDelete(root, replacement, parent);
        }
        else
        {
            // Two children case
            Node *successor = minValueNode(root->right);

            // Copy successor data to this node
            root->key = successor->key;

            // Delete the successor (which has at most one child)
            root->right = deleteNode(root->right, successor->key);
        }
    }

    return root;
}

// 5. Level-order traversal
void LevelOrder(Node *root)
{
    if (root == nullptr)
        return;

    queue<Node *> q;
    q.push(root);

    while (!q.empty())
    {
        Node *current = q.front();
        q.pop();

        // Print node value and color
        cout << current->key << " (" << (current->color == RED ? "R" : "B") << ") ";

        // Add children to queue if they exist
        if (current->left != nullptr)
            q.push(current->left);
        if (current->right != nullptr)
            q.push(current->right);
    }
}

// Main function for testing
int main()
{
    Node *root = nullptr;

    // Insert values
    root = insert(root, 7);
    root = insert(root, 3);
    root = insert(root, 18);
    root = insert(root, 10);
    root = insert(root, 22);
    root = insert(root, 8);
    root = insert(root, 11);
    root = insert(root, 26);

    // Display the tree
    cout << "Level Order Traversal after insertion:\n";
    LevelOrder(root);
    cout << "\n\n";

    // Search for a value
    int searchValue = 10;
    Node *found = search(root, searchValue);
    if (found)
        cout << "Found " << searchValue << " in the tree.\n";
    else
        cout << searchValue << " not found in the tree.\n";

    // Search for a value not in the tree
    searchValue = 15;
    found = search(root, searchValue);
    if (found)
        cout << "Found " << searchValue << " in the tree.\n";
    else
        cout << searchValue << " not found in the tree.\n\n";

    // Delete some values
    cout << "Deleting 18 from the tree.\n";
    root = deleteNode(root, 18);
    cout << "Level Order Traversal after deletion of 18:\n";
    LevelOrder(root);
    cout << "\n\n";

    cout << "Deleting 3 from the tree.\n";
    root = deleteNode(root, 3);
    cout << "Level Order Traversal after deletion of 3:\n";
    LevelOrder(root);
    cout << "\n\n";

    return 0;
}