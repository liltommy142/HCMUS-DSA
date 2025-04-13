#include <iostream>
#include <queue>
using namespace std;

enum Color
{
    RED,
    BLACK
};

// Cau trúc của một nút trong cây Red-Black
struct Node
{
    int key;                     // Giá trị khoa
    Color color;                 // Màu của nút (RED hoặc BLACK)
    Node *left, *right, *parent; // Con trỏ đen các nút con và nút cha
};

// Tạo một nút mới với giá trị cho trước
Node *newNode(int data)
{
    Node *node = new Node;
    node->key = data;
    node->color = RED; // Nút mới luon co màu đỏ
    node->left = node->right = node->parent = nullptr;
    return node;
}

// Hàm xoay trái
Node *leftRotate(Node *root, Node *x)
{
    Node *y = x->right;
    x->right = y->left;
    if (y->left)
        y->left->parent = x;
    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
    return root;
}

// Hàm xoay phải
Node *rightRotate(Node *root, Node *y)
{
    Node *x = y->left;
    y->left = x->right;
    if (x->right)
        x->right->parent = y;
    x->parent = y->parent;

    if (!y->parent)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
    return root;
}

// Sửa lỗi sau khi chen để duy tri tính chat của cây Red-Black
Node *fixInsert(Node *root, Node *pt)
{
    Node *parent, *grandparent;

    while (pt != root && pt->color == RED && pt->parent && pt->parent->color == RED)
    {
        parent = pt->parent;
        grandparent = parent->parent;

        if (!grandparent)
            break;

        // Trường hợp cha là con trái của ong
        if (parent == grandparent->left)
        {
            Node *uncle = grandparent->right;

            // Trường hợp 1: Chú - màu đỏ
            if (uncle && uncle->color == RED)
            {
                parent->color = uncle->color = BLACK;
                grandparent->color = RED;
                pt = grandparent;
            }
            else
            {
                // Trường hợp 2: pt là con phải
                if (pt == parent->right)
                {
                    root = leftRotate(root, parent);
                    pt = parent;
                    parent = pt->parent;
                }
                // Trường hợp 3: pt là con trái
                root = rightRotate(root, grandparent);
                swap(parent->color, grandparent->color);
                pt = parent;
            }
        }
        else
        {
            // Trường hợp cha là con phải của ÔÔng
            Node *uncle = grandparent->left;

            // Trường hợp 1: Chú - màu đỏ
            if (uncle && uncle->color == RED)
            {
                parent->color = uncle->color = BLACK;
                grandparent->color = RED;
                pt = grandparent;
            }
            else
            {
                // Trường hợp 2: pt là con trái
                if (pt == parent->left)
                {
                    root = rightRotate(root, parent);
                    pt = parent;
                    parent = pt->parent;
                }
                // Trường hợp 3: pt là con phải
                root = leftRotate(root, grandparent);
                swap(parent->color, grandparent->color);
                pt = parent;
            }
        }
    }
    root->color = BLACK;
    return root;
}

// Chen một nút vào cây nhị phân tim kiem
Node *bstInsert(Node *root, Node *pt)
{
    if (!root)
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
    return root;
}

// Chen một giá trị vào cây Red-Black
Node *insert(Node *root, int data)
{
    Node *pt = newNode(data);
    root = bstInsert(root, pt);
    return fixInsert(root, pt);
}

// Tim kiem một nút với giá trị cho trước
Node *search(Node *root, int data)
{
    if (!root || root->key == data)
        return root;
    return (data < root->key) ? search(root->left, data) : search(root->right, data);
}

// Tim nút co giá trị nhỏ nhat trong cây con
Node *minValueNode(Node *node)
{
    while (node && node->left)
        node = node->left;
    return node;
}

// Sửa lỗi sau khi xoa để duy tri tính chat của cây Red-Black
Node *fixDelete(Node *root, Node *x, Node *parent)
{
    while (x != root && (!x || x->color == BLACK))
    {
        if (!parent)
            break;

        if (x == parent->left)
        {
            Node *sib = parent->right;
            if (!sib)
                break;

            if (sib->color == RED)
            {
                sib->color = BLACK;
                parent->color = RED;
                root = leftRotate(root, parent);
                sib = parent->right;
            }

            if ((!sib->left || sib->left->color == BLACK) && (!sib->right || sib->right->color == BLACK))
            {
                sib->color = RED;
                x = parent;
                parent = x->parent;
            }
            else
            {
                if (!sib->right || sib->right->color == BLACK)
                {
                    if (sib->left)
                        sib->left->color = BLACK;
                    sib->color = RED;
                    root = rightRotate(root, sib);
                    sib = parent->right;
                }
                if (sib)
                {
                    sib->color = parent->color;
                    parent->color = BLACK;
                    if (sib->right)
                        sib->right->color = BLACK;
                    root = leftRotate(root, parent);
                }
                x = root;
                break;
            }
        }
        else
        {
            Node *sib = parent->left;
            if (!sib)
                break;

            if (sib->color == RED)
            {
                sib->color = BLACK;
                parent->color = RED;
                root = rightRotate(root, parent);
                sib = parent->left;
            }

            if ((!sib->left || sib->left->color == BLACK) && (!sib->right || sib->right->color == BLACK))
            {
                sib->color = RED;
                x = parent;
                parent = x->parent;
            }
            else
            {
                if (!sib->left || sib->left->color == BLACK)
                {
                    if (sib->right)
                        sib->right->color = BLACK;
                    sib->color = RED;
                    root = leftRotate(root, sib);
                    sib = parent->left;
                }
                if (sib)
                {
                    sib->color = parent->color;
                    parent->color = BLACK;
                    if (sib->left)
                        sib->left->color = BLACK;
                    root = rightRotate(root, parent);
                }
                x = root;
                break;
            }
        }
    }
    if (x)
        x->color = BLACK;
    return root;
}

// Xoa một nút với giá trị cho trước
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
        Node *y = root;
        Color yOriginalColor = y->color;
        Node *x = nullptr;
        Node *xParent = nullptr;

        if (!root->left)
        {
            x = root->right;
            xParent = root->parent;
            Node *temp = root;
            root = root->right;
            if (root)
                root->parent = xParent;
            delete temp;
        }
        else if (!root->right)
        {
            x = root->left;
            xParent = root->parent;
            Node *temp = root;
            root = root->left;
            if (root)
                root->parent = xParent;
            delete temp;
        }
        else
        {
            Node *successor = minValueNode(root->right);
            root->key = successor->key;
            root->right = deleteNode(root->right, successor->key);
            return root;
        }

        if (yOriginalColor == BLACK)
            root = fixDelete(root, x, xParent);
    }
    return root;
}

// Duyet cây theo mức
void LevelOrder(Node *root)
{
    if (!root)
        return;
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        Node *temp = q.front();
        q.pop();
        cout << temp->key << " (" << (temp->color == RED ? "R" : "B") << ") ";
        if (temp->left)
            q.push(temp->left);
        if (temp->right)
            q.push(temp->right);
    }
    cout << endl;
}

// Hàm chính
int main()
{
    Node *root = nullptr;
    int arr[] = {7, 3, 18, 10, 22, 8, 11, 26};

    for (int val : arr)
    {
        root = insert(root, val);
    }

    cout << "Duyet theo level sau khi chen:\n";
    LevelOrder(root);
    cout << "\n";

    int testValues[] = {10, 15};
    for (int v : testValues)
    {
        Node *found = search(root, v);
        cout << "Tim kiem " << v << ": " << (found ? "Tim thay" : "Khong tim thay") << endl;
    }

    root = deleteNode(root, 18);
    cout << "\nSau khi xoa 18:\n";
    LevelOrder(root);

    root = deleteNode(root, 3);
    cout << "\nSau khi xoa 3:\n";
    LevelOrder(root);

    return 0;
}