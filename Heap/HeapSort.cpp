#include <iostream>
#include <algorithm>
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
void buildHeap(int *arr, int size)
{
    int pivot = size / 2 - 1;
    for (int i = pivot; i >= 0; i--)
        Heaplify(arr, size, i);
}
void HeapSort(int *arr, int size)
{
    int temp_size = size - 1;
    while (temp_size >= 0)
    {
        int temp = arr[temp_size];
        arr[temp_size] = arr[0];
        arr[0] = temp;
        Heaplify(arr, temp_size, 0);
        temp_size--;
    }
}

int main()
{
    int size = 0;
    cout << "Please enter the size of the array : ";
    cin >> size;
    int *arr = new int[size];
    for (int i = 0; i < size; i++)
        cin >> arr[i];
    buildHeap(arr, size);
    cout << "The final heap is : \n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\t";
    cout << endl;
    HeapSort(arr, size);
    cout << "The final heap is : \n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << "\t";
    cout << endl;
    delete[] arr;
    return 0;
}
