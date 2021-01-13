/*
Given a Binary tree, the task is to calculate the diameter of the tree. 
The diameter of the tree is the maximum distance between two node on the tree.
Your task is to complete the diameter function. You can write one ore more function to help you complete this task.
*/
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
#define SEPARATOR "#<ab@17943918#@>#"
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
        int l = (int)posFromRoot.length();
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
    int getDiameter()
    {
        return getDiameter(root);
    }
    int getDiameter(Node *root)
    {
        //TODO
        if (root == NULL)
            return 0;

        // get the getHeigth of left and right sub-trees
        int lheight = getHeigth(root->pLeft);
        int rheight = getHeigth(root->pRight);

        // get the diameter of left and right sub-trees
        int ldiameter = getDiameter(root->pLeft);
        int rdiameter = getDiameter(root->pRight);

        // Return max of following three
        // 1) Diameter of left subtree
        // 2) Diameter of right subtree
        // 3) getHeigth of left subtree + getHeigth of right subtree + 1
        return max(lheight + rheight + 1,
                   max(ldiameter, rdiameter));
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
};