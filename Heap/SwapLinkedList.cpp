#include <iostream>
using namespace std;
struct Node
{
    Node *pNext;
    int data;
    Node()
    {
        pNext = NULL;
    }
    Node(int _data) : data(_data), pNext(NULL) {}
};
struct LinkedList
{
    Node *head;
    Node *current;
    LinkedList()
    {
        current = head = nullptr;
    }
    ~LinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->pNext;
            delete temp;
        }
        current = head = NULL;
    }
    void add(int _value);
    void swap(int, int);
    void print();
    void delete_node(int);
};
void LinkedList::swap(int x, int y)
{
    if (x == y)
        return;
    else
    {
        Node *currX = this->head;
        Node *preX = NULL;
        while (currX && currX->data != x)
        {
            preX = currX;
            currX = currX->pNext;
        }
        Node *currY = this->head;
        Node *preY = NULL;
        while (currY && currY->data != y)
        {
            preY = currY;
            currY = currY->pNext;
        }
        if (!currX || !currY)
        {
            return;
        }
        if (preX == nullptr)
        {
            this->head = currY;
        }
        else
        {
            preX->pNext = currY;
        }
        if (preY == nullptr)
        {
            this->head = currX;
        }
        else
        {
            preY->pNext = currX;
        }
        // Swap the pNext of the two pointers
        Node *temp = currX->pNext;
        currX->pNext = currY->pNext;
        currY->pNext = temp;
    }
}
void LinkedList::add(int _value)
{
    Node *new_node = new Node(_value);
    if (head == nullptr)
        current = head = new_node;
    else
    {
        Node *temp = head;
        Node *prev = nullptr;
        while (temp)
        {
            if (temp->data < new_node->data)
            {
                prev = temp;
                temp = temp->pNext;
            }
            else
            {
                break;
            }
        }
        if (temp == head)
        {
            new_node->pNext = head;
            head = new_node;
            return;
        }
        if (prev->pNext == nullptr)
        {
            prev->pNext = new_node;
        }
        else
        {
            new_node->pNext = prev->pNext;
            prev->pNext = new_node;
        }
    }
}
void LinkedList::delete_node(int _value)
{
    Node *temp = head;
    Node *prev = NULL;
    while (temp)
    {
        if (temp->data != _value)
        {
            prev = temp;
            temp = temp->pNext;
        }
        else
        {
            break;
        }
    }
    if (temp == head)
    {
        head = head->pNext;
        delete temp;
    }
    else
    {
        if (temp)
        {
            prev->pNext = temp->pNext;
            delete temp;
        }
    }
}
void LinkedList::print()
{
    Node *temp = head;
    while (temp)
    {
        cout << temp->data << "\t";
        temp = temp->pNext;
    }
}
int main()
{
    LinkedList test;
    test.add(10);
    test.add(1);
    test.add(20);
    test.add(100);
    test.add(50);
    test.add(-25);
    test.add(0);
    test.print();
    cout << endl;
    cout << "Testing Swapping : \n";
    test.swap(-25, 0);
    test.print();
    cout << endl;
    return 0;
}