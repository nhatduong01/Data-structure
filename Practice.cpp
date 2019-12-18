#include<iostream>
using namespace std;
struct node {
	int data;
	node* left;
	node* right;
};
node* MakeAnode(int value) {
	node* temp = new node();
	temp->data = value;
	temp->left = temp->right = NULL;
	return temp;
}
int MaxDepth(node* node) {
	if (node == NULL)
		return 0;
	else {
		int lDepth = MaxDepth(node->left);
		int rDepth = MaxDepth(node->right);
		if (lDepth > rDepth) return lDepth + 1;
		else return rDepth + 1;
	}
}
void Free(node* node) {
	if (node == NULL) return;
	Free(node->left);
	Free(node->right);
	free(node);
}
int LeftOf(const int value, const node* root) {
	return value <= root->data;
}
int RightOf(const int value, const node* root) {
	return value > root->data;
}
node* Insert(node *root, const int value) {
	if (root == NULL) {
		node* node1 = new node();
		node1->left = node1->right = NULL;
		node1->data = value;
		return node1;
	}
	if (LeftOf(value, root))
		root->left = Insert(root->left,value );
	else if (RightOf(value, root))
		root->right = Insert(root->right,value );
	return root;
}
bool Search(const node *root, int value) {
	if (root == NULL) return false;
	if (root->data == value) return true;
	else if (LeftOf(value, root)) return Search(root->left, value);
	else if (RightOf(value, root)) return Search(root->right, value);

}
int LeftmostValule(node* root)
{
	while (root->left != NULL)
		root = root->left;
	return root->data;
}
node *Delete(node* root, int value) 
{
	if (root == NULL)
		return root;
	if (LeftOf(value, root))
		root->left = Delete(root->left, value);
	 else if (RightOf(value, root))
		root->right = Delete(root->right, value);
	else 
	{
		if (root->left == NULL)
		{
			node* NewNode = root->right;
			free(root);
			return NewNode;
		}
		if (root->right == NULL) 
		{
			node* NewNode = root->left;
			free(root);
			return NewNode;
		}
		root->data = LeftmostValule(root->right);
		root->right = Delete(root->right, root->data);
	}
	return root;

}
void PreOrder(node* root) {
	if (root != NULL) {
		cout << root->data<<"\t";
		PreOrder(root->right);
		PreOrder(root->left);
		
	}
}

void main() {
	node* root = NULL;
	root = Insert(root, 25);
	root = Insert(root, 15);
	root = Insert(root, 50);
	root = Insert(root, 10);
	root = Insert(root, 22);
	root = Insert(root, 35);
	root = Insert(root, 70);
	root = Insert(root, 4);
	root = Insert(root, 12);
	root = Insert(root, 18);
	root = Insert(root, 24);
	root = Insert(root, 31);
	root = Insert(root, 44);
	root = Insert(root, 66);
	root = Insert(root, 90);
	cout << "The first order : \n";
	PreOrder(root);
	root = Delete(root, 35);
	cout << "\nAfter deletion : \n";
	PreOrder(root);
	if (Search(root, 22)) cout << "\n There is that number";
	else cout << "\nThere is not that number";
	Free(root);
	root == NULL;
}
