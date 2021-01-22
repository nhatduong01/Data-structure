/*
Implement interpolation Search and print out the traversed indexes
*/
#include <iostream>
using namespace std;
int interpolationSearch(int arr[], int left, int right, int x)
{
    int pos = left + ((x - arr[left]) * (right - left) / (arr[right] - arr[left]));
    if (pos > right || pos < left)
        return -1;
    cout << "We traverse on index: " << arr[pos] << endl;
    if (arr[pos] == x)
        return pos;
    else
    {
        if (arr[pos] > x)
            return interpolationSearch(arr, pos + 1, right, x);
        else
        {
            return interpolationSearch(arr, left, pos - 1, x);
        }
    }
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int x = 3;
    int result = interpolationSearch(arr, 0, n - 1, x);
    (result == -1) ? cout << "Element is not present in array"
                   : cout << "Element is present at index " << result;
    return 0;
}