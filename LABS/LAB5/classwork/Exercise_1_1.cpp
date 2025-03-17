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
        hashNode(string k, int v) : key(k), value(v) {} // Constructor to initialize key and value
    };

    int capacity;
    vector<hashNode *> table; // Vector to store pointers to hashNode

    void init(unsigned int hashSize)
    {
        capacity = hashSize;
        table.resize(capacity, nullptr); // Initialize the table with nullptrs
    }

    void release()
    {
        for (int i = 0; i < capacity; i++)
        {
            if (table[i] != nullptr)
            {
                delete table[i]; // Delete each node to free memory
                table[i] = nullptr;
            }
        }
        table.clear();
        table.resize(capacity, nullptr);
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
        unsigned int originalIndex = index;
        while (table[index] != nullptr && table[index]->key != key)
        {
            index = (index + 1) % capacity;
            if (index == originalIndex)
                return; // Full table
        }
        if (table[index] != nullptr)
        {
            table[index]->value = value; // Update existing
        }
        else
        {
            table[index] = new hashNode(key, value); // Create a new node
        }
    }

    int *searchValue(string key)
    {
        unsigned int index = hashFunction(key);
        unsigned int originalIndex = index;
        while (table[index] != nullptr)
        {
            if (table[index]->key == key)
            {
                return &(table[index]->value); // Return the value if found
            }
            index = (index + 1) % capacity;
            if (index == originalIndex)
                break;
        }
        return nullptr; // Return nullptr if not found
    }

    void removeKey(string key)
    {
        unsigned int index = hashFunction(key);
        unsigned int originalIndex = index;
        while (table[index] != nullptr)
        {
            if (table[index]->key == key)
            {
                delete table[index];    // Delete the node
                table[index] = nullptr; // Set the slot to nullptr
                return;
            }
            index = (index + 1) % capacity;
            if (index == originalIndex)
                break;
        }
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
