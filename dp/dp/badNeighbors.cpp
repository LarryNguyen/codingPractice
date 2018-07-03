#include <stdio.h>
#include <string.h>
#include <vector>

using namespace std;

int max(int a, int b){
	return (a>=b)?a:b;
}
int **A;
int findMaxDonations(int donations[], int left, int right){
	if(left == right){
		if(A[left][right] == -1){
			A[left][right] = donations[left];
		}
	}else if(right - left == 1){
		if(A[left][right] == -1){
			A[left][right] = max(donations[left], donations[right]);
		}
	}else if(right - left == 2){
		if(A[left][right] == -1){
			A[left][right] = max(donations[left] + donations[right], donations[left+1]);
		}
	}else{
		if(A[left+2][right] == -1)
			A[left+2][right] = findMaxDonations(donations, left+2, right);
		if(A[left+3][right] == -1)
			A[left+3][right] = findMaxDonations(donations, left+3, right);
		if(A[left][right] == -1)
			A[left][right] = max(donations[left] + A[left+2][right], donations[left+1] + A[left+3][right]);
	}
	return A[left][right];
}

int maxDonations(int donations[], int n){
	
	printf("Size = %d \n", n);
	for(int i = 0; i < n; i++)
		printf("%d ", donations[i]);
	printf("\n");

	A = (int **) malloc (sizeof(int)*n);
	for(int i = 0; i < n; i++){
		A[i] = (int*) malloc(sizeof(int)*n);
		for(int j = 0; j < n; j++){
			A[i][j] = -1;
		}
	}
	if(n == 1)
		return donations[0];
	if(n == 2)
		return max(donations[0], donations[1]);

	int maxVal = max(donations[0] + findMaxDonations(donations, 2, n-2), findMaxDonations(donations, 1, n-1));

	return maxVal;

}

int main(){
	//int donations[] = { 10, 3, 2, 5, 7, 8 };
	//int donations[] = { 7, 7, 7, 7, 7, 7, 7 };
	//int donations[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };
	int donations[] = {445, 298, 806, 321, 703, 71, 514, 289, 881, 992, 675, 644, 470, 469, 430, 353, 461, 907, 392, 394, 244, 544, 185, 350, 958, 192, 930, 453, 726, 844, 819, 197, 797, 323, 889, 835, 142, 650, 538, 87};

	int n = sizeof(donations)/sizeof(int);
	printf(">>>%d \n", maxDonations(donations, n));
	getchar();
	return 0;
}