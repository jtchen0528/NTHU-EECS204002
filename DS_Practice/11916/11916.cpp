#include<iostream>
#include<vector>

using namespace std;

int maxnum=0;
vector<vector<int> > m;
int path[100][2];
int matrow, matcol;
int movesteps;

void findmax(int row, int col, int steps);
int check(int row, int col);
int checkway(int row, int col);
void resetpath(){
	for(int i=0; i<100; i++){
		path[i][0]=-1;
		path[i][1]=-1;
	}
}

int main(){
	int matnum;
	int row, col;
	int i, j, k;

	cin >> matnum;

	for(i=0; i<matnum; i++){
		cin >> matcol >> matrow;
		cin >> col >> row;
		m = vector<vector<int> >(matrow);
		for(j=0; j<matrow; j++){
			m[j] = vector<int>(matcol);
			for(k=0; k<matcol; k++){
				cin >> m[j][k];
			}
		}
		cin >> movesteps;
		resetpath();
		findmax(row, col, movesteps);
/*		
		cout << movesteps << endl;
		
		for(j=0; j<matrow; j++){
			for(k=0; k<matcol; k++){
				cout << m[j][k] << " ";
			}
			cout << endl;
		}
*/
		cout << maxnum << endl;
		maxnum=0;

	}

	return 0;
}

void findmax(int row, int col, int steps){
	if(steps==0){
//		cout << m[row][col] << endl;
		if(maxnum<m[row][col]){
			maxnum = m[row][col];
		}
	}else{
		path[movesteps-steps][0]=row;
		path[movesteps-steps][1]=col;
		if((row+1<matrow)&&(check(row+1, col))&&(checkway(row+1, col))){
/*			cout << "from " << row << "," << col << " go down "
				<< "to " << row+1 << "," << col <<
				" =>"<< m[row+1][col] << endl;
*/			findmax(row+1, col, steps-1);
		}
		if((row-1>=0)&&(check(row-1, col))&&(checkway(row-1, col))){
/*			cout << "from " << row << "," << col << " go up "
				<< "to " << row-1 << "," << col <<
                " =>"<< m[row-1][col] << endl;
*/			findmax(row-1, col, steps-1);
		}
		if((col+1<matcol)&&(check(row, col+1))&&(checkway(row, col+1))){
/*			cout << "from " << row << "," << col << " go right "
				<< "to " << row << "," << col+1 << 
                " =>"<< m[row][col+1] << endl;
*/			findmax(row, col+1, steps-1);
		}
		if((col-1>=0)&&(check(row, col-1))&&(checkway(row, col-1))){
/*			cout << "from " << row << "," << col << " go left "
				<< "to " << row << "," << col-1 << 
                " =>"<< m[row][col-1] << endl;
*/			findmax(row, col-1, steps-1);
		}
		path[movesteps-steps][0]=-1;
		path[movesteps-steps][1]=-1;
	}
}

int check(int row, int col){
	int i;
	for(i=0; i<movesteps+1; i++){
		if((row==path[i][0])&&(col==path[i][1])){
	//		cout << "checked failed" << endl;
			return 0;
		}
	}
	return 1;
}

int checkway(int row, int col){
	if(m[row][col]==0){
		return 0;
	}else{
		return 1;
	}
}
