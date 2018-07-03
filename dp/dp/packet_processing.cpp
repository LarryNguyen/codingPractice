#include <stdio.h>

//int Packet[1000][2]; //0: arrive time ; 1: processing time
int N;
int CPU[5]; // waiting time
int dp[1000][9][9][9][9][9];
int test_case;
int nCPU;
int L[1000];
int T[1000];
#if 0
typedef struct Packet{
	int at;
	int len;
}Packet;
Packet packets[1000];
#endif
#if 0
void updateCPU(int cpu, int t){
	CPU[cpu][1] = CPU[cpu][1] + CPU[cpu][0] - t;
	if(CPU[cpu][1] <= 0){
		CPU[cpu][1] = 0;
		CPU[cpu][0] = t;
	}
}

void sort(Packet *A, int size){
	int i,j, tmp;
	//printf("\n===========\n");
	//for(i = 0; i <= size; i++){
	//		printf("-> (%d,%d)", A[i].at, A[i].len);			
	//	}
	//printf("\n");
	for(i = 0; i <= size;i++){
		for(j = 0; j <= size;j++){
			if(A[i].len > A[j].len){
				tmp = A[i].len;
				A[i].len = A[j].len;
				A[j].len = tmp;
			}
		}
	}
	//for(i = 0; i <= size; i++){
	//		printf("-> (%d,%d)", A[i].at, A[i].len);			
	//	}
	//printf("\n===================\n");
}

int check1(int nCPU){
	int i,j,k, count;
	int choose;
	int max;
	count = 0;
	for(i = 0; i < N; i++){
		
		//printf("%d>>> (%d,%d) \n", i, packets[i].at, packets[i].len);
		if(count == 0){
			for(k = i+1; k < N; k++){
				if(packets[k].at == packets[i].at){
					count++;
					//printf("(%d,%d) > ", packets[k].at, packets[k].len);
				}else
					break;
			}		
			if(count > 0){
				//printf("\nAfter SORT: \n");
				sort(&packets[i], count);
				//for(k = i; k <= i+count; k++){
					//printf("-> (%d,%d)", packets[k].at, packets[k].len);			
				//}
				//printf("\n");
			}
		}
		choose = -1;
		max = -1;
		for(j = 0; j< nCPU; j++){
			updateCPU(j, packets[i].at);
			tr[j] = CPU[j][1] + packets[i].len;
			if(tr[j] <= 10){
				if(tr[j] > max){
					max = tr[j];
					choose = j;
				}
			}
		}
			
		if(choose != -1){
			CPU[choose][0] += CPU[choose][1];
			CPU[choose][1] = packets[i].len;
			//solve[i] = 1;
			//break;
		}else{
			return -1;
		}
		if(count > 0)
			count--;
		
	}
	return 1;

}
#endif

int up(int p, int n){
	return (T[p] >= CPU[n])?0:CPU[n] - T[p];
}

int check2(int from){
	
	
	//if(dp[from] [CPU[0]] [CPU[1]] [CPU[2]] [CPU[3]] [CPU[4]] == test_case*10+nCPU)
	if(dp[from] [up(from,0)] [up(from,1)] [up(from,2)] [up(from,3)] [up(from,4)] == test_case*10+nCPU)
		return -1;

	if(from == N)
		return 1;
	int i,j;
	int prev_w;
	int all_queue_empty = 0;
	for(i=0; i < nCPU; i++){
		if(CPU[i] > T[from]){
			all_queue_empty = 1;
			break;
		}
	}
	//printf("%d>>> (%d,%d) \n", from, packets[from].at, packets[from].len);
	int flag = 0;
	for(j = 0; j< nCPU; j++){
		
		//tr = (packets[from].at >= CPU[j]) ? 0 : CPU[j]-packets[from].at;
		if(CPU[j]-T[from] + L[from] <= 10){
			prev_w = CPU[j];
			//int gap = (packets[from].at-CPU[j] <= 0)?0:packets[from].at-CPU[j];
			CPU[j] = (T[from] > CPU[j]) ? T[from]+ L[from] : CPU[j] + L[from];
			flag = check2(from+1);
			CPU[j] = prev_w;
			if(flag == 1){
				return 1;
			}
			if(flag == -1){
				dp[from] [up(from,0)] [up(from,1)] [up(from,2)] [up(from,3)] [up(from,4)] = test_case*10+nCPU;
				return -1;
			}
		}
		
		
	}
	if(all_queue_empty == 0){
		return -1;
	}	
	dp[from] [up(from,0)] [up(from,1)] [up(from,2)] [up(from,3)] [up(from,4)] = test_case*10+nCPU;

	return 0;
}

int Solver(){

	int i;

	for(nCPU = 1; nCPU <= 5; nCPU++){
		for(i = 0; i < 5; i++){
			CPU[i] = 0;
		}
		if(check2(0) > 0)
			return nCPU;
	}
	return -1;
}

int main(void)
{
	//int test_case;
	int Total;
    int x,y;

	freopen("packet_sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);
	scanf("%d", &Total);
	/*
	여러 개의 테스트 케이스를 처리하기 위한 부분입니다.
	*/
	for (test_case = 1; test_case <= Total; test_case++)
	{

		scanf("%d",&N);
		//printf("%d\n", N);

		for(x=0; x < N; x++){
			
			scanf("%d", &T[x]);
			scanf("%d", &L[x]);
			//printf("%d ", Packet[x][y]);

			//solve[x] = 0;
			//printf("\n");
		}
		//if(test_case==5)
		printf("#%d: %d\n", test_case, Solver());
	}
	getchar();

	return 0; 
}