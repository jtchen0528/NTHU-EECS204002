#include <iostream>
#include <string>
#define Max 999999999

using namespace std;

class Huffnode {
    public:
    Huffnode(bool mixv);
    Huffnode();
    ~Huffnode();
    bool mix;
    bool used;
    char ch;
    int freq;
    Huffnode* right;
    Huffnode* left;
};

Huffnode::Huffnode(bool mixv){
    ch = '\0';
    freq = 0;
    mix = mixv;
    right = NULL;
    left = NULL;
    used = false;
};

Huffnode::Huffnode(){
    ch = '\0';
    freq = 0;
    mix = false;
    right = NULL;
    left = NULL;
    used = false;
};

Huffnode::~Huffnode(){
};

void getFre(string* text, int n, Huffnode **textWord);
int indexof(Huffnode** textWord, char target, int length);
void resetB(char* buff, int length);
void sort(Huffnode** textWord);
void full(Huffnode** node);
bool encode(int code[26], int where, Huffnode* tree, char target);
Huffnode* HuffTree(Huffnode** leaf);

int main(){
    string word;
    string* text;
    char buff[10000];
    char dump;
    int n, i, j;
    int path[1000];
    Huffnode** leaf;
    Huffnode* root;

    leaf = new Huffnode*[28];


    for (i = 1; i < 28; i++){
        leaf[i] = NULL;
    }
    

    cin >> n >> word;
    text = new string[n];
    
    cin.getline(buff,10000);
    for (i = 0; i < n; i++){
        resetB(buff,10000);
        cin.getline(buff,10000);
        text[i] = buff;
    }
    
    getFre(text,n,leaf);
    sort(leaf);
    root = HuffTree(leaf);

    
    for (j = 0; j < word.length(); j++ ){
        for (i = 0; i < 1000; i++)
            path[i] = -1;

        encode(path, 0, root, word[j]);

        for (i = 0; path[i] != -1; i++)
            cout << path[i];
    }
    cout << endl;
    

}

void getFre(string* text, int n, Huffnode **textWord){
    int order = 1;
    int index;
    int i, j;
    char lower;

    for (i = 0; i < n; i++){
        for (j = 0; j < text[i].length(); j++){
            if (text[i][j] != ' ' && text[i][j] != '\n' && text[i][j] != '\r'){
        
                if (text[i][j] >= 'A' && text[i][j] <= 'Z')
                    text[i][j] = text[i][j] + 'a' - 'A';
                if((index = indexof(textWord,text[i][j],26)) == -1){
                    textWord[order] = new Huffnode;
                    textWord[order]->ch = text[i][j];
                    textWord[order]->freq++;
                    order++;
                }
                else {
                    textWord[index]->freq++;
                }
            }
        }
    }
}

int indexof(Huffnode** textWord, char target, int length){
    int i;

    for (i = 1; i < length+1; i++){
        if(textWord[i] != NULL && textWord[i]->ch == target){
            return i;
        }
    }
    return -1;
}

void resetB(char* buff, int length){
    int i;
    for (i = 0; i < length; i++)
        buff[i] = '\0';
}

void sort(Huffnode** textWord){
    int i, j;

    for (j = 2; j < 27; j++){
        if (textWord[j] == NULL)
            return;

        textWord[0] = textWord[j];
        
        for (i = j-1; textWord[i]->freq < textWord[0]->freq; i--){
            textWord[i+1] = textWord[i];
            textWord[i+1] = textWord[i];
        }
        textWord[i+1]= textWord[0];
    }
}

Huffnode* HuffTree(Huffnode** leaf){
    Huffnode** internode;
    internode = new Huffnode*[27];
    int leafmin, intermin;
    int leafind, interind;
    int i,j;
    int order = 1;
    Huffnode *templ, *tempr;

    for (i = 0; i < 27; i++)
        internode[i] = NULL;

    while(!((leaf[1] == NULL) && (internode[2] == NULL))){

        leafmin = Max;
        intermin = Max;

        for(i = 1; i < 27; i++){
            if(leaf[i] != NULL && leafmin > leaf[i]->freq){
                leafind = i;
                leafmin = leaf[i]->freq;
            }

            if(internode[i] != NULL && intermin > internode[i]->freq){
                interind = i;
                intermin = internode[i]->freq;
            }
        }

        if(leafmin <= intermin){
            templ = leaf[leafind];
            leaf[leafind] = NULL;
            full(leaf);
        }
        else{
            templ = internode[interind];
            internode[interind] = NULL;
            full(internode);
            order--;
        }

        leafmin = Max;
        intermin = Max;

        for(i = 1; i < 27; i++){
            
            if(leaf[i] != NULL && leafmin > leaf[i]->freq){
                leafind = i;
                leafmin = leaf[i]->freq;
            }

            if(internode[i] != NULL && intermin > internode[i]->freq){
                interind = i;
                intermin = internode[i]->freq;
            }
        }

        if(leafmin <= intermin){
            tempr = leaf[leafind];
            leaf[leafind] = NULL;
            full(leaf);
        }
        else {
            tempr = internode[interind];
            internode[interind] = NULL;
            full(internode);
            order--;
        }

        internode[order] = new Huffnode;
        internode[order]->freq = templ->freq + tempr->freq;
        internode[order]->left = templ;
        internode[order]->right = tempr;
        sort(internode);
        order++;
    }

    return internode[1];

}

void full(Huffnode** node){
    int i;
    int flag = 0;

    for(i = 1; !(node[i] == NULL && node[i+1] == NULL); i++){
        if (node[i] == NULL)
            flag = 1;
        if(flag == 1)
            node[i] = node[i+1];
    }
}

bool encode(int code[26], int where, Huffnode* tree, char target){
    Huffnode *temp = tree;


    if (temp == NULL){
        return false;
    }

    if(temp->ch == target){
        return true;
    }

    if(encode(code, where+1, tree->left, target)){
        code[where] = 0;
        return true;
    }
    if(encode(code, where+1, tree->right, target)){
        code[where] = 1;
        return true;
    }
    return false;
}
