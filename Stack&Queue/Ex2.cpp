#include <iostream>
using namespace std;
template <class T>
class DLinkedList
{
public:
    class Node; //forward declaration
protected:
    Node *head;
    Node *tail;
    int count;

public:
    DLinkedList();
    ~DLinkedList();
    void add(const T &e);
    void add(int index, const T &e);
    T removeAt(int index);
    bool removeItem(const T &removeItem);
    bool empty();
    int size();
    void clear();
    T get(int index);
    void set(int index, const T &e);
    int indexOf(const T &item);
    bool contains(const T &item);
};
template <class T>
class Stack
{
protected:
    DLinkedList<T> list;

public:
    Stack() {}
    void push(T item);
    T pop();
    T top();
    bool empty();
    int size();
    void clear();
};
template <class T>
void Stack<T>::push(T item)
{
    list.add(item);
}
template <class T>
T Stack<T>::pop()
{
    int idx = list.size();
    T temp = list.get(idx - 1);
    list.removeAt(idx - 1);
    return temp;
}
template <class T>
T Stack<T>::top()
{
    int inx = list.size();
    return list.get(inx - 1);
}
template <class T>
bool Stack<T>::empty()
{
    return list.empty() == true ? true : false;
}
template <class T>
int Stack<T>::size()
{
    return list.size();
}
template <class T>
void Stack<T>::clear()
{
    list.clear();
}
