/*
NOTE :Given class BinaryTree, you need to finish methods isBST() to determine if a tree is a binary search tree (BST)
*/
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template <class K, class V>
class BinaryTree
{
public:
    class Node;

private:
    Node *root;
    void clear(Node *_root)
    {
        if (_root)
        {
            clear(_root->pLeft);
            clear(_root->pRight);
            delete _root;
        }
    }

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
        clear(this->root);
    }
    class Node
    {
    private:
        K key;
        V value;
        Node *pLeft, *pRight;
        friend class BinaryTree<K, V>;

    public:
        Node(K key, V value) : key(key), value(value), pLeft(NULL), pRight(NULL) {}
        ~Node() {}
    };
    void addNode(string posFromRoot, K key, V value)
    {
        if (posFromRoot == "")
        {
            this->root = new Node(key, value);
            return;
        }
        Node *walker = this->root;
        int l = posFromRoot.length();
        for (int i = 0; i < l - 1; i++)
        {
            if (!walker)
                return;
            if (posFromRoot[i] == 'L')
                walker = walker->pLeft;
            if (posFromRoot[i] == 'R')
                walker = walker->pRight;
        }
        if (posFromRoot[l - 1] == 'L')
            walker->pLeft = new Node(key, value);
        if (posFromRoot[l - 1] == 'R')
            walker->pRight = new Node(key, value);
    }
    void clear()
    {
        clear(this->root);
    }
    bool isBST()
    {
        // TODO: return true if a tree is a BST; otherwise, return false.
        return isBST(this->root);
    }
    bool isBST(Node *root)
    {
        if (root == nullptr)
            return true;
        bool left = true, right = true;
        if (root->pLeft)
        {
            if (root->pLeft->value > root->value)
                return false;
            left = isBST(root->pLeft);
        }
        if (root->pRight)
        {
            if (root->pRight->value < root->value)
                return false;
            right = isBST(root->pRight);
        }
        if (left && right)
            return true;
        else
        {
            return false;
        }
    }

    // STUDENT ANSWER BEGIN

    // STUDENT ANSWER END
};