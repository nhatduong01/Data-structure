/*
Given class BinarySearchTree, you need to finish method find(i) to check whether value i is in the tree or not; 
method sum(l,r) to calculate sum of all all elements v in the tree that has value greater than or equal to l and less than or equal to r.

*/
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <class T>
class BinarySearchTree
{
public:
    class Node;

private:
    Node *root;

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
    }

    class Node
    {
    private:
        T value;
        Node *pLeft, *pRight;
        friend class BinarySearchTree<T>;

    public:
        Node(T value) : value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    Node *addRec(Node *root, T value);
    void add(T value);
    bool find(T i)
    {
        // TODO: return true if value i is in the tree; otherwise, return false.
        return find(this->root, i);
    }
    bool find(Node *_root, T i)
    {
        if (_root == nullptr)
            return false;
        if (_root->value > i)
            return find(_root->pLeft, i);
        else if (_root->value < i)
            return find(_root->pRight, i);
        else
        {
            return true;
        }
    }
    T Sum(Node *_root, int l, int r)
    {
        if (_root == nullptr)
            return 0;
        else
        {
            if (_root->value <= r && _root->value >= l)
                return _root->value + Sum(_root->pLeft, l, r) + Sum(_root->pRight, l, r);
            else if (_root->value > r)
            {
                return Sum(_root->pLeft, l, r);
            }
            else if (_root->value < l)
            {
                return Sum(_root->pRight, l, r);
            }
        }
    }
    T sum(T l, T r)
    {
        // TODO: return the sum of all element in the tree has value in range [l,r].
        T sum = 0;
        Node *temp = this->root;
        if (temp->value < l)
        {
            while (temp->value < l && temp)
            {
                temp = temp->pRight;
            }
        }
        else if (temp->value > r)
        {
            while (temp->value > r && temp)
            {
                temp = temp->pLeft;
            }
        }
        if (temp)
        {
            sum += temp->value;
            sum += Sum(temp->pLeft, l, r) + Sum(temp->pRight, l, r);
        }
        return sum;
    }
};
int main()
{
    BinarySearchTree<int> bst;
    for (int i = 0; i < 10; ++i)
    {
        bst.add(i);
    }
    //cout << bst.find(7) << endl;
    //cout << bst.sum(0, 4) << endl;
    return 0;
}