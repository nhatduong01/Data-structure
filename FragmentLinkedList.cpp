#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
using namespace std;

#ifndef ILIST_H
#define ILIST_H
int Ceil(float num)
{
    int inum = (int)num;
    if (num == (float)inum)
    {
        return inum;
    }
    return inum + 1;
}
template <class T>
class IList
{
public:
    virtual void add(const T &element) = 0;
    virtual void add(int index, const T &element) = 0;
    virtual T removeAt(int index) = 0;
    virtual bool removeItem(const T &item) = 0;
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual T get(int index) = 0;
    virtual void set(int index, const T &element) = 0;
    virtual int indexOf(const T &item) = 0;
    virtual bool contains(const T &item) = 0;
    virtual string toString() = 0;
};

#endif

// STUDENT ANSWER
#ifndef FRAGMENT_LINKED_LIST
#define FRAGMENT_LINKED_LIST
template <class T>
class FragmentLinkedList : IList<T>
{
public:
    class Node;
    class Iterator;

protected:
    Node **fragmentPointers;
    int fragmentMaxSize;
    int count;
    int numOfPtr;

public:
    FragmentLinkedList(int fragmentMaxSize = 5)
    {
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
    }
    virtual ~FragmentLinkedList()
    {
        count = 0;
        Node *current = new Node();
        current = *fragmentPointers;
        Node *next = new Node();
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
        delete[] fragmentPointers;
    }
    virtual void add(const T &element)
    {
        Node *new_node = new Node();
        Node *last = new Node();
        last = *fragmentPointers; // Assign to a pointer of the fragmentpointer
        new_node->data = element;
        new_node->next = nullptr;
        //Check if the list is empty or not
        if (*fragmentPointers == nullptr)
        {
            new_node->prev = nullptr;
            *fragmentPointers = new_node;
            count++;
            Arranging();
            return;
        }
        // Traverse to the last node
        while (last->next != nullptr)
        {
            last = last->next;
        }
        last->next = new_node;
        new_node->prev = last;
        count++;
        Arranging();
    }
    virtual void add(int index, const T &element)
    {
        if (index < 0)
            throw std::out_of_range("The index is out of range!");
        if (index >= count)
        {
            add(element);
            return;
        }
        else if (index <= 0)
        {
            // add to the first position
            Node *newNode = new Node();
            newNode->data = element;
            newNode->next = *fragmentPointers;
            newNode->prev = nullptr;
            if (*fragmentPointers != nullptr)
                (*fragmentPointers)->prev = newNode;
            *fragmentPointers = newNode;
            count++;
            Arranging();
            return;
        }
        else
        {
            Node *newNode = new Node();
            newNode->data = element;
            Node *temp = new Node();
            temp = *fragmentPointers;
            while (index != 0)
            {
                temp = temp->next;
                index--;
            }
            newNode->next = temp;
            newNode->prev = temp->prev;
            temp->prev->next = newNode;
            temp->prev = newNode;
            count++;
            //delete here
            Arranging();
            return;
        }
    }
    virtual T removeAt(int index)
    {
        Node *current = new Node();
        current = *fragmentPointers;
        if (index >= count || index < 0)
            throw std::out_of_range("The index is out of range!");
        for (int i = 0; i < index && current != nullptr; i++)
        {
            current = current->next;
        }
        T temp = current->data;
        removeItem(current->data);
        return temp;
    }
    virtual bool removeItem(const T &item)
    {
        Node *current = new Node();
        current = *fragmentPointers;
        while ((current->data != item))
        {
            current = current->next;
            if (current == nullptr)
            {
                delete current;
                return false;
            }
        }
        if (*fragmentPointers == current)
            *fragmentPointers = current->next;
        if (current->next != nullptr)
            current->next->prev = current->prev;
        if (current->prev != nullptr)
            current->prev->next = current->next;
        count--;
        Arranging();
        delete current;
        return true;
    }
    virtual bool empty()
    {
        return count == 0;
    }
    virtual int size()
    {
        return count;
    }
    virtual void clear()
    {
        Node *current = new Node();
        current = *fragmentPointers;
        Node *next = new Node();
        while (current != nullptr)
        {
            next = current->next;
            delete current;
            current = next;
        }
        this->count = 0;
        this->fragmentMaxSize = fragmentMaxSize;
        this->fragmentPointers = new Node *[2];
        this->fragmentPointers[0] = NULL;
        this->fragmentPointers[1] = NULL;
        this->numOfPtr = 2;
    }
    virtual T get(int index)
    {
        if (index >= count || index < 0)
            throw std::out_of_range("The index is out of range!");
        Node *current = new Node();
        current = *fragmentPointers;
        while (index > 0)
        {
            current = current->next;
            index--;
        }
        return current->data;
    }
    virtual void set(int index, const T &element)
    {
        if (index <= -1)
            throw std::out_of_range("The index is out of range");
        Node *current = *fragmentPointers;
        for (int i = 0; i < index && current != nullptr; i++)
        {
            current = current->next;
        }
        if (current == nullptr)
            return;
        else
        {
            current->data = element;
        }
    }
    virtual int indexOf(const T &item)
    {
        Node *current = new Node();
        current = *fragmentPointers;
        int index = 0;
        while (current->data != item)
        {
            current = current->next;
            index++;
            if (current == nullptr)
                return -1;
        }
        return index;
    }
    virtual bool contains(const T &item)
    {
        Node *current = *fragmentPointers;
        while (current != nullptr)
        {
            if (current->data == item)
                return true;
            current = current->next;
        }
        return false;
    }
    virtual string toString();
    Iterator begin(int index = 0)
    {
        if (index == -1)
            index = numOfPtr - 1;
        FragmentLinkedList::Iterator result(index, this, true);
        return result;
    }
    Iterator end(int index = -1)
    {
        if (index == -1 || index == numOfPtr - 1)
        {
            FragmentLinkedList::Iterator temp(numOfPtr - 1, this, true);
            temp++;
            return temp;
        }
        else
        {
            FragmentLinkedList::Iterator temp(index + 1, this, true);
            if (count % fragmentMaxSize == 0 && index == numOfPtr - 2)
                temp++;
            return temp;
        }
    }
    void print()
    {
        for (int i = 0; i < numOfPtr - 1; i++)
        {
            Node *current = fragmentPointers[i];
            int time = fragmentMaxSize;
            while (current != nullptr && time)
            {
                cout << current->data << "\t";
                current = current->next;
                time--;
            }
            cout << endl;
        }
    }
    void Arranging()
    {
        if (count == 0)
        {
            //clear();
            return;
            // I delete Clear here
        }
        Node *current = *fragmentPointers;
        int radio = Ceil((float)count / fragmentMaxSize) + 1;
        if (radio != numOfPtr)
        {
            fragmentPointers = new Node *[radio];
            numOfPtr = radio;
        }
        fragmentPointers[0] = current;
        for (int i = 1; i < numOfPtr - 1; i++)
        {
            int temp = fragmentMaxSize;
            while (temp != 0)
            {
                if (current == nullptr)
                    break;
                current = current->next;
                temp--;
            }
            fragmentPointers[i] = current;
        }
        while (current->next != nullptr)
        {
            current = current->next;
        }
        fragmentPointers[numOfPtr - 1] = current;
    }
    int getnumOfPtr()
    {
        return numOfPtr;
    }

public:
    class Node
    {
    private:
        T data;
        Node *next;
        Node *prev;
        friend class FragmentLinkedList<T>;

    public:
        Node()
        {
            next = 0;
            prev = 0;
        }
        Node(Node *next, Node *prev)
        {
            this->next = next;
            this->prev = prev;
        }
        Node(T data, Node *next, Node *prev)
        {
            this->data = data;
            this->next = next;
            this->prev = prev;
        }
    };

    class Iterator
    {
    private:
        FragmentLinkedList<T> *pList;
        Node *pNode;
        int index;

    public:
        Iterator(FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            this->pList = pList;
            if (begin)
            {
                this->pNode = pList->fragmentPointers[0];
                this->index = 0;
            }
            else
            {
                this->pNode = pList->fragmentPointers[pList->getnumOfPtr() - 1]->next;
                //this->pNode = pList->fragmentPointers[pList->getnumOfPtr() - 1];
                //this->pNode++;
                this->index = pList->fragmentMaxSize;
            }
        }
        Iterator(int fragmentIndex, FragmentLinkedList<T> *pList = 0, bool begin = true)
        {
            this->pList = pList;
            if (begin)
            {
                this->pNode = pList->fragmentPointers[fragmentIndex];
                this->index = (pList->fragmentMaxSize) * fragmentIndex;
            }
            else
            {
                this->pNode = pList->fragmentPointers[fragmentIndex + 1];
                this->index = (pList->fragmentMaxSize) * (fragmentIndex + 1);
            }
        }
        Iterator &operator=(const Iterator &iterator)
        {
            this->pList = iterator.pList;
            this->pNode = iterator.pNode;
            return *this;
        }
        T &operator*()
        {
            if (this->pNode)
                return this->pNode->data;
            else
            {
                throw std::out_of_range("Segmentation fault!");
            }
        }
        bool operator!=(const Iterator &iterator)
        {
            return (this->pNode == iterator.pNode) ? false : true;
        }
        void remove()
        {
            Node *current = this->pNode;
            if (this->pList->fragmentPointers[0] == this->pNode)
                this->pList->fragmentPointers[0] = current->next;
            if (this->pNode->next != nullptr)
                current->next->prev = current->prev;
            if (this->pNode->prev != nullptr)
                current->prev->next = current->next;
            this->pList->count--;
            this->pList->Arranging();
            this->pNode = this->pNode->prev;
            this->index--;
            delete current;
        }
        void set(const T &element)
        {
            this->pNode->data = element;
        }
        Iterator &operator++()
        {
            if (this->pNode)
            {
                pNode = pNode->next;
                this->index++;
                return *this;
            }
            else if (this->pList->count == 0)
            {
                pNode = this->pList->fragmentPointers[this->pList->getnumOfPtr() - 1]->next;
                // Set the index
                this->index = 0;
                // I add return here
                return *this;
            }
            else
            {
                this->pNode = this->pList->fragmentPointers[0];
                this->index++;
                return *this;
            }
        }
        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++*this;
            return temp;
        }
    };
};

template <class T>
string FragmentLinkedList<T>::toString()
{
    stringstream ss;
    ss << "[";
    Node *ptr = this->fragmentPointers[0];

    if (this->count == 0)
    {
        ss << "]";
        return ss.str();
    }
    // TODO
    for (int i = 0; ptr != nullptr; i++)
    {
        ss << to_string(ptr->data);
        if (i != count - 1)
            ss << ", ";
        ptr = ptr->next;
    }
    ss << "]";
    // END: TODO
    return ss.str();
}

#endif
// END: STUDENT ANSWER
int main()
{
    int _case = 0;
    cout << "Run case: ";
    cin >> _case;
    switch (_case)
    {
    //000000000000000000000000000000000000
    case 0:
    {
        //TESTCASE INPUT
        //=== Example
        FragmentLinkedList<int> fList;
        for (int i = 0; i < 20; i++)
            fList.add(i, i * i);

        for (FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.end(); it++)
            cout << *it << " ";
        cout << endl;
        //=== END: Example
        //END: TESTCASE INPUT

        break;
    }
    //1111111111111111111111111111111111111
    case 1:
    {
        FragmentLinkedList<int> testLinkedList(3);

        for (int i = 1; i <= 10; i++)
        {
            testLinkedList.add(i);
        }
        cout << "The initialization: " << endl;
        cout << testLinkedList.toString();
        cout << "\n-------------------------------\n";
        testLinkedList.add(1, 100);
        cout << testLinkedList.toString();
        cout << "\n-------------------------------\n";
        cout << "count is " << testLinkedList.size() << endl;
        testLinkedList.add(11, 1000);
        cout << testLinkedList.toString() << endl;
        cout << "The final count is: " << testLinkedList.size() << endl;
        testLinkedList.add(200);
        testLinkedList.add(300);
        testLinkedList.add(400);
        cout << testLinkedList.toString() << endl;
        cout << "Removing Stuff" << endl;
        testLinkedList.removeAt(3);
        cout << testLinkedList.toString() << endl;
        cout << "Removing item\n";
        testLinkedList.removeItem(200);
        cout << testLinkedList.toString() << endl;
        cout << "Removing the last item" << endl;
        testLinkedList.removeItem(400);
        cout << testLinkedList.toString() << endl;
        cout << "Adding at the first: " << endl;
        testLinkedList.add(0, 99);
        cout << testLinkedList.toString() << endl;
        cout << "Get the index of 5 : " << testLinkedList.get(5) << endl;
        cout << "The string of the first fragment : " << testLinkedList.toString() << endl;

        break;
    }
    //222222222222222222222222222222222222222
    case 2:
    {
        FragmentLinkedList<int> list;
        cout << "size of list1: " << list.size() << endl;
        FragmentLinkedList<int> fList = FragmentLinkedList<int>();
        for (int i = 0; i < 20; i++)
            fList.add(i * i);
        for (FragmentLinkedList<int>::Iterator it = fList.begin(); it != fList.begin(1); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        cout << "size of list2: " << fList.size() << endl;
        for (int i = 0; i < 20; i++)
        {
            fList.removeAt(fList.size() - 1);
        }
        cout << "size of list2 after removeAt: " << fList.size() << endl;
        fList.add(0, 30);
        //fList.add(2,32);
        fList.add(1, 33);
        fList.add(35);
        fList.add(36);
        fList.add(37);
        fList.add(38);
        fList.add(5, 40);
        fList.add(0, 41);
        //fList.removeItem(36);
        cout << "toString: " << fList.toString() << endl;
        cout << "contain 25?: " << fList.contains(25) << endl;
        cout << "contain 38?: " << fList.contains(38) << endl;
        cout << "index of 38: " << fList.indexOf(38) << endl;
        cout << "index of 45: " << fList.indexOf(45) << endl;
        fList.set(4, 25);
        cout << "---------------------\n";
        cout << "toString: " << fList.toString() << endl;
        cout << "get 4th element: " << fList.get(4) << endl;
        cout << "contain 25?: " << fList.contains(25) << endl;
        cout << "size of list one more time: " << fList.size() << endl;
        cout << "remove item = 30: " << fList.removeItem(30) << endl;
        fList.add(2, 38);
        cout << "remove item = 38: " << fList.removeItem(38) << endl;
        cout << "remove item = 37: " << fList.removeItem(37) << endl;
        //cout << fList.removeItem(36) << endl << endl;
        cout << "remove item = 35: " << fList.removeItem(35) << endl;
        cout << "size of the list one one more time: " << fList.size() << endl;
        fList.add(90);
        fList.add(6, 91);
        //FragmentLinkedList<int>::Iterator it1 = fList.begin();
        //
        //it1.remove();
        FragmentLinkedList<int>::Iterator it1 = fList.end(0);
        it1.set(24);
        cout << "toString: " << fList.toString() << endl;
        for (FragmentLinkedList<int>::Iterator it = fList.begin(1); it != fList.end(); it++)
        {
            cout << *it << " ";
            //it.remove();
        }
        cout << endl;
        //cout << fList.removeItem(41);
        FragmentLinkedList<int>::Iterator it2 = fList.begin();
        for (int i = 0; i < 4; i++)
            it2++;
        it2.remove();
        for (; it2 != fList.end(); it2++)
        {
            cout << *it2 << " ";
        }

        break;
    }
    //33333333333333333333333333333333333333

    //444444444444444444444444444444444444444444444444
    case 4:
    {
        FragmentLinkedList<int> fList(20);
        for (int i = 0; i < 200; i++)
        {
            fList.add(i);
        }
        for (auto it = fList.begin(); it != fList.end(); it++)
        {
            if (*it % 5 == 1 || *it % 4 == 0 || *it % 3 == 2 || *it % 7 == 2)
            {
                it.remove();
            }
        }
        //cout << fList.size() << endl;
        cout << fList.get(45) << '\n';
        cout << fList.toString() << '\n';

        break;
    }
    //55555555555555555555555555555555555555555555555
    case 5:
    {
        FragmentLinkedList<int> test(5);
        for (int i = 0; i < 20; i++)
        {
            test.add(i, i * i + 10);
        }
        cout << test.toString() << endl;
        //FragmentLinkedList<int>::Iterator it = test.begin();
        FragmentLinkedList<int>::Iterator it = test.end(2);
        it.remove();
        //FragmentLinkedList<int>::Iterator it = test.end();
        it++;
        for (; it != test.end(); it++)
        {
            cout << *it << " ";
        }
        cout << endl;
        for (it = test.begin(); it != test.end(); it++)
        {
            cout << *it << " ";
        }
        break;
    }
    //6666666666666666666666666666666666666666
    case 6:
    {
        FragmentLinkedList<int> test(10);
        for (int i = 0; i < 20; i++)
        {
            test.add(i, i * i + 10);
        }
        cout << test.toString() << endl;
        //FragmentLinkedList<int>::Iterator it = test.begin();
        auto it = test.begin();
        auto it2 = test.begin(1);
        for (; it != it2; it++)
        {
            cout << *it << " ";
            it.remove();
        }
        cout << test.toString() << endl;
        it = test.begin();
        for (; it != it2; it2++)
        {
            test.add(0, *it2);
            it2.remove();
        }
        cout << test.toString() << endl;

        break;
    }
    //777777777777777777777777777777777777777777777
    case 7:
    {
        FragmentLinkedList<int> test(10);
        for (int i = 0; i < 20; i++)
        {
            test.add(i, i * i + 10);
        }
        cout << test.toString() << endl;
        //FragmentLinkedList<int>::Iterator it = test.begin();
        auto it = test.begin();
        auto it2 = test.begin(1);
        for (; it != it2; it++)
        {
            cout << *it << " ";
            it.remove();
        }
        cout << "\n"
             << test.toString() << endl;
        cout << *it << " " << *it2 << "\n";
        it = test.begin();
        it2 = test.begin();
        for (; *it2 != 371; it2++)
            ;
        for (; it != it2;)
        {
            test.add(0, *it2);
            it2.remove();
        }
        cout << test.toString() << endl;

        break;
    }
    //8888888888888888888888888888888888888888888888888
    case 8:
    {
        FragmentLinkedList<int> List;
        List.add(0);
        List.add(100);
        List.removeAt(0);
        List.removeAt(0);
        cout << List.toString() << "\n";
        List.clear();

        List.add(0);
        List.add(100);
        List.removeItem(0);
        List.removeItem(100);
        cout << List.toString() << "\n";
        List.clear();

        List.add(0);
        List.add(100);
        List.clear();
        cout << List.toString() << "\n";

        List.add(0);
        List.add(100);
        auto it = List.begin();
        it.remove();
        it++;
        it.remove();
        cout << List.toString() << "\n";

        break;
    }
    case 9:
    {
        FragmentLinkedList<int> testLinkedList(3);
        for (int i = 1; i <= 10; i++)
        {
            testLinkedList.add(i);
        }
        testLinkedList.print();
        cout << "The string is : " << testLinkedList.toString() << endl;
        testLinkedList.add(4);
        testLinkedList.add(2);
        FragmentLinkedList<int>::Iterator temp = testLinkedList.begin();
        cout << *temp << endl;
        temp.remove();
        cout << "The string is : " << testLinkedList.toString() << endl;
        temp++;
        cout << *temp << endl;
        temp.remove();
        cout << "The final string is : " << testLinkedList.toString() << endl;
        temp++;
        for (FragmentLinkedList<int>::Iterator it = testLinkedList.begin(); it != testLinkedList.end(); it++)
        {
            it.remove();
        }
        cout << "The final string is : " << testLinkedList.toString() << endl;
        testLinkedList.clear();

        break;
    }
    case 10:
    {
        int a = 5, n = 16;
        FragmentLinkedList<int> fList(a);
        for (int i = 0; i < n; i++)
        {
            fList.add(i * i);
        }
        cout << "- Add i*i to list (i from 0 to " << n - 1 << "): " << endl;
        cout << fList.toString() << endl;

        fList.add(4, 7);
        cout << "- Add 7 to index 4:" << endl
             << fList.toString() << endl;

        cout << "- Remove item 4, return: " << fList.removeAt(4) << endl;
        cout << fList.toString() << endl;

        cout << "- Remove item last, return: " << fList.removeAt(fList.size() - 1) << endl;
        cout << fList.toString() << endl;

        cout << "- Remove item 5, return: " << fList.removeAt(5) << endl;
        cout << fList.toString() << endl;

        fList.set(4, 69);
        cout << "- Set index 4 to 69:" << endl
             << fList.toString() << endl;

        cout << "- Check index 6: " << fList.indexOf(6) << endl
             << endl;
        cout << "- Check index 10: " << fList.indexOf(10) << endl
             << endl;
        cout << "- Check item with value of 6: " << fList.contains(6) << endl
             << endl;
        cout << "- Check item with value of 64: " << fList.contains(64) << endl
             << endl;
        cout << "- Get value of index 5: " << fList.get(3) << endl
             << endl;

        using iterator = FragmentLinkedList<int>::Iterator;

        cout << "Original list:     " << fList.toString() << endl;
        cout << "Iterator checking: "
             << "[";
        string x = ", ";
        for (iterator i = fList.begin(); i != fList.end(); i++)
        {
            if (*i == fList.get(fList.size() - 1))
            {
                i.set(96);
                x = "";
            }
            cout << *i << x;
        }
        cout << "]" << endl
             << endl;

        iterator it = fList.begin();
        cout << "Prefix checking: " << *(it++) << " = " << *it << endl
             << endl;

        it = fList.begin();
        it.remove();
        it++;
        cout << "List after modified: " << endl
             << fList.toString() << endl;
        cout << "Remove & Increase the first node checking: " << *it;
        if (*it == fList.get(0))
            cout << "   --TRUE--";
        else
            cout << "  --FALSE--";
        cout << endl
             << endl;

        //Problem M
        it = fList.begin();
        fList.add(0, 69);
        it.remove();
        it++;
        cout << "List after modified: " << endl
             << fList.toString() << endl;
        cout << "Remove & Increase the first iterator points node checking: " << *it;
        cout << endl
             << endl;

        //Problem M repeat
        it = fList.begin();
        fList.add(0, 6969);
        it.remove();
        it++;
        cout << "List after modified: " << endl
             << fList.toString() << endl;
        cout << "Remove & Increase the first iterator points node checking: " << *it;
        cout << endl
             << endl;

        fList.clear();
        cout << "Check clear:  " << fList.toString() << endl
             << endl;
        break;
    }
    // default:
    // {
    //     cout << "Case ID not available.\n";
    //     break;
    // }
    case 11:
    {
        FragmentLinkedList<int> test(3);
        for (int i = 0; i < 9; i++)
            test.add(i * i);
        cout << test.toString() << endl;
        FragmentLinkedList<int>::Iterator test_it(&test, false);
        FragmentLinkedList<int>::Iterator test_it2(&test, true);
        for (auto it = test.begin(); it != test.end(); it++)
            cout << *it << "\t";
        cout << endl;
        for (; test_it2 != test_it; test_it2++)
            cout << *test_it2 << "\t";
        cout << endl;
        break;
    }
    case 12:
    {
        FragmentLinkedList<int> list;
        cout << list.size();
        break;
    }
    }
    /*
    FragmentLinkedList<int> list(5); 
    for(int i = 0 ; i < 20 ; i++ ){
        list.add(i,i);
    }
    cout<<list.toString()<<"\n\n";
    //cout<<list.removeAt(19)<<endl;
    for(auto it = list.begin(); it!= list.end() ; it++ ){
        if(*it == 19 || *it == 0 ) it.remove(); 
    } 
    cout<<list.toString()<<"\nCheck Fragment Pointer data : \n";*/
    system("pause");
    return 0;
}
