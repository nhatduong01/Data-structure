#include<iostream>
#define MAX 50
using namespace std;
void Merge(int arr[], int l, int m, int r) //Mergin the array array[l...m] and array[m+1...r] in the ascending order
{
	 int n1 = m - l + 1;//Number of components of the first identical  array
	 int n2 = r - m;//Number of components of the second identical array
	int arr1[MAX], arr2[MAX];// Innitialize the two array
	for ( int i =0;i<n1;i++)//Copy the array[l...m]
	{
		arr1[i] = arr[l + i];//Copy the array [m+1...r]
	}
	for (int i =0;i<n2;i++)
	{
		arr2[i] = arr[m + 1 + i];
	}
	int i = 0;// the index of array1
	int j = 0;// the index of array2
	int k = l;//the index of the merged array
	while (i < n1 && j < n2)
	{
		if (arr1[i] < arr2[j])
		{
			arr[k] = arr1[i];
			i++;
		}
		else 
		{
			arr[ k] = arr2[j];
			j++;
		}
		k++;
	}
	while (i<n1)
	{
		arr[ k] = arr1[i];
		i++;
		k++;
	}
	while (k < n2)
	{
		arr[ k] = arr2[i];
		k++;
		j++;
	}
}
void MergeSort(int arr[], int low,  int high)
{
	if (low < high)
	{
		 int middle = (high + low) / 2;
		 MergeSort(arr, middle + 1, high);
		 MergeSort(arr, low, middle);
		 Merge(arr, low, middle, high);
	}
}
void InputArray( int arr[], int size)
{
	for (int i = 0;i < size;i++)
	{
		cout << "Please enter the value of array[" << i << "] = ";
		cin >> arr[i];
	}
}
void OutputArray(int arr[], int size)
{
	cout << "----------The sorted array-----------\n";
	for (int i = 0;i < size;i++)
	{
		cout << arr[i] << "\t";
	}
}
void main()
{
	int size;
	cout << "Enter the size of the array : ";
	cin >> size;
	int arr[MAX];
	InputArray(arr, size);
	MergeSort(arr, 0, size - 1);
	OutputArray(arr, size);
}