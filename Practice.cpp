#include<iostream>
#define MAX 100
using namespace std;
int top = -1;
int stack[MAX];
void push(int value)
{
	if (top >= MAX - 1) cout << "\nThe stack is full cannot be inserted!";
	else
	{
		top++;
		stack[top] = value;
	}
}
int pop()
{
	int temp = 0;
	if (top == -1) cout << "\nThe stack is empty cannot be deleted!";
	else {
		temp = stack[top];
		top--;
	}
	return temp;
}
bool IsDigit(char temp)
{
	if ('0' <= temp && temp <= '9')
		return true;
	else
		return false;
}
void Evaluation(char Expression[])
{
	char Operator;
	int A = 0;
	int B = 0;
	double value = 0;
	for (int i = 0; Expression[i] != '.';i++)
	{
		Operator = Expression[i];
		if (IsDigit(Expression[i]))
			push(Expression[i]-'0');
		else
		{
			A = pop();
			B = pop();
	
			switch (Operator)
			{
			case'+':
				value = A + B;
				break;
			case'-':
				value = B - A;
				break;
			case'*':
				value = A * B;
				break;
			case'/':
				value = A / B;
				break;
			}
			push(value);
		}
	}
	cout << "\nThe final result is : " << pop() << endl;
}
void main()
{
	char Expression[MAX];
	for (int i = 0;i<=MAX-1;i++)
	{
		cin >> Expression[i];
		if (Expression[i] == '.')
			break;
	}
	Evaluation(Expression);
}