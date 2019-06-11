#include <iostream>
#include <string>

using namespace std;

struct Node{
	char letter;
	int freq;
	Node *left;
	Node *right;
	Node *next;
	Node *last;
};

Node *head = NULL;

char list[26][2];
int listorder[26] = {0};
int order=0;

void addletter(char c){

	for(int i=0; i<26; i++){
		if(c==list[i][0]){
			list[i][1]++;
			if(listorder[i]==0){
				order++;
				listorder[i]=order;
			}
		}
	}
}

void printnode(){
	Node *ptr = head, *lastptr = ptr;;
	while(ptr!= NULL){
		cout << ptr->letter << " " << ptr->freq << endl;
		lastptr = ptr;
		ptr =  ptr->next;
	}
	cout << endl;
	Node *ptr2 = lastptr;
	while(ptr2!=NULL){
		cout << ptr2->letter << " " << ptr2->freq << endl;
		ptr2 =  ptr2->last;
	}
}

void huffman(){
	Node *ptr = head, *lastptr, *ptrmin1, *ptrmin2;
	while(ptr != NULL){
		lastptr = ptr;
		ptr = ptr->next;
	}
	int min1, min2;
	min1 = lastptr->freq;
	min2 = lastptr->last->freq;
//	cout << min1 << min2 << " ";
	ptr = head;
	while(ptr->freq != min1){
		ptr = ptr->next;
	}
	ptrmin1 = ptr;
	if(ptr->next != NULL){
		ptr->next->last = ptr->last;
	}else{
		if(ptr->last != NULL){
			ptr->last->next = NULL;
		}else{
			head = NULL;
		}
	}
	if(ptr != head){
		if(ptr->last != NULL){
			ptr->last->next = ptr->next;	
		}
	}else{
		head = ptr->next;
	}
	ptr = head;
	while(ptr->freq != min2){
		ptr = ptr->next;
	}
	ptrmin2 = ptr;
	if(ptr->next != NULL){
		ptr->next->last = ptr->last;
	}else{
		if(ptr->last != NULL){
			ptr->last->next = ptr->last;
		}else{
			head = NULL;
		}
	}
	if(ptr != head){
		if(ptr->last != NULL){
			ptr->last->next = ptr->next;	
		}
	}else{
		head = ptr->next;
	}
	Node *new_node = new Node;
	new_node->letter = '@';
	new_node->freq = min1+min2;
//	cout << ptrmin1->letter << ptrmin1->freq << " ";
//	cout << ptrmin2->letter << ptrmin2->freq << endl;
		new_node->left = ptrmin1;
		new_node->right = ptrmin2;
	ptr = head;
	if(head != NULL){
		int end = 0;
		while(end == 0){
			if(ptr->next == NULL){
				end = 2;
			}else{
				if(ptr->freq >= new_node->freq){
					ptr = ptr->next;
				}else{
					end = 1;
				}
			}
		}
//		cout << ptr->letter << endl;
		if(ptr->next != NULL){
			if(ptr != head){
				new_node->next = ptr;
				new_node->last = ptr->last;
				if(ptr->last != NULL){
					ptr->last->next = new_node;
				}
				ptr->last = new_node;
			}else{
				head = new_node;
				new_node->next = ptr;
				ptr->last = head;
			}
		}else{
			if(ptr->last != NULL){
				ptr->last->next = new_node;
				new_node->last = ptr->last;
				ptr->last = new_node;
				new_node->next = ptr;
			}else{
				head = new_node;
				new_node->last = NULL;
				new_node->next = ptr;
				ptr->last = new_node;
			}
		}
	}else{
		head = new_node;
	}
}

void traversal(Node* p)
{
    if (!p) return;
    cout << p->letter << " " << p->freq << endl;    // 先輸出樹根
    traversal(p->left); // 次輸出左子樹
    traversal(p->right);// 後輸出右子樹
}

bool findID(Node *ptr, char let){
	if(ptr == NULL) return false;
	if(ptr->letter == let){
		return true;
	}
	int rs1 = findID(ptr->left, let);
	int rs2 = findID(ptr->right, let);
	return rs1||rs2;
}

void findlet(char letter){
	Node *ptr = head;
	while(ptr != NULL){
		if(findID(ptr->left, letter)){
			cout << 0;
			ptr = ptr->left;
		}else{
			ptr = ptr->right;
			if(ptr != NULL){
				cout << 1;
			}
		}
	}
}

int main(){
	int linenum;
	string word;
	char c;
	cin >> linenum >> c >> word;
	c = getchar();
//	cout << linenum << "," << word << endl;
	for(int i=0; i<26; i++){
		list[i][0] = i+97;
		list[i][1] = '0';
		listorder[i] = 0;
	}
	string text;
	for(int i=0; i<linenum; i++){
		getline(cin,text);
		for(int j=0; j<text.size(); j++){
			if((text[j]!=' ')&&(text[j]!='\n')&&(text[j]!='\r')){
				addletter(text[j]);
			}
		}
/*
		while(((c=getchar())!='\n')&&(c!='\r')){
			if(c!=' '){
				addletter(c);
			}
		}
*/	}

	char newlist[order];
	int freq[order];
	char max='0';
	int maxnum, maxord;
	for(int i=0; i<order; i++){
		max = '0';
		for(int j=0; j<26; j++){
			if((list[j][1])>=max){
				if((max == list[j][1])&&(maxord < listorder[j])){				
				}else{
					max = list[j][1];
					maxord = listorder[j];
					maxnum = j;
				}
			}
		}
		newlist[i] = list[maxnum][0];
		freq[i] = max-'0';
		list[maxnum][1] = '0';
		listorder[maxnum] = 0;
	}
	
	
	Node *new_node = new Node;
	new_node->letter = newlist[0];
	new_node->freq = freq[0];
	new_node->last = head;
	head = new_node;
	Node *ptr = head;
	head->last = NULL;
	head->right = NULL;
	head->left = NULL;
	for(int i=1; i<order; i++){
		Node *new_node = new Node;
		new_node->letter = newlist[i];
		new_node->freq = freq[i];
		new_node->last = ptr;
		new_node->right = NULL;
		new_node->left = NULL;
		ptr->next = new_node;
		ptr = ptr->next;
	}
	ptr->next = NULL;

	for(int i=0; i<20; i++){
//	while(head->next != NULL){
		huffman();
	}
	
	printnode();
//	traversal(head);
	
	for(int i=0; i<word.length(); i++){
		findlet(word[i]);
	}
	cout << endl;
}

