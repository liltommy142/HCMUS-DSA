#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct hashTable
{
    struct hashNode
    {
        string key;
        int value;
        hashNode *next;                                                // Pointer to next node in the chain
        hashNode(string k, int v) : key(k), value(v), next(nullptr) {} // Constructor with next initialized to nullptr
    };

    int capacity;
    vector<hashNode *> table; // Vector to store heads of linked lists

    void init(unsigned int hashSize)
    {
        capacity = hashSize;
        table.resize(capacity, nullptr); // Initialize the table with nullptrs
    }

    void release()
    {
        for (int i = 0; i < capacity; i++)
        {
            hashNode *current = table[i];
            while (current != nullptr)
            {
                hashNode *temp = current;
                current = current->next;
                delete temp; // Delete each node in the chain
            }
            table[i] = nullptr;
        }
        table.clear();
    }

    unsigned int hashFunction(string key)
    {
        const int p = 31;
        const int m = 1e9 + 9;
        unsigned long long hashValue = 0;
        unsigned long long p_pow = 1;

        for (char c : key)
        {
            hashValue = (hashValue + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hashValue % capacity;
    }

    void add(string key, int value)
    {
        unsigned int index = hashFunction(key);

        // Check if key already exists
        hashNode *current = table[index];
        while (current != nullptr)
        {
            if (current->key == key)
            {
                current->value = value; // Update existing value
                return;
            }
            current = current->next;
        }

        // Key not found, add new node at the beginning of the list
        hashNode *newNode = new hashNode(key, value);
        newNode->next = table[index];
        table[index] = newNode;
    }

    int *searchValue(string key)
    {
        unsigned int index = hashFunction(key);

        hashNode *current = table[index];
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return &(current->value); // Return pointer to value if found
            }
            current = current->next;
        }

        return nullptr; // Key not found
    }

    void removeKey(string key)
    {
        unsigned int index = hashFunction(key);

        hashNode *current = table[index];
        hashNode *prev = nullptr;

        // Search for the key
        while (current != nullptr && current->key != key)
        {
            prev = current;
            current = current->next;
        }

        // If key not found
        if (current == nullptr)
            return;

        // If key found at head
        if (prev == nullptr)
        {
            table[index] = current->next;
        }
        else
        {
            // If key found in the middle or end
            prev->next = current->next;
        }

        delete current; // Free memory
    }
};

int main()
{
    hashTable ht;
    ht.init(10); // Initialize hash table with capacity 10

    // Add key-value pairs
    ht.add("MacOS", 5);
    ht.add("Windows", 10);
    ht.add("Linux", 15);
    ht.add("Tommy", 20);
    ht.add("John", 25);

    // Search for values
    int *val = ht.searchValue("MacOS");
    if (val)
        cout << "Value of MacOS: " << *val << endl;
    else
        cout << "MacOS not found" << endl;

    val = ht.searchValue("grape");
    if (val)
        cout << "Value of grape: " << *val << endl;
    else
        cout << "grape not found" << endl;

    val = ht.searchValue("John");
    if (val)
        cout << "Value of John: " << *val << endl;
    else
        cout << "John not found" << endl;

    // Remove a key
    ht.removeKey("Windows");
    val = ht.searchValue("Windows");
    if (!val)
        cout << "Windows not found" << endl;

    // Add a new key-value pair
    ht.add("kiwi", 30);
    val = ht.searchValue("kiwi");
    if (val)
        cout << "Value of kiwi: " << *val << endl;

    // Update an existing key-value pair
    ht.add("MacOS", 50);
    val = ht.searchValue("MacOS");
    if (val)
        cout << "Updated value of MacOS: " << *val << endl;

    // Release memory and clear the table
    ht.release();

    return 0;
}