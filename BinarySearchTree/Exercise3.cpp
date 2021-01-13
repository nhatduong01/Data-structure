/*
Given a Binary tree, the task is to traverse all the nodes of the tree using Breadth First Search algorithm. 
Print the order of visited nodes (has no blank space at the end)
*/
#include <iostream>
#include <string>
#include <queue>
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
    void BFS()
    {
        int height = getHeigth(this->root);
        for (int i = 1; i <= height; i++)
            BFS(root, i);
    }
    void BFS(Node *root, int level)
    {
        if (root == nullptr)
            return;
        if (level == 1)
            cout << root->value << " ";
        else if (level > 1)
        {
            BFS(root->pLeft, level - 1);
            BFS(root->pRight, level - 1);
        }
    }
    int getHeigth(Node *root)
    {
        if (root == nullptr)
            return 0;
        else
        {
            int l = 1 + getHeigth(root->pLeft);
            int r = 1 + getHeigth(root->pRight);
            return l > r ? l : r;
        }
    }

    // STUDENT ANSWER BEGIN
    // STUDENT ANSWER END
};
int main()
{
    BinaryTree<int, int> binaryTree;
    binaryTree.addNode("", 2, 4);  // Add to root
    binaryTree.addNode("L", 3, 6); // Add to root's left node
    binaryTree.addNode("R", 5, 9); // Add to root's right node
    binaryTree.BFS();
    return 0;
}