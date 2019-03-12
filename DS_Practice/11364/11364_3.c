#include<stdio.h>
#define MAXDIG 7000
#define MAXFIB 30000

void Fibonacci(int num);
int FindFib(int digits, int last);
int checknum(int s[MAXDIG], int num, int digits);
void swap(int * p, int * q);

int Fib[3][MAXDIG]={0};
int nowdig=1;

int main(){
	int Fibnum, i, j, digits, found, lastfound=1;
	Fib[0][0]=1;
	Fib[1][0]=1;
	scanf("%d", &Fibnum);
	printf("%d\n", Fibnum);




	for(i=0; i<Fibnum; i++){
		scanf("%d", &digits);
		printf("%d ", digits);
		found=FindFib(digits, lastfound);
		for(j=digits-1; j>=0; j--){
			printf("%d", Fib[2][j]);
		}
		lastfound=found-1;
		for(j=0; j<10; j++){
			printf(" %d", checknum(Fib[2], j, digits));
		}
		printf("\n");
	}

}

void Fibonacci(int num){
	int i, j, adder=0;
	for(i=0; i<nowdig; i++){
		Fib[2][i]=Fib[1][i]+Fib[0][i]+adder;
		adder=0;
		if(Fib[2][i]>9){
			Fib[2][i]=Fib[2][i]-10;
			Fib[2][i+1]++;
			adder=1;
		}
	}
	if(Fib[2][i]!=0){
		nowdig++;
	}
	swap(Fib[0], Fib[1]);
	swap(Fib[1], Fib[2]);
	for(j=0; j<nowdig; j++){
		Fib[2][j]=Fib[1][j];
	}
}
	
int checknum(int s[MAXDIG], int num, int digits){
	int i, val=0;
	for(i=0; i<digits; i++){
		if(s[i]==num){
			val++;
		}
	}
	return val;
}

int FindFib(int digits, int last){
	int i, end=0, j, find;
	for(i=last+1; end==0; i++){
		Fibonacci(i);
		if(Fib[2][digits-1]!=0){
			end=1;
		}
	}
	find=i;
	return find;
}

void swap(int a[MAXDIG], int b[MAXDIG]){
	int i, temp;
	for(i=0; i<MAXDIG; i++){
		temp=a[i];
		a[i]=b[i];
		b[i]=temp;
	}
}
