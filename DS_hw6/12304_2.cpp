#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <queue>

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

typedef struct Node * p_Node;

struct cmp
{
    bool operator () (p_Node const &p1, p_Node const &p2)
    {
        return p1->freq > p2->freq;
    }
};

p_Node createNode(char let, int freq, p_Node left, p_Node right)
{
    p_Node node = (p_Node)malloc(sizeof(struct Node));
    node->freq = freq;
	node->letter = let;
    node->left = left;
    node->right = right;

    return node;
}

p_Node buildTree(char *lett, int * vec, int n)
{
    priority_queue<p_Node, vector<p_Node>, cmp> forest;

    for(int i = 0; i < n; i++)
    {
        p_Node node = createNode(lett[i], vec[i], NULL, NULL);
        forest.push(node);
    }

    while(forest.size() > 1)
    {
        p_Node node1 =  forest.top();
		cout << node1->letter << " ";
        forest.pop();
        p_Node node2 =  forest.top();
		cout << node2->letter << endl;
        forest.pop();
        cout<<node1->freq<<"  "<<node2->freq<<endl;
        p_Node new_node = createNode('@', node1->freq + node2->freq, node1, node2);
        forest.push(new_node);
    }
    return forest.top();
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

	for(int i=0; i<order; i++){
		cout << newlist[i] << " " << freq[i] << endl;
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
/*
	while(head->next != NULL){
		huffman();
	}
*/
	head = buildTree(newlist, freq, order);

	for(int i=0; i<word.length(); i++){
		findlet(word[i]);
	}
	cout << endl;

	traversal(head);

}
