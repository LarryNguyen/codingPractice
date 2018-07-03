#include <stdio.h>
#include <string>


int Block[20][3];
int dp[1<<20][20][3];
int maxVal = 0;
int N;
char A[] ={"abcde"};
int visit;
char B[100]={""};
//int len;

void printText(){
	int i;
	printf("visit = %d >>> ", visit);
	for(i = 0; i<N; i++){
			if((visit & (1<<i)) != 0)
				printf("%c-", A[i]);
		}
		printf("\n");
}

int max(int x, int y){
	if(x>y) return x;
	else return y;
}
int recurMax(int r0, int r1, int height, int b, int r){
	int i,j;
	int m = 0;
	//if(num == 0){	
		//printf("%s \n", B);
	//	if(max < total){
	//		max = total;
	//	}
	//	return;
	//}
	for(i = 0; i<N; i++){
		if((visit & (1<<i))==0){
			visit |= 1<<i;			
			//B[len-num] = A[i];
			//TODO:
			//check condition of SOS block
			//do sthing here
			for(j = 0; j < 3; j++){
				switch(j){
				case 0://heigh = r0
					if((Block[i][1] <= r0 && Block[i][2] <= r1) || (Block[i][1] <= r1 && Block[i][2] <= r0)){
						m = max(m,recurMax(Block[i][1], Block[i][2], Block[i][0], i, j));
					}
					break;
				case 1://heigh = r1
					if((Block[i][0] <= r0 && Block[i][2] <= r1) || (Block[i][0] <= r1 && Block[i][2] <= r0)){
						m = max(m,recurMax(Block[i][0], Block[i][2], Block[i][1], i, j));
					}
					break;
				case 2://heigh = r2
					if((Block[i][0] <= r0 && Block[i][1] <= r1) || (Block[i][0] <= r1 && Block[i][1] <= r0)){
						m = max(m,recurMax(Block[i][0], Block[i][1], Block[i][2], i, j));
					}
					break;
				}
			}
			
			visit -= 1<<i;
		}
		dp[visit][i][
	}	
}

void findMaxHeight(){
	int i;
	visit = 0;
	for(i = 0; i < N; i++){
		visit |= (1<<i);
		recurMax(Block[i][0], Block[i][1], Block[i][2], 0, 2);
		recurMax(Block[i][0], Block[i][2], Block[i][1], 0, 1);
		recurMax(Block[i][1], Block[i][2], Block[i][0], 0, 0);
		visit -= (1<<i);
	}
}

int main(){
	FILE *fp = fopen("sos_sample_input.txt", "r");
	if(fp == NULL){
		printf("can't open file \n");
		return -1;
	}
	int num_testCase, x, y, i;
	fscanf(fp,"%d",&num_testCase);
	//printf("%d test cases\n", num_testCase);
	//num_testCase =1;
	for(i = 1; i <= num_testCase; i++){
		maxVal = 0;
		fscanf(fp,"%d",&N);
		//printf("%d\n", N);

		for(x=0; x < N; x++){
			for(y=0; y < 3; y++){
				fscanf(fp, "%d", &Block[x][y]);
				//printf("%d ", Block[x][y]);
			}
			//printf("\n");
		}
		visit = 0;
	//	N= 5;
		findMaxHeight();
		printf("#%d: %d\n", i, maxVal);
	}	
	
	getchar();
	return 0;
}