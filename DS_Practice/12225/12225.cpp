#include<iostream>
#include<string>

using namespace std;

struct Node{
    string stop;
    struct Node *next;
};

struct Node* head = NULL;

void insert(string new_stop){
    struct Node* new_node = new Node;
    new_node->stop = new_stop;
    new_node->next = head;
    head = new_node;
}

void display(){
	struct Node* ptr = head;
	while(ptr!=NULL){
		cout << ptr->stop << "," << endl;
		ptr = ptr->next;
	}
}

void insert(string src, string dst, string newstop, int method){
	struct Node* ptr = head;
	struct Node* nextptr = ptr->next;
	while(nextptr!=NULL){
		if(method==1){
			if((ptr->stop == src)&&(nextptr->stop == dst)){
				struct Node* new_node = new Node;
				new_node->stop = newstop;
				new_node->next = nextptr;
				ptr->next = new_node;
			}
		}
		if(method==2){
			if((ptr->stop == src)&&(nextptr->stop == dst)){
				struct Node* new_node = new Node;
				new_node->stop = newstop;
				new_node->next = nextptr;
				ptr->next = new_node;
				nextptr = ptr->next;
			}
			if((ptr->stop == dst)&&(nextptr->stop == src)){
				struct Node* new_node = new Node;
				new_node->stop = newstop;
				new_node->next = nextptr;
				ptr->next = new_node;
				nextptr = ptr->next;
			}
		}
		ptr = ptr->next;
		nextptr = nextptr->next;
	}
}

void rename(string newstop, string newname){
	struct Node* ptr = head;
	while(ptr!=NULL){
		if(ptr->stop == newstop){
			ptr->stop = newname;
		}
		ptr = ptr->next;
	}
}

int count(){
	struct Node* ptr = head;
	int i=0;
	while(ptr!=NULL){
		i++;
		ptr = ptr->next;
	}
	return i-1;
}

int check(string cstop){
	struct Node* ptr = head;
	while(ptr != NULL){
		if(ptr->stop == cstop){
			return 1;
		}
		ptr = ptr->next;
	}
	return 0;
}

void search(string src, string dst){
	struct Node* ptr = head;
	struct Node* ptr2 = head;
	int i=0, count=0, test=10000, ok=0;
	if(check(src)&&check(dst)){
		if(src==dst){
			cout << src << " " << dst << " 0" << endl;
		}else{
			while(ptr!=NULL){
				if(ptr->stop == src){
					count=1;
					i=0;
				}
				if((ptr->stop == dst)&&(count == 1)){
					count = 0;
					if(test>i){
						test = i;
					}
	//				cout << i << endl;
				}
				if(count){
	//				cout <<i<<"."<< ptr->stop << " ";
					i++;
				}	
				ptr = ptr->next;
			}
			ptr = head->next;
			while(ptr!=NULL){
				if(ptr->stop == src){
					count=1;
					i=0;
				}
				if((ptr->stop == dst)&&(count == 1)){
					count = 0;
					if(test>i){
						test = i;
					}
				}
				if(count){
	//				cout <<i<<"."<< ptr->stop << " ";
					i++;
				}	
				ptr = ptr->next;
			}
//			cout << endl;
		cout << src << " " << dst << " " << test << endl;
		}
	}else if(!check(src)&&!check(dst)){
		cout << src << " " << dst << " Missing both" << endl;
	}else if(!check(src)&&check(dst)){
		cout << src << " " << dst << " Missing src" << endl;
	}else if(check(src)&&!check(dst)){
		cout << src << " " << dst << " Missing dst" << endl;	
	}
}

void twice(){
	struct Node* ptr = head;
	ptr = ptr->next;
	while(ptr != NULL){
		insert(ptr->stop);
		ptr = ptr->next;
	}

}

int main(){
	int commandnum, method, searchnum;
	string command, src, dst, newstop;
	insert("NTHU");
	insert("TSMC");
	insert("NTHU");
	cin >> commandnum;
	while(commandnum>0){
		cin >> command;
		if(command == "INSERT"){
			cin >> src >> dst >> newstop >> method;
//			cout << src << " " << dst << " " << newstop << " " << method << endl;
			insert(src, dst, newstop, method);
		}else{
			cin >> src >> newstop;
//			cout << src << " " << newstop << endl;
			rename(src, newstop);
		}
		commandnum--;
	}
	cin >> searchnum;
	cout << "Total " << count() <<endl;
	while(searchnum>0){
		cin >> src >> dst;
		search(src, dst);
		searchnum--;
	}

}

