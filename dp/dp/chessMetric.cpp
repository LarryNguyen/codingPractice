#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long dp[100][100][55];
int canMove(int start[], int end[]){
	if((abs(start[0]- end[0]) == 1 && start[1] == end[1]) ||		
		(start[0] == end[0] && abs(start[1]- end[1]) == 1) ||
		(abs(start[0] - end[0]) == 1 && abs(start[1]- end[1])==1) ||
		(abs(start[0] - end[0]) == 1 && abs(start[1] - end[1])==2) ||
		(abs(start[0] - end[0]) == 2 && abs(start[1] - end[1])==1)){
			return 1;
	}
	return 0;
		
}

int canMoveL(int start[], int end[]){
	if(	(abs(start[0] - end[0]) == 1 && abs(start[1] - end[1])==2) ||
		(abs(start[0] - end[0]) == 2 && abs(start[1] - end[1])==1)){
			return 1;
	}
	return 0;
		
}

int isPoint(int point[], int size){
	if((point[0] < 0) || (point[1] < 0) || (point[0] >size) || (point[1] > size))
		return 0;
	else
		return 1;
}
#if 0
long long howMany(int size, int start[], int end[], int numMoves){
	long count = 0;
	int next[] = {0,0};
	if(size <= 0)
		return 0;
	if(numMoves <=0)
		return 0;
	if(numMoves == 1){
		if(canMove(start, end) == 1){
			return 1;
		}
	}else{
		for(next[0]=start[0]-1; next[0]<=start[0]+1; next[0]++){
			for(next[1]=start[1]-1; next[1]<=start[1]+1; next[1]++){
				if(next[0] != start[0] || next[1] != start[1]){
					if(isPoint(next, size))
						count += howMany(size, next, end, numMoves-1);
						//printf("Next-1p = [%d,%d]\n", next[0], next[1]);
				}
			}
		}

		for(next[0]=start[0]-2; next[0]<=start[0]+2; next[0]++){
			for(next[1]=start[1]-2; next[1]<=start[1]+2; next[1]++){
				if(next[0] != start[0] || next[1] != start[1]){
					if(isPoint(next, size)){
						if(canMoveL(start,next)){
							count += howMany(size, next, end, numMoves-1);
							//printf("NextL = [%d,%d]\n", next[0], next[1]);
						}
					}
				}
			}
		}
		
	}

	return count;
}
#else
const int dx[16]={1,1,1,0,-1,-1,-1,0, 2,1,-1,-2,-2,-1,1,2}; 
const int dy[16]={1,0,-1,-1,-1,0,1,1, -1,-2,-2,-1,1,2,2,1};

long long howMany(int size, int start[], int end[], int numMoves){
	long long count = 0;
	int next[] = {0,0};
	if(size <= 0)
		return 0;
	if(numMoves <=0)
		return 0;
	if(numMoves == 1){
		if(canMove(start, end) == 1){
			return 1;
		}
	}else{
		int sx = start[0];
		int sy = start[1];
		int ex = end[0];
		int ey = end[1];

		for(int m = 0; m < 55; m++){
			for(int x = 0; x < 100; x++){
				for(int y=0; y < 100; y++){
					dp[x][y][m] = 0;
				}
			}
		}
		dp[sx][sy][0] = 1;
		for(int m = 1; m <= numMoves; m++){
			for(int x = 0; x < size; x++){
				for(int y=0; y < size; y++){
					for(int i = 0; i < 16; i++){
						int nx = x + dx[i];
						int ny = y + dy[i];
						if((nx < 0) || (ny < 0) || (nx >=size) || (ny >= size))
							continue;
						dp[nx][ny][m] += dp[x][y][m-1];
					}
				}
			}
		}
		return dp[ex][ey][numMoves];
	}
	
}
#endif
int main(){
	int n = 100;
	int start[] = {0,0};
	int end[] = {0,99};
	int numMoves = 50;

	long long count = howMany(n, start, end, numMoves);
	printf(">>> %lld \n", count);
	getchar();
}
