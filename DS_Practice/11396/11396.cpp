#include<iostream>
#include<vector>

using namespace std;

vector<vector<int> > m;
vector<vector<int> > fil;

void printvec(vector<vector<int> > vec){
	int i, j;
	for(i=0; i<vec.size(); i++){
		for(j=0; j<vec[i].size()-1; j++){
			cout << vec[i][j] << " ";
		}
		cout << vec[i][j] << endl;
	}
}

void resetm(){
	int i, j;
	for(i=0; i<m.size(); i++){
		for(j=0; j<m[i].size(); j++){
			m[i][j]=0;
		}
	}
}

int convert(int row, int col){
	int i, j, num=0, sum=0;
	for(i=0; i<row; i++){
		for(j=0; j<col; j++){
			sum=sum+(m[i][j]*fil[row-i-1][col-j-1]);
		}
	}
	return sum;
}

int main(){

	int matnum;
	int matrow, matcol, matval, resval=0;
	int filrow, filcol, filval;
	int i, j, k, l, row, col, val, result;

	vector<vector<int> > mat;

	cin >> matnum;
//	cout << matnum << endl;

	for(i=0; i<matnum; i++){
	//get the original matrix
		cin >> matrow >> matcol >> matval;
	//	cout << matrow<< " " << matcol << " " << matval << endl;
		mat = vector<vector<int> >(matval);
		for(j=0; j<matval; j++){
			mat[j] = vector<int>(3);
			cin >> row >> col >> val;
			mat[j][0] = row;
			mat[j][1] = col;
			mat[j][2] = val;
		}
	//	printvec(mat); cout << endl;
	//get the filter matrix
		cin >> filrow >> filcol >> filval;
	//	cout << filrow<< " " << filcol << " " << filval << endl;
		fil = vector<vector<int> >(filrow);
		m = vector<vector<int> >(filrow);
		for(j=0; j<filrow; j++){
			fil[j] = vector<int>(filcol);
			m[j] = vector<int>(filcol);
			for(k=0; k<filcol; k++){
				fil[j][k]=0;
				m[j][k]=0;
			}
		}
		for(j=0; j<filval; j++){
			cin >> row >> col >> val;
			fil[row][col] = val;
		}
//		printvec(fil); cout << endl;

	//transform m
		int rowc=0;

		vector<vector<int> > res(1);
		res[0] = vector<int>(3);
		res[0][0] = matrow;
		res[0][1] = matcol;
		for(j=0; j<matrow; j++){
			for(k=0; k<matcol; k++){
				for(l=rowc; l<matval; l++){
					if(mat[l][0]==j-filrow/2-1){
						rowc=l;
					}
					if((mat[l][0]<=j+filrow/2)&&(mat[l][0]>=j-filrow/2)){
						if((mat[l][1]<=k+filcol/2)&&(mat[l][1]>=k-filcol/2)){		
							row=filrow/2+mat[l][0]-j;
							col=filcol/2+mat[l][1]-k;
			//				cout << row << " " << col <<endl;
							m[row][col]=mat[l][2];
						}
					}if(mat[l][0]>j+filrow/2){
						break;
					}
				}
				result = convert(filrow, filcol);
				if(result!=0){
					resval++;
//					cout << resval << " " << result << " " << endl;
					res.resize(resval+1);
					res[resval]=vector<int>(3);
					res[resval][0]=j;
					res[resval][1]=k;
					res[resval][2]=result;
				}
			//	printvec(m);
				resetm();
			}
//			cout << endl;
		}
		res[0][2]=resval;
		printvec(res);
		resval=0;
		rowc=0;
	}
	return 0;
}


