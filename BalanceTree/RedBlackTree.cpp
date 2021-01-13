#include <iostream>
#include <queue>
#include <math.h>
using namespace std;
void printNSpace(int n)
{
    for (int i = 0; i < n - 1; i++)
        cout << " ";
}
void printInteger(int &n)
{
    cout << n << " ";
}
enum Color
{
    Red,
    Black
};
struct Node
{
    Color color;
    int key;
    Node *pLeft;
    Node *pRight;
    Node *pParent;
    Node()
    {
        pLeft = pRight = pParent = NULL;
        color = Black;
    }
    Node(int _key)
    {
        key = _key;
        color = Black;
        pLeft = pRight = pParent = NULL;
    }
};
class RedBlackTree
{
    void removeFixup(Node *);
    Node *BiggestLeft(Node *);
    Node *root;
    void remove(Node *&, int);
    void NLR_traverse(Node *_root)
    {
        if (_root)
        {
            cout << _root->key << "_" << _root->color << " ";
            NLR_traverse(_root->pLeft);
            NLR_traverse(_root->pRight);
        }
    }
    void LRN_traverse(Node *_root)
    {
        if (_root)
        {
            LRN_traverse(_root->pLeft);
            LRN_traverse(_root->pRight);
            cout << _root->key << "_" << _root->color << " ";
        }
    }
    void Left_Rotation(Node *);
    void Right_Rotation(Node *);
    void insert(Node *&);
    void InsertFixup(Node *);
    void clear(Node *&root)
    {
        if (root)
        {
            clear(root->pLeft);
            clear(root->pRight);
            delete root;
        }
    }
    int getHeightRec(Node *node)
    {
        if (node == NULL)
            return 0;
        int lh = this->getHeightRec(node->pLeft);
        int rh = this->getHeightRec(node->pRight);
        return (lh > rh ? lh : rh) + 1;
    }

public:
    void remove(int);
    void NLR_traverse()
    {
        NLR_traverse(this->root);
    }
    void LRN_traverse()
    {
        LRN_traverse(this->root);
    }
    int getHeight()
    {
        return this->getHeightRec(this->root);
    }
    void printTreeStructure();
    RedBlackTree()
    {
        root = NULL;
    }
    ~RedBlackTree()
    {
        clear();
    }
    void insert(int _key)
    {
        Node *new_node = new Node(_key);
        insert(new_node);
    }
    void clear()
    {
        clear(this->root);
        this->root = NULL;
    }
};
void RedBlackTree::removeFixup(Node *fixedNode)
{
    while (fixedNode != this->root && fixedNode->color == Black)
    {
        if (fixedNode == fixedNode->pParent->pLeft)
        {
            Node *temp = fixedNode->pParent->pRight;
            if (temp->color == Red)
            // Case 1 we turn to 2, 3, 4
            {
                temp->color = Black;
                fixedNode->pParent->color = Red;
                Left_Rotation(fixedNode->pParent);
                temp = fixedNode->pParent->pRight;
            }
            int a = 0;
            int b = 0;
            if (temp->pRight == nullptr || temp->pRight->color == Black)
                a = 1;
            if (temp->pLeft == nullptr || temp->pLeft->color == Black)
                b = 1;
            if (a && b)
            {
                temp->color = Red;
                fixedNode = fixedNode->pParent;
            }
            else
            {
                if (b == 0 && a == 1)
                // Case 3 we turn to case 4
                {
                    temp->pLeft->color = Black;
                    temp->color = Red;
                    Right_Rotation(temp);
                    temp = fixedNode->pParent->pRight;
                }
                // Case 4
                temp->color = fixedNode->pParent->color;
                fixedNode->pParent->color = Black;
                temp->pRight->color = Black;
                Left_Rotation(fixedNode->pParent);
                fixedNode = this->root;
            }
        }
        else
        {
            Node *temp = fixedNode->pParent->pLeft;
            if (temp->color == Red)
            {
                temp->color = Black;
                fixedNode->pParent->color = Red;
                Right_Rotation(fixedNode->pParent);
                temp = fixedNode->pParent->pLeft;
            }
            int a = 0;
            int b = 0;
            if (temp->pRight == nullptr || temp->pRight->color == Black)
                a = 1;
            if (temp->pLeft == nullptr || temp->pLeft->color == Black)
                b = 1;
            if (b && a)
            {
                temp->color = Red;
                fixedNode = fixedNode->pParent;
            }
            else
            {
                if (b == 1 && a == 0)
                {
                    temp->pRight->color = Black;
                    temp->color = Red;
                    Left_Rotation(temp);
                    temp = fixedNode->pParent->pLeft;
                }
                temp->color = fixedNode->pParent->color;
                fixedNode->pParent->color = Black;
                temp->pLeft->color = Black;
                Right_Rotation(fixedNode->pParent);
                fixedNode = this->root;
            }
        }
    }
    fixedNode->color = Black;
}
Node *RedBlackTree::BiggestLeft(Node *root)
{
    if (root->pRight)
        return BiggestLeft(root->pRight);
    else
    {
        return root;
    }
}
void RedBlackTree::remove(Node *&_root, int _key)
{
    if (_root == nullptr)
        return;
    else
    {
        if (_root->key > _key)
        {
            remove(_root->pLeft, _key);
            return;
        }
        else if (_root->key < _key)
        {
            remove(_root->pRight, _key);
            return;
        }
        else
        {
            if (!_root->pRight && !_root->pLeft)
            //The node have no child
            {
                Node *temp = _root;
                if (temp == this->root)
                {
                    delete temp;
                    this->root = nullptr;
                    _root = nullptr;
                    return;
                }
                if (_root->color == Black)
                {
                    removeFixup(temp);
                }
                if (temp == temp->pParent->pRight)
                {
                    temp->pParent->pRight = nullptr;
                }
                else
                {
                    temp->pParent->pLeft = nullptr;
                }
                _root = nullptr;
                delete temp;
            }
            else if (!_root->pRight)
            {
                Node *temp = _root;
                _root->pLeft->pParent = _root->pParent;
                if (_root->pParent)
                {
                    if (temp->color == Black)
                    {
                        removeFixup(_root->pLeft);
                    }
                    if (_root == _root->pParent->pLeft)
                    {
                        _root->pParent->pLeft = _root->pLeft;
                    }
                    else
                    {
                        _root->pParent->pRight = _root->pLeft;
                    }
                    //_root = _root->pLeft;
                    delete temp;
                }
                else
                {
                    this->root = _root->pLeft;
                    delete temp;
                    removeFixup(_root);
                    return;
                }
            }
            else if (!_root->pLeft)
            {
                Node *temp = _root;
                _root->pRight->pParent = _root->pParent;
                if (_root->pParent)
                {
                    if (temp->color == Black)
                    {
                        removeFixup(_root->pRight);
                    }
                    if (_root == _root->pParent->pLeft)
                    {
                        _root->pParent->pLeft = _root->pRight;
                    }
                    else
                    {
                        _root->pParent->pRight = _root->pRight;
                    }
                    delete temp;
                    //_root = _root->pRight;
                }
                else
                {
                    this->root = _root->pRight;
                    delete temp;
                    removeFixup(_root);
                    return;
                }
                // _root = nullptr;
                // delete temp;
            }
            else
            {
                Node *temp = BiggestLeft(_root->pLeft);
                _root->key = temp->key;
                remove(temp, temp->key);
            }
        }
    }
}
void RedBlackTree::remove(int _key)
{
    remove(this->root, _key);
}
void RedBlackTree::Left_Rotation(Node *_root)
{
    Node *y = _root->pRight;
    _root->pRight = y->pLeft;
    if (y->pLeft != NULL)
    {
        y->pLeft->pParent = _root;
    }
    y->pParent = _root->pParent;
    if (_root->pParent == NULL)
    {
        this->root = y;
    }
    else if (_root == _root->pParent->pLeft)
        _root->pParent->pLeft = y;
    else
    {
        _root->pParent->pRight = y;
    }
    y->pLeft = _root;
    _root->pParent = y;
    //_root = y;
}
void RedBlackTree::Right_Rotation(Node *_root)
{
    Node *y = _root->pLeft;
    _root->pLeft = y->pRight;
    if (y->pRight != NULL)
    {
        y->pRight->pParent = _root;
    }
    y->pParent = _root->pParent;
    if (_root->pParent == NULL)
    {
        this->root = y;
    }
    else if (_root == _root->pParent->pLeft)
        _root->pParent->pLeft = y;
    else
    {
        _root->pParent->pRight = y;
    }
    y->pRight = _root;
    _root->pParent = y;
    //_root = y;
}
void RedBlackTree::insert(Node *&new_node)
{
    Node *prev = NULL;
    Node *temp = this->root;
    while (temp != NULL)
    {
        prev = temp;
        if (new_node->key < temp->key)
            temp = temp->pLeft;
        else
        {
            temp = temp->pRight;
        }
    }
    new_node->pParent = prev;
    if (prev == NULL)
    {
        new_node->color = Black;
        this->root = new_node;
        return;
    }
    else if (new_node->key < prev->key)
        prev->pLeft = new_node;
    else
    {
        prev->pRight = new_node;
    }
    new_node->pLeft = new_node->pRight = NULL;
    new_node->color = Red;
    InsertFixup(new_node);
}
void RedBlackTree::printTreeStructure()
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
            cout << temp->key << "_" << temp->color;
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
void RedBlackTree::InsertFixup(Node *fixed_Node)
{
    while (fixed_Node->pParent && fixed_Node->pParent->color == Red)
    {
        if (fixed_Node->pParent == fixed_Node->pParent->pParent->pLeft)
        {
            Node *temp = fixed_Node->pParent->pParent->pRight;
            if (temp)
            {
                if (temp->color == Red)
                //Case1
                {
                    fixed_Node->pParent->color = Black;
                    temp->color = Black;
                    fixed_Node->pParent->pParent->color = Red;
                    fixed_Node = fixed_Node->pParent->pParent;
                }
                else
                {
                    if (fixed_Node == fixed_Node->pParent->pRight)
                    // Case 2 we rotate to become case 3
                    {
                        fixed_Node = fixed_Node->pParent;
                        Left_Rotation(fixed_Node);
                    }
                    // This is case 3
                    fixed_Node->pParent->color = Black;
                    fixed_Node->pParent->pParent->color = Red;
                    Right_Rotation(fixed_Node->pParent->pParent);
                }
                //The cases are symmetric
            }
            else
            {
                if (fixed_Node == fixed_Node->pParent->pRight)
                // Case 2 we rotate to become case 3
                {
                    fixed_Node = fixed_Node->pParent;
                    Left_Rotation(fixed_Node);
                }
                // This is case 3
                fixed_Node->pParent->color = Black;
                fixed_Node->pParent->pParent->color = Red;
                Right_Rotation(fixed_Node->pParent->pParent);
            }
        }
        else
        {
            Node *temp = fixed_Node->pParent->pParent->pLeft;
            if (temp)
            {
                if (temp->color == Red)
                {
                    fixed_Node->pParent->color = Black;
                    temp->color = Black;
                    fixed_Node->pParent->pParent->color = Red;
                    fixed_Node = fixed_Node->pParent->pParent;
                }
                else
                {
                    if (fixed_Node == fixed_Node->pParent->pLeft)
                    {
                        fixed_Node = fixed_Node->pParent;
                        Right_Rotation(fixed_Node);
                    }
                    fixed_Node->pParent->color = Black;
                    fixed_Node->pParent->pParent->color = Red;
                    Left_Rotation(fixed_Node->pParent->pParent);
                }
            }
            else
            {
                if (fixed_Node == fixed_Node->pParent->pLeft)
                {
                    fixed_Node = fixed_Node->pParent;
                    Right_Rotation(fixed_Node);
                }
                fixed_Node->pParent->color = Black;
                fixed_Node->pParent->pParent->color = Red;
                Left_Rotation(fixed_Node->pParent->pParent);
            }
        }
    }
    this->root->color = Black;
}
int main()
{
    RedBlackTree test_tree;
    for (int i = 1; i <= 20; i++)
        test_tree.insert(i);
    test_tree.printTreeStructure();
    cout << endl;
    test_tree.NLR_traverse();
    for (int i = 1; i <= 10; i++)
        test_tree.remove(i);
    test_tree.printTreeStructure();
    cout << endl;
    test_tree.NLR_traverse();
    for (int i = 1; i <= 10; i++)
        test_tree.insert(i);
    cout << endl;
    test_tree.printTreeStructure();
    cout << endl;
    test_tree.NLR_traverse();
    for (int i = 11; i <= 20; i++)
        test_tree.remove(i);
    cout << endl;
    test_tree.printTreeStructure();
    cout << endl;
    test_tree.NLR_traverse();
    for (int i = 1; i <= 10; i++)
    {
        test_tree.remove(i);
    }
    test_tree.NLR_traverse();
    test_tree.printTreeStructure();
    for (int i = 0; i < 150; i++)
        test_tree.insert(i);
    test_tree.NLR_traverse();
    cout << "\nLast test \n";
    for (int i = 31; i <= 100; i++)
        test_tree.remove(i);
    test_tree.NLR_traverse();
    // RedBlackTree test_tree;
    // test_tree.insert(5);
    // test_tree.insert(11);
    // test_tree.insert(10);
    // test_tree.insert(12);
    // test_tree.printTreeStructure();
    // cout << "\nTesting delete\n";
    // test_tree.remove(5);
    // test_tree.printTreeStructure();
    // test_tree.remove(11);
    // test_tree.printTreeStructure();
    // test_tree.remove(10);
    // test_tree.printTreeStructure();
    // test_tree.remove(12);
    // test_tree.printTreeStructure();
    // int arr[] = {10, 52, 98, 32, 68, 92, 48, 13, 42, 63, 99, 100, 50, 40, 12, 11, 9, 0, 1, 3, 7};
    // for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    // {
    //     test_tree.insert(arr[i]);
    // }
    // test_tree.NLR_traverse();
    // cout << endl;
    // test_tree.LRN_traverse();
    // cout << endl;
    // test_tree.printTreeStructure();
    // test_tree.remove(52);
    // cout << endl;
    // test_tree.printTreeStructure();
    // cout << endl;
    // test_tree.NLR_traverse();
    // cout << "\n Next Test \n";
    // test_tree.remove(50);
    // test_tree.printTreeStructure();
    // cout << endl;
    // test_tree.NLR_traverse();
    // cout << "\n Next Test \n";
    // test_tree.remove(48);
    // test_tree.printTreeStructure();
    // cout << endl;
    // test_tree.NLR_traverse();
    // cout << "\n Next Test \n";
    // test_tree.remove(10);
    // test_tree.printTreeStructure();
    // cout << endl;
    // test_tree.NLR_traverse();
    // test_tree.clear();
    // cout << endl;
    // test_tree.printTreeStructure();
    // int arr1[] = {10, 52, 98, 32, 68, 92, 48, 13, 42, 63, 99, 100, 50, 40, 12, 11, 9, 0, 1, 3, 7};
    // for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    // {
    //     test_tree.insert(arr1[i]);
    // }
    // test_tree.printTreeStructure();
    // cout << "\nThe biggest test \n";
    // test_tree.remove(10);
    // test_tree.remove(52);
    // test_tree.remove(98);
    // test_tree.remove(32);
    // test_tree.remove(68);
    // test_tree.printTreeStructure();
    // cout << endl;
    // test_tree.NLR_traverse();
    // for (int i = 150; i < 200; i++)
    //     test_tree.insert(i);
    // test_tree.printTreeStructure();
    // for (int i = 150; i < 200; i++)
    //     test_tree.remove(i);
    // test_tree.printTreeStructure();
    // for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
    // {
    //     test_tree.remove(arr1[i]);
    // }
    // test_tree.insert(10);
    // test_tree.insert(52);
    // test_tree.insert(98);
    // test_tree.insert(32);
    // test_tree.insert(68);
    // test_tree.insert(92);
    // test_tree.insert(48);
    // test_tree.insert(13);
    // test_tree.insert(42);
    // test_tree.insert(63);
    // test_tree.insert(99);
    // test_tree.insert(100);
    // test_tree.insert(50);
    // test_tree.insert(40);
    // cout << endl;
    // test_tree.printTreeStructure();
    // test_tree.remove(63);
    // test_tree.printTreeStructure();
    // test_tree.remove(0);
    // test_tree.printTreeStructure();
    // test_tree.remove(5);
    // test_tree.printTreeStructure();
    // test_tree.remove(32);
    // test_tree.printTreeStructure();
    system("pause");
    return 0;
}