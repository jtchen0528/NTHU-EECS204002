#include<stdio.h>

int check(int s[100][100], int square_col);
void printsquare(int s[100][100], int square_col);

int main(){
	
	int square_amount;
	int square_col;
	int square[100][100] = {0};
	int row, col, i, sum=0, max=0, min=1000000;
	int rowsumtime=0, rowmaxtime=0, rowmintime=0;
	int colsumtime=0, colmaxtime=0, colmintime=0;
	int rowsum[100] = {0};
	int colsum[100] = {0};
	int diag[2] = {0};
	int status=3, testvalue1, testvalue2;
	int rowchmax, rowchmin, colchmax, colchmin;
	int solved=0;

	scanf("%d\n", &square_amount);
//	printf("%d\n", square_amount);

	for(;square_amount>0;){
		scanf("%d\n", &square_col);								//scan square
		for(row = 0; row < square_col; row++){
			for(col = 0; col < square_col; col++){
				scanf("%d", &square[row][col]);
				rowsum[row] = rowsum[row] + square[row][col];	//total row sum
			}
		}
		
		for(col = 0; col < square_col; col++){
			for(row = 0; row < square_col; row++){
				colsum[col] = colsum[col] + square[row][col];	// total col sum
			}
		}
		
		for(row = 0; row < square_col; row++){					// diag sum
			diag[0] = diag[0] + square[row][row];
			diag[1] = diag[1] + square[square_col-row-1][row];
		}

		for(row = 0; row < square_col; row++){
			if(rowsum[row] > max){
				max = rowsum[row];
			}
			if(rowsum[row] < min){
				min = rowsum[row];
			}
		}
		sum = (max + min)/2;

		for(row = 0; row < square_col; row++){
			if(rowsum[row]==max){
				rowmaxtime++;
				rowchmax = row;
			}
			if(rowsum[row]==sum){
				rowsumtime++;
			}
			if(rowsum[row]==min){
				rowmintime++;
				rowchmin = row;
			}
		}
		
		max=0; min=1000000;

		for(col = 0; col < square_col; col++){
			if(colsum[col] > max){
				max = colsum[col];
			}
			if(colsum[col] < min){
				min = colsum[col];
			}
		}
		sum = (max + min)/2;

		for(col = 0; col < square_col; col++){
			if(colsum[col]==max){
				colmaxtime++;
				colchmax = col;
			}
			if(colsum[col]==sum){
				colsumtime++;
			}
			if(colsum[col]==min){
				colmintime++;
				colchmin = col;
			}
		}
		
		if(((rowmaxtime + rowmintime + rowsumtime) == square_col*3) && ((colmaxtime + colmintime + colsumtime) == square_col*3)){
			status = 1;
			
			if(check(square, square_col)==1){
			printf("good %d\n", sum);
			}else{
				printf("bad\n");
			}
		}else if(((rowmaxtime + rowmintime + rowsumtime) == square_col) && ((colmaxtime + colmintime + colsumtime) == square_col)){
			status = square[rowchmax][colchmax];
			square[rowchmax][colchmax] = square[rowchmin][colchmin];
			square[rowchmin][colchmin] = status;
			if(check(square, square_col)==1){
			status = 2;
			printf("fixable %d\n", sum);
			for(row = 0; row < square_col; row++){
				for(col = 0; col < square_col; col++){
					if(!(((row == rowchmax) && (col == colchmax)) || ((row == rowchmin) && (col == colchmin)))){
						printf("%6d", square[row][col]);
						square[row][col] = 0;
					}else{
						if(square[row][col]>999){printf("(%d)", square[row][col]);}
						else if(square[row][col]>99){printf(" (%d)", square[row][col]);}
						else if(square[row][col]>9){printf("  (%d)", square[row][col]);}
						else {printf("   (%d)", square[row][col]);}
					}
				}
				printf("\n");
			}
			}else{
				printf("bad\n");
			}
		}else if(((rowmaxtime + rowmintime + rowsumtime) == square_col) && ((colmaxtime + colmintime + colsumtime) == 3*square_col)){	
			for(col = 0; col < square_col; col++){
				status = square[rowchmax][col];
				square[rowchmax][col] = square[rowchmin][col];
				square[rowchmin][col] = status;
//				printf("check resule = %d\n", check(square, square_col));
					testvalue1 = 0;
					testvalue2 = 0;
				for(i=0; i<square_col; i++){
					testvalue1 = testvalue1 + square[rowchmax][i];
					testvalue2 = testvalue2 + square[rowchmin][i];
				}
//				printsquare(square, square_col);
//				printf("t1=%d, t2=%d\n", testvalue1, testvalue2);
				if(check(square, square_col)==0){
//					printf("bad\n");
				}else{
				if((testvalue1 == sum)&&(testvalue2 == sum)){
//				printsquare(square, square_col);
						printf("fixable %d\n", sum);
						solved = 1;
					for(row = 0; row < square_col; row++){
						for(i = 0; i < square_col; i++){
							if(!(((row == rowchmax) && (i == col)) || ((row == rowchmin) && (i == col)))){
								printf("%6d", square[row][i]);
								square[row][i] = 0;
							}else{
								if(square[row][i]>999){printf("(%d)", square[row][i]);}
								else if(square[row][i]>99){printf(" (%d)", square[row][i]);}
								else if(square[row][i]>9){printf("  (%d)", square[row][i]);}
								else {printf("   (%d)", square[row][i]);}
							}
						}
						printf("\n");
					}
				}
				}
					status = square[rowchmax][col];
					square[rowchmax][col] = square[rowchmin][col];
					square[rowchmin][col] = status;
			}
			status = 2;
			if(solved == 0){
				printf("bad\n");
			}else{solved = 1;}
		}else if(((rowmaxtime + rowmintime + rowsumtime) == 3*square_col) && ((colmaxtime + colmintime + colsumtime) == square_col)){	
			for(row = 0; row < square_col; row++){
				status = square[row][colchmax];
				square[row][colchmax] = square[row][colchmin];
				square[row][colchmin] = status;
					testvalue1 = 0;
					testvalue2 = 0;
//				printf("check resule = %d\n", check(square, square_col));
				for(i=0; i<square_col; i++){
					testvalue1 = testvalue1 + square[i][colchmax];
					testvalue2 = testvalue2 + square[i][colchmin];
				}
				if(check(square, square_col)==0){
//					printf("bad\n");
				}else{
				if((testvalue1 == sum)&&(testvalue2 == sum)){
//				printsquare(square, square_col);
					printf("fixable %d\n", sum);
					solved = 1;
					for(i = 0; i < square_col; i++){
						for(col = 0; col < square_col; col++){
							if(!(((col == colchmax) && (i == row)) || ((col == colchmin) && (i == row)))){
								printf("%6d", square[i][col]);
								square[i][col] = 0;
							}else{
								if(square[i][col]>999){printf("(%d)", square[i][col]);}
								else if(square[i][col]>99){printf(" (%d)", square[i][col]);}
								else if(square[i][col]>9){printf("  (%d)", square[i][col]);}
								else {printf("   (%d)", square[i][col]);}
							}
						}
						printf("\n");
					}
				}
				}
				status = square[row][colchmax];
				square[row][colchmax] = square[row][colchmin];
				square[row][colchmin] = status;
			}
			status = 2;
			if(solved == 0){
				printf("bad\n");
			}else{solved = 1;}
		}else if(((rowmaxtime + rowmintime + rowsumtime) < square_col) || ((colmaxtime + colmintime + colsumtime) < square_col)){
			status = 0;
			printf("bad\n");
		}else{
			if(check(square, square_col)==0){printf("bad\n");}
			status = 3;
		}

		for(row = 0; row < square_col; row++){
			for(col = 0; col < square_col; col++){
				square[row][col] = 0;
			}
		}


//		printf("%d\n", square_col);

		for(row = 0; row < square_col; row++){
//			printf("%d, ", rowsum[row]);
			rowsum[row] = 0;
		}
//		printf("\n");

		for(col = 0; col < square_col; col++){
//			printf("%d, ", colsum[col]);
			colsum[col] = 0;
		}
//		printf("\n");
//		printf("%d, %d\n", diag[0], diag[1]);

/*		printf("sum=%d, max=%d, min=%d\n", sum, max, min); 
		printf("rowsumtime=%d, rowmaxtime=%d, rowmintime=%d\n", rowsumtime, rowmaxtime, rowmintime);
		printf("colsumtime=%d, colmaxtime=%d, colmintime=%d\n", colsumtime, colmaxtime, colmintime);
		printf("rowchmax=%d, rowchmin=%d, colchmax=%d, colchmin=%d\n", rowchmax, rowchmin, colchmax, colchmin);
*/		sum=0, max=0, min=100000, rowsumtime=0, rowmaxtime=0, rowmintime=0, colsumtime=0, colmaxtime=0, colmintime=0;
//		printf("status = %d\n", status);

		square_amount--;
	}
	
	return 0;

}

int check(int s[100][100], int square_col){
	int row, col, test=0, sum=0;
	for(row = 0; row < square_col; row++){
		for(col = 0; col < square_col; col++){
			sum = sum + s[row][col];
		}
		if(test == 0){
			test = sum;
		}else{
			if(sum != test){
				return 0;
			}
		}
		sum = 0;
	}
	for(col = 0; col < square_col; col++){
		for(row = 0; row < square_col; row++){
			sum = sum + s[row][col];
		}
		if(test == 0){
			test = sum;
		}else{
			if(sum != test){
				return 0;
			}
		}
		sum = 0;
	}
	for(row = 0; row < square_col; row++){
		sum = sum + s[row][row];
	}
	if(sum != test){
		return 0;
	}
	sum = 0;
	for(row = 0; row < square_col; row++){
		sum = sum + s[square_col-row-1][row];
	}
	if(sum != test){
		return 0;
	}

	return 1;
}

void printsquare(int s[100][100], int square_col){
	int row, col;
	for(row = 0; row < square_col; row++){
		for(col = 0; col < square_col; col++){
			printf("%d ", s[row][col]);
		}
		printf("\n");
	}
}
















