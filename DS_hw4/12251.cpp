#include <iostream>
#include <vector>

using namespace std;

struct Node{
	int ID;
	int X;
	int Y;
	char mark;
	struct Node *parent;
	struct Node *first;
	struct Node *second;
};

struct Node* head = NULL;
char check[3][3] = {0};
int move = 0;
int win = 0;

void printnode(struct Node* ptr){
	if(!ptr)return;
	printnode(ptr->first);
	printnode(ptr->second);
//	cout << "ID: " << ptr->ID ;
	cout << ptr->X << " ";
	cout << ptr->Y << " " ;
	cout << ptr->mark << endl;
}

void checkwin(struct Node* ptr){
	int i;
	if(win == 0){
	if(!ptr){
		if((check[0][0]==check[0][1])&&(check[0][1]==check[0][2])&&(check[0][0]!=0)||
		(check[1][0]==check[1][1])&&(check[1][1]==check[1][2])&&(check[1][0]!=0)||
		(check[2][0]==check[2][1])&&(check[2][1]==check[2][2])&&(check[2][0]!=0)||
		(check[0][0]==check[1][0])&&(check[1][0]==check[2][0])&&(check[0][0]!=0)||
		(check[1][0]==check[1][1])&&(check[1][1]==check[2][1])&&(check[1][0]!=0)||
		(check[2][0]==check[2][1])&&(check[2][1]==check[2][2])&&(check[2][0]!=0)||
		(check[0][0]==check[1][1])&&(check[1][1]==check[2][2])&&(check[0][0]!=0)||
		(check[2][0]==check[1][1])&&(check[1][1]==check[0][2])&&(check[2][0]!=0)){
			cout << "Win" << endl;
			for(int j=0; j<3; j++){
				for(i=0; i<2; i++){
					if(check[i][j]==0){
						cout << "_";
					}else{
						cout << check[i][j];
					}
					cout << " ";
				}
				if(check[i][j]==0){
					cout << "_";
				}else{
					cout << check[i][j];
				}
				cout << endl;
			}
		win = 1;
		}
		return;
	}
	check[ptr->X][ptr->Y] = ptr->mark;
	checkwin(ptr->first);
	checkwin(ptr->second);
	check[ptr->X][ptr->Y] = 0;	
	}
}

struct Node* foundptr;

void findID(struct Node* ptr, int id){
	if(ptr == NULL) return;
	if(ptr->ID == id){
		foundptr = ptr;
		return;
	}
	findID(ptr->first, id);
	findID(ptr->second, id);
}

void insert(int new_ID, int new_X, int new_Y, char new_mark, int new_parent){
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->ID = new_ID;
	new_node->X = new_X;
	new_node->Y = new_Y;
	new_node->mark = new_mark;
	struct Node* ptr = head;

	findID(head, new_parent);

	new_node->parent = foundptr;
	
	if(foundptr->first==NULL){
		foundptr->first = new_node;
	}else{
		foundptr->second = new_node;
	}

}

int main(){
	int commandnum;
	int inID, inX, inY, inParent;
	char inTurn, inTurn2;
	int inID2, inX2, inY2, inParent2;
	int i;


	cin >> commandnum;
	cin >> inID >> inParent >> inX >> inY >> inTurn;
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
	new_node->ID = inID;
	new_node->X = inX;
	new_node->Y = inY;
	new_node->mark = inTurn;
	new_node->parent = new_node;
	head = new_node;
//	cout << head->ID << head->X << head->Y << path[0][0] << head->mark<< path[0][1]<< endl;

	for(;commandnum>1; commandnum--){
		cin >> inID >> inParent >> inX >> inY >> inTurn;
//		cout <<" "<< inID <<" "<< inParent <<" "<< inX <<" "<<inY <<" "<< inTurn << endl;
		insert(inID, inX, inY, inTurn, inParent);
	}

//	printnode(head);
	checkwin(head);

	if(win == 0){
		cout << "Tie" << endl;
		printnode(head);
	}

}

