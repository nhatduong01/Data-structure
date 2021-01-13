/*
Given class BinaryTree, you need to finish methods getHeight(), preOrder(), inOrder(), postOrder().
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

public:
    BinaryTree() : root(nullptr) {}
    ~BinaryTree()
    {
        // You have to delete all Nodes in BinaryTree. However in this task, you can ignore it.
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
    // STUDENT ANSWER BEGIN
    int getHeight(Node *_root)
    {
        if (_root == nullptr)
            return 0;
        else
        {
            int a = getHeight(_root->pLeft);
            int b = getHeight(_root->pRight);
            return 1 + ((a > b) ? a : b);
        }
    }
    int getHeight()
    {
        // TODO: return height of the binary tree.
        return getHeight(this->root);
    }
    string preOrder(Node *_root)
    {
        if (_root)
        {
            stringstream result;
            //result << _root->value << " " << preOrder(_root->pLeft) << " " << preOrder(_root->pRight);
            result << _root->value;
            if (_root->pLeft)
                result << " " << preOrder(_root->pLeft);
            if (_root->pRight)
                result << " " << preOrder(_root->pRight);
            return result.str();
        }
        else
        {
            return "";
        }
    }
    string preOrder()
    {
        // TODO: return the sequence of values of nodes in pre-order.
        return preOrder(this->root);
    }
    string inOrder(Node *_root)
    {
        if (_root)
        {
            stringstream result;
            //result << inOrder(_root->pLeft) << " " << _root->value << " " << inOrder(_root->pRight);
            if (_root->pLeft)
                result << inOrder(_root->pLeft) << " ";
            result << _root->value;
            if (_root->pRight)
                result << " " << inOrder(_root->pRight);
            return result.str();
        }
        return "";
    }
    string inOrder()
    {
        // TODO: return the sequence of values of nodes in pre-order.
        return inOrder(this->root);
    }
    string postOrder(Node *_root)
    {
        if (_root)
        {
            stringstream result;
            //result << postOrder(_root->pLeft) << " " << postOrder(_root->pRight) << " " << _root->value;
            if (_root->pLeft)
                result << postOrder(_root->pLeft) << " ";
            if (_root->pRight)
                result << postOrder(_root->pRight) << " ";
            result << _root->value;
            return result.str();
        }
        return "";
    }
    string postOrder()
    {
        // TODO: return the sequence of values of nodes in pre-order.
        return postOrder(this->root);
    }
    // STUDENT ANSWER END
};
int main()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);  // Add to root
    binaryTree.addNode("L", 3, 6); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node

    cout << binaryTree.getHeight() << endl;
    cout << binaryTree.preOrder() << endl;
    cout << binaryTree.inOrder() << endl;
    cout << binaryTree.postOrder() << endl;
    return 0;
}