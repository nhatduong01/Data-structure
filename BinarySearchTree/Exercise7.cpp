/*
Given class BinarySearchTree, you need to finish method getMin() and getMax() in this question.
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
    // STUDENT ANSWER BEGIN
    T getMin(Node *_root)
    {
        if (_root->pLeft)
            return getMin(_root->pLeft);
        else
        {
            return _root->value;
        }
    }
    T getMin()
    {
        //TODO: return the minimum values of nodes in the tree.
        retrun getMin(this->root);
    }
    T getMax(Node *_root)
    {
        if (_root->pRight)
        {
            retrun getMax(_root->pRight);
        }
        else
        {
            return _root->value;
        }
    }
    T getMax()
    {
        //TODO: return the maximum values of nodes in the tree.
        return getMax(this->root);
    }
    // STUDENT ANSWER END
};