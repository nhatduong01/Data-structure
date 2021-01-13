#include <iostream>
#include <algorithm>
#define MAX 1000
using namespace std;
void Heaplify(int *arr, int size, int pivot)
{
    int biggest = pivot;
    int left_child = 2 * biggest + 1;
    int right_child = 2 * biggest + 2;
    if (left_child < size && arr[biggest] < arr[left_child])
    {
        biggest = left_child;
    }
    if (right_child < size && arr[biggest] < arr[right_child])
    {
        biggest = right_child;
    }
    if (biggest != pivot)
    {
        swap(arr[biggest], arr[pivot]);
        Heaplify(arr, size, biggest);
    }
}
void deleteHeap(int *arr, int pos, int &size)
{
    if (pos >= size)
    {
        cout << "Invalid\n";
        return;
    }
    arr[pos] = arr[size - 1];
    size--;
    Heaplify(arr, size, pos);
}
void insert(int *arr, int new_value, int &size)
{
    arr[size] = new_value;
    size++;
    Heaplify(arr, size, size - 2);
}
void buildHeap(int *arr, int size)
{
    int pivot = size / 2 - 1;
    for (int i = pivot; i >= 0; i--)
        Heaplify(arr, size, i);
}
int main()
{
    int arr[MAX] = {1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17};

    int size = 11;
    buildHeap(arr, size);
    cout << "The final heap is : \n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\t";
    cout << endl;
    deleteHeap(arr, 3, size);
    cout << "The final heap is : \n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\t";
    cout << endl;
    deleteHeap(arr, 1, size);
    cout << "The final heap is : \n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\t";
    cout << endl;
    insert(arr, 100, size);
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\t";
    cout << endl;
    system("pause");
    return 0;
}
