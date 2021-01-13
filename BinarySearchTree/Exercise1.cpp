/*
In this question, you have to perform add and delete on binary search tree. Note that:

- When deleting a node which still have 2 children, take the inorder successor (smallest node of the right sub tree of that node) to replace it.

- When adding a node which has the same value as parent node, add it in the left sub tree.

Your task is to implement two functions: add and deleteNode. You could define one or more functions to achieve this task.
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
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
        clear();
    }

    //Helping function

    void add(T value)
    {
        if (!root)
        {
            root = new Node(value);
            return;
        }
        Node *temp = root;
        Node *prev = nullptr;
        while (temp)
        {
            if (value > temp->value)
            {
                prev = temp;
                temp = temp->pRight;
            }
            else
            {
                prev = temp;
                temp = temp->pLeft;
            }
        }
        temp = new Node(value);
        if (value > prev->value)
            prev->pRight = temp;
        else
            prev->pLeft = temp;
    }

    void deleteNode(T value)
    {
        deleteNode(this->root, value);
    }
    void deleteNode(Node *&root, T value)
    {
        if (root)
        {
            if (value < root->value)
            {
                deleteNode(root->pLeft, value);
            }
            else if (value > root->value)
            {
                deleteNode(root->pRight, value);
            }
            else
            {
                if (!root->pRight && !root->pLeft)
                {
                    Node *temp = root;
                    root = nullptr;
                    delete temp;
                }
                else if (!root->pRight)
                {
                    Node *temp = root;
                    root = root->pLeft;
                    delete temp;
                }
                else if (!root->pLeft)
                {
                    Node *temp = root;
                    root = root->pRight;
                    delete temp;
                }
                else
                {
                    T temp = getSmallestRight(root->pRight);
                    root->value = temp;
                    deleteNode(root->pRight, temp);
                }
            }
        }
    }
    T getSmallestRight(Node *root)
    {
        if (root->pLeft)
            return getSmallestRight(root->pLeft);
        else
        {
            return root->value;
        }
    }
    Node *getDeletedNode(Node *root)
    {
        if (root->pLeft)
            return getDeletedNode(root->pLeft);
        else
        {
            return root;
        }
    }

    string inOrderRec(Node *root)
    {
        stringstream ss;
        if (root != nullptr)
        {
            ss << inOrderRec(root->pLeft);
            ss << root->value << " ";
            ss << inOrderRec(root->pRight);
        }
        return ss.str();
    }

    string inOrder()
    {
        return inOrderRec(this->root);
    }
    void clear()
    {
        clear(this->root);
    }
    void clear(Node *root)
    {
        if (root)
        {
            clear(root->pLeft);
            clear(root->pRight);
            delete root;
        }
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
};
int main()
{

    BinarySearchTree<int> bst;
    bst.add(9);
    bst.add(2);
    bst.add(10);
    bst.deleteNode(9);
    cout << bst.inOrder();
}
