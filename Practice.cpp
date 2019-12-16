#include<iostream>
using namespace std;
struct LinkedList {
	int data;
	   struct LinkedList* next;
};
typedef  struct LinkedList* node; // Change the name
node Create(int value) {
	node temp;
	temp = new struct LinkedList();
	temp-> next = NULL;
	temp->data = value;
	return temp;
}
node AddHead(node head, int value) {
	node temp = Create(value);
	if (head == NULL) temp = head;
	else {
		temp->next = head;
		head = temp;
	}
	return head;
}
node AddTail(node head, int value) {
	node temp, p;
	temp = Create(value);
	if (head == NULL) head = temp;
	else {
		p = head;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = temp;
	}
	return head;
}
node AddAt(node head, int value, int position) {
	if (head == NULL || position == 0) AddHead(head, value);
	else {
		int k = 1;
		 node p = head;
		 while (k != position && p->next != NULL) {
			 k++;
			 p = p->next;
		 }
		 if (k != position)  head = AddTail(head, value);
		 else {
			 node temp = Create(value);
			 temp->next = p->next;
			 p->next = temp;
		 }
	}
	return head;
}
node HeadDel(node head) {
	if (head == NULL) cout << "There is nothing to delete\n";
	else head = head->next;
	return head;
}
node TailDel(node head) {
	
		node p = head;
		while (p->next->next != NULL) {
			p = p->next;
		}
		p->next = NULL;
		return head;
}
node Deletion(node head, int position) {
	int k = 1;
	node p = head;
	while (p->next->next != NULL && k != position) {
		k++;
		p = p->next;
	}
	if (k != position) TailDel(head);
	else {
		p->next = p->next->next;
	}
	return head;
}
int get(node head, int index) {
	int k = 1;
	node p = head;
	while (p->next != NULL && k != index) {
		k++;
		p = p->next;
	}
	return p->data;
}
int Value(node head, int value) {
	int k = 0;
	node p = head;
	while (k != value && p->next != NULL) {
		if (p->data = value) {
			return k;
			break;
		}
		k++;
		p = p->next;
	}
	return -1;
}
void Traverser(node head) {
	cout << endl;
	for (node p = head;p != NULL;p = p->next) {
		cout << p->data << "\t";
	}
}
int length(node head) {
	int length = 0;
	for (node p = head; p != NULL;p = p->next)
		length++;
	return length;
}
node InitHead() {
	node head = NULL;
	return head;
}
node inputnode() {
	node head = InitHead();
	int value, size;
	do {
		cout << "Please enter the size";
		cin >> size;
	} while (size <= 0);
		for (int i = 0; i < size;i++) {
			cout << "Please enter the value";
			cin >> value;
			head = AddTail(head, value);
		}
		return head;
}
void main() {
	node head = inputnode();
	Traverser(head);
	cout << "\nAdd a  component in the linked list\n";
	AddAt(head, 45, 2);
	Traverser(head);
	Deletion(head, 1);
	Traverser(head);
}