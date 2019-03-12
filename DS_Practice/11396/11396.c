#include<stdio.h>
#define MAX 1000
#define MF 30

int convert(int frow, int fcol);
void fillmat(int row, int col, int valnum, int frow, int fcol);
void zero(int s[MF][MF]);

int matinfo[MAX][3]={0};
int coninfo[MAX][3]={0};
int mat[MF][MF]={0};
int fil[MF][MF]={0};

int main(){
	int matrixnum;
	int matrow, matcol, valnum;
	int convalnum=0, conrow=0;
	int fmatrow, fmatcol, fvalnum;
	int i, j, k, row, col, val=0;

	scanf("%d", &matrixnum);

	for(k=0; k<matrixnum; k++){
		scanf("%d", &matrow);
		scanf("%d", &matcol);
		scanf("%d", &valnum);
	
		for(i=0; i<valnum; i++){
			scanf("%d %d %d", &matinfo[i][0], &matinfo[i][1], &matinfo[i][2]);
		}
/*		for(i=0; i<valnum; i++){
			printf("%d %d %d\n", matinfo[i][0], matinfo[i][1], matinfo[i][2]);
		}
*/	
		scanf("%d", &fmatrow);
		scanf("%d", &fmatcol);
		scanf("%d", &fvalnum);
	
		for(i=0; i<fvalnum; i++){
			scanf("%d %d", &row, &col);
			scanf("%d", &val);
			fil[row-1][col-1]=val;
		}

/*		for(i=0; i<fmatrow; i++){
			for(j=0; j<fmatcol; j++){
				printf("%d ", fil[i][j]);
			}
			printf("\n");
		}
*/	
		for(i=0; i<matrow; i++){
			for(j=0; j<matrow; j++){
				fillmat(i, j, valnum, fmatrow, fmatcol);
//				val=convert(fmatrow, fmatcol);
				if(val!=0){
					convalnum++;
//					coninfo[conrow][0]=i;
//					coninfo[conrow][1]=j;
//					coninfo[conrow][2]=val;
					conrow++;
				}
				zero(mat);
			}
		}
		zero(fil);
	}
	return 0;
}

int convert(int frow, int fcol){
	int val=0, i, j;
	for(i=0; i<frow; i++){
		for(j=0; j<fcol; j--){
			val=val+mat[i][j]*fil[frow-1-i][fcol-1-j];
		}
	}
	return val;
}

void zero(int s[MF][MF]){
	int i, j;
	for(i=0; i<MF; i++){
		for(j=0; j<MF; j++){
			s[i][j]=0;
		}
	}
}

void fillmat(int row, int col, int valnum, int frow, int fcol){
	int i, end=0, r, c;
	int rowup, rowlow, colup, collow;
	rowup=row+(frow-1)/2; colup=col+(fcol-1)/2;
	rowlow=row-(frow-1)/2; collow=col-(fcol-1)/2;
	for(i=0; i<valnum, end==0; i++){
		if((matinfo[i][0]<=rowup)&&(matinfo[i][1]<=colup)){
		///////////////////////////////////////////////////////////////////////////////
			r=matinfo[i][0];
			c=matinfo[i][1];
//			mat[(frow-1)/2+row-r][(fcol-1)/2+col-c]=matinfo[i][2];
		}
	}
}

