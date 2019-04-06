#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;

struct Node{ 
   string stop; 
   struct Node *next; 
}; 

struct Node* head = NULL;   
//struct Node* newhead = NULL;

void insert(string new_stop){ 
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
	new_node->stop = new_stop; 
	new_node->next = head; 
	head = new_node; 
} 
/*
void insertnew(string new_stop){ 
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
	new_node->stop = new_stop; 
	new_node->next = newhead; 
	newhead = new_node; 
} 
*/
void display(){ 
	struct Node* ptr;
	struct Node* nextptr;
	ptr = head;
	nextptr = ptr->next;
	while (ptr != NULL) {
		if(nextptr != NULL){
			cout << ptr->stop << "->"; 
			ptr = ptr->next; 
			nextptr = ptr->next;
		}else{
			cout << ptr->stop;
			ptr = ptr->next;
		}
	} 
	cout << endl;
} 

void addstop(string src, string dst, string newstop, int method){
	struct Node* ptr;
	struct Node* dstptr;
	struct Node* nextstop;
	ptr = head;
	nextstop = ptr->next;
	if(method==2){
		while ((ptr != NULL)&&(method>0)&&(nextstop != NULL)){		
			if(((ptr->stop == src)&&(nextstop->stop == dst))
				||(ptr->stop == dst)&&(nextstop->stop == src)){
				dstptr = ptr->next;
				struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
				new_node->stop = newstop; 
				new_node->next = dstptr; 
				ptr->next = new_node;
				method--;
			}else if(nextstop == NULL){
				method--;
			}
			ptr = ptr->next; 
			nextstop = ptr->next;
		}
	}else{
		while ((ptr != NULL)&&(method>0)){		
			if((ptr->stop == src)&&(nextstop->stop == dst)){
				dstptr = ptr->next;
				struct Node* new_node = (struct Node*) malloc(sizeof(struct Node)); 
				new_node->stop = newstop; 
				new_node->next = dstptr; 
				ptr->next = new_node;
				method--;
			}
			ptr = ptr->next;
			nextstop = ptr->next;
		}
	}	
}

void deletestop(string delstop){
	struct Node* ptr;
	struct Node* previous;
	ptr = head;
	while(ptr != NULL){
		if(ptr->stop != delstop){
			previous = ptr;
			ptr = ptr->next;
		}else{
			previous->next = ptr->next;
			ptr = ptr->next;
		}
	}
}
/*
void reversestop(){
	struct Node* ptr;
	struct Node* tmp;
	ptr = head;
	newhead = NULL;
	while(ptr!=NULL){
		insertnew(ptr->stop);
		ptr = ptr->next;
	}
	head = newhead;
	ptr = newhead;
	while(ptr!=NULL){
		tmp = ptr;
		ptr = ptr->next;
		free(tmp);
	}
	
}
*/
void reverse(){
	struct Node* previous = NULL;
	struct Node* current = head;
	struct Node* nextcurrent = head->next;
	while(nextcurrent!=NULL){
		current->next = previous;
		previous = current;
		current = nextcurrent;
		nextcurrent = nextcurrent->next;
	}
	current->next = previous;
	head = current;
}

int main(){
	int commandnum, i;
	string command;
	string src, dst, newstop;
	int method;
	
	cin >> commandnum;
	insert("NTHU");
	insert("TSMC");
	insert("NTHU");
	for(i=0; i<commandnum; i++){
		cin >> command;
		if(command == "INSERT"){
			cin >> src >> dst >> newstop >> method;
//			cout << command << " " << src << " " << dst << " " << newstop << " " << method << endl;
			addstop(src, dst, newstop, method);
//			display();
		}
		if(command == "DELETE"){
			cin >> src;
//			cout << command  << " " << src << endl;
			deletestop(src);
//			display();
		}
		if(command== "REVERSE"){
//			cout << "reversed";
			reverse();
//			display();
		}
		
	}
	display();

}
