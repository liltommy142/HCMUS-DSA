#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một nút trong danh sách liên kết
struct Node
{
    int data;
    Node *next;
};

// Hàm thêm một nút vào đầu danh sách
void addHead(Node *&head, int value)
{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

// Hàm thêm một nút vào cuối danh sách
void addTail(Node *&head, int value)
{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

// Hàm duyệt và in danh sách
void traverse(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Hàm đếm số nút trong danh sách
int countNodes(Node *head)
{
    int count = 0;
    Node *temp = head;
    while (temp != nullptr)
    {
        count++;
        temp = temp->next;
    }
    return count;
}

// Hàm xóa nút đầu tiên của danh sách
void removeHead(Node *&head)
{
    if (head != nullptr)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

// Hàm xóa nút cuối cùng của danh sách
void removeTail(Node *&head)
{
    if (head == nullptr)
        return;

    if (head->next == nullptr)
    {
        delete head;
        head = nullptr;
    }
    else
    {
        Node *temp = head;
        while (temp->next->next != nullptr)
        {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
    }
}

// Hàm xóa các nút trùng lặp trong danh sách
void removeDuplicates(Node *head)
{
    Node *current = head;
    while (current != nullptr && current->next != nullptr)
    {
        Node *runner = current;
        while (runner->next != nullptr)
        {
            if (runner->next->data == current->data)
            {
                Node *temp = runner->next;
                runner->next = runner->next->next;
                delete temp;
            }
            else
            {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

int main()
{
    Node *head = nullptr;

    // Thêm các giá trị vào danh sách
    addTail(head, 10); // Thêm giá trị 10 vào cuối danh sách
    addTail(head, 20); // Thêm giá trị 20 vào cuối danh sách
    addTail(head, 20); // Thêm giá trị 20 vào cuối danh sách (trùng lặp)
    addTail(head, 30); // Thêm giá trị 30 vào cuối danh sách
    addHead(head, 5);  // Thêm giá trị 5 vào đầu danh sách

    cout << "Initial list: "; // In danh sách ban đầu
    traverse(head);           // Duyệt và in danh sách

    cout << "Total nodes: " << countNodes(head) << endl; // In tổng số nút trong danh sách

    cout << "Removing head...\n"; // Thông báo xóa nút đầu
    removeHead(head);             // Xóa nút đầu
    traverse(head);               // Duyệt và in danh sách sau khi xóa nút đầu

    cout << "Removing tail...\n"; // Thông báo xóa nút cuối
    removeTail(head);             // Xóa nút cuối
    traverse(head);               // Duyệt và in danh sách sau khi xóa nút cuối

    cout << "Removing duplicates...\n"; // Thông báo xóa các nút trùng lặp
    removeDuplicates(head);             // Xóa các nút trùng lặp
    traverse(head);                     // Duyệt và in danh sách sau khi xóa các nút trùng lặp

    return 0; // Kết thúc chương trình
}