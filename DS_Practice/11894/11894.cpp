#include<iostream>
#include<string>

using namespace std;

struct Node{
	string name;
	string gift;
	struct Node *next;
};

struct Node* head = NULL;

void insert(string new_name, string new_gift){
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	new_node->name = new_name;
	new_node->gift = new_gift;
	new_node->next = head;
	head = new_node;
}

void reverse(){
	struct Node* previous = NULL;
	struct Node* current = head;
	if(current != NULL){
	struct Node* nextone = current->next;
	while(nextone != NULL){
		current->next = previous;
		previous = current;
		current = nextone;
		nextone = nextone->next;
	}
	current->next = previous;
	head = current;
	}
}

void display(){
	struct Node* ptr;
	struct Node* nextptr;
	ptr = head;
	if(ptr==NULL){
		cout << "Empty" << endl;	
	}else{
	nextptr = ptr->next;
	cout << "SantaFinalList" << endl;
	while(ptr != NULL){
		if(nextptr != NULL){
			cout << "(" << ptr->name << ",";
			cout << ptr->gift << ")->";
			ptr = ptr->next;
			nextptr = ptr->next;
		}else{
			cout << "(" << ptr->name << ",";
			cout << ptr->gift << ")" << endl;
			ptr = ptr->next;
		}
	}
	}
}

void append(string new_name, string new_gift){
	int found = 0;
	struct Node* ptr;
	struct Node* previous;
	struct Node* naughty = NULL;
	struct Node* naughtynext = NULL;
	ptr = head;
	while(ptr!=NULL){
		if(ptr->name == new_name){
			ptr->gift = new_gift;
			found == 1;
		}
		if(ptr->gift == "coal"){
			naughty = ptr;
			naughtynext = ptr->next;
		}
		previous = ptr;
		ptr = ptr->next;
	}
	if(!found && (naughty!=NULL)){
		struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
		new_node->name = new_name;
		new_node->gift = new_gift;
		new_node->next = naughtynext;
		naughty->next = new_node;
	}else if(!found){
		struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
		new_node->name = new_name;
		new_node->gift = new_gift;
		new_node->next = head;
		head = new_node;
	}
}

void naughty(string new_name){
	struct Node* ptr;
	struct Node* previous;
	ptr = head;
	while(ptr!=NULL){
		if(ptr->name != new_name){
			previous = ptr;
		}else{
			previous->next = ptr->next;
		}
		ptr = ptr->next;
	}
	insert(new_name, "coal");
}

int main(){
	string command = "test";
	int num;
	string name, gift;

	while(command != "End"){
		cin >> command;
//		cout << command;
		if(command == "End"){
		}else{
			cin >> num;
			while(num>0){
				if(command == "SantaList"){
					cin >> name >> gift;
					insert(name, gift);
				}else if(command == "AppendList"){
					cin >> name >> gift;
					append(name, gift);
				}else{
					cin >> name;
					naughty(name);
				}
				num--;
			}
//			cout << endl;
		}
	}
	reverse();
	display();

	return 0;
}

