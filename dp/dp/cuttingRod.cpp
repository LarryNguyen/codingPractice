#include <stdio.h>
#include <malloc.h>

int max(int a, int b){
	if(a>=b)
		return a;
	else
		return b;
}
int cutRod(int arr[], int size){
	int * mp = (int*) malloc(sizeof(int)*(size+1));
	for(int i = 0; i < size; i++){
		mp[i+1] = arr[i];
	}	

	for(int i = 2; i <= size; i++){
		for(int j = 1; j < i; j++){
			mp[i] = max(mp[i], mp[j]+mp[i-j]);
		}		
	}
	return mp[size];
}
int main(){
	int arr[] = {1, 5, 8, 9, 10, 17, 17, 20};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum Obtainable Value is %d\n", cutRod(arr, size));
    getchar();
    return 0;
}