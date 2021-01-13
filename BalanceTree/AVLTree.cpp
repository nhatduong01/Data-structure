#include <iostream>
#include <queue>
#include <math.h>
using namespace std;
int max(int a, int b)
{
    return a > b ? a : b;
}
void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}

void printInteger(int &n)
{
    cout << n << " ";
}

template <class T>
class AVLTree
{
public:
    class Node;
    AVLTree() { this->root = nullptr; }

private:
    Node *root;

protected:
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

public:
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure()
    {
        int height = this->getHeight();
        if (this->root == NULL)
        {
            cout << "NULL\n";
            return;
        }
        queue<Node *> q;
        q.push(root);
        Node *temp;
        int count = 0;
        int maxNode = 1;
        int level = 0;
        int space = pow(2, height);
        printNSpace(space / 2);
        while (!q.empty())
        {
            temp = q.front();
            q.pop();
            if (temp == NULL)
            {
                cout << " ";
                q.push(NULL);
                q.push(NULL);
            }
            else
            {
                cout << temp->data;
                q.push(temp->pLeft);
                q.push(temp->pRight);
            }
            printNSpace(space);
            count++;
            if (count == maxNode)
            {
                cout << endl;
                count = 0;
                maxNode *= 2;
                level++;
                space /= 2;
                printNSpace(space / 2);
            }
            if (level == height)
                return;
        }
    }
    void RotateLeft(Node *&_root)
    {
        Node *temp = _root->pRight;
        _root->pRight = temp->pLeft;
        temp->pLeft = _root;
        _root->height = max(Height(_root->pLeft), Height(_root->pRight)) + 1;
        temp->height = max(Height(temp->pRight), Height(temp->pLeft)) + 1;
        _root = temp;
    }
    void RotateRight(Node *&_root)
    {
        Node *temp = _root->pLeft;
        _root->pLeft = temp->pRight;
        temp->pRight = _root;
        _root->height = max(Height(_root->pLeft), Height(_root->pRight)) + 1;
        temp->height = max(Height(temp->pRight), Height(temp->pLeft)) + 1;
        _root = temp;
    }
    void insert(const T &value)
    {
        insert(this->root, value);
    }
    void insert(Node *&root, const T &value)
    {

        if (root == nullptr)
        {
            Node *temp = new Node(value);
            root = temp;
            return;
        }
        else
        {
            if (value < root->data)
            {

                insert(root->pLeft, value);
            }
            else
            {
                insert(root->pRight, value);
            }
        }
        root->height = max(Height(root->pLeft), Height(root->pRight)) + 1;
        SeflBalancing(root);
    }
    /*int Height(Node *_root)
    {
        if (_root == nullptr)
            return 0;
        else
        {
            int pLeft = 0;
            int pRight = 0;
            pLeft = 1 + Height(_root->pLeft);
            pRight = 1 + Height(_root->pRight);
            return pLeft < pRight ? pRight : pLeft;
        }
    }*/
    int Height(Node *_root)
    {
        if (_root == nullptr)
            return 0;
        else
        {
            return _root->height;
        }
    }
    int BalanceFactor(Node *_root)
    {
        if (_root)
        {
            return Height(_root->pLeft) - Height(_root->pRight);
        }
        return 0;
    }
    void SeflBalancing(Node *&_root)
    {
        if (!_root)
            return;
        if (BalanceFactor(_root) > 1)
        {
            if (BalanceFactor(_root->pLeft) >= 0)
            {
                RotateRight(_root);
            }
            else if (BalanceFactor(_root->pLeft) <= -1)
            {
                RotateLeft(_root->pLeft);
                RotateRight(_root);
            }
            /*else if (BalanceFactor(_root->pLeft) == 0)
            {
                RotateRight(_root);
            }*/
        }
        else if (BalanceFactor(_root) < -1)
        {
            if (BalanceFactor(_root->pRight) >= 1)
            {
                RotateRight(_root->pRight);
                RotateLeft(_root);
            }
            else if (BalanceFactor(_root->pRight) <= 0)
            {
                RotateLeft(_root);
            }
            /*else if (BalanceFactor(_root->pRight) == 0)
            {
                RotateLeft(_root);
            }*/
        }
    }
    void remove(const T &value)
    {
        remove(this->root, value);
    }
    void remove(Node *&root, const T &value)
    {
        if (root == nullptr)
            return;
        else
        {
            if (value < root->data)
            {
                remove(root->pLeft, value);
            }
            else if (value > root->data)
            {
                remove(root->pRight, value);
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
                    T temp = getGreatestLeft(root->pLeft);
                    root->data = temp;
                    remove(root->pLeft, temp);
                }
            }
            if (root)
                root->height = max(Height(root->pLeft), Height(root->pRight)) + 1;
            SeflBalancing(root);
        }
    }
    T getGreatestLeft(Node *root)
    {
        if (root->pRight)
            return getGreatestLeft(root->pRight);
        else
        {
            return root->data;
        }
    }
    void printInorder()
    {
        printInorder(root);
    }
    void printInorder(Node *root)
    {
        if (root == nullptr)
            return;
        printInorder(root->pLeft);
        cout << root->data << " ";
        printInorder(root->pRight);
    }
    bool search(const T &key, Node *root)
    {
        if (root == nullptr)
            return false;
        else
        {
            if (key < root->data)
                return search(key, root->pLeft);
            else if (key > root->data)
                return search(key, root->pRight);
            else
            {
                return true;
            }
        }
    }
    bool search(const T &key)
    {
        return search(key, this->root);
    }
    class Node
    {
    private:
        T data;
        Node *pLeft, *pRight;
        friend class AVLTree<T>;
        int height;

    public:
        Node(T value) : data(value), pLeft(NULL), pRight(NULL), height(1) {}
        ~Node() {}
    };
};
int main()
{

    AVLTree<int> avl;
    int arr[] = {10, 52, 98, 32, 68, 92, 48, 13, 42, 63, 99, 100, 50, 40, 12, 11, 9, 0, 1, 3, 7};
    for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    {
        avl.insert(arr[i]);
    }
    avl.printTreeStructure();
    avl.remove(52);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(92);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(50);
    cout << endl;
    avl.printTreeStructure();
    cout << "\n Big test" << endl;
    for (int i = 0; i < 10; i++)
    {
        avl.remove(arr[i]);
        cout << endl;
        avl.printTreeStructure();
    }
    cout << "Out loop" << endl;
    avl.remove(99);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(40);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(7);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(1);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(0);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(3);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(11);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(9);
    cout << endl;
    avl.printTreeStructure();
    avl.remove(12);
    cout << endl;
    avl.printTreeStructure();
    system("pause");
    return 0;
}