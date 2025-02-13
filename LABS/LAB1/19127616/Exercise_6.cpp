#include <iostream>
using namespace std;

// Định nghĩa cấu trúc của một nút trong hàng đợi
struct Node
{
    int data;
    Node *next;
};

// Hàm duyệt và in hàng đợi
void traverse(Node *front)
{
    Node *temp = front;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Lớp Queue (Hàng đợi)
class Queue
{
private:
    Node *frontNode; // Con trỏ đến nút đầu của hàng đợi
    Node *rearNode;  // Con trỏ đến nút cuối của hàng đợi

public:
    // Hàm khởi tạo
    Queue()
    {
        frontNode = nullptr;
        rearNode = nullptr;
    }

    // Hàm hủy
    ~Queue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    // Hàm thêm một phần tử vào hàng đợi
    void enqueue(int value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;

        if (rearNode == nullptr)
        {
            frontNode = newNode;
            rearNode = newNode;
        }
        else
        {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    // Hàm lấy một phần tử ra khỏi hàng đợi
    void dequeue()
    {
        if (frontNode == nullptr)
        {
            cout << "Queue is empty!" << endl;
            return;
        }
        Node *temp = frontNode;
        frontNode = frontNode->next;
        if (frontNode == nullptr)
        {
            rearNode = nullptr;
        }
        delete temp;
    }

    // Hàm lấy giá trị của phần tử đầu hàng đợi
    int front()
    {
        if (frontNode == nullptr)
        {
            cout << "Queue is empty!" << endl;
            return -1; // Trả về giá trị lỗi
        }
        return frontNode->data;
    }

    // Hàm kiểm tra hàng đợi có rỗng không
    bool isEmpty()
    {
        return frontNode == nullptr;
    }

    // Hàm hiển thị nội dung hàng đợi
    void display()
    {
        traverse(frontNode);
    }
};

int main()
{
    Queue queue;

    // Minh họa các thao tác trên hàng đợi
    queue.enqueue(10); // Thêm giá trị 10 vào hàng đợi
    queue.enqueue(20); // Thêm giá trị 20 vào hàng đợi
    queue.enqueue(30); // Thêm giá trị 30 vào hàng đợi

    cout << "Queue after enqueues: "; // In hàng đợi sau khi thêm các phần tử
    queue.display();                  // Hiển thị nội dung hàng đợi

    cout << "Front of queue: " << queue.front() << endl; // In giá trị đầu hàng đợi

    queue.dequeue();                 // Lấy phần tử ra khỏi hàng đợi
    cout << "Queue after dequeue: "; // In hàng đợi sau khi lấy phần tử ra
    queue.display();                 // Hiển thị nội dung hàng đợi

    cout << "Front of queue: " << queue.front() << endl; // In giá trị đầu hàng đợi

    queue.dequeue(); // Lấy phần tử ra khỏi hàng đợi
    queue.dequeue(); // Lấy phần tử ra khỏi hàng đợi
    queue.dequeue(); // Thử lấy phần tử ra khỏi hàng đợi khi hàng đợi rỗng

    return 0; // Kết thúc chương trình
}