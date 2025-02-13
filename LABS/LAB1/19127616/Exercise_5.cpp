#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một nút trong ngăn xếp
struct Node
{
    int data;
    Node *next;
};

// Hàm duyệt và in ngăn xếp
void traverse(Node *top)
{
    Node *temp = top;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Lớp Stack (Ngăn xếp)
class Stack
{
private:
    Node *topNode; // Con trỏ đến nút đầu của ngăn xếp

public:
    // Hàm khởi tạo
    Stack()
    {
        topNode = nullptr;
    }

    // Hàm hủy
    ~Stack()
    {
        while (!isEmpty())
        {
            pop();
        }
    }

    // Hàm thêm một phần tử vào ngăn xếp
    void push(int value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = topNode;
        topNode = newNode;
    }

    // Hàm lấy một phần tử ra khỏi ngăn xếp
    void pop()
    {
        if (topNode == nullptr)
        {
            cout << "Stack is empty!" << endl;
            return;
        }
        Node *temp = topNode;
        topNode = topNode->next;
        delete temp;
    }

    // Hàm lấy giá trị của phần tử đầu ngăn xếp
    int top()
    {
        if (topNode == nullptr)
        {
            cout << "Stack is empty!" << endl;
            return -1; // Trả về giá trị lỗi
        }
        return topNode->data;
    }

    // Hàm kiểm tra ngăn xếp có rỗng không
    bool isEmpty()
    {
        return topNode == nullptr;
    }

    // Hàm hiển thị nội dung ngăn xếp
    void display()
    {
        traverse(topNode);
    }
};

int main()
{
    Stack stack;

    // Minh họa các thao tác trên ngăn xếp
    stack.push(10); // Thêm giá trị 10 vào ngăn xếp
    stack.push(20); // Thêm giá trị 20 vào ngăn xếp
    stack.push(30); // Thêm giá trị 30 vào ngăn xếp

    cout << "Stack after pushes: "; // In ngăn xếp sau khi thêm các phần tử
    stack.display();                // Hiển thị nội dung ngăn xếp

    cout << "Top of stack: " << stack.top() << endl; // In giá trị đầu ngăn xếp

    stack.pop();                 // Lấy phần tử ra khỏi ngăn xếp
    cout << "Stack after pop: "; // In ngăn xếp sau khi lấy phần tử ra
    stack.display();             // Hiển thị nội dung ngăn xếp

    cout << "Top of stack: " << stack.top() << endl; // In giá trị đầu ngăn xếp

    stack.pop(); // Lấy phần tử ra khỏi ngăn xếp
    stack.pop(); // Lấy phần tử ra khỏi ngăn xếp
    stack.pop(); // Thử lấy phần tử ra khỏi ngăn xếp khi ngăn xếp rỗng

    return 0; // Kết thúc chương trình
}