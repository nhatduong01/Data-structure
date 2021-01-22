/*
Implement Binary Search 
*/
#include <iostream>
using namespace std;
int binarySearch(int arr[], int left, int right, int x)
{
    int mid = (left + right) / 2;
    cout << "We traverse on index: " << arr[mid] << "\n";
    if (arr[mid] == x)
        return mid;
    else
    {
        if (left == right)
            return -1;
        else
        {
            if (x > arr[mid])
                return binarySearch(arr, mid, right, x);
            else
            {
                return binarySearch(arr, left, mid, x);
            }
        }
    }
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int x = 10;
    int n = sizeof(arr) / sizeof(arr[0]);
    int result = binarySearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                   : cout << "Element is present at index " << result;
    return 0;
}