#include <iostream>
using namespace std;

struct Node
{
    int key, height;
    Node *left;
    Node *right;
    Node(int val) : key(val), height(1), left(nullptr), right(nullptr) {}
};

// Height
int getHeight(Node *n)
{
    return n ? n->height : 0;
}

// Balance Factor
int getBalance(Node *n)
{
    return n ? getHeight(n->left) - getHeight(n->right) : 0;
}

// Update height
void updateHeight(Node *n)
{
    if (n)
        n->height = 1 + max(getHeight(n->left), getHeight(n->right));
}

// Rotate Right
Node *rotateRight(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// Rotate Left
Node *rotateLeft(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// Insert + Balance
Node *insert(Node *node, int key)
{
    if (!node)
        return new Node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    updateHeight(node);
    int balance = getBalance(node);

    // Balance Cases
    if (balance > 1 && key < node->left->key)
        return rotateRight(node); // LL
    if (balance < -1 && key > node->right->key)
        return rotateLeft(node); // RR
    if (balance > 1 && key > node->left->key)
    {
        node->left = rotateLeft(node->left); // LR
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key)
    {
        node->right = rotateRight(node->right); // RL
        return rotateLeft(node);
    }

    return node;
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

int main()
{
    Node *root = nullptr;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Inorder: ";
    inorder(root);
    cout << "\n\nTree Structure:\n";
    printTree(root);

    return 0;
}
