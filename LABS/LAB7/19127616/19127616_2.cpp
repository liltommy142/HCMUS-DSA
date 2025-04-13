#include <iostream>
#include <queue>
using namespace std;

const int MAX = 3; // Bậc của cây B

struct Node
{
    int keys[MAX];           // Mảng chứa các khoa
    Node *children[MAX + 1]; // Con trỏ đen các nút con
    int numKeys;             // Số lượng khoa hiện tại
    bool isLeaf;             // Co phải là nút lá khong?

    Node(bool leaf)
    {
        isLeaf = leaf;
        numKeys = 0;
        for (int i = 0; i <= MAX; i++)
            children[i] = nullptr;
    }
};

// Tạo một nút mới
Node *newNode(bool isLeaf)
{
    return new Node(isLeaf);
}

Node *deleteNode(Node *x, int key);

// Duyệt cây NLR
void NLR(Node *root)
{
    if (!root)
        return;
    for (int i = 0; i < root->numKeys; i++)
        cout << root->keys[i] << " ";
    for (int i = 0; i <= root->numKeys; i++)
        NLR(root->children[i]);
}

// Duyệt cây LNR
void LNR(Node *root)
{
    if (!root)
        return;
    for (int i = 0; i < root->numKeys; i++)
    {
        LNR(root->children[i]);
        cout << root->keys[i] << " ";
    }
    LNR(root->children[root->numKeys]);
}

// Duyệt cây LRN
void LRN(Node *root)
{
    if (!root)
        return;
    for (int i = 0; i <= root->numKeys; i++)
        LRN(root->children[i]);
    for (int i = 0; i < root->numKeys; i++)
        cout << root->keys[i] << " ";
}

// Duyệt theo level (Level Order)
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

        for (int i = 0; i < temp->numKeys; i++)
            cout << temp->keys[i] << " ";
        cout << "| ";

        for (int i = 0; i <= temp->numKeys; i++)
            if (temp->children[i])
                q.push(temp->children[i]);
    }
    cout << endl;
}

// Tim kiem một khoa
Node *search(Node *root, int key)
{
    if (!root)
        return nullptr;
    int i = 0;
    while (i < root->numKeys && key > root->keys[i])
        i++;

    if (i < root->numKeys && root->keys[i] == key)
        return root;

    if (root->isLeaf)
        return nullptr;

    return search(root->children[i], key);
}

// Chia nút con y của x tại chỉ số i
void splitChild(Node *x, int i, Node *y)
{
    Node *z = newNode(y->isLeaf);
    z->numKeys = 1;
    z->keys[0] = y->keys[2];

    if (!y->isLeaf)
    {
        z->children[0] = y->children[2];
        z->children[1] = y->children[3];
    }

    y->numKeys = 1;

    for (int j = x->numKeys; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];

    x->children[i + 1] = z;

    for (int j = x->numKeys - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[1];
    x->numKeys++;
}

// Thêm khoa vào nút khong đầy
void insertNonFull(Node *x, int key)
{
    int i = x->numKeys - 1;

    if (x->isLeaf)
    {
        while (i >= 0 && key < x->keys[i])
        {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = key;
        x->numKeys++;
    }
    else
    {
        while (i >= 0 && key < x->keys[i])
            i--;
        i++;
        if (x->children[i]->numKeys == MAX)
        {
            splitChild(x, i, x->children[i]);
            if (key > x->keys[i])
                i++;
        }
        insertNonFull(x->children[i], key);
    }
}

// Thêm một giá trị
Node *insert(Node *root, int key)
{
    if (!root)
    {
        root = newNode(true);
        root->keys[0] = key;
        root->numKeys = 1;
        return root;
    }

    if (root->numKeys == MAX)
    {
        Node *s = newNode(false);
        s->children[0] = root;
        splitChild(s, 0, root);
        insertNonFull(s, key);
        return s;
    }
    else
    {
        insertNonFull(root, key);
        return root;
    }
}

// Gộp các nút con trong quá trinh xoa
Node *merge(Node *x, int idx)
{
    Node *child = x->children[idx];
    Node *sibling = x->children[idx + 1];

    child->keys[1] = x->keys[idx];
    child->keys[2] = sibling->keys[0];

    if (!child->isLeaf)
    {
        child->children[2] = sibling->children[0];
        child->children[3] = sibling->children[1];
    }

    for (int i = idx + 1; i < x->numKeys; ++i)
        x->keys[i - 1] = x->keys[i];

    for (int i = idx + 2; i <= x->numKeys; ++i)
        x->children[i - 1] = x->children[i];

    child->numKeys = 3;
    x->numKeys--;

    delete sibling;
    return x;
}

// Mượn từ nút anh em trước
void borrowFromPrev(Node *x, int idx)
{
    Node *child = x->children[idx];
    Node *sibling = x->children[idx - 1];

    for (int i = child->numKeys - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->isLeaf)
    {
        for (int i = child->numKeys; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = x->keys[idx - 1];

    if (!child->isLeaf)
        child->children[0] = sibling->children[sibling->numKeys];

    x->keys[idx - 1] = sibling->keys[sibling->numKeys - 1];

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

// Mượn từ nút anh em sau
void borrowFromNext(Node *x, int idx)
{
    Node *child = x->children[idx];
    Node *sibling = x->children[idx + 1];

    child->keys[child->numKeys] = x->keys[idx];

    if (!child->isLeaf)
        child->children[child->numKeys + 1] = sibling->children[0];

    x->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->numKeys; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->isLeaf)
    {
        for (int i = 1; i <= sibling->numKeys; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->numKeys += 1;
    sibling->numKeys -= 1;
}

// Xoa khoa từ nút lá
void removeFromLeaf(Node *x, int idx)
{
    for (int i = idx + 1; i < x->numKeys; ++i)
        x->keys[i - 1] = x->keys[i];
    x->numKeys--;
}

// Xoa khoa từ nút khong phải lá
void removeFromNonLeaf(Node *x, int idx)
{
    int key = x->keys[idx];

    if (x->children[idx]->numKeys >= 2)
    {
        Node *cur = x->children[idx];
        while (!cur->isLeaf)
            cur = cur->children[cur->numKeys];
        x->keys[idx] = cur->keys[cur->numKeys - 1];
        x->children[idx] = deleteNode(x->children[idx], x->keys[idx]);
    }
    else if (x->children[idx + 1]->numKeys >= 2)
    {
        Node *cur = x->children[idx + 1];
        while (!cur->isLeaf)
            cur = cur->children[0];
        x->keys[idx] = cur->keys[0];
        x->children[idx + 1] = deleteNode(x->children[idx + 1], x->keys[idx]);
    }
    else
    {
        merge(x, idx);
        x->children[idx] = deleteNode(x->children[idx], key);
    }
}

// Hàm hỗ trợ xoa
Node *deleteNode(Node *x, int key)
{
    int idx = 0;
    while (idx < x->numKeys && key > x->keys[idx])
        idx++;

    if (idx < x->numKeys && x->keys[idx] == key)
    {
        if (x->isLeaf)
            removeFromLeaf(x, idx);
        else
            removeFromNonLeaf(x, idx);
    }
    else
    {
        if (x->isLeaf)
            return x;

        bool flag = (idx == x->numKeys);
        if (x->children[idx]->numKeys == 1)
        {
            if (idx > 0 && x->children[idx - 1]->numKeys >= 2)
                borrowFromPrev(x, idx);
            else if (idx < x->numKeys && x->children[idx + 1]->numKeys >= 2)
                borrowFromNext(x, idx);
            else
            {
                if (idx != x->numKeys)
                    merge(x, idx);
                else
                    merge(x, idx - 1), idx--;
            }
        }

        x->children[idx] = deleteNode(x->children[idx], key);
    }
    return x;
}

// Điểm vào để xoa
Node *deleteKey(Node *root, int key)
{
    if (!root)
        return nullptr;

    root = deleteNode(root, key);

    if (root->numKeys == 0)
    {
        Node *tmp = root;
        if (!root->isLeaf)
            root = root->children[0];
        else
            root = nullptr;
        delete tmp;
    }

    return root;
}

// Hàm chính
int main()
{
    Node *root = nullptr;
    int values[] = {10, 20, 5, 6, 12, 30, 7, 17};
    for (int val : values)
        root = insert(root, val);

    cout << "Duyet theo level sau khi them:\n";
    LevelOrder(root);

    cout << "\nDuyet LNR: ";
    LNR(root);
    cout << "\nDuyet NLR: ";
    NLR(root);
    cout << "\nDuyet LRN: ";
    LRN(root);
    cout << "\n\n";

    int searchVal = 6;
    cout << "Tim kiem " << searchVal << ": ";
    cout << (search(root, searchVal) ? "Tim thay\n" : "Khong tim thay\n");

    root = deleteKey(root, 6);
    cout << "\nSau khi xoa 6:\n";
    LevelOrder(root);

    root = deleteKey(root, 17);
    cout << "\nSau khi xoa 17:\n";
    LevelOrder(root);

    return 0;
}