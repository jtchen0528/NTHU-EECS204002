#include<iostream>

using namespace std;

struct Node{
	int data;
	struct Node *next;
};

struct Node* head = NULL;

int main(){
	struct Node* ptr = head;
	struct Node* new_node = new Node;
	new_node->data = 1;
	ptr = new_node;
	head = ptr;
	cout << ptr->data << endl;
	cout << head->data << endl;
}
