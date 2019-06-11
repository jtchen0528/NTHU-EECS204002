#include <iostream>
#include <string>
#include <vector>

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
	Node *ptr = head, *lastptr, *ptr2;
	while(ptr != NULL){
		lastptr = ptr;
		ptr = ptr->next;
	}
	int minfreq;
	if(lastptr->freq == lastptr->last->freq){
		minfreq = lastptr->freq;
		ptr = head;
		while(ptr->freq != minfreq){
			ptr = ptr->next;
		}
		ptr->last->next = ptr->next->next;
		ptr->next->next->last = ptr->last;
		Node *new_node = new Node;
		new_node->letter = '@';
		new_node->freq = 2*minfreq;
		new_node->left = ptr;
		new_node->right = ptr->next;
		if(ptr != head){
			ptr2 = head;
			while(ptr2->freq >= new_node->freq){
				ptr2 = ptr2->next;
			}
			if(ptr2 != head){
				new_node->last = ptr2->last;
				ptr2->last = new_node;
				ptr2->last->next = ptr2;
				ptr2->last->last->next = new_node;
				new_node->next = ptr2;
			}else{
				new_node->last = ptr2->last;
				ptr2->last = new_node;
				new_node->next = ptr2;
				head = new_node;
			}
		}else{
			head = new_node;
		}
	}else if(lastptr->freq != lastptr->last->freq){
		minfreq = lastptr->last->freq;
		ptr = head;
		while(ptr->freq != minfreq){
			ptr = ptr->next;
		}
		Node *new_node = new Node;
		new_node->letter = '@';
		new_node->freq = lastptr->freq + lastptr->last->freq;
		new_node->left = lastptr;
		new_node->right = ptr;
		if(ptr != head){
			ptr->last->next = ptr->next;
			ptr->next->last = ptr->last;
			lastptr->last->next = NULL;
			ptr2 = head;
			while(ptr2->freq >= new_node->freq){
				ptr2 = ptr2->next;
			}
			if(ptr2 != head){
				new_node->last = ptr2->last;
				ptr2->last = new_node;
				ptr2->last->next = ptr2;
				ptr2->last->last->next = new_node;
				new_node->next = ptr2;
			}else{
				new_node->last = ptr2->last;
				ptr2->last = new_node;
				new_node->next = ptr2;
				head = new_node;
			}
		}else{
			head = new_node;
		}
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
			ptr = ptr->left;
			cout << 0;
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
	for(int i=0; i<linenum; i++){
		while(((c=getchar())!='\n')&&(c!='\r')){
			if(c!=' '){
				addletter(c);
			}
		}
	}

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
	for(int i=1; i<order; i++){
		Node *new_node = new Node;
		new_node->letter = newlist[i];
		new_node->freq = freq[i];
		new_node->last = ptr;
		ptr->next = new_node;
		ptr = ptr->next;
	}


//	printnode();
	while(head->next != NULL){
		huffman();
	}

	for(int i=0; i<word.length(); i++){
		findlet(word[i]);
	}
	cout << endl;

	traversal(head);

}
