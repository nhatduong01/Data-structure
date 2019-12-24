#include<iostream>
#define MAX 1000
using namespace std;
void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}
void InputArray(int arr[], int size)
{
	for (int i = 0;i < size;i++)
	{
		cout << "Please enter the value of array[" << i << "] = ";
		cin >> arr[i];
	}
}
void OutputArray(int arr[], int size)
{
	cout << "-----The final array-------------\n";
	for (int i = 0;i < size;i++)
	{
		cout << arr[i] << "\t";
	}
}
int Parition(int arr[], int low, int high)
{
	int pivot = arr[low];
	int left = low+1;
	int right = high;
	while (true)
	{
		while (left <= right && arr[left] < pivot) left++;
		while (right >= left && arr[right] > pivot) right--;
		if (right <=left) break;
		Swap(arr[right], arr[left]);
		right--;
		left++;
	}
	Swap(arr[right], arr[low]);
	return right;
}
void QuickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		int p = Parition(arr, low, high);
		QuickSort(arr, p + 1, high);
		QuickSort(arr, low, p - 1);
	}
}
void main()
{
	int size = 0;
	cout << "Please enter the size of the array : ";
	cin >> size;
	int arr[MAX];
	InputArray(arr, size);
	QuickSort(arr, 0, size - 1);
	OutputArray(arr, size);
	
}
