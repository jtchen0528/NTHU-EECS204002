#include<stdio.h>
#include<algorithm>

int main(){
	int listA[1000000]={0}, listB[1000000]={0};
	int listAnum, listBnum;
	int i, j, k, diff=0, num, end=0;

	scanf("%d", &listAnum);
	for(i=0; i < listAnum; i++){
		scanf("%d", &listA[i]);
	}
	
	std::sort(listA, listA+listAnum);

	scanf("%d", &listBnum);
	for(i=0; i < listBnum; i++){
		scanf("%d", &listB[i]);
	}
	std::sort(listB, listB+listBnum);
	

	printf("L1\tL2\n");
	printf("%d\t%d\n", listAnum, listBnum);

	for(i=0, k=0; ((i<listAnum)||(k<listBnum)); i++, k++){
		if((listA[i]==listB[k])&&((listA[i]!=0)&&(listB[k]!=0))){
			printf("%d\t%d\n",listA[i], listB[k]);
		}else{
			if(listA[i]==0){
				printf("\t%d\tX\n", listB[k]);
				diff++;
				i--;
			}else if(listB[k]==0){
				printf("%d\t\tX\n", listA[i]);
				diff++;
				k--;
			}else{
			if(listA[i]>listB[k]){
				printf("\t%d\tX\n", listB[k]);
				diff++;
				i--;
			}else{
				printf("%d\t\tX\n", listA[i]);
				diff++;
				k--;
			}
			}
		}
	}
	
	printf("%d differences\n", diff);

	return 0;
}
