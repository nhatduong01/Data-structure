#include<iostream>
#define MAXSIZE 100
using namespace std;
int top = -1;
bool IsFull(int capacity) 
{
	if (top >= capacity-1) return true;
	else return false;
}
bool IsEmpty() 
{
	if (top == -1) return true;
	else return false;
}
 void Push (int stack[], int value, int capacity)
 {
	 if (IsFull(capacity))  cout << "\nThe stack is full cannot be inserted\n";
	 else 
	 {
		 top++;
		 stack[top] = value;
	 }
 }
 void Pop ()
 {
	 if (IsEmpty()) cout << "The stack is empty\n";
	 else top--;
 }
 int Top (int stack[])
 {
	 return stack[top];
 }
 int size() 
 {
	 return top + 1;
 }
 void main ()
 {
	 int capacity=0;
	 cout << "Please enter the capacity of the stack";
	 cin >> capacity;
	 int stack[MAXSIZE];
	 for (int i = 0;i < capacity;i++)
	 {
		 int temp = 0;
		 cout << "Enter the " << i + 1 << " value of the stack";
		 cin >> temp;
		 Push(stack, temp, capacity);
	 }

	 Pop();
	 cout << "The value of the top is " << Top(stack) << "\n";
	 if (!IsFull(capacity)) cout << "The stack is not full";
	 Push(stack, 100, capacity);
	 Push(stack, 101, capacity);
	 cout << "The value of the top is " << Top(stack) << "\n";



 }
