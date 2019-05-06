#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Node{
	int data;
	struct Node *left;
	struct Node *down;
	struct Node *right;
	struct Node *up;
	struct Node *parent;
};

struct Node* head = NULL;

int path[10000][3]={0};
int paths = 0;

void resetpath(){
	paths = 0;
	for(int i=0; i<10000; i++){
		path[i][0] = -1;
		path[i][1] = -1;
		path[i][2] = -1;
	}
}

void printpath(){
	cout << "paths: " << endl;
	cout << "X Y   data" << endl;
	for(int i=0; i<=paths; i++){
		cout << path[i][1] << " " << path[i][0] << "    " << path[i][2] <<endl;
	}
}

void printmat(int mat[100][100], int r, int c){
	for(int i=0; i<r; i++){
		for(int j=0; j<c; j++){
			cout << mat[i][j] << " "; 
		}
		cout << endl;
	}
}

void resetmat(int mat[100][100]){
	for(int i=0; i<100; i++){
		for(int j=0; j<100; j++){
			mat[i][j] = 0;
		}
	}
}

bool checkpath(int X, int Y){
	for(int i=0; i<=paths; i++){
		if((path[i][0]==X)&&(path[i][1]==Y)){
			return false;
		}
	}
	return true;
}

struct Node* lastptr = NULL;
struct Node* last = NULL;

void tree(int mat[100][100], int matrow, int matcol, int X, int Y, int dir){
	struct Node* new_node = new Node;
	new_node->data = mat[X][Y];
	new_node->parent = lastptr;
	if(dir==1){lastptr->left = new_node; last = lastptr; lastptr = lastptr->left;}
	else if(dir==2){lastptr->down = new_node; last = lastptr; lastptr = lastptr->down;}
	else if(dir==3){lastptr->right = new_node; last = lastptr; lastptr = lastptr->right;}
	else if(dir==4){lastptr->up = new_node; last = lastptr; lastptr = lastptr->up;}
	else{head = new_node; last = lastptr; lastptr = head;}
	path[paths][0] = X;
	path[paths][1] = Y;
	path[paths][2] = new_node->data;
//	printpath();
	paths++;
	if(((Y-1)>=0)&&(mat[X][Y-1]!=0)){
		if(checkpath(X, Y-1)){
//			cout << "go left" << endl;
			tree(mat, matrow, matcol, X, Y-1, 1);
		}
	}
	if(((X+1)<100)&&(mat[X+1][Y]!=0)){
		if(checkpath(X+1, Y)){
//			cout << "go down" << endl;
			tree(mat, matrow, matcol, X+1, Y, 2);
		}
	}
	if(((Y+1)<100)&&(mat[X][Y+1]!=0)){
		if(checkpath(X, Y+1)){
//			cout << "go right" << endl;
			tree(mat, matrow, matcol, X, Y+1, 3);
		}
	}
	if(((X-1)>=0)&&(mat[X-1][Y]!=0)){
		if(checkpath(X-1, Y)){
//			cout << "go up" << endl;
			tree(mat, matrow, matcol, X-1, Y, 4);
		}
	}
	lastptr = lastptr->parent;
	paths--;
	path[paths][0] = -1;
	path[paths][0] = -1;
	path[paths][0] = -1;

}

void killtree(struct Node *ptr){
	if(ptr==NULL){
		delete ptr;
		return;
	}
	killtree(ptr->left);
	killtree(ptr->down);
	killtree(ptr->right);
	killtree(ptr->up);
}

void preorder(struct Node *ptr, int f){
	if(!ptr) return;
	if(!f){
		cout << " " << ptr->data;
	}else{
		cout << ptr->data;
	}
	preorder(ptr->left, 0);
	preorder(ptr->down, 0);
	preorder(ptr->right, 0);
	preorder(ptr->up, 0);
}

void postorder(Node *ptr, int f){
	if(!ptr) return;
	postorder(ptr->left, 0);
	postorder(ptr->down, 0);
	postorder(ptr->right, 0);
	postorder(ptr->up, 0);
	if(!f){
		cout << ptr->data << " ";
	}else{
		cout << ptr->data;
	}
}

void levelorder(struct Node* ptr, int f)
{
    queue<Node*> q;
    q.push(ptr);
    struct Node* p;
    while (!q.empty())
    {
    	p = q.front(); q.pop();
		if(!f){
			cout << " " << p->data;
		}else{
			cout << p->data;
		}
        if (p->left)  q.push(p->left);
        if (p->down)  q.push(p->down);
        if (p->right)  q.push(p->right);
        if (p->up) q.push(p->up);
		f=0;
    }
}

int main (){
	int matnum, matrow, matcol, startX, startY;
	int mat[100][100] = {0};
	int i, j;
	string method;
	
	cin >> matnum;

	while(matnum>0){
		cin >> matrow >> matcol;
		cin >> startX >> startY;
		resetmat(mat);
		for(i=0; i<matcol; i++){
			for(j=0; j<matrow; j++){
				cin >> mat[i][j];
			}
		}
		
		resetpath();
		lastptr = NULL;
		head = NULL;

		tree(mat, matrow, matcol, startY, startX, 0);

		cin >> method;
//		printmat(mat, matrow, matcol);
//		cout << method << endl << endl;

		if(method == "Pre-order-traversal"){
			preorder(head, 1);
			cout << endl;
		}else if(method == "Post-order-traversal"){
			postorder(head, 1);	
			cout << endl;
		}else{
			levelorder(head, 1);
			cout << endl;
		}

//		cout << head->down->data;

		killtree(head);
	
		matnum--;
	}

	
}
