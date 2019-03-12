#include<stdio.h>
#include<algorithm>

using namespace std;

void printlot(int lot[1000][6], int lotnum);
void sortlot(int lot[1000][6], int srow, int scol, int erow, int ecol);
void checklot(int lot[1000][6], int srow, int scol, int erow, int ecol);
void print1lot(int lot[6]);
int checkwin(int winlot[1000][6], int lot[6], int winlotnum);

int main(){

	int win[1000][6]={0};
	int lottery[6]={0};
	int winnum, lotterynum;
	char c;
	int i, j, k, tmp[6]={0};
	int check;

	scanf("%c", &c);
	printf("%c", c);
	printf("\n");

	scanf("%d", &winnum);
	printf("%d\n", winnum);
	for(i=0; i<winnum; i++){
		for(j=0; j<6; j++){
			scanf("%d", &win[i][j]);
		}
		std::sort(win[i], win[i]+6);
	}

	

	sortlot(win, 0, 0, winnum, 6);
	checklot(win, 0, 0, winnum, 6);

	printlot(win, winnum);

	scanf("%d", &lotterynum);
	printf("%d\n", lotterynum);
	for(i=0; i<lotterynum; i++){
		for(j=0; j<6; j++){
			scanf("%d", &lottery[j]);
		}
		std::sort(lottery, lottery+6);
		print1lot(lottery);
		check=checkwin(win, lottery, winnum);
		if(check!=0){
			if(lotterynum!=i+1){
				printf("Y %d\n", check);
			}else{
				printf("Y %d", check);
			}
		}else{
			if(lotterynum!=i+1){
				printf("N\n");
			}else{
				printf("N");
			}
		}
	}

	return 0;
}

void printlot(int lot[1000][6], int lotnum){
	int i, j;
	for(i=0; i<lotnum; i++){
		for(j=0; j<5; j++){
			if(lot[i][j]>9){
				printf("%d ", lot[i][j]);
			}else{
				printf("0%d ", lot[i][j]);
			}
		}
		if(lot[i][j]>9){
			printf("%d\n", lot[i][j]);
		}else{
			printf("0%d\n", lot[i][j]);
		}
	}
}

void sortlot(int lot[1000][6], int srow, int scol, int erow, int ecol){
	int i, j, k, temp;
	for(i=srow; i<erow; i++){
		for(j=i; j<erow; j++){
			if(lot[j][scol]<lot[i][scol]){
				for(k=scol; k<ecol; k++){
					temp=lot[j][k];
					lot[j][k]=lot[i][k];
					lot[i][k]=temp;
				}
			}
		}
	}
}

void checklot(int lot[1000][6], int srow, int scol, int erow, int ecol){
	int i, j, repeatnum=0, end=0;
	for(i=srow; i<erow; i++){
		if(lot[i][scol]==lot[i+1][scol]){
			repeatnum++;
			for(j=i+1; j<erow, end==0; j++){
				if(lot[j][scol]==lot[j+1][scol]){
					repeatnum++;
				}else{
					end=1;
				}
			}
			end=0;
			sortlot(lot, i, scol+1, i+repeatnum+1, ecol);
			checklot(lot, i, scol+1, i+repeatnum+1, ecol);
		}
		i=i+repeatnum;
		repeatnum=0;
	}
}

void print1lot(int lot[6]){
	for(int i=0; i<6; i++){
		if(lot[i]>9){
			printf("%d ", lot[i]);
		}else{
			printf("0%d ", lot[i]);
		}
	}
}

int checkwin(int winlot[1000][6], int lot[6], int winlotnum){
	int i, j, fail=0;
	for(i=0; i<winlotnum; i++){
		if(winlot[i][0]==lot[0]){
			for(j=1; j<6; j++){
				if(winlot[i][j]!=lot[j]){
					fail=1;
				}
			}
			if(fail==0){
				return i+1;
			}
			fail=0;
		}
	}
	return 0;
}
