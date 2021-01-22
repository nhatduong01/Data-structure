/*
Implement interpolation Search and print out the traversed indexes*/
#include <iostream>
using namespace std;
int jumpSearch(int arr[], int x, int n)
{
    // TODO: print the traversed indexes and return the index of value x in array if x is found, otherwise, return -1.
    int idx = 0;
    while (arr[idx] <= x)
    {
        cout << idx << " ";
        if (arr[idx] == x)
            return idx;
        idx += 4;
        if (idx > n - 1)
        {
            for (int i = idx - 3; i <= n; i++)
            {

                cout << i << " ";
                if (i == n)
                    return -1;
                if (arr[i] == x)
                    return i;
            }
        }
    }
    cout << idx << " ";
    for (int i = idx - 3; i < idx; i++)
    {
        cout << i << " ";
        if (arr[i] == x)
            return i;
    }
    return -1;
}
int main()
{

    int arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 611, 612, 613, 1000, 1002, 2000, 2003, 2004, 2005, 2006};
    int x = 36;
    int n = sizeof(arr) / sizeof(arr[0]);
    int index = jumpSearch(arr, x, n);

    if (index != -1)
    {
        cout << "\nNumber " << x << " is at index " << index;
    }
    else
    {
        cout << "\n"
             << x << " is not in array!";
    }
    return 0;
}