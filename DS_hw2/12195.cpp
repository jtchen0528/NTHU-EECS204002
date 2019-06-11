#include<iostream>
#include<vector>

using namespace std;

vector<char> word;
vector<vector<char> > mat;
//vector<vector<int> > check;
int check[10000][2]={0};
int wordlen=0;
int matdi;

void getword(int row, int col, int last, int repeat);
void nextword(int row, int col, int last, int repeat);
int checkword(int row, int col);
void rearrange(char last);

int main(){
	int i, j;
	
	cin >> matdi;
//	cout << matdi << endl;
	mat = vector<vector<char> >(matdi);
	for(i=0; i<matdi; i++){
		mat[i] = vector<char>(matdi);
		for(j=0; j<matdi; j++){
			cin >> mat[i][j];
		}
	}

	for(i=0; i<matdi; i++){
		for(j=0; j<matdi; j++){
			getword(i, j, 0, 0);
		//	word.pop_back();
			wordlen=0;
	//		cout << i << " " << j << endl;
		}
	}

	return 0;
}

void getword(int row, int col, int last, int repeat){
	int i;
	if(repeat==0){
		if((mat[row][col]=='a')||(mat[row][col]=='e')||(mat[row][col]=='i')||
		   (mat[row][col]=='o')||(mat[row][col]=='u')){
		}else{
			nextword(row, col, 0, 1);
		}
	}
	if(repeat==1){
		if((mat[row][col]=='a')||(mat[row][col]=='e')||(mat[row][col]=='i')||
		   (mat[row][col]=='o')||(mat[row][col]=='u')){
			nextword(row, col, 1, 2);
		}else{
		}
	}
	if(repeat==2){
		if((mat[row][col]=='a')||(mat[row][col]=='e')||(mat[row][col]=='i')||
		   (mat[row][col]=='o')||(mat[row][col]=='u')){
			nextword(row, col, 1, 2);
		}else{
			nextword(row, col, 0, 3);
		}
	}
	if(repeat==3){
		if((mat[row][col]=='a')||(mat[row][col]=='e')||(mat[row][col]=='i')||
		   (mat[row][col]=='o')||(mat[row][col]=='u')){
			nextword(row, col, 1, 4);
		}else{
		}
	}
	if(repeat==4){
		if((mat[row][col]=='a')||(mat[row][col]=='e')||(mat[row][col]=='i')||
		   (mat[row][col]=='o')||(mat[row][col]=='u')){
			nextword(row, col, 1, 4);
		}else{		
			for(i=0; i<wordlen; i++){
				cout << word[i];
			}
			cout << mat[row][col] << " ";
			rearrange(mat[row][col]);
			nextword(row, col, 0, 5);
		}
	}
	if(repeat==5){
		if((mat[row][col]=='a')||(mat[row][col]=='e')||(mat[row][col]=='i')||
		   (mat[row][col]=='o')||(mat[row][col]=='u')){
			nextword(row, col, 1, 4);
		}else{
		}
		
	}
}

int checkword(int row, int col){
	int i;
	for(i=0; i<wordlen; i++){
		if((check[i][0]==row)&&(check[i][1]==col)){
//			cout << " checked 0 ";
			return 0;
		}
	}
//	cout << " checked 1 ";
	return 1;
}

void nextword(int row, int col, int last, int repeat){
	wordlen++;
	word.push_back(mat[row][col]);
//	check = vector<vector<int> >(wordlen);
//	check[wordlen-1] = vector<int>(2);
	check[wordlen-1][0]=row;
	check[wordlen-1][1]=col;
//	cout << check[wordlen-1][0] << check[wordlen-1][1] << ":" << word[wordlen-1] << " ";
//	cout << " get down ";
	if(row<matdi-1){
		if(checkword(row+1, col))getword(row+1, col, last, repeat);
	}
//	cout << " get right ";
	if(col<matdi-1){
		if(checkword(row, col+1))getword(row, col+1, last, repeat);
	}
	if(row>0){
//	cout << " get up ";
		if(checkword(row-1, col))getword(row-1, col, last, repeat);
	}
	if(col>0){
//	cout << " get left ";
		if(checkword(row, col-1))getword(row, col-1, last, repeat);
	}
	wordlen--;
	word.pop_back();
	check[wordlen][0]=-1;
	check[wordlen][1]=-1;
}


void rearrange(char last){
	int i;
	for(i=0; i<wordlen; i++){
		if((word[i]=='a')||(word[i]=='e')||(word[i]=='i')||
			(word[i]=='o')||(word[i]=='u')){
			cout << word[i];
		}
	}
	for(i=0; i<wordlen; i++){
		if(!((word[i]=='a')||(word[i]=='e')||(word[i]=='i')||
			(word[i]=='o')||(word[i]=='u'))){
			cout << word[i];
		}
	}
	cout << last << endl;
}
