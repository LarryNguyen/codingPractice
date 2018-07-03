#include <stdio.h>
#include <string.h>


int visit[52][52];
int map[52][52];
int min = 1000000000;
int N;

void dfs(int pre_X, int pre_Y, int X, int Y, int length);

void dfs(int pre_X, int pre_Y, int X, int Y, int length){
	int nextX,nextY;

	if(X == 1 && Y == 0){
		if (min > length){
			min = length;
		}
		return;
	}

	if(map[X][Y] < 3){
		//type 1,2
		if(Y == pre_Y){
			//type 2
			if(X==pre_X-1){
				nextX = X-1;
			}
			else if (X ==pre_X+1){
				nextX = X+1;
			}
			nextY = Y;
		}else if(X == pre_X){
			//type 1
			if(pre_Y==Y+1){
				nextY = Y-1;
			}
			else if (pre_Y ==Y-1){
				nextY = Y+1;
			}
			nextX = X;
		}
		//if(nextX != -1 && nextY != -1 && nextX <= N && nextY <= N){
		if(nextX != -1){
			if(map[nextX][nextY] != 0 && visit[nextX][nextY] == 0 && (nextX + nextY + length) < min){
				visit[nextX][nextY] = 1;
				dfs(X,Y,nextX,nextY,length+1);
				visit[nextX][nextY] = 0;
			}
		}

	}else if(map[X][Y]>2){
		//type 3,4,5,6
		if(pre_X==X){
			nextX = X + 1;
			nextY = Y;
			if(map[nextX][nextY] != 0 && visit[nextX][nextY] == 0 && (nextX + nextY + length) < min){
				visit[nextX][nextY] = 1;
				dfs(X,Y,nextX,nextY,length+1);
				visit[nextX][nextY] = 0;
			}

			nextX = X - 1;
			nextY = Y;
			if(map[nextX][nextY] != 0 && visit[nextX][nextY] == 0 && (nextX + nextY + length) < min){
				visit[nextX][nextY] = 1;
				dfs(X,Y,nextX,nextY,length+1);
				visit[nextX][nextY] = 0;
			}
		}else if(pre_Y==Y){
			nextY = Y + 1;
			nextX = X;
			if(map[nextX][nextY] != 0 && visit[nextX][nextY] == 0 && (nextX + nextY + length) < min){
				visit[nextX][nextY] = 1;
				dfs(X,Y,nextX,nextY,length+1);
				visit[nextX][nextY] = 0;
			}

			nextY = Y - 1;
			nextX = X;
			if(map[nextX][nextY] != 0 && visit[nextX][nextY] == 0 && (nextX + nextY + length) < min){
				visit[nextX][nextY] = 1;
				dfs(X,Y,nextX,nextY,length+1);
				visit[nextX][nextY] = 0;
			}
		}
	}
}

int main(){
	FILE *fp = fopen("sample_sample_input.txt", "r");
	if(fp == NULL){
		printf("can't open file \n");
		return -1;
	}
	int num_testCase;
	fscanf(fp,"%d",&num_testCase);
	//printf("%d test cases\n", num_testCase);
	//num_testCase =1;
	for(int i = 0; i < num_testCase; i++){
		fscanf(fp,"%d",&N);
		//printf("%d\n", N);

		for (int x = 0; x <= N + 1; x++){
            for (int y = 0; y <= N + 1; y++){
                map[x][y] = 0;
                visit[x][y] = 0;
            }
        }
		map[N][N + 1] = 1;
        map[1][0] = 1;
		for(int x=1; x <= N; x++){
			for(int y=1; y <= N; y++){
				int val;
				fscanf(fp, "%d", &map[x][y]);
				printf("%d ", map[x][y]);
			}
			printf("\n");
		}

		visit[0][1]=1;
		dfs(N,N+1,N,N,1);
		printf("#%d: %d\n", i, min-1);
		min = 100000000;

	}
	
	
	getchar();
	return 0;
}