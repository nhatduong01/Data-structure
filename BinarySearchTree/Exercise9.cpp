/*
Given a Binary tree, the task is to calculate the sum of leaf nodes. (Leaf nodes are nodes which have no children)
*/
#include <iostream>
#include <string>
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
    //Helping functions
    int sumOfLeafs(Node *_root)
    {
        if (_root == nullptr)
            return 0;
        if (_root->pLeft == nullptr && _root->pRight == nullptr)
            return _root->value;
        if (_root->pLeft && _root->pRight)
            return sumOfLeafs(_root->pLeft) + sumOfLeafs(_root->pRight);
        else if (_root->pLeft)
            return sumOfLeafs(_root->pLeft);
        else
        {
            return sumOfLeafs(_root->pRight);
        }
    }
    int sumOfLeafs()
    {
        //TODO
        return sumOfLeafs(this->root);
    }
};
int main()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);
    cout << binaryTree.sumOfLeafs();
    return 0;
}